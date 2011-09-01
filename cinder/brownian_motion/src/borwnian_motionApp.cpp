#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "cinder/Vector.h"
#include "cinder/ImageIO.h"
#include "cinder/Utilities.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"
#include "cinder/Rand.h"

#include "Path.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class borwnian_motionApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    // PARAMS
	params::InterfaceGl	mParams;
	
	// CAMERA
	CameraPersp			mCam;
	Quatf				mSceneRotation;
	Vec3f				mEye, mCenter, mUp;
	float				mCameraDistance;
    
    Path path;
};


typedef borwnian_motionApp bm;

void bm::prepareSettings( Settings *settings ){
    settings->setWindowSize( 1280, 720 );
	settings->setFrameRate( 60.0f );
}

void borwnian_motionApp::setup(){
    Rand::randomize();
    gl::enableAdditiveBlending();
    setFullScreen(true);
    
	// SETUP CAMERA
	mCameraDistance = 1500.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f::zero();
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 200000.0f );
    
    // SETUP PARAMS
	mParams = params::InterfaceGl( "Flocking", Vec2i( 200, 300 ) );
	mParams.addParam( "Scene Rotation", &mSceneRotation, "opened=1" );
	mParams.addSeparator();
	mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w" );
    
    path.setup();
}

void borwnian_motionApp::mouseDown( MouseEvent event )
{
}

void borwnian_motionApp::update() {
    // UPDATE CAMERA
	mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCam.lookAt( mEye, mCenter, mUp );
	gl::setMatrices( mCam );
	gl::rotate( mSceneRotation );
    
    path.add_node();
    
    for(int i =0 ; i< 1000; i++) {
        path.add_node();
    }
}

void borwnian_motionApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
    
    gl::color( ColorA( 1.0f, 1.0f, 1.0f, 1.0f ) );
    //	gl::drawSphere( Vec3f(1.0f, 0.0f, 0.0f), 2.0f, 8 );
    
    path.draw();
}


CINDER_APP_BASIC( borwnian_motionApp, RendererGl )
