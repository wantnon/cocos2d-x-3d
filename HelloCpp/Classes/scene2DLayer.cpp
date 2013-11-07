//
//  scene2DLayer.cpp
//  HelloCpp
//
//  Created by ck02-084 on 13-11-6.
//
//

#include "scene2DLayer.h"
bool Cscene2DLayer::init(){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    //demo name
    {
        CCLabelTTF* pLabel = CCLabelTTF::create("cocos2d-x 3D Drawing Demo", "Arial", 45);
        pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - pLabel->getContentSize().height));
        this->addChild(pLabel, 1);
    }
    // author info
    {
        CCLabelTTF* pLabel = CCLabelTTF::create("by yang chao (wantnon) 2013-11-6", "Arial", 30);
        pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - pLabel->getContentSize().height-60));
        this->addChild(pLabel, 1);
    }
    return true;
}
void Cscene2DLayer::visit(){
    //set projection
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    //enable depth test
    CCDirector::sharedDirector()->setDepthTest(false);
    //call CCLayer' visit
    CCLayer::visit();
}