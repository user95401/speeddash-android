#include "includes.h"

#include "cocosHooks.hpp" //νσ θ ορθυ αλÿtό

#include "MenuLayer.hpp"
const char* MenuLayerMod::version = "1.0";
const char* MenuLayerMod::upadateInfoUrl = "http://speeddash.ml/getInf.php?actualVersion";
const char* MenuLayerMod::versionsUrl = "http://speeddash.ml/download";

#include "LoadingLayer.hpp"

void ApplyPatches() {
	//KittyMemory
	PatchManager tmp;
	//many thanks to Wyliemaster <3
	tmp.addPatch("libcocos2dcpp.so", 0x21F341, "E0"); //icon_hack
	tmp.addPatch("libcocos2dcpp.so", 0x21E4BC, "FF"); //icon_hack_colour
	tmp.addPatch("libcocos2dcpp.so", 0x322EBE, "0C"); //songid_bypass
	tmp.addPatch("libcocos2dcpp.so", 0x2153CE, "0B"); //rated_small_anticheat
	//make sure to apply the patches
	tmp.Modify();
}

//this is where all your hooks should be
void ApplyHooks() {
	MenuLayerHook();
	LoadingLayerHook();
	ApplyPatches();
	HOOK("_ZN7cocos2d8CCSprite25createWithSpriteFrameNameEPKc", CCSprite_createWithSpriteFrameNameHook, CCSprite_createWithSpriteFrameNameOrg);
	HOOK("_ZN7cocos2d13CCLabelBMFont6createEPKcS2_", CCLabelBMFont_createHook, CCLabelBMFont_createOrg);
}

//this function will run when the app starts
void loader() {
	ApplyHooks();
}

//starter
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	loader();
	return JNI_VERSION_1_6;
}   

