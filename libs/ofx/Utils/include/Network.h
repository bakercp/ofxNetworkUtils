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


using Poco::Net::NetworkInterface;


namespace ofx {
namespace Utils {


class Network
{
public:
    enum AddressType
    {
        WILDCARD,  // e.g. all zeros
        BROADCAST, // e.g. all bits are 1
        LOOPBACK,  // e.g. 127.0.01 / ::1
        MULTICAST, // e.g. 224.0.0.0 to 239.255.255.255 range
        UNICAST,   // e.g. not a wildcard, broadcast or multicast address
        LINK_LOCAL,// e.g. 169.254.0.0/16 (aka self-assigned)
        SITE_LOCAL // e.g. 10.0.0.0/24, 192.168.0.0/16 or 172.16.0.0 to 172.31.255.255
    };

    typedef Poco::Net::HostEntry HostEntry;

    static std::string getNodeName();
    static std::string getHostName();
    static std::string getMacAddress();

    static HostEntry getHostByName(const string& hostname);
    static HostEntry getHostByAddress(const Poco::Net::IPAddress& ipAddress);
    static HostEntry getHost(const string& address);
    static HostEntry getThisHost();

    static NetworkInterface::NetworkInterfaceList listNetworkInterfaces(AddressType addressType, NetworkInterface::IPVersion ipVersion = NetworkInterface::IPv4_OR_IPv6);

    static Poco::Net::IPAddress getPublicIPAddress();



    // TODO: NetworkInterfaceList code has been updated in newer versions of
    // POCO.  For network interface information, call POCO directly.

};


} } // namespace ofx::Utils
