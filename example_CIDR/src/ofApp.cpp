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


#include "ofApp.h"


void ofApp::setup()
{
    thisHost = ofx::Net::NetworkUtils::getThisHost();
    nodeName = ofx::Net::NetworkUtils::getNodeName();
    publicIp = ofx::Net::NetworkUtils::getPublicIPAddress();

    cidr = ofx::Net::CIDRAddress("127.0.0.1/26");

    ofx::Net::CIDRAddress addr0("127.0.0.23");
    ofx::Net::CIDRAddress addr1("127.0.0.63");

    std::cout << "Raw:          " << cidr.toString() << std::endl;
    std::cout << "Broadcast :   " << cidr.getBroadcastAddress().toString() << endl;
    std::cout << "Host Max :    " << cidr.getHostMax().toString() << endl;
    std::cout << "Host Min :    " << cidr.getHostMin().toString() << endl;
    std::cout << "Network Addr: " << cidr.getNetworkAddress().toString() << endl;

    std::cout << "# ADDR: " << cidr.getMaximumAddresses() << endl;
    std::cout << "# HOST: " << cidr.getMaximumSubnets() << endl;

    std::cout << "# IN RANGE? : " << addr0.toString() << ": " << cidr.contains(addr0) << endl;
    std::cout << "# IN RANGE? : " << addr1.toString() << ": " << cidr.contains(addr1) << endl;
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

