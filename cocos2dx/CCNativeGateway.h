//
// Created by Shubin Fedor on 16/10/14.
//


#ifndef __CCNativeGateway_H_
#define __CCNativeGateway_H_

#include "json/rapidjson.h"
#include "json/document.h"
#include <string>

class CCNativeGateway {
public:
    static const rapidjson::Value &dispatch(char const *bunch, char const *method, rapidjson::Value &parameters);

private:
    static rapidjson::Document &createDictForMethod(char const *bunch, char const *method);

    static rapidjson::Document &addParams(rapidjson::Document &dict, rapidjson::Value &parameters);

    static rapidjson::Document &dispatch(rapidjson::Document &dict);

    static void serialize(rapidjson::Document &dict, std::string &result);

    static rapidjson::Document &deserialize(std::string &str);
};


#endif //__CCNativeGateway_H_
