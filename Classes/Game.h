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

class Game : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

};
#endif
