#include "MenuLayer.hpp"
void MenuLayerMod::versionsLink(cocos2d::CCObject* pSender) {
    CCApplication::sharedApplication()->openURL(versionsUrl);
}
void MenuLayerMod::onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response) {
    std::vector<char>* responseData = response->getResponseData();
    std::string responseString(responseData->begin(), responseData->end());
    if (responseString != "") versionLabel->setColor({ 255, 255, 255 });
    if (responseString != version) {
        AchievementNotifier::sharedState()->notifyAchievement("Update available!", ("You can download new " + responseString + " version on the website.").c_str(), "GJ_downloadsIcon_001.png", true);
        versionLabel->setColor({ 255, 60, 60 });
        versionLabel->runAction(CCRepeatForever::create(CCSequence::create(
            CCEaseSineIn::create(CCScaleTo::create(0.3, versionLabel->getScale() + 0.1)),
            CCEaseBounceOut::create(CCScaleTo::create(0.5, versionLabel->getScale())),
            CCDelayTime::create(1.0),
            nullptr)));
        CCMenuItem* versionItem = CCMenuItem::create(versionLabel, menu_selector(MenuLayerMod::versionsLink));
        versionItem->setContentSize(versionLabel->getContentSize());
        versionItem->setAnchorPoint(versionLabel->getAnchorPoint());
        versionItem->setPosition(versionLabel->getPosition());
        versionItem->setScale(versionLabel->getScale());
        MenuLayer* MenuLayerSelf = (MenuLayer*)versionLabel->getParent();
        CCMenu* versionsLinkMenu = CCMenu::createWithItem(versionItem);
        versionsLinkMenu->setPosition({ 0,0 });
        MenuLayerSelf->addChild(versionsLinkMenu);
    }
}

bool (*MenuLayer_init_org)(MenuLayer*);
bool MenuLayer_init_h(MenuLayer* self) {
    if (!MenuLayer_init_org(self)) return false;
    MenuLayerMod::versionLabel = CCLabelBMFont::create(MenuLayerMod::version, "chatFont.fnt");
    MenuLayerMod::versionLabel->setPosition({ CCDirector::sharedDirector()->getWinSize().width, 0 });
    MenuLayerMod::versionLabel->setAnchorPoint({ 1.1f, 0 });
    MenuLayerMod::versionLabel->setScale({ 0.6f });
    MenuLayerMod::versionLabel->setColor({ 0, 0, 0 });
    MenuLayerMod::versionLabel->setOpacity({ 110 });
    MenuLayerMod::versionLabel->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(3, 180), CCFadeTo::create(3, 110), nullptr)));
    self->addChild(MenuLayerMod::versionLabel);

    //udate if sddso herer
    CCHttpRequest* request = new CCHttpRequest;
    request->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
    request->setUrl(MenuLayerMod::upadateInfoUrl);
    request->setResponseCallback(self, httpresponse_selector(MenuLayerMod::onUpdateHttpResponse));
    CCHttpClient::getInstance()->send(request);
    request->release();

    return true;
}

void (*MenuLayer_onFacebook_org)(MenuLayer*, void*, cocos2d::CCObject*);
void MenuLayer_onFacebook_h(MenuLayer* self, void* a, cocos2d::CCObject* pSender) { 
    CCApplication::sharedApplication()->openURL("https://speeddash.ispsite.ru/redirect.php?onFacebook");
}
void (*MenuLayer_onTwitter_org)(MenuLayer*, void*, cocos2d::CCObject*);
void MenuLayer_onTwitter_h(MenuLayer* self, void* a, cocos2d::CCObject* pSender) {
    CCApplication::sharedApplication()->openURL("https://speeddash.ispsite.ru/redirect.php?onTwitter");
}
void (*MenuLayer_onYouTube_org)(MenuLayer*, void*, cocos2d::CCObject*);
void MenuLayer_onYouTube_h(MenuLayer* self, void* a, cocos2d::CCObject* pSender) {
    CCApplication::sharedApplication()->openURL("https://speeddash.ispsite.ru/redirect.php?onYouTube");
}

void MenuLayerHook() {
    //GD_HOOK(base + 0x1907B0, MenuLayer_init);
    HOOK("_ZN9MenuLayer4initEv", MenuLayer_init_h, MenuLayer_init_org);
    //GD_HOOK(base + 0x191960, MenuLayer_onFacebook);
    HOOK("_ZN9MenuLayer10onFacebookEPN7cocos2d8CCObjectE", MenuLayer_onFacebook_h, MenuLayer_onFacebook_org);
    //GD_HOOK(base + 0x191980, MenuLayer_onTwitter);
    HOOK("_ZN9MenuLayer9onTwitterEPN7cocos2d8CCObjectE", MenuLayer_onTwitter_h, MenuLayer_onTwitter_org);
    //GD_HOOK(base + 0x1919A0, MenuLayer_onYouTube);
    HOOK("_ZN9MenuLayer9onYouTubeEPN7cocos2d8CCObjectE", MenuLayer_onYouTube_h, MenuLayer_onYouTube_org);
}