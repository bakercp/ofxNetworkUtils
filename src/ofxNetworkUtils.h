//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#define OFX_NETWORKUTILS_VERSION_MAJOR 0
#define OFX_NETWORKUTILS_VERSION_MINOR 10
#define OFX_NETWORKUTILS_VERSION_PATCH 0
#define OFX_NETWORKUTILS_VERSION_PRERELEASE "master"


#include "Poco/Net/HostEntry.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/NetworkInterface.h"
#include "Poco/Environment.h"
#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/DNS.h"
#include "Poco/Net/HostEntry.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/NetworkInterface.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "ofx/Net/IPAddressRange.h"
#include "ofx/Net/NetworkUtils.h"
#include "ofx/Net/NetworkInterfaceListener.h"


namespace ofxNet = ofx::Net;
