//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    thisHost = ofxNet::NetworkUtils::getThisHost();
    nodeName = ofxNet::NetworkUtils::getNodeName();
    publicIp = ofxNet::NetworkUtils::getPublicIPAddress();

    siteLocalInterfaces = ofxNet::NetworkUtils::listNetworkInterfaces(ofxNet::NetworkUtils::SITE_LOCAL);
}


void ofApp::draw()
{
    ofBackground(0);

    int x = 12;
    int y = 12;

    std::stringstream ss;

    ss << std::setw(10) << "Hostname: " << nodeName << std::endl;
    ss << std::setw(10) << "Public IP: " << publicIp.toString() << std::endl;
    ss << "------------------------------" << endl;

    ofDrawBitmapString(ss.str(), x, y += 36);

    auto iter = siteLocalInterfaces.begin();

    while (iter != siteLocalInterfaces.end())
    {
        ss.str(""); // clear our stringstream

        Poco::Net::NetworkInterface iface = (*iter);

        ss << std::endl << std::setw(18) << "IFace Name: " << iface.name();
        ss << std::endl << std::setw(18) << "Local IP: " << iface.address().toString();

        ofDrawBitmapString(ss.str(), x + 5, y += 24);

        ++iter;
    }
}

