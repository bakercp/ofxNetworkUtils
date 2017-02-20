//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//
//

#pragma once


#include "ofEvents.h"
#include "Poco/Net/NetworkInterface.h"


namespace ofx {
namespace Net {


class NetworkInterfaceListener
{
public:
    NetworkInterfaceListener();
    ~NetworkInterfaceListener();

    void update(ofEventArgs& args);

    /// \returns the last known interface map.
    const Poco::Net::NetworkInterface::Map& interfaces() const;

    ofEvent<const Poco::Net::NetworkInterface> onInterfaceUp;
    ofEvent<const Poco::Net::NetworkInterface> onInterfaceDown;

    enum
    {
        /// \brief The default polling interval in milliseconds.
        DEFAULT_POLL_INTERVAL = 1000
    };


private:
    ofEventListener _updateListener;

    uint64_t _lastUpdate = 0;
    uint64_t _updateInterval = DEFAULT_POLL_INTERVAL;

    Poco::Net::NetworkInterface::Map _interfaces;

};



} } // ofx::Utils
