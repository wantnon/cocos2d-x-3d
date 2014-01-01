//
//  scene3DLayer.cpp
//  HelloCpp
//
//  Created by ck02-084 on 13-11-6.
//
//

#include "scene3DLayer.h"
bool Cscene3DLayer::init(){
    //enable touch
	setTouchEnabled( true );
    //add 3d obj to layer
    Cobj3D*obj=new Cobj3D();
    obj->init("logo.png");
    obj->setAnchorPoint(ccp(0,0));
    obj->setPosition(ccp(0,0));
    this->addChild(obj,1);
    pObjList.push_back(obj);
    obj->release();
    //update eye pos
    updateEyePos();
    //set camera
    //here we set the camera, and in visit(), cocos2d-x will call camera->locate() to apply the camera matrix to matrix stack.
    CCCamera*camera=this->getCamera();
    camera->setEyeXYZ(20, 10, 20);
    camera->setCenterXYZ(0, 0, 0);
    camera->setUpXYZ(0, 1, 0);
    return true;
}
void Cscene3DLayer::visit(){
    //set projection
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLLoadIdentity();
    //enable depth test
    CCDirector::sharedDirector()->setDepthTest(true);
    //call CCLayer's visit
    CCLayer::visit();
}
void Cscene3DLayer::updateEyePos(){
    float cosA=cosf(A*M_PI/180);
    float sinA=sinf(A*M_PI/180);
    float cosB=cosf(B*M_PI/180);
    float sinB=sinf(B*M_PI/180);
    eyePos.x=r*cosB*sinA;
    eyePos.y=r*sinB;
    eyePos.z=r*cosB*cosA;
    eyePos.w=1;
}

void Cscene3DLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        
        //----update mos
        mosxf=mosx;
        mosyf=mosy;
        mosx=loc_winSpace.x;
        mosy=loc_winSpace.y;
        
    }
}
void Cscene3DLayer::ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
       
        
        //----update mos
        mosxf=mosx;
        mosyf=mosy;
        mosx=loc_winSpace.x;
        mosy=loc_winSpace.y;
        //----update eyePos
        A+=-(mosx-mosxf)*0.4;
        B+=(mosy-mosyf)*0.4;
        updateEyePos();
        this->getCamera()->setEyeXYZ(eyePos.x, eyePos.y, eyePos.z);
    }
}

void Cscene3DLayer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
	for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCLOG("loc_winSpace:%f,%f",loc_winSpace.x,loc_winSpace.y);
        
        //now because in 3d mode, so convertToGL coordinate's result is not as in 2D.
      //  CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
      //  CCLOG("loc_GLSpace:%f,%f",loc_GLSpace.x,loc_GLSpace.y);
        
        //----update mos
        mosxf=mosx;
        mosyf=mosy;
        mosx=loc_winSpace.x;
        mosy=loc_winSpace.y;
        
        
        
    }
}

