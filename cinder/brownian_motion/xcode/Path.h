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
    void setup();
    void draw();
    void add_node();
    
    typedef std::list<ci::Vec3f> path_t;
    path_t m_path;
};

// extern void glVertex3fv (const GLfloat *v);