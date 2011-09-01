//
//  Path.cpp
//  borwnian_motion
//
//  Created by Antoine Hersen on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "Path.h"
#include "cinder/Rand.h"

using namespace ci;


void Path::setup() {
    m_path.push_back( ci::Vec3f::zero());
    m_path.push_back( ci::Vec3f(1.0f, 0.0f, 0.0f));
    
    for(int i =0 ; i< 100; i++) {
        add_node();
    }
}

void Path::add_node() {
    ci::Vec2f new_dir;
    switch(ci::Rand::randInt(4)) {
        case 0:
            new_dir = ci::Vec2f(0,1);
            break;
        case 1:
            new_dir = ci::Vec2f(0,-1);
            break;
        case 2:
            new_dir = ci::Vec2f(1,0);
            break;
        case 3:
            new_dir = ci::Vec2f(-1,0);
            break;
    }

    Vec3f last =  m_path.back();
    m_path.pop_back();
    Vec3f before_last = m_path.back();
    m_path.push_back( last);
    
    Vec3f dir = last - before_last;
    
    Vec3f new_point;
    
    if( dir.x < -0.1f || dir.x > 0.1f ) {
        new_point = last + Vec3f(0.0f, new_dir.x, new_dir.y);
    } else if( dir.y < -0.1f || dir.y > 0.1f ) {
        new_point = last + Vec3f(new_dir.x, 0.0f, new_dir.y);
    } else if( dir.z < -0.1f || dir.z > 0.1f ) {
        new_point = last + Vec3f(new_dir.x, new_dir.y, 0.0f);
    }
    
    m_path.push_back(new_point);
    
}

void Path::draw() {
    glPushMatrix();

    float scale = 5;
    glScalef(scale, scale, scale);

    glBegin(GL_LINE_STRIP);
    glColor4f( 1.0f, 1.0f, 1.0f, 0.3f);

    for(path_t::iterator it = m_path.begin(); it != m_path.end(); it++) {
        glVertex3f(it->x, it->y, it->z);
    }
    glEnd();
    glPopMatrix();
}