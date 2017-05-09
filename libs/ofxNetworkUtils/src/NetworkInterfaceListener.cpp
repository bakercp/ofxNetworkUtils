//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Net/NetworkInterfaceListener.h"
#include "Poco/Net/NetException.h"
#include "ofUtils.h"


namespace ofx {
namespace Net {


NetworkInterfaceListener::NetworkInterfaceListener():
    _updateListener(ofEvents().update.newListener(this, &NetworkInterfaceListener::update))
{
}


NetworkInterfaceListener::~NetworkInterfaceListener()
{
}


void NetworkInterfaceListener::update(ofEventArgs& args)
{
    auto now = ofGetElapsedTimeMillis();

    if (_lastUpdate == 0 || (now + _lastUpdate) > _updateInterval)
    {
        auto interfaces = Poco::Net::NetworkInterface::map();

        {
            auto _iter = _interfaces.cbegin();

            while (_iter != _interfaces.cend())
            {
                if (interfaces.find(_iter->first) == interfaces.end())
                {
                    Poco::Net::NetworkInterface updated;

                    try
                    {
                        updated = Poco::Net::NetworkInterface::forIndex(_iter->second.index());
                    }
                    catch (const Poco::Net::InterfaceNotFoundException& exc)
                    {
                        updated = Poco::Net::NetworkInterface(_iter->second.index());
                    }

                    onInterfaceDown.notify(this, updated);
                }

                ++_iter;
            }
        }

        {
            auto iter = interfaces.cbegin();

            while (iter != interfaces.cend())
            {
                if (_interfaces.find(iter->first) == _interfaces.end())
                {
                    onInterfaceUp.notify(this, iter->second);
                }
                
                ++iter;
            }
        }
        
        _interfaces = interfaces;
        _lastUpdate = now;
    }
}


const Poco::Net::NetworkInterface::Map& NetworkInterfaceListener::interfaces() const
{
    return _interfaces;
}


} } // namespace ofx::Net
