#include "LoadingLayer.hpp"
using namespace std;
const char* (*LoadingLayer_getString_org)(LoadingLayer*);
const char* LoadingLayer_getString_h(LoadingLayer* self, void*) {
    GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
    const char* s[16] = {
        "Loading speedrun...",
        "SGD",
        "Speed Geometry Dash!",
        "SpeedDash",
        "user666 was here",
        "Nekori, user666, thebekshdet?",
        "SpeeeeeedDash",
        "Back for more are ya?",
        "Counting to lEET",
        "Loading resources (Speed up)?",
        "Pro tip: Speed",
        "Pro tip: Don't crash",
        "discord.gg/KYXyhxC86u",
        "speeddash.ml",
        "- SpeedDash Reloaded -",
        "Welcome to SpeedDash!"
    };
    srand(time(NULL));
    return s[rand() % 16];
}

void LoadingLayerHook() {
    //GD_HOOK(base + 0x18cf40, LoadingLayer_getString);
    HOOK("_ZN12LoadingLayer16getLoadingStringEv", LoadingLayer_getString_h, LoadingLayer_getString_org);
}