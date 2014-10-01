// =============================================================================
//
// Copyright (c) 2014 Christopher Baker <http://christopherbaker.net>
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


#pragma once


#include <vector>
#include "Poco/Net/IPAddress.h"


namespace ofx {
namespace Net {


class IPAddressRange
{
public:
    typedef std::vector<IPAddressRange> List;

    /// \brief Creates a wildcard (zero) IPv4 IPAddress with /32.
    IPAddressRange();
    IPAddressRange(const std::string& range);
    IPAddressRange(const Poco::Net::IPAddress& ip);
    IPAddressRange(const Poco::Net::IPAddress& ip, unsigned prefix);

    virtual ~IPAddressRange();

    Poco::Net::IPAddress getAddress() const;
    Poco::Net::IPAddress getSubnet() const;
    Poco::Net::IPAddress getMask() const;

//  bool contains(const IPAddressRange& range) const;
    bool contains(const Poco::Net::IPAddress& address) const;

    unsigned getMaskPrefixLength() const;
    Poco::Net::IPAddress getWildcardMask() const;

    Poco::Net::IPAddress getHostMax() const;
    Poco::Net::IPAddress getHostMin() const;

    Poco::Net::IPAddress::Family family() const;

    std::string toString() const;

    bool operator == (const IPAddressRange& range) const;

    static const Poco::Net::IPAddress MAXIMUM_PREFIX_IPV4;
#ifdef POCO_HAVE_IPv6
    static const Poco::Net::IPAddress MAXIMUM_PREFIX_IPV6;
#endif

private:
    static unsigned maximumPrefix(Poco::Net::IPAddress::Family family);
    
    static const Poco::Net::IPAddress& maximumPrefixIPAddress(Poco::Net::IPAddress::Family family);

    Poco::Net::IPAddress _address;
    Poco::Net::IPAddress _mask;
    Poco::Net::IPAddress _subnet;

};


} } // namespace ofx::Net
