//
//  VisualAgitation.cpp
//  VisualAgitation
//
//  Created by Antoine Hersen on 8/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "VisualAgitation.h"

static const int WIDTH = 320, HEIGHT = 240;
using namespace ci;

void VisualAgitation::setup() {
    mChannel = Channel32f(WIDTH, HEIGHT );
    try {
		mCapture = Capture( WIDTH, HEIGHT );
		mCapture.start();
	}
	catch( ... ) {
        std::cout << "Failed to initialize capture" << std::endl;
	}
}

void VisualAgitation::update() {
    if( mCapture && mCapture.checkNewFrame() ) {
		Channel32f newChan(mCapture.getSurface() );
        
        Channel32f::Iter iterNew = newChan.getIter();
        Channel32f::Iter iterOld = mChannel.getIter();

        deltaSum = 0.0f;
        
        while( iterNew.line() && iterOld.line() ) {
            while( iterNew.pixel() && iterOld.pixel() ) {
                deltaSum += fabsf( iterNew.v() - iterOld.v());
            }
        }
        mChannel = newChan ;
	}
}


float VisualAgitation::agitation() {
    return deltaSum;
}