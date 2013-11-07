

#ifndef HelloWorld_obj3D_h
#define HelloWorld_obj3D_h
#include "cocos2d.h"

#include<iostream>
#include<map>
using namespace std;

#include "indexVBO3d.h"
#include "myDef.h"
using namespace cocos2d;

//if program1 and program2 have a uniform variable with the same name, the two variable's uniform ID (GLint) may be different. 
//so safe way is let each shader program hold his own uniform IDs. that is why i create the class CGLProgramWithMyUnifos.
class CGLProgramWithMyUnifos{
	CCGLProgram*program;
public:
	map<string,GLint> myUnifoMap;
    CGLProgramWithMyUnifos(){
		program=NULL;
	}
	virtual ~CGLProgramWithMyUnifos(){
		program->release();
	}
    void setProgram(CCGLProgram*_program){
        if(program){
            program->release();
        }
        program=_program;
        program->retain();
    }
    CCGLProgram*getProgram(){
        return program;
    }

};

class Cobj3D : public CCSprite{
public:
	Cobj3D() {
        indexVBO3d=NULL;
    }
	virtual ~Cobj3D(){
        if(indexVBO3d){
            indexVBO3d->release();
            indexVBO3d=NULL;
        }
    };
	bool init(string texFileName) ;
	void draw() ;
private:
	
	CGLProgramWithMyUnifos program;
    CindexVBO3d* indexVBO3d;

};
#endif
