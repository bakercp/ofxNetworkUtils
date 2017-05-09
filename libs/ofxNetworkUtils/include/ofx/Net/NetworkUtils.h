//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include "Poco/Net/HostEntry.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/NetworkInterface.h"


namespace ofx {
namespace Net {


/// \brief A collection of network utilities.
class NetworkUtils
{
public:
    /// \brief A typedef for Poco::Net::HostEntry.
    typedef Poco::Net::HostEntry HostEntry;

    /// \brief A typedef for Poco::Net::NetworkInterface.
    typedef Poco::Net::NetworkInterface NetworkInterface;

    /// \brief A typedef for Poco::Net::NetworkInterface::NetworkInterfaceList.
    typedef Poco::Net::NetworkInterface::NetworkInterfaceList NetworkInterfaceList;

    /// \brief An enumeration of address types.
    enum AddressType
    {
        /// \brief Any address type.
        ANY,
        /// \brief Wildcard address (e.g. all zeros)
        WILDCARD,
        /// \brief Broadcast address (e.g. all bits are 1)
        BROADCAST,
        /// \brief Loopback address (e.g. 127.0.0.1 / ::1)
        LOOPBACK,
        /// \brief Multicast address (e.g. 224.0.0.0 to 239.255.255.255 range)
        MULTICAST,
        /// \brief Unicast address (e.g. not a wildcard, broadcast or multicast address)
        UNICAST,
        /// \brief Linklocal address (e.g. 169.254.0.0/16 (aka self-assigned))
        LINK_LOCAL,
        /// \brief Broadcast address (e.g. 10.0.0.0/24, 192.168.0.0/16 or 172.16.0.0 to 172.31.255.255)
        SITE_LOCAL
    };

    /// \brief Query the Node Name.
    /// \returns the node (or host) name if successful.
    static std::string getNodeName();

    /// \brief Query the Node Name.
    /// \returns the host name if successful.
    static std::string getHostName();

    /// \brief Query the system's MAC address
    /// \returns the MAC address of the first Ethernet adapter found on the
    ///          system with the format (format "xx:xx:xx:xx:xx:xx").
    static std::string getMacAddress();

    /// \param hostname The hostname to query for host information.
    /// \returns a HostEntry for the given hostname.
    static HostEntry getHostByName(const std::string& hostname);

    /// \param ipAddress The address to query for host information.
    /// \returns a HostEntry for the given address.
    static HostEntry getHostByAddress(const Poco::Net::IPAddress& ipAddress);

    /// \param address The address to query for host information.
    /// \returns a HostEntry for the given address.
    static HostEntry getHost(const std::string& address);

    /// \returns a HostEntry about this system.
    static HostEntry getThisHost();

    /// \brief List all network interfaces of a given AddressType.
    /// \param addressType The AddressType to search for.
    /// \param ipVersion The IPVersion to search for.
    /// \returns a list of network interfaces.
    static NetworkInterfaceList listNetworkInterfaces(AddressType addressType,
                                                      NetworkInterface::IPVersion ipVersion = NetworkInterface::IPv4_OR_IPv6);

    /// \brief Get a public IP address for the default interface.
    /// \param url The public IP address discovery endpoint.
    ///        Users may choose to use their own endpoint. The
    ///        endpoint must return a single plain text IPv4 or IPv6
    ///        IP address.
    /// \returns An IP address if successful.  If unsuccessful, a default
    ///        wildard (0.0.0.0) IP address will be returned.
    static Poco::Net::IPAddress getPublicIPAddress(const std::string& url = DEFAULT_PUBLIC_IP_QUERY_URL);

    /// \brief The default URL to determine the machine's public IP.
    static const std::string DEFAULT_PUBLIC_IP_QUERY_URL;

};


} } // namespace ofx::Net
