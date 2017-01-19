//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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
        ofLogError("NetworkUtils::getNodeName") << exc.displayText();
        return nodeName;
    }
    catch (const Poco::Net::NoAddressFoundException& exc)
    {
        ofLogError("NetworkUtils::getNodeName") << exc.displayText();
        return nodeName;
    }
    catch (const Poco::Net::DNSException& exc)
    {
        ofLogError("NetworkUtils::getNodeName") << exc.displayText();
        return nodeName;
    }
    catch (const Poco::IOException& exc)
    {
        ofLogError("NetworkUtils::getNodeName") << exc.displayText();
        return nodeName;
    }
    catch (...)
    {
        ofLogError("NetworkUtils::getNodeName") << "Unknown Exception: " << nodeName;
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
        ofLogError("NetworkUtils::getMacAddress") << exc.displayText();
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
        ofLogError("NetworkUtils::getHostByName") << exc.displayText();
        return hostEntry;
    }
    catch (const Poco::Net::NoAddressFoundException& exc)
    {
        ofLogError("NetworkUtils::getHostByName") << exc.displayText();
        return hostEntry;
    }
    catch (const Poco::Net::DNSException& exc)
    {
        ofLogError("NetworkUtils::getHostByName") << exc.displayText();
        return hostEntry;
    }
    catch (const Poco::IOException& exc)
    {
        ofLogError("NetworkUtils::getHostByName") << exc.displayText();
        return hostEntry;
    }
    catch (...)
    {
        ofLogError("NetworkUtils::getHostByName") << "Unknown Exception: " << hostname;
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
        ofLogError("NetworkUtils::getHostByAddress") << exc.displayText();
        return hostEntry;
    }
    catch (const Poco::Net::DNSException& exc)
    {
        ofLogError("NetworkUtils::getHostByAddress") << exc.displayText();
        return hostEntry;
    }
    catch (const Poco::IOException& exc)
    {
        ofLogError("NetworkUtils::getHostByAddress") << exc.displayText();
        return hostEntry;
    }
    catch (...)
    {
        ofLogError("NetworkUtils::getHostByAddress") << "Unknown Exception: " << ipAddress.toString();
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
        ofLogError("NetworkUtils::getHost") << exc.displayText();
        return hostEntry;
    }
    catch (const Poco::Net::DNSException& exc)
    {
        ofLogError("NetworkUtils::getHost") << exc.displayText();
        return hostEntry;
    }
    catch (const Poco::IOException& exc)
    {
        ofLogError("NetworkUtils::getHost") << exc.displayText();
        return hostEntry;
    }
    catch (...)
    {
        ofLogError("NetworkUtils::getHost") << "Unknown Exception: " << address;
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
        ofLogError("NetworkUtils::getThisHost") << exc.displayText();
        return hostEntry;
    }
    catch (const Poco::Net::NoAddressFoundException& exc)
    {
        ofLogError("NetworkUtils::getThisHost") << exc.displayText();
        return hostEntry;
    }
    catch (const Poco::Net::DNSException& exc)
    {
        ofLogError("NetworkUtils::getThisHost") << exc.displayText();
        return hostEntry;
    }
    catch (const Poco::IOException& exc)
    {
        ofLogError("NetworkUtils::getThisHost") << exc.displayText();
        return hostEntry;
    }
    catch (...)
    {
        ofLogError("NetworkUtils::getThisHost") << "Unknown Exception.";
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
            ofLogError("NetworkUtils::getPublicIPAddress") << response.error;
            return Poco::Net::IPAddress();
        }
    }
    catch (const Poco::Net::InvalidAddressException& exc)
    {
        ofLogError("NetworkUtils::getPublicIPAddress") << exc.displayText();
        return Poco::Net::IPAddress();
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("NetworkUtils::getPublicIPAddress") << exc.displayText();
        return Poco::Net::IPAddress();
    }
}


} } // namespace ofx::Net
