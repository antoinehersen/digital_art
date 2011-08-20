#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/Texture.h"
#include "cinder/Channel.h"
#include "cinder/Capture.h"


#include "ParticleController.h"

#define TOTAL_PARTICLES 4800
#define RESOLUTION 14
static const int WIDTH = 640, HEIGHT = 480;


using namespace ci;
using namespace ci::app;
using namespace std;

class RasterVideoApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove(MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    Channel32f mChannel;
	gl::Texture	mTexture;
	
	ParticleController mParticleController;
	
	bool mDrawParticles;
	bool mDrawImage;
    
    Capture				mCapture;
    
    Vec2i mMouseLoc;

};

void RasterVideoApp::setup()
{
    setFullScreen(true);    

    Url url( "http://libcinder.org/media/tutorial/paris.jpg" );
	mChannel = Channel32f( loadImage( loadUrl( url ) ) );
	mTexture = mChannel;
    
	mParticleController = ParticleController( RESOLUTION );
	
	mDrawParticles = true;
	mDrawImage = false;
    
    try {
		mCapture = Capture( app::getWindowWidth(), app::getWindowHeight() );
		mCapture.start();
	}
	catch( ... ) {
		console() << "Failed to initialize capture" << std::endl;
	}
}

void RasterVideoApp::mouseDown( MouseEvent event )
{

}

void RasterVideoApp::mouseMove(MouseEvent event ) {
    mMouseLoc = event.getPos();

}

void RasterVideoApp::keyDown( KeyEvent event )
{
	if( event.getChar() == '1' ){
		mDrawImage = ! mDrawImage;
	} else if( event.getChar() == '2' ){
		mDrawParticles = ! mDrawParticles;
	}
}

void RasterVideoApp::update()
{
    if( mCapture && mCapture.checkNewFrame() ) {
		mChannel = Channel32f(mCapture.getSurface() );
	}
    
	
	mParticleController.update( mChannel, mMouseLoc );
}

void RasterVideoApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ), true ); 
    
    if( mDrawImage ){
		mTexture.enableAndBind();
		gl::draw( mTexture, getWindowBounds() );
	}
	
	if( mDrawParticles ){
		glDisable( GL_TEXTURE_2D );
		mParticleController.draw();
	}
}


CINDER_APP_BASIC( RasterVideoApp, RendererGl )
