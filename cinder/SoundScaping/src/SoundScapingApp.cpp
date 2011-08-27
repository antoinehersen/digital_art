#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "cinder/app/AppBasic.h"
#include "cinder/audio/Io.h"
#include "cinder/audio/Output.h"
#include "cinder/audio/FftProcessor.h"
#include "cinder/audio/PcmBuffer.h"

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
};

void SoundScapingApp::setup() {
    //add the audio track the default audio output
	mTrack = audio::Output::addTrack( audio::load( loadResource( "../resources/drums.mp3", 129, "MP3" )));
	
	//you must enable enable PCM buffering on the track to be able to call getPcmBuffer on it later
	mTrack->enablePcmBuffering( true );
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
    glTranslatef( 0.0, 200.0, 0.0 );
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
	gl::color( Color( 1.0f, 0.5f, 0.25f ) );
	gl::draw( leftBufferLine );
	gl::draw( rightBufferLine );
	
}

void SoundScapingApp::drawFft() {
	float ht = 100.0f;
	uint16_t bandCount = 32;
	
	if( ! mPcmBuffer ) return;
	
	//use the most recent Pcm data to calculate the Fft
	std::shared_ptr<float> fftRef = audio::calculateFft( mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_LEFT ), bandCount );
	if( ! fftRef ) {
		return;
	}
	
	float * fftBuffer = fftRef.get();
	
	//draw the bands
	for( int i = 0; i < ( bandCount ); i++ ) {
		float barY = fftBuffer[i] / bandCount * ht;
		glBegin( GL_QUADS );
        glColor3f( 255.0f, 255.0f, 0.0f );
        glVertex2f( i * 3, ht );
        glVertex2f( i * 3 + 1, ht );
        glColor3f( 0.0f, 255.0f, 0.0f );
        glVertex2f( i * 3 + 1, ht - barY );
        glVertex2f( i * 3, ht - barY );
		glEnd();
	}
}


CINDER_APP_BASIC( SoundScapingApp, RendererGl )
