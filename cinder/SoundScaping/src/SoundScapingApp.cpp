#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SoundScapingApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void SoundScapingApp::setup()
{
}

void SoundScapingApp::mouseDown( MouseEvent event )
{
}

void SoundScapingApp::update()
{
}

void SoundScapingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( SoundScapingApp, RendererGl )
