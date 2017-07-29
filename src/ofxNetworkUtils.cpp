//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofxNetworkUtils.h"
#include "ofConstants.h"


#if (OFX_NETWORKUTILS_VERSION_MAJOR > OF_VERSION_MAJOR || OFX_NETWORKUTILS_VERSION_MINOR > OF_VERSION_MINOR)
    #warning Your version of openFrameworks may be too old for this addon.
    #warning Please try the stable branch of this addon or see the README.md for more info.
#elif (OFX_NETWORKUTILS_VERSION_MAJOR < OF_VERSION_MAJOR || OFX_NETWORKUTILS_VERSION_MINOR < OF_VERSION_MINOR)
    #warning Your version of openFrameworks may be too new for this addon.
    #warning Please try the stable branch of this addon or see the README.md for more info.
#endif