//
// Created by Shubin Fedor on 16/10/14.
//

#include "CCBunchManager.h"
#include "CCNativeGateway.h"
#include "json/document.h"

#define BUNCH_MANAGER "BunchManager"

void CCBunchManager::registerBunch(const char *bunch) {
    rapidjson::Document dict = rapidjson::Document();
    dict.SetObject();
    dict.AddMember("bunch", bunch, dict.GetAllocator());
    CCNativeGateway::dispatch(
            BUNCH_MANAGER,
            "registerBunch",
            dict
    );
}
