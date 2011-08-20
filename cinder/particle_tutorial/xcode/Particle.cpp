//
//  Particle.cpp
//  particle_tutorial
//
//  Created by Antoine Hersen on 8/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

Particle::Particle()
{
}

Particle::Particle( Vec2f loc )
{
	mLoc	= loc;
	mDir	= Rand::randVec2f();
	mVel	= 0.0f ; //Rand::randFloat( 5.0f );
	mRadius	= 3.0f;
    mSeed =  Rand::randFloat( 0.0f, 6.0f );

}

void Particle::update(float time)
{
	mLoc += mDir * mVel;
    mRadius = cos( time + mSeed) * 8.0f * sin(0.01f* time) ;
}

void Particle::draw()
{
	gl::drawSolidCircle( mLoc, mRadius );
}
