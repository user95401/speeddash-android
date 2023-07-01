#pragma once
#include "includes.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class MenuLayerMod : MenuLayer {
public:
    inline CCLabelBMFont static* versionLabel;
    const char static* version;
    const char static* versionsUrl;
    const char static* upadateInfoUrl;
    void versionsLink(cocos2d::CCObject*);
    void onUpdateHttpResponse(CCHttpClient*, CCHttpResponse*);
};

void MenuLayerHook();
