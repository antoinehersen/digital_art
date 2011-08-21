#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class VisualAgitationApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void VisualAgitationApp::setup()
{
}

void VisualAgitationApp::mouseDown( MouseEvent event )
{
}

void VisualAgitationApp::update()
{
}

void VisualAgitationApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( VisualAgitationApp, RendererGl )
