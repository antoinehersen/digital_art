#include <algorithm>
#include <vector>

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "cinder/app/AppBasic.h"
#include "cinder/audio/Io.h"
#include "cinder/audio/Output.h"
#include "cinder/audio/FftProcessor.h"
#include "cinder/audio/PcmBuffer.h"

#include "SoundArc.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SoundScapingApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    void drawWaveForm();
    void drawFft();
    
    audio::TrackRef mTrack;
	audio::PcmBuffer32fRef mPcmBuffer;
    
    uint16_t bandCount;
    std::vector<float> cumlFFT;

};

void SoundScapingApp::setup() {
   setFullScreen(true);
    
    //add the audio track the default audio output
	//mTrack = audio::Output::addTrack( audio::load( loadResource( "../resources/drums.mp3", 129, "MP3" )));
    mTrack = audio::Output::addTrack( audio::load( loadResource( "../resources/MakeLight.m4a", 129, "M4A" )));
	
	//you must enable enable PCM buffering on the track to be able to call getPcmBuffer on it later
	mTrack->enablePcmBuffering( true );
    
    bandCount = 50;;
    cumlFFT = std::vector<float>(bandCount, 0.0f);

}

void SoundScapingApp::mouseDown( MouseEvent event ) {
}

void SoundScapingApp::update() {
    //get the latest pcm buffer from the track
	mPcmBuffer = mTrack->getPcmBuffer();
}

void SoundScapingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
	
	glPushMatrix();
    glTranslatef( 0.0, 0.0, 0.0 );
    drawWaveForm();
    glTranslatef( 0.0, 400.0, 0.0 );
    drawFft();
	glPopMatrix();
    
}

void SoundScapingApp::drawWaveForm() {	
	//if the buffer is null, for example if this gets called before any PCM data has been buffered
	//don't do anything
	if( ! mPcmBuffer ) {
		return;
	}
	
	uint32_t bufferLength = mPcmBuffer->getSampleCount();
	audio::Buffer32fRef leftBuffer = mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_LEFT );
	audio::Buffer32fRef rightBuffer = mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_RIGHT );
    
	int displaySize = getWindowWidth();
	float scale = displaySize / (float)bufferLength;
	
	PolyLine<Vec2f>	leftBufferLine;
	PolyLine<Vec2f>	rightBufferLine;
	
	for( int i = 0; i < bufferLength; i++ ) {
		float x = ( i * scale );
        
		//get the PCM value from the left channel buffer
		float y = ( ( leftBuffer->mData[i] - 1 ) * - 100 );
		leftBufferLine.push_back( Vec2f( x , y) );
		
		y = ( ( rightBuffer->mData[i] - 1 ) * - 100 );
		rightBufferLine.push_back( Vec2f( x , y) );
	}
	gl::color( Color( 0.0f, 0.5f, 1.0f ) );
	gl::draw( leftBufferLine );
	gl::draw( rightBufferLine );
	
}

void SoundScapingApp::drawFft() {
	float ht = 200.0f;
	
	if( ! mPcmBuffer ) return;
	
	//use the most recent Pcm data to calculate the Fft
	std::shared_ptr<float> fftRef = audio::calculateFft( mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_LEFT ), bandCount * 2);
	if( ! fftRef ) {
        std::cout << "Pb with fft" << std::endl;
		return;
	}
	
	float * fftBuffer = fftRef.get();
    
    float maxBand = *max_element(cumlFFT.begin() ,cumlFFT.end() );

	float width = 6.0;
	//draw the bands
	for( int i = 0; i < ( bandCount ); i++ ) {
		float barY = (fftBuffer[i] / bandCount) * ht;

		glBegin( GL_QUADS );
        glColor3f( 255.0f, 255.0f, 0.0f );
        glVertex2f( i * width - 1, ht );
        glVertex2f( i * width , ht );
        glColor3f( 0.0f, 255.0f, 0.0f );
        glVertex2f( i * width , ht - barY );
        glVertex2f( i * width - 1, ht - barY );
		glEnd();
        
        barY = ( cumlFFT[i] += barY ) / maxBand ;
        barY *= ht;
        glPushMatrix();

        glTranslatef( 0.0, 10.0, 0.0 );


        
        glBegin( GL_QUADS );
        glColor3f( 255.0f, 0.0f, 0.0f );

        glVertex2f( i * width, ht );
        glVertex2f( i * width + 1, ht );
        glColor3f( 255.0f, 255.0f, 0.0f );

        glVertex2f( i * width + 1,ht + barY );
        glVertex2f( i * width, ht + barY );
		glEnd();
        glPopMatrix();
        
        cumlFFT[i] *= 0.99;

	}
    glPushMatrix();
    glTranslatef(600.0f, 0.0f, 0.0f);
    
    float scale = 300.0f / maxBand;
    glScalef(scale, scale, scale);
    
    SoundArc::draw_bands( &cumlFFT[0],  bandCount /2 );

    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(800.0f, 200.0f, 0.0f);
    
    float scale2 = 600.0f / bandCount;
    glScalef(scale2, scale2, scale2);
    
    SoundArc::draw_bands( fftBuffer,  bandCount /2 );
    
    glPopMatrix();

}


CINDER_APP_BASIC( SoundScapingApp, RendererGl )
