//
//  Particle.h
//  particle_tutorial
//
//  Created by Antoine Hersen on 8/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"

#include <vector>

class Particle {
public:
	Particle();
	Particle( ci::Vec2f );
	void update(float time);
	void draw();
	
	ci::Vec2f	mLoc;
	ci::Vec2f	mDir;
	float		mVel;
	
	float		mRadius;
    float       mSeed;
};