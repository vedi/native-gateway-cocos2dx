//
// Created by Shubin Fedor on 16/10/14.
//


#ifndef __Cocos2dxGatewayAdapter_H_
#define __Cocos2dxGatewayAdapter_H_

#include <string>

class Cocos2dxGatewayAdapter {
public:
    static void dispatch(const char *, std::string &retStr);
};


#endif //__Cocos2dxGatewayAdapter_H_
