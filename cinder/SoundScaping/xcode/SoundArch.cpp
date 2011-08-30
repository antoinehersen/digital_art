//
//  SoundArch.cpp
//  SoundScaping
//
//  Created by Antoine Hersen on 8/29/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SoundArc.h"
#include "cinder/gl/gl.h"

#include <math.h>


void SoundArc::draw_circle(int nb_segment) {
    draw_arc(2*M_PI);
}


void SoundArc::draw_arc(float angle, int nb_segment) {
    glBegin( GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f );
    
    float step = angle / nb_segment;
    
    for( int i = 0 ; i <= nb_segment; i++) {
        float angle = step * i;
        glVertex2f(cos(angle ), sin(angle ) );
    }
    
    glEnd();
}

void SoundArc::draw_bands(float * fftBuffer, int bandCounts) {
    
    float angle = 2*M_PI / bandCounts;
    float angle_deg = angle * 180.0f / M_PI;
    
    glPushMatrix();
    for( int i = 0 ; i < bandCounts; i++ ) {
        glPushMatrix();
        glColor3f( 1.0f - 1.0f * i / bandCounts, 1.0f, 1.0f * i / bandCounts );

        float scale = fftBuffer[i];
        glScalef(scale, scale, scale);
        draw_arc(angle);    
        glPopMatrix();
        
        glRotatef( angle_deg, 0.0f, 0.0f, 1.0f);
    }
    glPopMatrix();


}