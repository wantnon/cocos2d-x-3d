

#include "obj3D.h"
#include <iostream>
#include <map>
#include "support/ccUtils.h"
#include "myFunc.h"
using namespace cocos2d ;
using namespace std ;


bool Cobj3D::init(string texFileName)
{
    
    //init this CCSprite
    this->initWithFile(texFileName.c_str());
    //shader program
	{
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("shader0.fsh").c_str())->getCString();
        GLchar * vertSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("shader0.vsh").c_str())->getCString();
		CCGLProgram* pProgram = new CCGLProgram();
		pProgram->initWithVertexShaderByteArray(vertSource, fragSource);
        //bind attribute
		pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        pProgram->addAttribute(kCCAttributeNameNormal, kCCVertexAttrib_Normals);
        //link  (must after bindAttribute)
		pProgram->link();
        //get cocos2d-x build-in uniforms
		pProgram->updateUniforms();
        //get my own uniforms
		map<string,GLint> myUnifoMap;
        myUnifoMap["modelMat"] = glGetUniformLocation(pProgram->getProgram(),"modelMat");
        myUnifoMap["lightPos_world"] = glGetUniformLocation(pProgram->getProgram(),"lightPos_world");
        myUnifoMap["eyePos_world"] = glGetUniformLocation(pProgram->getProgram(),"eyePos_world");
        myUnifoMap["diffuseMaterial"] = glGetUniformLocation(pProgram->getProgram(),"diffuseMaterial");
        myUnifoMap["diffuseLight"] = glGetUniformLocation(pProgram->getProgram(),"diffuseLight");
        myUnifoMap["ambientMaterial"] = glGetUniformLocation(pProgram->getProgram(),"ambientMaterial");
		myUnifoMap["ambientLight"] = glGetUniformLocation(pProgram->getProgram(),"ambientLight");
        myUnifoMap["specularMaterial"] = glGetUniformLocation(pProgram->getProgram(),"specularMaterial");
        myUnifoMap["specularLight"] = glGetUniformLocation(pProgram->getProgram(),"specularLight");
        myUnifoMap["shininess"] = glGetUniformLocation(pProgram->getProgram(),"shininess");
        //make program
        program.myUnifoMap=myUnifoMap;
        program.setProgram(pProgram);
        //program can be released
        pProgram->release();
        //check gl error
		CHECK_GL_ERROR_DEBUG();
	}
	//check gl error
	CHECK_GL_ERROR_DEBUG();
    // create model
    float d=6;
    const int posArrayLen=6*4*4;
	float posArray[posArrayLen]={-d,-d,d,1, d,-d,d,1, d,d,d,1, -d,d,d,1,//front v0~v3
                          -d,-d,-d,1, -d,d,-d,1, d,d,-d,1, d,-d,-d,1,//back v4~v7
                          -d,d,d,1, d,d,d,1, d,d,-d,1, -d,d,-d,1,//up v8~v11
                          -d,-d,d,1, -d,-d,-d,1, d,-d,-d,1, d,-d,d,1,//dn v12~v15
                          -d,d,d,1, -d,d,-d,1, -d,-d,-d,1, -d,-d,d,1,//left v16~v19
                          d,d,d,1, d,-d,d,1, d,-d,-d,1, d,d,-d,1//right v20~v23
                         };
    const int normalArrayLen=6*4*4;
    float normalArray[normalArrayLen]={0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0,//front
                             0,0,-1,0, 0,0,-1,0, 0,0,-1,0, 0,0,-1,0,//back
                             0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0,//up
                             0,-1,0,0, 0,-1,0,0, 0,-1,0,0, 0,-1,0,0,//dn
                             1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0,//left
                             -1,0,0,0, -1,0,0,0, -1,0,0,0, -1,0,0,0//right
                            };
    const int texCoordArrayLen=6*4*2;
    float texCoordArray[texCoordArrayLen]={0,1, 1,1, 1,0, 0,0,//front
                            0,1, 1,1, 1,0, 0,0,//back
                            0,1, 1,1, 1,0, 0,0,//up
                            0,1, 1,1, 1,0, 0,0,//dn
                            0,1, 1,1, 1,0, 0,0,//left
                            0,1, 1,1, 1,0, 0,0//right
                           };
    const int indexArrayLen=6*2*3;
	int indexArray[indexArrayLen]={0,1,2, 2,3,0,//front
        4,5,6, 6,7,4,//back
        8,9,10, 10,11,8,//up
        12,13,14, 14,15,12,//dn
        16,17,18, 18,19,16,//left
        20,21,22, 22,23,20//right
    };
	//create indexVBO
	CindexVBO3d::enableAttribArrays();
	indexVBO3d=new CindexVBO3d();
	indexVBO3d->genBuffers();
	//submit data to VBO
	indexVBO3d->submitPos(posArray,posArrayLen,GL_STATIC_DRAW);
    indexVBO3d->submitNormal(normalArray,normalArrayLen,GL_STATIC_DRAW);
    indexVBO3d->submitTexCoord(texCoordArray,texCoordArrayLen,GL_STATIC_DRAW);
	indexVBO3d->submitIndex(indexArray,indexArrayLen,GL_STATIC_DRAW);
	//check gl error
	CHECK_GL_ERROR_DEBUG();


	return true ;
}
void Cobj3D::draw()
{
    //----change shader
    this->setShaderProgram(program.getProgram());

    ccGLEnable(m_eGLServerState);
    //pass values for cocos2d-x build-in uniforms
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    //pass values for my own uniforms
    float modelMat[16]={1,0,0,0,//col 1
                        0,1,0,0,
                        0,0,1,0,
                        0,0,0,1};
    glUniformMatrix4fv(program.myUnifoMap["modelMat"],1,GL_FALSE,modelMat);
    float lightPos_world[4]={20,60,40,1};
    glUniform4fv(program.myUnifoMap["lightPos_world"],1,lightPos_world);
    CCCamera*camera=this->getCamera();
    float eyePos_world[4]={0,0,0,1};
    camera->getEyeXYZ(eyePos_world, eyePos_world+1, eyePos_world+2);
    glUniform4fv(program.myUnifoMap["eyePos_world"],1,eyePos_world);
    float diffuseMaterial[4]={1,1,1,1};//0.8,0.8,0.8,1
	glUniform4fv(program.myUnifoMap["diffuseMaterial"],1,diffuseMaterial);
    float diffuseLight[4]={1,1,1,1};
    glUniform4fv(program.myUnifoMap["diffuseLight"], 1, diffuseLight);
    float ambientMaterial[4]={0.5,0.5,0.5,1};//0.2,0.2,0.2,1
    glUniform4fv(program.myUnifoMap["ambientMaterial"],1,ambientMaterial);
    float ambientLight[4]={0.5,0.5,0.5,1};//0,0,0,1
    glUniform4fv(program.myUnifoMap["ambientLight"],1,ambientLight);
    float specularMaterial[4]={0.2,0.2,0.2,1};//0,0,0,1
    glUniform4fv(program.myUnifoMap["specularMaterial"],1,specularMaterial);
    float specularLight[4]={1,1,1,1};
    glUniform4fv(program.myUnifoMap["specularLight"],1,specularLight);
    float shininess=20;
    glUniform1f(program.myUnifoMap["shininess"],shininess);
    //attach texture to texture attach point
    glActiveTexture(GL_TEXTURE0);//back to GL_TEXTURE0
    glBindTexture(GL_TEXTURE_2D, this->getTexture()->getName());
    //draw
    indexVBO3d->setPointers();
    indexVBO3d->draw(GL_TRIANGLES);
    
    
}