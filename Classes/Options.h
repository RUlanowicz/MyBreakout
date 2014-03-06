//
//  Options.h
//  MyBreakout
//
//  Created by Ryan Ulanowicz on 3/5/14.
//
//

#ifndef __MyBreakout__Options__
#define __MyBreakout__Options__
#include "cocos2d.h"
#include <iostream>

class Options : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void soundOff(Object* pSender);
    
    void soundOn(Object* pSender);
    
    void menuCloseCallback(Object* pObject);
    
    CREATE_FUNC(Options);
    
};

#endif /* defined(__MyBreakout__Options__) */
