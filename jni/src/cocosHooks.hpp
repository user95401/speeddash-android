#pragma once
#include <cocos2d.h>
using namespace cocos2d;

inline CCSprite* (__cdecl* CCSprite_createOrg)(const char* name);
CCSprite* CCSprite_createHook(const char* name);

inline CCSprite* (__cdecl* CCSprite_createWithSpriteFrameNameOrg)(const char* name);
CCSprite* CCSprite_createWithSpriteFrameNameHook(const char* name);

inline CCLabelBMFont* (__cdecl* CCLabelBMFont_createOrg)(const char* str, const char* fntFile);
CCLabelBMFont* CCLabelBMFont_createHook(const char* str, const char* fntFile);
