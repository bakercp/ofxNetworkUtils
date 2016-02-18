// =============================================================================
//
// Copyright (c) 2013-2016 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/Net/NetworkUtils.h"
#include "Poco/Environment.h"
#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/DNS.h"
#include "Poco/Net/NetException.h"
#include "ofLog.h"
#include "ofURLFileLoader.h"


namespace ofx {
namespace Net {


const std::string NetworkUtils::DEFAULT_PUBLIC_IP_QUERY_URL = "http://bot.whatismyipaddress.com";


std::string NetworkUtils::getHostName()
{
    std::string nodeName = "UNKNOWN";

    try
    {
        nodeName = Poco::Net::DNS::hostName();
    }
    catch (const Poco::Net::HostNotFoundException& exc)
    {
        ofLogError("Network::getNodeName") << "Host not found: " << exc.displayText();
        return nodeName;
    }
    catch (const Poco::Net::NoAddressFoundException& exc)
    {
        ofLogError("Network::getNodeName") << "No Address found: " << exc.displayText();
        return nodeName;
    }
    catch (const Poco::Net::DNSException& exc)
    {
        ofLogError("Network::getNodeName") << "DNS Exception: " << exc.displayText();
        return nodeName;
    }
    catch (const Poco::IOException& exc)
    {
        ofLogError("Network::getNodeName") << "IO Exception: " << exc.displayText();
        return nodeName;
    }
    catch (...)
    {
        ofLogError("Network::getNodeName") << "Unknown Exception: " << nodeName;
        return nodeName;
    }

    return nodeName;
}


std::string NetworkUtils::getNodeName()
{
    return Poco::Environment::nodeName();
}


std::string NetworkUtils::getMacAddress()
{
    std::string nodeId = "UNKNOWN";
    
    try
    {
        nodeId = Poco::Environment::nodeId();
    }
    catch (const Poco::SystemException& exc)
    {
        ofLogError("Network::getMacAddress") << exc.displayText();
        return nodeId;;
    }
    
    return nodeId;;
}


NetworkUtils::HostEntry NetworkUtils::getHostByName(const std::string& hostname)
{
    NetworkUtils::HostEntry hostEntry;

    try
    {
        hostEntry = Poco::Net::DNS::hostByName(hostname);
    }
    catch (const Poco::Net::HostNotFoundException& exc)
    {
        ofLogError("Network::getHostByName") << "Host not found: " << hostname;
        return hostEntry;
    }
    catch (const Poco::Net::NoAddressFoundException& exc)
    {
        ofLogError("Network::getHostByName") << "No Address found: " << hostname;
        return hostEntry;
    }
    catch (const Poco::Net::DNSException& exc)
    {
        ofLogError("Network::getHostByName") << "DNS Exception: " << hostname;
        return hostEntry;
    }
    catch (const Poco::IOException& exc)
    {
        ofLogError("Network::getHostByName") << "IO Exception: " << hostname;
        return hostEntry;
    }
    catch (...)
    {
        ofLogError("Network::getHostByName") << "Unknown Exception: " << hostname;
        return hostEntry;
    }
    
    return hostEntry;
}

NetworkUtils::HostEntry NetworkUtils::getHostByAddress(const Poco::Net::IPAddress& ipAddress)
{
    NetworkUtils::HostEntry hostEntry;

    try
    {
        hostEntry = Poco::Net::DNS::hostByAddress(ipAddress);
    }
    catch (const Poco::Net::HostNotFoundException& exc)
    {
        ofLogError("Network::getHostByAddress") << "Host not found: " << ipAddress.toString();
        return hostEntry;
    }
    catch (const Poco::Net::DNSException& exc)
    {
        ofLogError("Network::getHostByAddress") << "DNS Exception: " << ipAddress.toString();
        return hostEntry;
    }
    catch (const Poco::IOException& exc)
    {
        ofLogError("Network::getHostByAddress") << "IO Exception: " << ipAddress.toString();
        return hostEntry;
    }
    catch (...)
    {
        ofLogError("Network::getHostByAddress") << "Unknown Exception: " << ipAddress.toString();
        return hostEntry;
    }
    
    return hostEntry;
}


NetworkUtils::HostEntry NetworkUtils::getHost(const std::string& address)
{
    NetworkUtils::HostEntry hostEntry;

    try
    {
        hostEntry = Poco::Net::DNS::resolve(address);
    }
    catch (const Poco::Net::HostNotFoundException& exc)
    {
        ofLogError("Network::getHost") << "Host not found: " << address;
        return hostEntry;
    }
    catch (const Poco::Net::DNSException& exc)
    {
        ofLogError("Network::getHost") << "DNS Exception: " << address;
        return hostEntry;
    }
    catch (const Poco::IOException& exc)
    {
        ofLogError("Network::getHost") << "IO Exception: " << address;
        return hostEntry;
    }
    catch (...)
    {
        ofLogError("Network::getHost") << "Unknown Exception: " << address;
        return hostEntry;
    }
    
    return hostEntry;
}


NetworkUtils::HostEntry NetworkUtils::getThisHost()
{
    NetworkUtils::HostEntry hostEntry;

    try
    {
        hostEntry = Poco::Net::DNS::thisHost();
    }
    catch (const Poco::Net::HostNotFoundException& exc)
    {
        ofLogError("Network::getThisHost") << "Host not found.";
        return hostEntry;
    }
    catch (const Poco::Net::NoAddressFoundException& exc)
    {
        ofLogError("Network::getThisHost") << "No Address found.";
        return hostEntry;
    }
    catch (const Poco::Net::DNSException& exc)
    {
        ofLogError("Network::getThisHost") << "DNS Exception.";
        return hostEntry;
    }
    catch (const Poco::IOException& exc)
    {
        ofLogError("Network::getThisHost") << "IO Exception.";
        return hostEntry;
    }
    catch (...)
    {
        ofLogError("Network::getThisHost") << "Unknown Exception.";
        return hostEntry;
    }
    
    return hostEntry;
}

NetworkUtils::NetworkInterfaceList NetworkUtils::listNetworkInterfaces(AddressType addressType,
                                                             NetworkInterface::IPVersion ipVersion)
{
    NetworkInterfaceList all = Poco::Net::NetworkInterface::list();
    NetworkInterfaceList results;  // empty to start
    NetworkInterfaceList::iterator iter = all.begin();

    while (iter != all.end())
    {
        bool match = false;

        Poco::Net::NetworkInterface iface = (*iter);
        Poco::Net::IPAddress address = iface.address();

        switch (addressType)
        {
            case WILDCARD:
                match = address.isWildcard();
                break;
            case BROADCAST:
                match = address.isBroadcast();
                break;
            case LOOPBACK:
                match = address.isLoopback();
                break;
            case MULTICAST:
                match = address.isMulticast();
                break;
            case UNICAST:
                match = address.isUnicast();
                break;
            case LINK_LOCAL:
                match = address.isLinkLocal();
                break;
            case SITE_LOCAL:
                match = address.isSiteLocal();
                break;
        }

        if (match)
        {
            if ((ipVersion == NetworkInterface::IPv4_OR_IPv6) ||
                (ipVersion == NetworkInterface::IPv4_ONLY && !iface.supportsIPv6() && iface.supportsIPv4()) ||
                (ipVersion == NetworkInterface::IPv6_ONLY && !iface.supportsIPv4() && iface.supportsIPv6()))
            {
                results.push_back(iface);
            }
        }

        ++iter;
    }

    return results;
}


Poco::Net::IPAddress NetworkUtils::getPublicIPAddress(const std::string& url)
{
    try
    {
        ofHttpResponse response = ofLoadURL(url);

        if (response.status == 200)
        {
            return Poco::Net::IPAddress(response.data.getText());
        }
        else
        {
            ofLogError("Network::getPublicIPAddress") << response.error;
            return Poco::Net::IPAddress();
        }
    }
    catch (Poco::Net::InvalidAddressException& exc)
    {
        ofLogError("Network::getPublicIPAddress") << exc.displayText();
        return Poco::Net::IPAddress();
    }
    catch (Poco::Exception& exc)
    {
        ofLogError("Network::getPublicIPAddress") << exc.displayText();
        return Poco::Net::IPAddress();
    }
}


} } // namespace ofx::Net
