//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofxNet::IPAddressRange range0;
    ofxNet::IPAddressRange range1(Poco::Net::IPAddress("192.168.0.1"));
    ofxNet::IPAddressRange range2(Poco::Net::IPAddress("192.168.0.33"), 23);
    ofxNet::IPAddressRange range3("2001:0db8:85a3::8a2e:0370:7334/64");
    ofxNet::IPAddressRange range4("192.168.5.219/28");
    ofxNet::IPAddressRange range5("2001:0db8:85a3::8a2e:0370:7334");
    ofxNet::IPAddressRange range6("0.0.0.0/31");

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

    ofxNet::IPAddressRange a("192.168.5.219/28");
    ofxNet::IPAddressRange b("192.168.5.219/27");

    std::cout << toString(a, b) << std::endl;
    std::cout << toString(b, a) << std::endl;

}


void ofApp::draw()
{
    ofBackground(0);
}


std::string ofApp::toString(const ofxNet::IPAddressRange& range)
{
    int tab = 20;
    std::stringstream ss;
    ss << std::setw(tab) << "Range: " << range.toString() << std::endl;
    ss << std::setw(tab) << "Subnet: " << range.subnet().toString() << std::endl;
    ss << std::setw(tab) << "Mask: " << range.mask().toString() << std::endl;
    if (range.family() == Poco::Net::IPAddress::IPv4)
    {
        const uint8_t* bytes = reinterpret_cast<const uint8_t*>(range.mask().addr());
        ss << std::setw(tab) << "Binary Mask: ";
        ss << ofToBinary(bytes[0]) << ".";
        ss << ofToBinary(bytes[1]) << ".";
        ss << ofToBinary(bytes[2]) << ".";
        ss << ofToBinary(bytes[3]);
        ss << std::endl;
    }
    ss << std::setw(tab) << "Prefix Mask: " << range.maskPrefixLength() << std::endl;
    ss << std::setw(tab) << "Wildcard Mask: " << range.wildcardMask().toString() << std::endl;
    ss << std::setw(tab) << "Host Min: " << range.hostMin().toString() << std::endl;
    ss << std::setw(tab) << "Host Max: " << range.hostMax().toString() << std::endl;
    ss << "--------------------------------------------------------------------------------";

    return ss.str();
}


std::string ofApp::toString(const ofxNet::IPAddressRange& range,
                            const Poco::Net::IPAddress& address)
{
    std::stringstream ss;

    ss << address.toString();
    ss << (range.contains(address) ? " is in " : " is NOT in ");
    ss << range.toString();
    ss << " (" << range.hostMin().toString();
    ss << " - " << range.hostMax().toString();
    ss << ")" << std::endl;

    return ss.str();
}


std::string ofApp::toString(const ofxNet::IPAddressRange& range0,
                            const ofxNet::IPAddressRange& range1)
{
    std::stringstream ss;

    ss << "The range: ";
    ss << range0.toString();
    ss << " (" << range0.hostMin().toString();
    ss << " - " << range0.hostMax().toString();
    ss << ") ";

    ss << (range1.contains(range0) ? " is contained in " : " is NOT contained in ");

    ss << "The range: ";
    ss << range1.toString();
    ss << " (" << range1.hostMin().toString();
    ss << " - " << range1.hostMax().toString();
    ss << ")" << std::endl;

    return ss.str();
}

