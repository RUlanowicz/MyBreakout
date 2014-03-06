//
//  Game.h
//  MyBreakout
//
//  Created by Ryan Ulanowicz on 3/2/14.
//
//

#ifndef MyBreakout_Game_h
#define MyBreakout_Game_h

#include "cocos2d.h"
#include "CCTouch.h"
#include "stdio.h"

class Game : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(Game);
    
    void moveFrame(float dt);

    virtual bool paddleDown(cocos2d::Touch *touch, cocos2d::Event *event);
    
    virtual void paddleMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    
    virtual void paddleEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    void myUpdate(float dt);
    
    cocos2d::Vector<cocos2d::Sprite *> _blocks;
    
    void newLife();
    
    void resetGame();
    
    void soundOff(Object* pSender);
    
    void gameHome(Object* pSender);
    
    void gameReset(Object* pSender);
    
    void drawMenu(bool winner);
};
#endif
