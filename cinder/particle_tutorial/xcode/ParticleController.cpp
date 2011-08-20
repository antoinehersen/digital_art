//
//  ParticleController.cpp
//  particle_tutorial
//
//  Created by Antoine Hersen on 8/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "cinder/Perlin.h"
#include "ParticleController.h"

using namespace ci;
using std::list;


ParticleController::ParticleController() {
}


ParticleController::ParticleController(  int res )
{
    
    int mXRes = app::getWindowWidth()/res;
	int mYRes = app::getWindowHeight()/res;
    
    ci::Perlin perlin(4,12);
    
    for( int y=0; y<mYRes; y++ ){
        for( int x=0; x<mXRes; x++ ){
            float noise = perlin.fBm(x*1.1,y*1.0);
            addParticle( x, y, noise);
            std::cout << noise << std::endl;
        }
    }
}

void ParticleController::update()
{
    float time = app::getElapsedSeconds();
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->update(time);
	}
}

void ParticleController::draw()
{
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->draw();
	}
}

void ParticleController::addParticles( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		float x = Rand::randFloat( app::getWindowWidth() );
		float y = Rand::randFloat( app::getWindowHeight() );
		mParticles.push_back( Particle( Vec2f( x, y ) ) );
	}
}

void ParticleController::addParticle( int xi, int yi, float noise ) {
    float x = ( xi + 0.5f ) * 10.0f;
    float y = ( yi + 0.5f ) * 10.0f;
    Particle particle = Particle( Vec2f( x, y ) );
    particle.mSeed = noise * 6.0f;
    mParticles.push_back(  particle);
}

void ParticleController::removeParticles( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		mParticles.pop_back();
	}
}

