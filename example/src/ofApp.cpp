// =============================================================================
//
// Copyright (c) 2013-2015 Christopher Baker <http://christopherbaker.net>
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


#include "ofApp.h"


void ofApp::setup()
{
    thisHost = ofx::NetworkUtils::getThisHost();
    nodeName = ofx::NetworkUtils::getNodeName();
    publicIp = ofx::NetworkUtils::getPublicIPAddress();

    siteLocalInterfaces = ofx::NetworkUtils::listNetworkInterfaces(ofx::NetworkUtils::SITE_LOCAL);
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

    Poco::Net::NetworkInterface::NetworkInterfaceList::iterator iter = siteLocalInterfaces.begin();

    while(iter != siteLocalInterfaces.end())
    {
        ss.str(""); // clear our stringstream

        Poco::Net::NetworkInterface iface = (*iter);

        ss << std::endl << std::setw(18) << "IFace Name: " << iface.name();
        ss << std::endl << std::setw(18) << "Local IP: " << iface.address().toString();

        ofDrawBitmapString(ss.str(), x + 5, y += 24);

        ++iter;
    }
}

