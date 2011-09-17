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

#include "cinder/Easing.h"


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


ci::Vec3f Path::last(){
    return m_path.back();
}

void Path::draw() {

    glBegin(GL_LINE_STRIP);
    glColor4f( 1.0f, 1.0f, 1.0f, m_alpha);

    for(path_t::iterator it = m_path.begin(); it != m_path.end(); it++) {

        glVertex3f(it->x, it->y, it->z);
    }
    glEnd();
}

float interf(float from, float to, float inter) {
    return (to - from) * inter + from;
    
}

Vec3f interVec3f(Vec3f from, Vec3f to, float inter) {
    return Vec3f(interf(from.x, to.x, inter),
                 interf(from.y, to.y, inter),
                 interf(from.z, to.z, inter));
}

void Path::draw(float inter) {
    
    Vec3f last =  m_path.back();
    m_path.pop_back();
    
    Vec3f interLast = interVec3f( m_path.back() , last, inter);
    m_alpha = 0.4;
    
    glBegin(GL_LINE_STRIP);
    
    float curr_size = 0;
    float total_size = m_path.size();
    for(path_t::iterator it = m_path.begin(); it != m_path.end(); it++) {
        m_alpha = curr_size / total_size;
        curr_size += 1.0f;
        m_alpha = ( easeInAtan (m_alpha))*0.3 + 0.08;
        glColor4f( 1.0f, 1.0f, 1.0f, m_alpha);

        
        glVertex3f(it->x, it->y, it->z);
        
    }
    glVertex3f(interLast);
    glEnd();
    
    glPointSize(2.0f);
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
    glVertex3f(interLast);
    glEnd();
    
    m_path.push_back( last);

}
