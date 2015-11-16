// =============================================================================
//
// Copyright (c) 2014-2015 Christopher Baker <http://christopherbaker.net>
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
    ofx::Net::IPAddressRange range0;
    ofx::Net::IPAddressRange range1(Poco::Net::IPAddress("192.168.0.1"));
    ofx::Net::IPAddressRange range2(Poco::Net::IPAddress("192.168.0.33"), 23);
    ofx::Net::IPAddressRange range3("2001:0db8:85a3::8a2e:0370:7334/64");
    ofx::Net::IPAddressRange range4("192.168.5.219/28");
    ofx::Net::IPAddressRange range5("2001:0db8:85a3::8a2e:0370:7334");
    ofx::Net::IPAddressRange range6("0.0.0.0/31");

    std::cout << toString(range0);
    std::cout << "-----" << std::endl;
    std::cout << toString(range1);
    std::cout << "-----" << std::endl;
    std::cout << toString(range2);
    std::cout << "-----" << std::endl;
    std::cout << toString(range3);
    std::cout << "-----" << std::endl;
    std::cout << toString(range4);
    std::cout << "-----" << std::endl;
    std::cout << toString(range5);
    std::cout << "-----" << std::endl;

    Poco::Net::IPAddress test0("192.168.0.1");
    Poco::Net::IPAddress test1("2001:0db8:85a3::8a2e:0370:7334");
    Poco::Net::IPAddress test2("127.0.0.2");
    Poco::Net::IPAddress test3("10.10.10.2");
    Poco::Net::IPAddress test4("::FFFF");
    Poco::Net::IPAddress test5("0.0.0.1");

    std::cout << toString(range0, test0) << std::endl;
    std::cout << toString(range0, test1) << std::endl;
    std::cout << toString(range0, test2) << std::endl;
    std::cout << toString(range0, test3) << std::endl;
    std::cout << toString(range0, test4) << std::endl;
    std::cout << toString(range0, test4) << std::endl;

    std::cout << toString(range0, test5) << std::endl;
    std::cout << toString(range6, test5) << std::endl;

    ofx::Net::IPAddressRange a("192.168.5.219/28");
    ofx::Net::IPAddressRange b("192.168.5.219/27");

    std::cout << toString(a, b) << std::endl;
    std::cout << toString(b, a) << std::endl;

}


void ofApp::draw()
{
    ofBackground(0);
}

std::string ofApp::toString(const ofx::Net::IPAddressRange& range)
{
    int tab = 20;
    std::stringstream ss;
    ss << std::setw(tab) << "Range: " << range.toString() << std::endl;
    ss << std::setw(tab) << "Subnet: " << range.getSubnet().toString() << std::endl;
    ss << std::setw(tab) << "Mask: " << range.getMask().toString() << std::endl;

    ss << std::setw(tab) << "Prefix Mask: " << range.getMaskPrefixLength() << std::endl;
    ss << std::setw(tab) << "Wildcard Mask: " << range.getWildcardMask().toString() << std::endl;

    ss << std::setw(tab) << "Host Min: " << range.getHostMin().toString() << std::endl;
    ss << std::setw(tab) << "Host Max: " << range.getHostMax().toString() << std::endl;

    return ss.str();
}


std::string ofApp::toString(const ofx::Net::IPAddressRange& range,
                            const Poco::Net::IPAddress& address)
{
    std::stringstream ss;

    ss << address.toString();
    ss << (range.contains(address) ? " is in " : " is NOT in ");
    ss << range.toString();
    ss << " (" << range.getHostMin().toString();
    ss << " - " << range.getHostMax().toString();
    ss << ")" << std::endl;

    return ss.str();
}


std::string ofApp::toString(const ofx::Net::IPAddressRange& range0,
                            const ofx::Net::IPAddressRange& range1)
{
    std::stringstream ss;

    ss << "The range: ";
    ss << range0.toString();
    ss << " (" << range0.getHostMin().toString();
    ss << " - " << range0.getHostMax().toString();
    ss << ") ";

    ss << (range1.contains(range0) ? " is contained in " : " is NOT contained in ");

    ss << "The range: ";
    ss << range1.toString();
    ss << " (" << range1.getHostMin().toString();
    ss << " - " << range1.getHostMax().toString();
    ss << ")" << std::endl;

    return ss.str();
}

