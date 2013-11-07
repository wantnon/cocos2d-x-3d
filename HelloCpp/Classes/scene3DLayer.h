//
//  scene3DLayer.h
//  HelloCpp
//
//  Created by ck02-084 on 13-11-6.
//
//

#ifndef __HelloCpp___scene3DLayer__
#define __HelloCpp___scene3DLayer__

#include <iostream>
#include "cocos2d.h"
#include "kazmath/vec4.h"
#include "obj3D.h"
using namespace cocos2d;
class Cscene3DLayer : public CCLayer
{
public:
	Cscene3DLayer() {
        const float r_value=30;
        r=r_value;
        A=0;
        B=0;
        kmVec4Fill(&eyePos, 0, sqrt(2)*r_value, sqrt(2)*r_value, 1);
        kmVec4Fill(&eyeTg, 0, 0, 0, 1);
        
        mosx=mosxf=0;
        mosy=mosyf=0;
        
    }
	virtual ~Cscene3DLayer(){
    };
    bool init();
    void visit();//draw is not recursive, visit does
public:
    //touch
	virtual void ccTouchesBegan(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
	virtual void ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
private:
    kmVec4 eyePos;
    kmVec4 eyeTg;
    float r;//distance from eyePos to eyeTg
    float A;//angle in XZ plane
    float B;//angle vertical
    void updateEyePos();
    vector<Cobj3D*> pObjList;
    
    float mosx,mosxf;
    float mosy,mosyf;
    
    
};

#endif /* defined(__HelloCpp___scene3DLayer__) */
