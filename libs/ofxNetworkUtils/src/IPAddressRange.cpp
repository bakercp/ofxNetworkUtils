//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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
    _subnet(bitwiseOp(_address, _mask, BitwiseOp::AND))
{
}


IPAddressRange::IPAddressRange(const std::string& CIDR)
{
    std::size_t position = CIDR.find("/");

    if (!Poco::Net::IPAddress::tryParse(CIDR.substr(0, position), _address))
    {
        ofLogError("IPAddressRange::IPAddressRange") << "Unable to parse address: " << CIDR;
        _address = Poco::Net::IPAddress();
    }

    unsigned prefix = maximumPrefix(_address.family());

    if (position != std::string::npos)
    {
        std::string prefixString = CIDR.substr(position + 1);

        if (!Poco::NumberParser::tryParseUnsigned(prefixString,
                                                  prefix) || prefix > maximumPrefix(_address.family()))
        {
            prefix = maximumPrefix(_address.family());
            ofLogError("IPAddressRange::IPAddressRange") << "Invalid prefix CIDR prefix: " << prefixString << ", using " << prefix;
        }
    }

    _mask = Poco::Net::IPAddress(prefix, _address.family());
    _subnet = bitwiseOp(_address, _mask, BitwiseOp::AND);

}


IPAddressRange::IPAddressRange(const Poco::Net::IPAddress& address):
    _address(address),
    _mask(maximumPrefixIPAddress(_address.family())),
    _subnet(bitwiseOp(_address, _mask, BitwiseOp::AND))
{
}


IPAddressRange::IPAddressRange(const Poco::Net::IPAddress& address,
                               unsigned prefix):
    _address(address),
    _mask(prefix, _address.family()),
    _subnet(bitwiseOp(_address, _mask, BitwiseOp::AND))
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


Poco::Net::IPAddress IPAddressRange::address() const
{
    return _address;
}


Poco::Net::IPAddress IPAddressRange::subnet() const
{
    return _subnet;
}


Poco::Net::IPAddress IPAddressRange::mask() const
{
    return _mask;
}


bool IPAddressRange::contains(const IPAddressRange& range) const
{
    // TODO: this could be more efficient.
    return maskPrefixLength() <= range.maskPrefixLength()
        && contains(range.hostMin())
        && contains(range.hostMax());
}


bool IPAddressRange::contains(const Poco::Net::IPAddress& address) const
{
    if (address.family() != _address.family())
    {
        return false;
    }
    else
    {
        return _subnet == bitwiseOp(address, _mask, BitwiseOp::AND);
    }
}


unsigned IPAddressRange::getMaskPrefixLength() const
{
    return maskPrefixLength();
}


Poco::Net::IPAddress IPAddressRange::getWildcardMask() const
{
    return wildcardMask();
}


Poco::Net::IPAddress IPAddressRange::getHostMax() const
{
    return hostMax();
}


Poco::Net::IPAddress IPAddressRange::getHostMin() const
{
    return hostMin();
}


unsigned IPAddressRange::maskPrefixLength() const
{
    return _mask.prefixLength();
}


Poco::Net::IPAddress IPAddressRange::wildcardMask() const
{
    return bitwiseOp(maximumPrefixIPAddress(_subnet.family()), _mask, BitwiseOp::XOR);
}


Poco::Net::IPAddress IPAddressRange::hostMax() const
{
    return bitwiseOp(_address, wildcardMask(), BitwiseOp::OR);
}


Poco::Net::IPAddress IPAddressRange::hostMin() const
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


bool IPAddressRange::operator != (const IPAddressRange& range) const
{
    return !(*this == range);
}


bool IPAddressRange::operator < (const IPAddressRange& range) const
{
    return _address < range._address &&
           _subnet < range._subnet &&
           _mask < range._mask;
}


bool IPAddressRange::operator <= (const IPAddressRange& range) const
{
    return !(range < *this);
}


bool IPAddressRange::operator > (const IPAddressRange& range) const
{
    return range < *this;
}


bool IPAddressRange::operator >= (const IPAddressRange& range) const
{
    return !(*this < range);
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
    
    ofLogWarning("IPAddressRange::maximumPrefix") << "Unknon IPAdress family.";
    return 32;
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

    ofLogWarning("IPAddressRange::maximumPrefixIPAddress") << "Unknown IPAddress family.";
    return MAXIMUM_PREFIX_IPV4;
}



Poco::Net::IPAddress IPAddressRange::bitwiseOp(const Poco::Net::IPAddress& address,
                                               const Poco::Net::IPAddress& mask,
                                               BitwiseOp op)
{
    try
    {
        if (address.family() == Poco::Net::IPAddress::Family::IPv6 &&
            mask.family() == Poco::Net::IPAddress::Family::IPv6)
        {
            if (address.scope() != mask.scope())
                throw Poco::InvalidArgumentException("Scope ID of passed IPv6 address does not match with the source one.");

            const Poco::Net::Impl::IPv6AddressImpl t(address.addr(), address.scope());
            const Poco::Net::Impl::IPv6AddressImpl o(mask.addr(), mask.scope());
            Poco::Net::Impl::IPv6AddressImpl result;

            switch (op)
            {
                case BitwiseOp::AND:
                    result = t & o;
                    break;
                case BitwiseOp::OR:
                    result = t | o;
                    break;
                case BitwiseOp::XOR:
                    result = t ^ o;
                    break;
            }

            return Poco::Net::IPAddress(result.addr(), result.length(), result.scope());

        }
        else
        {
            // This will throw an exception if in compatible mask / address.
            switch (op)
            {
                case BitwiseOp::AND:
                    return address & mask;
                case BitwiseOp::OR:
                    return address | mask;
                case BitwiseOp::XOR:
                    return address ^ mask;
            }
        }
    }
    catch (const Poco::InvalidArgumentException& exc)
    {
        ofLogError("IPAddressRange::makeSubnet") << exc.displayText();
        return Poco::Net::IPAddress();
    }
}


} } // namespace ofx::Net
