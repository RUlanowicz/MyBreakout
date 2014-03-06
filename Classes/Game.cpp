//
//  Game.cpp
//  MyBreakout
//
//  Created by Ryan Ulanowicz on 3/2/14.
//
//

#include "Game.h"
#include "CCTouch.h"
#include "CCArray.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "CCUserDefault.h"
#include "CCMenu.h"
#include "CCMenuItem.h"

USING_NS_CC;

Sprite* ball;
Sprite* paddle;
Size visibleSize;
Point origin;
float x_velocity, y_velocity, temp;
cocos2d::Vector<cocos2d::Sprite *> _blocks;
bool touched, lifelost, game_won;
LabelTTF *label,*winner,*game_score;
int count, score, soundOn;
bool game_sound_status;

Scene* Game::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Game::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    game_sound_status = UserDefault::getInstance()->getBoolForKey("sound");
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    char text[256];
    sprintf(text,"Score: %d",score);
    game_score = LabelTTF::create(text, "Ariel", 36);
    game_score->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    this->addChild(game_score);
    touched = false;
    lifelost = false;
    this->_blocks = cocos2d::Vector<cocos2d::Sprite *>{15};
    
    for(int i = 0; i < 10; i++){
        auto temp = Sprite::create("Paddle.jpg");
        temp->setScale(visibleSize.width/(6*temp->getContentSize().width));
        if(i<5){
            temp->setPosition(Point(((i*visibleSize.width)/5)+temp->getContentSize().width,origin.y+visibleSize.height-temp->getContentSize().height));
        }
        else if(i<10){
            temp->setPosition(Point((((i-5)*visibleSize.width)/5)+temp->getContentSize().width,origin.y+visibleSize.height-temp->getContentSize().height*3));
        }
        else{
            temp->setPosition(Point((((i-10)*visibleSize.width)/5)+temp->getContentSize().width,origin.y+visibleSize.height-temp->getContentSize().height*5));
        }
        this->addChild(temp,0);
        this->_blocks.pushBack(temp);
    }
    x_velocity = visibleSize.width*.25;
    y_velocity = visibleSize.width*.25;
    
    count = 10;
    
    ball = Sprite::create("ball-hd.png");
    ball->setPosition(Point(origin.x + visibleSize.width/2, origin.y + (2*ball->getContentSize().height)));
    this->addChild(ball,1);
    
    paddle = Sprite::create("Paddle.jpg");
    paddle->setScale(visibleSize.width/(6*paddle->getContentSize().width), (visibleSize.width/(6*paddle->getContentSize().width))/2);
    //paddle->setScale(visibleSize.width/(6*paddle->getContentSize().width));
    paddle->setPosition(Point(origin.x + visibleSize.width/2, origin.y + paddle->getContentSize().height));
    this->addChild(paddle,0);
    
    //this->schedule(schedule_selector(Game::moveFrame));
    this->schedule(schedule_selector(Game::myUpdate));
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Game::paddleDown, this);
    listener->onTouchMoved = CC_CALLBACK_2(Game::paddleMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game::paddleEnded, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool Game::paddleDown(Touch *touch, Event *event){
    touched = true;
    return true;
}

void Game::paddleMoved(Touch *touch, Event *event){
    paddle->setPosition(Point(touch->getLocation().x,paddle->getPosition().y));
}

void Game::paddleEnded(Touch *touch, Event *event){
    
}

void Game::myUpdate(float dt){
    if(touched){
        auto detect_one = ball->getBoundingBox();
        //Rect(ball->getPositionX(),ball->getPositionY(),ball->getContentSize().width,ball->getContentSize().height*2);
        auto detect_two = paddle->getBoundingBox();
        //Rect(paddle->getPositionX(),paddle->getPositionY(),paddle->getContentSize().width,paddle->getContentSize().height*2);
        if(detect_one.intersectsRect(detect_two)){
            if(game_sound_status){
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mouth.wav");
            }
            y_velocity = -y_velocity;
        }
        
        for(auto block: this->_blocks){
            auto detect_three = block->getBoundingBox();
            if(detect_three.intersectsRect(detect_one)){
                block->setVisible(false);
                _blocks.eraseObject(block);
                count--;
                this->removeChild(game_score);
                score+=50;
                char text[256];
                sprintf(text,"Score: %d",score);
                game_score = LabelTTF::create(text, "Ariel", 36);
                game_score->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
                this->addChild(game_score,0);
                y_velocity = -y_velocity;
                if(count == 0){
                    drawMenu(true);
                }
                if(game_sound_status)
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("scifi002.mp3");
                break;
            }
        }
        
        ball->setPosition(Point(ball->getPositionX() + x_velocity*dt, ball->getPositionY() + y_velocity*dt));
        
        if(ball->getPositionY() > visibleSize.height - (ball->getContentSize().height/2)){
            y_velocity = -y_velocity;
        }
        
        if(ball->getPositionX() > visibleSize.width - (ball->getContentSize().width/2) || ball ->getPositionX() < origin.x+(ball->getContentSize().width/2)){
            x_velocity = -x_velocity;
        }
        
        if(ball->getPositionY() < origin.y+(ball->getContentSize().height/2)){
            drawMenu(false);
        }
    }
}

void soundOff(Object* pSender){
    if(soundOn)
        soundOn=false;
    else
        soundOn=true;
}

void Game::gameReset(Object* pSender){
    score = 0;
    touched = false;
    auto myGame = Game::createScene();
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(myGame);
}

void Game::gameHome(Object* pSender){
    touched = false;
    score = 0;
    Director::getInstance()->resume();
    Director::getInstance()->popScene();
}

void Game::drawMenu(bool winner){
    if(winner){
        
        auto label = LabelTTF::create("Winner", "Arial", 56);
        label->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);

    }
    else{
        auto label = LabelTTF::create("Loser", "Arial", 56);
        label->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
    game_score->setVisible(false);
    Director::getInstance()->pause();
    auto startOver = MenuItemFont::create("New Game", CC_CALLBACK_1(Game::gameReset, this));
    auto goHome = MenuItemFont::create("Main Menu", CC_CALLBACK_1(Game::gameHome, this));
    
    startOver->setPosition(origin.x + visibleSize.width/2,visibleSize.height/2);
    goHome->setPosition(origin.y + visibleSize.width/2,visibleSize.height/2-(2*goHome->getContentSize().height));
    
    auto mainMenu = Menu::create(startOver,goHome,NULL);
    
    mainMenu->setPosition(Point::ZERO);
    this->addChild(mainMenu,4);
}

