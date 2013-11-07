//
//  scene2DLayer.h
//  HelloCpp
//
//  Created by ck02-084 on 13-11-6.
//
//

#ifndef __HelloCpp__scene2DLayer__
#define __HelloCpp__scene2DLayer__

#include <iostream>

#include "cocos2d.h"
using namespace cocos2d;
class Cscene2DLayer : public CCLayer
{
public:
	Cscene2DLayer() {
    }
	virtual ~Cscene2DLayer(){
    };
    bool init();
    void visit();//draw is not recursive, visit does
    
};


#endif /* defined(__HelloCpp__scene2DLayer__) */
