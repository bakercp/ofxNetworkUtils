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
    void setup() override;
    void draw() override;

    void onInterfaceUp(const Poco::Net::NetworkInterface& interface);
    void onInterfaceDown(const Poco::Net::NetworkInterface& interface);

    ofxNet::NetworkInterfaceListener networkInterfaceListener;

    ofEventListener interfaceUpListener;
    ofEventListener interfaceDownListener;

};
