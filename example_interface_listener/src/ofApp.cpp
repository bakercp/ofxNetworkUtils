//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    interfaceUpListener = networkInterfaceListener.onInterfaceUp.newListener(this, &ofApp::onInterfaceUp);
    interfaceDownListener = networkInterfaceListener.onInterfaceDown.newListener(this, &ofApp::onInterfaceDown);
}


void ofApp::draw()
{
    ofBackground(0);

    std::stringstream ss;

    ss << "IPv4 Interfaces" << std::endl << std::endl;
    ss << "Name\tIP Address" << std::endl;
    ss << "----\t----------" << std::endl;
    for (auto entry: networkInterfaceListener.interfaces())
    {
        auto interface = entry.second;

        Poco::Net::IPAddress iPv4Address;
        interface.firstAddress(iPv4Address, Poco::Net::IPAddress::IPv4);

        if (!iPv4Address.isWildcard())
        {
            ss << interface.displayName() << "\t" << iPv4Address.toString() << std::endl;
        }
    }

    ofDrawBitmapStringHighlight(ss.str(), 14, 14);
}


void ofApp::onInterfaceUp(const Poco::Net::NetworkInterface& interface)
{
    ofLogNotice("ofApp::onInterfaceUp") << interface.displayName() << " went up with: ";

    Poco::Net::IPAddress iPv4Address;
    Poco::Net::IPAddress iPv6Address;
    interface.firstAddress(iPv4Address, Poco::Net::IPAddress::IPv4);
    interface.firstAddress(iPv6Address, Poco::Net::IPAddress::IPv6);

    if (!iPv4Address.isWildcard())
    {
        ofLogNotice("ofApp::onInterfaceUp") << "\tIPv4: " << iPv4Address.toString();
    }
    if (!iPv6Address.isWildcard())
    {
        ofLogNotice("ofApp::onInterfaceUp") << "\tIPv6: " << iPv6Address.toString();
    }
}


void ofApp::onInterfaceDown(const Poco::Net::NetworkInterface& interface)
{
    ofLogNotice("ofApp::onInterfaceDown") << interface.displayName() << " went down.";
}

