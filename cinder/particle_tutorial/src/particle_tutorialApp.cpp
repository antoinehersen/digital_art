#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class particle_tutorialApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void particle_tutorialApp::setup()
{
}

void particle_tutorialApp::mouseDown( MouseEvent event )
{
}

void particle_tutorialApp::update()
{
}

void particle_tutorialApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( particle_tutorialApp, RendererGl )
