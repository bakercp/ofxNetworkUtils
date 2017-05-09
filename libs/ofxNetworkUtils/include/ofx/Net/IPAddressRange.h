//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <vector>
#include "Poco/Net/IPAddress.h"
#include "ofConstants.h"


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
    /// If no mask can be found a mask of /32 will be used for IPv4 addresses
    /// and a mask of /128 will be used for IPv6 addresses.
    ///
    /// \param CIDR CIDR style address range.
    /// \sa https://en.wikipedia.org/wiki/Classless_Inter-Domain_Routing
    IPAddressRange(const std::string& CIDR);

    /// \brief Create a range from one ip address.
    /// \param ip The single ip address representing the range.
    IPAddressRange(const Poco::Net::IPAddress& address);

    /// \brief Create a range from one ip address and a prefix.
    ///
    /// If an invalid prefix is given a mask of /32 will be used for IPv4
    /// addresses and a mask of /128 will be used for IPv6 addresses.
    ///
    /// \param ip The single ip address representing the range.
    /// \param prefix The prefix used to create the mask.
    IPAddressRange(const Poco::Net::IPAddress& address, unsigned prefix);

    /// \brief Destroy the IPAddressRange.
    virtual ~IPAddressRange();

    OF_DEPRECATED_MSG("Use address() instead.", Poco::Net::IPAddress getAddress() const);
    OF_DEPRECATED_MSG("Use subnet() instead.", Poco::Net::IPAddress getSubnet() const);
    OF_DEPRECATED_MSG("Use mask() instead.", Poco::Net::IPAddress getMask() const);

    /// \brief Get the address component of the range.
    /// \returns the address component of the rage.
    Poco::Net::IPAddress address() const;

    /// \brief Get the subnet of the range.
    /// \returns the subnet of the rage.
    Poco::Net::IPAddress subnet() const;

    /// \brief Get the network mask for the range.
    /// \returns the network mask for the range.
    Poco::Net::IPAddress mask() const;

    /// \brief Test to see if this IPAddressRange contains another.
    /// \param range The range to test.
    /// \returns true iff the given range is fully contained within this range.
    bool contains(const IPAddressRange& range) const;

    /// \brief Test to see if this IPAddressRange contains an IPAddress.
    /// \param address The address to test.
    /// \returns true iff the given address is contained within this range.
    bool contains(const Poco::Net::IPAddress& address) const;

    OF_DEPRECATED_MSG("Use maskPrefixLength() instead.", unsigned getMaskPrefixLength() const);
    OF_DEPRECATED_MSG("Use wildcardMask() instead.", Poco::Net::IPAddress getWildcardMask() const);
    OF_DEPRECATED_MSG("Use hostMax() instead.", Poco::Net::IPAddress getHostMax() const);
    OF_DEPRECATED_MSG("Use hostMin() instead.", Poco::Net::IPAddress getHostMin() const);

    /// \brief Get the mask's prefix length.
    ///
    /// Equivalent to mask().prefixLength();
    ///
    /// \returns the mask's prefix length.
    unsigned maskPrefixLength() const;

    /// \brief Get the wildcard mask for this range.
    /// \returns the wildcard mask for this range.
    /// \sa https://en.wikipedia.org/wiki/Wildcard_mask
    Poco::Net::IPAddress wildcardMask() const;

    /// \returns the smallest IPAddress in this range.
    Poco::Net::IPAddress hostMax() const;

    /// \returns the largest IPAddress in this range.
    Poco::Net::IPAddress hostMin() const;

    /// \returns the IPAddress::Family (IPV4 or IPV6) for this range.
    Poco::Net::IPAddress::Family family() const;

    /// \returns a the CIDR representation of this IPAddressRange.
    std::string toString() const;

    bool operator == (const IPAddressRange& range) const;
    bool operator != (const IPAddressRange& range) const;
    bool operator <  (const IPAddressRange& range) const;
    bool operator <= (const IPAddressRange& range) const;
    bool operator >  (const IPAddressRange& range) const;
    bool operator >= (const IPAddressRange& range) const;

    /// \brief The maximum prefix length for an IPV4 address.
    static const Poco::Net::IPAddress MAXIMUM_PREFIX_IPV4;

#ifdef POCO_HAVE_IPv6
    /// \brief The maximum prefix length for an IPV6 address.
    static const Poco::Net::IPAddress MAXIMUM_PREFIX_IPV6;
#endif

private:
    /// \brief Poco bitwise operators are broken for IPv6.
    /// \sa https://github.com/pocoproject/poco/issues/1552
    enum class BitwiseOp
    {
        AND,
        OR,
        XOR
    };

    /// \brief Poco bitwise operators are broken for IPv6.
    /// \sa https://github.com/pocoproject/poco/issues/1552
    static Poco::Net::IPAddress bitwiseOp(const Poco::Net::IPAddress& address,
                                          const Poco::Net::IPAddress& mask,
                                          BitwiseOp op);

    /// \brief Get the maximum prefix length for the given IPAddress family.
    /// \param family The IPAddress family.
    /// \returns the maximum prefix length for the given family.
    static unsigned maximumPrefix(Poco::Net::IPAddress::Family family);

    /// \brief Get the maximum prefix IPAddress for the given IPAddress family.
    /// \param family The IPAddress family.
    /// \returns the maximum prefix IPAddress for the given family.
    static const Poco::Net::IPAddress& maximumPrefixIPAddress(Poco::Net::IPAddress::Family family);

    /// \brief The IP address.
    Poco::Net::IPAddress _address;

    /// \brief The IP address mask.
    Poco::Net::IPAddress _mask;

    /// \brief The IP address subnet.
    Poco::Net::IPAddress _subnet;

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
