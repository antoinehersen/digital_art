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
    void reset();
	void mouseDown( MouseEvent event );
    void mouseMove(MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    Channel32f mChannel;
	//gl::Texture	mTexture;
	
	ParticleController mParticleController;
    
    Capture				mCapture;
    
    Vec2i mMouseLoc;
    
    bool useFullScreen;
    
};

void RasterVideoApp::setup()
{
    setFullScreen(useFullScreen);    
    
    mChannel = Channel32f(app::getWindowWidth(), app::getWindowHeight() );
    
	mParticleController = ParticleController( RESOLUTION );
    
    
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
    
    if( event.getCode() == KeyEvent::KEY_f ) {
        useFullScreen = ! useFullScreen;
        reset();
	}
	else if( event.getCode() == KeyEvent::KEY_ESCAPE ) {
        useFullScreen= false;
        reset();
	} else if( event.getCode() == KeyEvent::KEY_q ) {
        mCapture.stop();
        exit(0);
    }

}

void RasterVideoApp::update()
{
    if( mCapture && mCapture.checkNewFrame() ) {
		mChannel = Channel32f(mCapture.getSurface() );
	}
    
	
	mParticleController.update( mChannel, mMouseLoc );
}

void RasterVideoApp::reset() {
    mCapture.stop();
    setup();
}

void RasterVideoApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ), true ); 
    
	
    glDisable( GL_TEXTURE_2D );
    mParticleController.draw();
}


CINDER_APP_BASIC( RasterVideoApp, RendererGl )
