#pragma once
#include <defs/all.hpp>

#include <Geode/utils/web.hpp>

#include <managers/web.hpp>

class GlobedMenuLayer : public cocos2d::CCLayer {
public:
    static constexpr float LIST_WIDTH = 358.f;
    static constexpr float LIST_HEIGHT = 220.f;

    static GlobedMenuLayer* create();

private:
    Ref<CCMenuItemSpriteExtra> levelListButton, roomButton, serverSwitcherButton, discordButton, settingsButton;
    cocos2d::CCMenu *leftButtonMenu, *rightButtonMenu;

    bool currentlyShowingButtons = false;

    bool init() override;
    void keyBackClicked() override;
    void keyDown(cocos2d::enumKeyCodes key) override;
    void update(float dt) override;
};
