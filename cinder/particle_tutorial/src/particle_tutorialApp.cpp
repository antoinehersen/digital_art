#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class particle_tutorialApp : public AppBasic {
  public:
//    particle_tutorialApp();
    
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    ParticleController particles;
    
};



void particle_tutorialApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 800, 600 );
//	settings->setFrameRate( 60.0f );
}


void particle_tutorialApp::setup()
{
 // setFullScreen(true);    
    particles = ParticleController(10);
//    particles.addParticles( 1000);
    
}

void particle_tutorialApp::mouseDown( MouseEvent event )
{
}

void particle_tutorialApp::keyDown( KeyEvent event )
{
	if( event.getCode() == KeyEvent::KEY_f ) {
		setFullScreen( ! isFullScreen() );
	}
	else if( event.getCode() == KeyEvent::KEY_ESCAPE ) {
		setFullScreen( false );
	}
}

void particle_tutorialApp::update()
{
    particles.update();
}


void particle_tutorialApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    particles.draw();
    
//    std::cout << getElapsedSeconds() << std::endl;

}


CINDER_APP_BASIC( particle_tutorialApp, RendererGl )
