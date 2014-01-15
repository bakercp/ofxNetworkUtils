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


#pragma once


#include <string>
#include "Poco/Environment.h"
#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/DNS.h"
#include "Poco/Net/HostEntry.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/NetworkInterface.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "ofLog.h"
#include "ofURLFileLoader.h"


namespace ofx {
namespace Utils {


class Network
    /// \brief A collection of network utilities.
{
public:
    typedef Poco::Net::HostEntry HostEntry;
        ///< \brief A typedef for Poco::Net::HostEntry.

    typedef Poco::Net::NetworkInterface NetworkInterface;
        ///< \brief A typedef for Poco::Net::NetworkInterface.

    typedef Poco::Net::NetworkInterface::NetworkInterfaceList NetworkInterfaceList;
        ///< \brief A typedef for Poco::Net::NetworkInterface::NetworkInterfaceList.

    enum AddressType
        /// \brief An enumeration of address types.
    {
        WILDCARD,
            ///< \brief Wildcard address (e.g. all zeros)
        BROADCAST,
            ///< \brief Broadcast address (e.g. all bits are 1)
        LOOPBACK,
            ///< \brief Loopback address (e.g. 127.0.01 / ::1)
        MULTICAST,
            ///< \brief Multicast address (e.g. 224.0.0.0 to 239.255.255.255 range)
        UNICAST,
            ///< \brief Unicast address (e.g. not a wildcard, broadcast or multicast address)
        LINK_LOCAL,
            ///< \brief Linklocal address (e.g. 169.254.0.0/16 (aka self-assigned))
        SITE_LOCAL
            ///< \brief Broadcast address (e.g. 10.0.0.0/24, 192.168.0.0/16 or 172.16.0.0 to 172.31.255.255)
    };

    static std::string getNodeName();
        ///< \brief Query the Node Name.
        ///< \returns the node (or host) name if successful.

    static std::string getHostName();
        ///< \brief Query the Node Name.
        ///< \returns the host name if successful.

    static std::string getMacAddress();
        ///< \brief Query the system's MAC address
        ///< \returns the MAC address of the first Ethernet adapter found on the
        ///<         system with the format (format "xx:xx:xx:xx:xx:xx").

    static HostEntry getHostByName(const std::string& hostname);
        ///< \param hostname The hostname to query for host information.
        ///< \returns a HostEntry for the given hostname.

    static HostEntry getHostByAddress(const Poco::Net::IPAddress& ipAddress);
        ///< \param ipAddress The address to query for host information.
        ///< \returns a HostEntry for the given address.

    static HostEntry getHost(const std::string& address);
        ///< \param address The address to query for host information.
        ///< \returns a HostEntry for the given address.

    static HostEntry getThisHost();
        ///< \returns a HostEntry about this system.

    static NetworkInterfaceList listNetworkInterfaces(AddressType addressType,
                                                      NetworkInterface::IPVersion ipVersion = NetworkInterface::IPv4_OR_IPv6);
        ///< \brief List all network interfaces of a given address type.
        ///< \param addressType The address type to search for.
        ///< \param ipVersion The IPVersion to search for.
        ///< \returns a list of network interfaces.

    static Poco::Net::IPAddress getPublicIPAddress(const std::string& url = DEFAULT_PUBLIC_IP_QUERY_URL);
        ///< \brief Get a public IP address for the default interface.
        ///< \param url The public IP address discovery endpoint.
        ///<        Users may choose to use their own endpoint.  The
        ///<        endpoint must return a single plain text IPv4 or IPv6
        ///<        IP address.
        ///< \returns An IP address if successful.  If unsuccessful, a default
        ///<        wildard (0.0.0.0) IP address will be returned.

    static const std::string DEFAULT_PUBLIC_IP_QUERY_URL;
        ///< \brief The default URL to determine the machine's public IP.

    // TODO: NetworkInterfaceList code has been updated in newer versions of
    // POCO.  For network interface information, call POCO directly.

    //    static bool isInRange(const std::string cidr)

};


} } // namespace ofx::Utils
