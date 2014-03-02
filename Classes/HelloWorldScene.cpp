#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CCMenuItem.h"
#include "CCMenu.h"
#include "Game.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //auto label = LabelTTF::create("Breakout", "Arial", 56);
    
    // position the label on the center of the screen
    //label->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(label, 1);
    
    auto newGame = MenuItemFont::create("New Game", CC_CALLBACK_1(HelloWorld::menuNewGame, this));
    auto optionsScene = MenuItemFont::create("Options", CC_CALLBACK_1(HelloWorld::optionsNewScene, this));
    
    newGame->setPosition(origin.x + visibleSize.width/2,visibleSize.height/2);
    optionsScene->setPosition(origin.y + visibleSize.width/2,visibleSize.height/2-(2*newGame->getContentSize().height));
    
    auto mainMenu = Menu::create(newGame,optionsScene,NULL);
    
    mainMenu->setPosition(Point::ZERO);
    this->addChild(mainMenu,1);
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("logo.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - sprite->getContentSize().height));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("intro.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(100);
    
    return true;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuNewGame(Object* pSender){
    Scene* sceneGame = Game::createScene();
    Director::getInstance()->pushScene(sceneGame);
}

void HelloWorld::optionsNewScene(Object* pSender){
    
}
