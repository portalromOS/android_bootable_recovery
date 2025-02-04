/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright (C) 2023 The PortalRom Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_TAG "Vold"

#include <cutils/log.h>

#include <sysutils/NetlinkEvent.h>
#include <volume_manager/VolumeManager.h>
#include "NetlinkHandler.h"

NetlinkHandler::NetlinkHandler(int listenerSocket) : NetlinkListener(listenerSocket) {}

NetlinkHandler::~NetlinkHandler() {}

bool NetlinkHandler::start() {
    return this->startListener() == 0;
}

void NetlinkHandler::stop() {
    this->stopListener();
}

void NetlinkHandler::onEvent(NetlinkEvent* evt) {
    android::volmgr::VolumeManager* vm = android::volmgr::VolumeManager::Instance();
    const char* subsys = evt->getSubsystem();

    if (!subsys) {
        SLOGW("No subsystem found in netlink event");
        return;
    }

    if (!strcmp(subsys, "block")) {
        vm->handleBlockEvent(evt);
    }
}
