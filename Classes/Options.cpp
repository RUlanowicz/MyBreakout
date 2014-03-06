//
//  Options.cpp
//  MyBreakout
//
//  Created by Ryan Ulanowicz on 3/5/14.
//
//

#include "Options.h"
#include "cocos2d.h"
#include "game.h"
#include "CCMenuItem.h"
#include "CCMenu.h"
#include "stdio.h"
#include "HelloWorldScene.h"
#include "CCUserDefault.h"
#include "SimpleAudioEngine.h"

cocos2d::Scene* Options::createScene(){
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Options::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Options::init(){
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = cocos2d::MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Options::menuCloseCallback, this));
    
	closeItem->setPosition(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                 origin.y + closeItem->getContentSize().height/2);
    
    // create menu, it's an autorelease object
    auto menu = cocos2d::Menu::create(closeItem, NULL);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu, 1);
    
    auto newGame = cocos2d::MenuItemFont::create("Sound On", CC_CALLBACK_1(Options::soundOn, this));
    auto optionsScene = cocos2d::MenuItemFont::create("Sound Off", CC_CALLBACK_1(Options::soundOff, this));
    
    newGame->setPosition(origin.x + visibleSize.width/2,visibleSize.height/2);
    optionsScene->setPosition(origin.y + visibleSize.width/2,visibleSize.height/2-(2*newGame->getContentSize().height));
    
    auto mainMenu = cocos2d::Menu::create(newGame,optionsScene,NULL);
    
    mainMenu->setPosition(cocos2d::Point::ZERO);
    this->addChild(mainMenu,1);

    return true;
}

void Options::soundOff(Object* pObject){
    cocos2d::UserDefault::getInstance()->setBoolForKey("sound", false);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void Options::soundOn(Object* pObject){
    cocos2d::UserDefault::getInstance()->setBoolForKey("sound", true);
}

void Options::menuCloseCallback(Object* pObject){
    cocos2d::Director::getInstance()->popScene();
}