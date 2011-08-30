//
//  SoundArc.h
//  SoundScaping
//
//  Created by Antoine Hersen on 8/29/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

class SoundArc {
public:
    static void draw_circle(int nb_segment = 40);
    static void draw_arc(float angle, int nb_segment = 40);

    static void draw_bands(float * fftBuffer, int bandCounts);

};