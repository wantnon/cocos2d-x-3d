cocos2d-x 3d drawing demo
by yang chao (wantnon) 2013-11-6
blog: http://user.qzone.qq.com/350479720/blog/1383750859

important note:
to properly run this program, you should make some modification to cocos2d-x 2.2:
find CCDirector::setProjection function and mask the code below:
	    kmVec3 eye, center, up;
            kmVec3Fill( &eye, size.width/2, size.height/2, zeye );
            kmVec3Fill( &center, size.width/2, size.height/2, 0.0f );
            kmVec3Fill( &up, 0.0f, 1.0f, 0.0f);
            kmMat4LookAt(&matrixLookup, &eye, &center, &up);
            kmGLMultMatrix(&matrixLookup);