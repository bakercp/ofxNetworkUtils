//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxNetworkUtils.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();

    Poco::Net::HostEntry thisHost;
    std::string nodeName;

    Poco::Net::IPAddress publicIp;

    Poco::Net::NetworkInterface::List siteLocalInterfaces;

};
