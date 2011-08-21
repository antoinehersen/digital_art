//
//  VisualAgitation.h
//  VisualAgitation
//
//  Created by Antoine Hersen on 8/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "cinder/Channel.h"
#include "cinder/Capture.h"


class VisualAgitation {
public:
    void setup();
    void update();
    float agitation();
    
private:
    ci::Channel32f mChannel;
    ci::Capture	   mCapture;
    
    float deltaSum;
};


