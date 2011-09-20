//
//  Path.h
//  borwnian_motion
//
//  Created by Antoine Hersen on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include <list>
#include "cinder/gl/gl.h"


class Path {
public:
    Path();
    
    void setup();
    void draw();
    void draw(float inter);
    void add_node();
    
    ci::Vec3f last();
    ci::Vec3f get(size_t i);
    ci::Vec3f getLast(size_t i);
    
    void push_back(ci::Vec3f );
        
  
    
    float m_alpha;
    
private :
    
    typedef ci::Vec3f * path_t;
    path_t m_path;
    
    size_t last_idx;
    const size_t arr_size;
    
    void generateVBO();
    void drawVBO();
    
    std::list< GLuint > vbos;
};

// extern void glVertex3fv (const GLfloat *v);