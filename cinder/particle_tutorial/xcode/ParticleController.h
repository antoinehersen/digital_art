//
//  ParticleController.h
//  particle_tutorial
//
//  Created by Antoine Hersen on 8/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "Particle.h"
#include <list>

class ParticleController {
public:
    ParticleController();

	ParticleController(  int res );
	void update();
	void draw();
	void addParticles( int amt );
    void addParticle( int xi, int yi, float noise = 0.0f );
	void removeParticles( int amt );
    
	
	std::list<Particle>	mParticles;
};