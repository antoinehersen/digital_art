#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class borwnian_motionApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void borwnian_motionApp::setup()
{
}

void borwnian_motionApp::mouseDown( MouseEvent event )
{
}

void borwnian_motionApp::update()
{
}

void borwnian_motionApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( borwnian_motionApp, RendererGl )
