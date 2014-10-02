// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofx/Net/IPAddressRange.h"
#include "Poco/Net/NetException.h"
#include "Poco/NumberParser.h"
#include <iostream>
#include "ofLog.h"


namespace ofx {
namespace Net {


const Poco::Net::IPAddress IPAddressRange::MAXIMUM_PREFIX_IPV4(32, Poco::Net::IPAddress::IPv4);
#ifdef POCO_HAVE_IPv6
const Poco::Net::IPAddress IPAddressRange::MAXIMUM_PREFIX_IPV6(128, Poco::Net::IPAddress::IPv6);
#endif


IPAddressRange::IPAddressRange():
    _address(Poco::Net::IPAddress::IPv4),
    _mask(maximumPrefixIPAddress(Poco::Net::IPAddress::IPv4)),
    _subnet(_address & _mask)
{
}


IPAddressRange::IPAddressRange(const std::string& addr)
{
    std::size_t position = addr.find("/");

    if (!Poco::Net::IPAddress::tryParse(addr.substr(0, position), _address))
    {
        ofLogWarning("CIDRAddress::CIDRAddress") << "Unable to parse address: " << addr;
        _address = Poco::Net::IPAddress();
    }

    unsigned prefix = maximumPrefix(_address.family());

    if (position != std::string::npos)
    {
        std::string prefixString = addr.substr(position + 1);

        if (!Poco::NumberParser::tryParseUnsigned(prefixString, prefix) || prefix > maximumPrefix(_address.family()))
        {
            ofLogWarning("CIDRAddress::CIDRAddress") << "Invalid prefix CIDR prefix: " << prefixString;
            prefix = maximumPrefix(_address.family());
        }
    }

    _mask = Poco::Net::IPAddress(prefix, _address.family());

    _subnet = _address & _mask;
}


IPAddressRange::IPAddressRange(const Poco::Net::IPAddress& address):
    _address(address),
    _mask(maximumPrefixIPAddress(_address.family())),
    _subnet(_address & _mask)
{
}


IPAddressRange::IPAddressRange(const Poco::Net::IPAddress& address,
                               unsigned prefix):
    _address(address),
    _mask(prefix, _address.family()),
    _subnet(_address & _mask)
{
}


IPAddressRange::~IPAddressRange()
{
}


Poco::Net::IPAddress IPAddressRange::getAddress() const
{
    return _address;
}


Poco::Net::IPAddress IPAddressRange::getSubnet() const
{
    return _subnet;
}


Poco::Net::IPAddress IPAddressRange::getMask() const
{
    return _mask;
}


unsigned IPAddressRange::getMaskPrefixLength() const
{
    return _mask.prefixLength();
}


Poco::Net::IPAddress IPAddressRange::getWildcardMask() const
{
    return maximumPrefixIPAddress(_subnet.family()) ^ _mask;
}



bool IPAddressRange::contains(const IPAddressRange& range) const
{
    // TODO: this could be more efficient.
    return getMaskPrefixLength() <= range.getMaskPrefixLength()
        && contains(range.getHostMin())
        && contains(range.getHostMax());
}


bool IPAddressRange::contains(const Poco::Net::IPAddress& address) const
{
    if (address.family() != _address.family())
    {
        return false;
    }
    else
    {
        return _subnet == (address & _mask);
    }
}


Poco::Net::IPAddress IPAddressRange::getHostMax() const
{
    return _address | (maximumPrefixIPAddress(_subnet.family()) ^ _mask);
}


Poco::Net::IPAddress IPAddressRange::getHostMin() const
{
    return _subnet;
}


Poco::Net::IPAddress::Family IPAddressRange::family() const
{
    return _address.family();
}


std::string IPAddressRange::toString() const
{
    std::stringstream ss;

    ss << _address.toString();
    ss << "/";
    ss << _mask.prefixLength();

    return ss.str();
}


bool IPAddressRange::operator == (const IPAddressRange& range) const
{
    return _address == range._address &&
           _subnet == range._subnet &&
           _mask == range._mask;
}


unsigned IPAddressRange::maximumPrefix(Poco::Net::IPAddress::Family family)
{
    switch (family)
    {
        case Poco::Net::IPAddress::IPv4:
            return 32;
#ifdef POCO_HAVE_IPv6
        case Poco::Net::IPAddress::IPv6:
            return 128;
#endif
        default:
            return 32;
    }
}


const Poco::Net::IPAddress& IPAddressRange::maximumPrefixIPAddress(Poco::Net::IPAddress::Family family)
{
    switch (family)
    {
        case Poco::Net::IPAddress::IPv4:
            return MAXIMUM_PREFIX_IPV4;
#ifdef POCO_HAVE_IPv6
        case Poco::Net::IPAddress::IPv6:
            return MAXIMUM_PREFIX_IPV6;
#endif
        default:
            return MAXIMUM_PREFIX_IPV4;
    }
}



} } // namespace ofx::Net
