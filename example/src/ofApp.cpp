//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(1);

    thisHost = ofxNet::NetworkUtils::getThisHost();
    nodeName = ofxNet::NetworkUtils::getNodeName();
    publicIp = ofxNet::NetworkUtils::getPublicIPAddress();

}


void ofApp::draw()
{
    ofBackground(0);

    int x = 14;
    int y = 14;

    std::stringstream ss;

    ss << "Host Name: " << thisHost.name() << std::endl;
    ss << "Node Name: " << nodeName << std::endl;
    ss << "Public IP: " << publicIp.toString() << std::endl;
    ss << "--------------------------------" << std::endl;

    siteLocalInterfaces = ofxNet::NetworkUtils::listNetworkInterfaces(ofxNet::NetworkUtils::SITE_LOCAL);

    for (const auto& interface: siteLocalInterfaces)
    {
        ss << "Interface: [" << interface.name() << "] (" << interface.address().toString() << ")" << std::endl;
    }

    ofDrawBitmapString(ss.str(), x, y);
}
