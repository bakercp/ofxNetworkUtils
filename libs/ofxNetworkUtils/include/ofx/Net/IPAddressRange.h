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


/// \brief Represents a range of IP addresses.
///
/// Address ranges can be defined using CIDR notation and subnets.
///
/// \sa https://en.wikipedia.org/wiki/Classless_Inter-Domain_Routing
class IPAddressRange
{
public:
    /// \brief Typedef for a collection of IPAddressRanges.
    typedef std::vector<IPAddressRange> List;

    /// \brief Create a wildcard (zero) IPv4 IPAddress with /32.
    IPAddressRange();

    /// \brief Create a range using CIDR notation.
    ///
    /// If unable to parse the CIDR notaion, will create a wildcard (zero) IPv4
    /// IPAddress with a mask of /32.
    ///
    /// \param CIDR CIDR style address range.
    /// \sa https://en.wikipedia.org/wiki/Classless_Inter-Domain_Routing
    IPAddressRange(const std::string& CIDR);

    /// \brief Create a range from one ip address.
    /// \param ip The single ip address representing the range.
    IPAddressRange(const Poco::Net::IPAddress& ip);

    /// \brief Create a range from one ip address and a prefix.
    /// \param ip The single ip address representing the range.
    /// \param prefix The prefix used to create the mask.
    IPAddressRange(const Poco::Net::IPAddress& ip, unsigned prefix);

    /// \brief Destroy the IPAddressRange.
    virtual ~IPAddressRange();

    /// \brief Get the address component of the range.
    /// \returns the address component of the rage.
    Poco::Net::IPAddress getAddress() const;

    /// \brief Get the subnet of the range.
    /// \returns the subnet of the rage.
    Poco::Net::IPAddress getSubnet() const;

    /// \brief Get the network mask for the range.
    /// \returns the network mask for the range.
    Poco::Net::IPAddress getMask() const;

    /// \brief Test to see if this IPAddressRange contains another.
    /// \param range The range to test.
    /// \returns true iff the given range is fully contained within this range.
    bool contains(const IPAddressRange& range) const;

    /// \brief Test to see if this IPAddressRange contains an IPAddress.
    /// \param address The address to test.
    /// \returns true iff the given address is contained within this range.
    bool contains(const Poco::Net::IPAddress& address) const;

    /// \brief Get the mask's prefix length.
    ///
    /// Equivalent to getMask().prefixLength();
    ///
    /// \returns the mask's prefix length.
    unsigned getMaskPrefixLength() const;

    /// \brief Get the wildcard mask for this range.
    /// \returns the wildcard mask for this range.
    /// \sa https://en.wikipedia.org/wiki/Wildcard_mask
    Poco::Net::IPAddress getWildcardMask() const;

    /// \returns the smallest IPAddress in this range.
    Poco::Net::IPAddress getHostMax() const;

    /// \returns the largest IPAddress in this range.
    Poco::Net::IPAddress getHostMin() const;

    /// \returns the IPAddress::Family (IPV4 or IPV6) for this range.
    Poco::Net::IPAddress::Family family() const;

    /// \brief Get the CIDR representation of this IPAddressRange.
    /// \returns a the CIDR representation of this IPAddressRange.
    std::string toString() const;

    /// \brief Test two IPAddressRanges for equality.
    /// \param range The range to compare.
    /// \returns true if this IPAddressRange is equal to range.
    bool operator == (const IPAddressRange& range) const;

    /// \brief The maximum prefix length for an IPV4 address.
    static const Poco::Net::IPAddress MAXIMUM_PREFIX_IPV4;

#ifdef POCO_HAVE_IPv6
    /// \brief The maximum prefix length for an IPV6 address.
    static const Poco::Net::IPAddress MAXIMUM_PREFIX_IPV6;
#endif

private:
    /// \brief Get the maximum prefix length for the given IPAddress family.
    /// \param family The IPAddress family.
    /// \returns the maximum prefix length for the given family.
    static unsigned maximumPrefix(Poco::Net::IPAddress::Family family);

    /// \brief Get the maximum prefix IPAddress for the given IPAddress family.
    /// \param family The IPAddress family.
    /// \returns the maximum prefix IPAddress for the given family.
    static const Poco::Net::IPAddress& maximumPrefixIPAddress(Poco::Net::IPAddress::Family family);

    Poco::Net::IPAddress _address; ///< The IP address.
    Poco::Net::IPAddress _mask;    ///< The IP address mask.
    Poco::Net::IPAddress _subnet;  ///< The IP address subnet.

    /// \brief Output the IPAddressRange in CIDR notation.
    /// \param os The output stream.
    /// \param address The IPAddressRange range.
    /// \returns the appended output stream.
    friend std::ostream& operator << (std::ostream& os,
                                      const IPAddressRange& address);

};


inline std::ostream& operator << (std::ostream& os,
                                  const IPAddressRange& address)
{
    os << address.toString();
    return os;
}


} } // namespace ofx::Net
