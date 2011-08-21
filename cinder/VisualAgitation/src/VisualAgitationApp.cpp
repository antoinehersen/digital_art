#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"


#include "VisualAgitation.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class VisualAgitationApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    VisualAgitation mVisualAgitation;
};

void VisualAgitationApp::setup()
{
    mVisualAgitation.setup();
}

void VisualAgitationApp::mouseDown( MouseEvent event )
{
}

void VisualAgitationApp::update()
{
    mVisualAgitation.update();

}

void VisualAgitationApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    std::cout << mVisualAgitation.agitation() << std::endl;
    
    gl::drawSolidCircle( Vec2f(app::getWindowWidth()/2, app::getWindowHeight() /2), mVisualAgitation.agitation() /100.0f );

}


CINDER_APP_BASIC( VisualAgitationApp, RendererGl )
