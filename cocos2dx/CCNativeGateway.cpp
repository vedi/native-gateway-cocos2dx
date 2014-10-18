//
// Created by Shubin Fedor on 16/10/14.
//

#include "CCNativeGateway.h"
#include <iostream>
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <JniHelper.h>
#include <jni.h>
#include <string>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Cocos2dxGatewayAdapter.h"
#endif

rapidjson::Document&CCNativeGateway::createDictForMethod(char const *bunch, char const *method) {
    rapidjson::Document *pDoc = new rapidjson::Document();
    rapidjson::Document &doc = *pDoc;
    doc.SetObject();

    doc.AddMember("bunch", bunch, doc.GetAllocator());
    doc.AddMember("method", method, doc.GetAllocator());
    return doc;
}

rapidjson::Document &CCNativeGateway::addParams(rapidjson::Document &dict, rapidjson::Value &parameters) {
    dict.AddMember("params", parameters, dict.GetAllocator());
    return dict;
}

rapidjson::Document &CCNativeGateway::dispatch(rapidjson::Document &dict) {
    std::string str;
    serialize(dict, str);

    std::string retStr = "{}";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    const char *className = "com.vedidev.nativebridge.cocos2dx.Cocos2dxGatewayAdapter";
    const char *methodName = "dispatch";
    const char *paramCode = "(Ljava/lang/String;)Ljava/lang/String;";

    cocos2d::JniMethodInfo t;

    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                       className,
                                       methodName,
                                       paramCode)) {

        jstring stringArg1 = t.env->NewStringUTF(str.c_str());
        jstring retString = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1);

        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(t.classID);

        const char *nativeString = t.env->GetStringUTFChars(retString, 0);
        std::string retStr(nativeString);
        t.env->ReleaseStringUTFChars(retString, nativeString);
    } else {
        fprintf(stderr, "Cannot resolve java class\n");
        exit(1);
    }

    fprintf(stderr, "Result json is: %s", retStr.c_str());

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Cocos2dxGatewayAdapter::dispatch(str.c_str(), retStr);
#endif

    return deserialize(retStr);
}

void CCNativeGateway::serialize(rapidjson::Document &dict, std::string &result) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    dict.Accept(writer);
    result.clear();
    result.append(buffer.GetString());
}

rapidjson::Document &CCNativeGateway::deserialize(std::string &str) {
    rapidjson::Document *doc = new rapidjson::Document();
    doc->Parse<0>(str.c_str());
    assert(!doc->HasParseError());

    return *doc;
}

const rapidjson::Value &CCNativeGateway::dispatch(const char *bunch, const char *method, rapidjson::Value &parameters) {
    rapidjson::Document &dict = CCNativeGateway::createDictForMethod(bunch, method);
    rapidjson::Value &ret = dispatch(CCNativeGateway::addParams(dict, parameters));
    delete &dict;
    return ret;
}
