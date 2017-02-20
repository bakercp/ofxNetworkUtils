//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
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

    static std::string toString(const ofxNet::IPAddressRange& range);

    static std::string toString(const ofxNet::IPAddressRange& range,
                                const Poco::Net::IPAddress& address);

    static std::string toString(const ofxNet::IPAddressRange& range0,
                                const ofxNet::IPAddressRange& range1);
};
