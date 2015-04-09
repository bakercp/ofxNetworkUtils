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


extern "C" {
    #include <libcidr.h>
}


#include <vector>
#include "Poco/Net/IPAddress.h"


namespace ofx {
namespace Net {


class CIDRAddress
{
public:
    typedef std::vector<CIDRAddress> List;

    /// \brief Creates a wildcard (zero) IPv4 IPAddress with /32.
    CIDRAddress();
    CIDRAddress(const CIDRAddress& addr);
    CIDRAddress(const std::string& addr);
    CIDRAddress(const Poco::Net::IPAddress& addr);

	CIDRAddress& operator = (const CIDRAddress& addr);

    virtual ~CIDRAddress();


    bool contains(const CIDRAddress& address) const;

    CIDRAddress getBroadcastAddress() const;
    CIDRAddress getHostMax() const;
    CIDRAddress getHostMin() const;
    CIDRAddress getNetworkAddress() const;

    Poco::Net::IPAddress::Family family() const;

    List getSubnets() const;

    CIDRAddress getSupernet() const;

    /// \brief Determine the total number of addresses in a netblock
    /// (including the network and broadcast addresses).
    std::size_t getMaximumAddresses() const;

    /// \brief Determine the total number of host addresses in a netblock
    /// (excluding the network and broadcast addresses).
    std::size_t getMaximumSubnets() const;

    std::string toString() const;

    bool operator == (const CIDRAddress& addr) const;

private:
    /// \brief Create a CIDRAddress.
    ///
    /// The CIDRAddress takes ownership of the pointer.
    CIDRAddress(CIDR* addr);

    CIDR* _cidr;

};


} } // namespace ofx::Net
