//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//
//
//
//#pragma once
//
//
//#include "ofEvents.h"
//
//
//namespace ofx {
//namespace Utils {
//
//
//class NetworkInterfaceEventArgs: public ofEventArgs
//{
//public:
//    NetworkInterfaceEventArgs(NetworkInterface& interface): _interface(interface))
//    {
//    }
//
//    NetworkInterface& getInterfaceRef()
//    {
//        return _interface;
//    }
//
//private:
//
//    NetworkInterface& _interface;
//};
//
//
//class NetworkInterfaceEvents
//{
//public:
//    ofEvent<NetworkInterfaceEventArgs> onInterfaceAdded;
//    ofEvent<NetworkInterfaceEventArgs> onInterfaceRemoved;
//    ofEvent<NetworkInterfaceEventArgs> onInterfaceChanged;
//
//};
//
//
//class NetworkInterfaceListener
//{
//public:
//    NetworkInterfaceListener();
//    ~NetworkInterfaceListener();
//
//};
//
//
//
//} } // ofx::Utils
