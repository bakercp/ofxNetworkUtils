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


#include "ofx/Net/CIDRAddress.h"
#include "Poco/NumberParser.h"
#include <iostream>
#include "ofLog.h"


namespace ofx {
namespace Net {


CIDRAddress::CIDRAddress(): _cidr(cidr_from_str("0.0.0.0/32"))
{
}


CIDRAddress::CIDRAddress(CIDR* cidr): _cidr(cidr)
{
    if (!_cidr)
    {
        ofLogError("CIDRAddress::CIDRAddress") << "Invalid pointer.";
        _cidr = cidr_from_str("0.0.0.0/32");
    }
}


CIDRAddress::CIDRAddress(const CIDRAddress& addr): _cidr(cidr_dup(addr._cidr))
{
    if (!_cidr)
    {
        ofLogError("CIDRAddress::CIDRAddress") << "Invalid address: " << addr.toString();
        _cidr = cidr_from_str("0.0.0.0/32");
    }
}


CIDRAddress::CIDRAddress(const std::string& addr)
{
    _cidr = cidr_from_str(addr.c_str());

    if (!_cidr)
    {
        ofLogError("CIDRAddress::CIDRAddress") << "Invalid address: " << addr;
        _cidr = cidr_from_str("0.0.0.0/32");
    }
}


CIDRAddress::CIDRAddress(const Poco::Net::IPAddress& addr)
{
    if (Poco::Net::IPAddress::IPv4 == addr.family())
    {
        _cidr = cidr_from_inaddr(reinterpret_cast<const in_addr*>(addr.addr()));
    }
    else if (Poco::Net::IPAddress::IPv6 == addr.family())
    {
        _cidr = cidr_from_in6addr(reinterpret_cast<const in6_addr*>(addr.addr()));
    }
    else
    {
        _cidr = cidr_from_str("0.0.0.0/32");
    }

    if (!_cidr)
    {
        ofLogError("CIDRAddress::CIDRAddress") << "Invalid address: " << addr.toString();
        _cidr = cidr_from_str("0.0.0.0/32");
    }
}


CIDRAddress& CIDRAddress::operator = (const CIDRAddress& addr)
{
    _cidr = cidr_dup(addr._cidr);
}


CIDRAddress::~CIDRAddress()
{
    if (_cidr) cidr_free(_cidr);
}


bool CIDRAddress::contains(const CIDRAddress& address) const
{

    if (getMaximumAddresses() > address.getMaximumAddresses())
    {
        cout << "max addressed=" << getMaximumAddresses() << " max of other=" << address.getMaximumAddresses() << endl;
        return 0 == cidr_contains(_cidr, address._cidr);
    }
    else if (*this == address)
    {
        return true;
    }
    else
    {
        return false;
    }
}


CIDRAddress CIDRAddress::getBroadcastAddress() const
{
    return CIDRAddress(cidr_addr_broadcast(_cidr));
}


CIDRAddress CIDRAddress::getHostMax() const
{
    return CIDRAddress(cidr_addr_hostmax(_cidr));
}


CIDRAddress CIDRAddress::getHostMin() const
{
    return CIDRAddress(cidr_addr_hostmin(_cidr));
}


CIDRAddress CIDRAddress::getNetworkAddress() const
{
    return CIDRAddress(cidr_addr_network(_cidr));
}


Poco::Net::IPAddress::Family CIDRAddress::family() const
{
    int family = cidr_get_proto(_cidr);

    switch (family)
    {
        case CIDR_IPV4:
            return Poco::Net::IPAddress::IPv4;
        case CIDR_IPV6:
            return Poco::Net::IPAddress::IPv6;
        default:
            ofLogFatalError("CIDRAddress::family") << "Unknown address family.";
            return Poco::Net::IPAddress::IPv4;
    }
}


CIDRAddress::List CIDRAddress::getSubnets() const
{
    CIDR** pSubnets = cidr_net_subnets(_cidr);

    List subnets;

    subnets.push_back(CIDRAddress(pSubnets[0]));
    subnets.push_back(CIDRAddress(pSubnets[1]));

    cidr_free(pSubnets[0]);
    cidr_free(pSubnets[1]);

    free(pSubnets);

    return subnets;
}


CIDRAddress CIDRAddress::getSupernet() const
{
    return CIDRAddress(cidr_net_supernet(_cidr));
}


std::size_t CIDRAddress::getMaximumAddresses() const
{
    const char* str = cidr_numaddr(_cidr);

    if (str)
    {
        try
        {
            return Poco::NumberParser::parse(std::string(str));
        }
        catch (const Poco::SyntaxException& exc)
        {
            ofLogFatalError("CIDRAddress::getNumAddresses") << exc.displayText();
            return 0;
        }
    }
    else
    {
        ofLogFatalError("CIDRAddress::getNumAddresses") << "Error.  Should not be here.";
        return 0;
    }
}


std::size_t CIDRAddress::getMaximumSubnets() const
{
    const char* str = cidr_numhost(_cidr);

    if (str)
    {
        try
        {
            return Poco::NumberParser::parse(std::string(str));
        }
        catch (const Poco::SyntaxException& exc)
        {
            ofLogFatalError("CIDRAddress::getNumHosts") << exc.displayText();
            return 0;
        }
    }
    else
    {
        ofLogFatalError("CIDRAddress::getNumHosts") << "Error.  Should not be here.";
        return 0;
    }
}


std::string CIDRAddress::toString() const
{
    if (_cidr)
    {
        char* pStr = cidr_to_str(_cidr, 0);
        std::string str = pStr ? pStr : "";
        free(pStr);
        return str;
    }
    else
    {
        ofLogFatalError("CIDRAddress::toString") << "CIDR Pointer is not allocated.";
        return "";
    }
}


bool CIDRAddress::operator == (const CIDRAddress& addr) const
{
    return cidr_equals(_cidr, addr._cidr);
}


} } // namespace ofx::Net
