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

Path::Path():
    arr_size(50000),
    last_idx(-1) {
    m_path = (Vec3f *) malloc(sizeof(Vec3f) * arr_size);
    
}

ci::Vec3f Path::get(size_t i) {
    size_t id = i % arr_size;
  //  id = (id < 0) ? - id : id;
    return m_path[ id];
}
ci::Vec3f Path::getLast(size_t i) {
   return get( last_idx - i);
}
ci::Vec3f Path::last() {
    return getLast(0);
}


void Path::push_back(ci::Vec3f v ) {
    last_idx ++;
    if (last_idx == arr_size) {
        generateVBO();
        last_idx = 0;
    }
    m_path[last_idx] = v;
}

//void generateVBO();
//void drawVBO();
//
//std::list< GLuint > vbos;


void Path::generateVBO() {
    
    ///// Vertex
    GLuint posBufferName;
    
    // Create a vertex buffer object (VBO) to store positions
    glGenBuffers(1, &posBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, posBufferName);
    
    vbos.push_back(posBufferName);
    
    // Allocate and load position data into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f) * arr_size, m_path, GL_STATIC_DRAW);
    
//    std::cout << posBufferName << ' '  << sizeof(Vec3f) * arr_size << std::endl;
    
}

void Path::drawVBO() {
    for(std::list<GLuint>::iterator it = vbos.begin() ; it != vbos.end(); it ++) {
        glBindBuffer(GL_ARRAY_BUFFER, *it);
        glEnableClientState(GL_VERTEX_ARRAY);             // activate vertex coords array
        glVertexPointer(3, GL_FLOAT, 0, 0); 
        glDrawArrays(GL_LINE_STRIP, 0, arr_size);

    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}


Vec3f addNoise(Vec3f v) {
    const float noise = 0.02;
    float x = v.x + Rand::randFloat( -noise, noise);
    float y = v.y + Rand::randFloat( -noise, noise);
    float z = v.z + Rand::randFloat( -noise, noise);
    return Vec3f(x,y,z);
}


void Path::setup() {
    push_back( ci::Vec3f::zero());
    push_back( ci::Vec3f(1.0f, 0.0f, 0.0f));
    
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

    Vec3f last_v =  last();
    Vec3f before_last =getLast(1);
    
    Vec3f dir = last_v - before_last;    
    Vec3f new_point;
    
    if( dir.x < -0.1f || dir.x > 0.1f ) {
        new_point = last_v + Vec3f(0.0f, new_dir.x, new_dir.y);
    } else if( dir.y < -0.1f || dir.y > 0.1f ) {
        new_point = last_v + Vec3f(new_dir.x, 0.0f, new_dir.y);
    } else if( dir.z < -0.1f || dir.z > 0.1f ) {
        new_point = last_v + Vec3f(new_dir.x, new_dir.y, 0.0f);
    }
 //   new_point = addNoise(new_point);
    push_back(new_point);
    
}





void Path::draw() {

    glBegin(GL_LINE_STRIP);
    glColor4f( 1.0f, 1.0f, 1.0f, m_alpha);

    for(size_t it = 0; it != last_idx ; it++) {
        Vec3f v = m_path[it];
        glVertex3f(v.x, v.y, v.z);
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
    
    Vec3f interLast = interVec3f( getLast(1) , last(), inter);
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_MULTISAMPLE_ARB );
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST); 
    
    glColor4f( 1.0f, 1.0f, 1.0f, m_alpha);

    drawVBO();
    glColor4f( 1.0f, 1.0f, 1.0f, m_alpha + 0.1f);

    glBegin(GL_LINE_STRIP);
    
//    float curr_size = 0;
//    float total_size = m_path.size();
    

    
    for(size_t it = 0; it < last_idx; it++) {
//        float alpha = curr_size / total_size;
//        curr_size += 1.0f;
//        alpha = ( easeInAtan (alpha))*m_alpha + 0.08;
//        glColor4f( 1.0f, 1.0f, 1.0f, alpha);

        Vec3f v = m_path[it];
        glVertex3f(v.x, v.y, v.z);
        
    }
    glColor4f( 1.0f, 1.0f, 1.0f, 0.8f);

    glVertex3f(interLast);
    glEnd();
    
    glPointSize(3.0f);
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
    glVertex3f(interLast);
    glEnd();
    

}
