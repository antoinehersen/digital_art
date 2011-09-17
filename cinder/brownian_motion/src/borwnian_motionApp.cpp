#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "cinder/Vector.h"
#include "cinder/ImageIO.h"
#include "cinder/Utilities.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"
#include "cinder/Rand.h"

#include "cinder/Easing.h"


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
    
    bool everySecond();
    float interpolate;
    Vec3f interVec3f(Vec3f from, Vec3f to);
    float interf(float from, float to);

    
    // PARAMS
	params::InterfaceGl	mParams;
	
	// CAMERA
	CameraPersp			mCam;
	Quatf				mSceneRotation;
	Vec3f				mEye, mCenter, mUp;
    Vec3f				mOldEye, mOldCenter, mOldUp;

	float				mCameraDistance;
    float upFactor;
    
    float               mLineW;
    float lastTime;
    
    Vec3f lastLast, prevPoint;
    
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
 //   setFullScreen(true);
    
	// SETUP CAMERA
	mCameraDistance = 5.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f::zero();
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 0.1f, 200000.0f );
    
    mLineW = 1.0f;
    path.m_alpha = 0.2f;
    upFactor = 2.0f;
    
    // SETUP PARAMS
	mParams = params::InterfaceGl( "Browniw", Vec2i( 200, 300 ) );
	mParams.addParam( "Scene Rotation", &mSceneRotation, "opened=1" );
	mParams.addSeparator();
	mParams.addParam( "Eye Distance", &mCameraDistance, "min=-5.0 max=20 step=0.5 keyIncr=s keyDecr=w" );
    mParams.addParam( "Alpha", &path.m_alpha, "min=0.0 max=1.0 step=0.05 keyIncr=q keyDecr=e" );
    mParams.addParam( "Line Width", &mLineW, "min=0.0 max=5.0 step=0.05 " );
    mParams.addParam( "Up Factor", &upFactor, "min=0.5 max=5.0 step=0.05 " );
    
    
    
    path.setup();
    
    path.add_node();
    
    for(int i =0 ; i< 300000; i++) {
        path.add_node();
    }
    mCenter = path.last();
    //   for(int i =0 ; i< 1000000; i++) {
    //       path.add_node();
    //       }
    for(int i =0 ; i< 10; i++) {
        
        path.add_node();
        mCenter = mEye;
        mEye =  path.last();
    }
    
    lastTime = getElapsedSeconds();
}

void borwnian_motionApp::mouseDown( MouseEvent event )
{
}

bool borwnian_motionApp::everySecond() {
    const float duration = 2.5f;
    float time = getElapsedSeconds();
    

    
    if ( time >= lastTime + duration ) {
        lastTime = time;
        interpolate = 0;
        return true;
    }
    interpolate = (time - lastTime) / duration;
    
 //   interpolate = easeInOutQuad( interpolate);
    return false;
}
float borwnian_motionApp::interf(float from, float to) {
    return (to - from) * interpolate + from;
    
}

Vec3f borwnian_motionApp::interVec3f(Vec3f from, Vec3f to) {
    return Vec3f(interf(from.x, to.x),
                interf(from.y, to.y),
                interf(from.z, to.z));
}

void borwnian_motionApp::update() {
    

    Vec3f newPoint = path.last();
    mCenter = newPoint;
    mUp = (lastLast - prevPoint).cross( newPoint - prevPoint) ;
    Vec3f s = mUp + mOldUp;
    if (fabs(s.x) < 0.01f && fabs(s.y) < 0.01f && fabs(s.z) < 0.01 ) {
        mUp = - mUp;
    }
    
    mEye =  mCameraDistance*(newPoint - prevPoint) + newPoint + mUp *upFactor;
    
    if (everySecond()) {
        lastLast = prevPoint;
        prevPoint = path.last();
        path.add_node();
        mOldCenter = mCenter;
        mOldUp = mUp;
        mOldEye = mEye;
    }
    
    // UPDATE CAMERA
    //	mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCam.lookAt( interVec3f(mOldEye,mEye),
                interVec3f(mOldCenter,mCenter),
                interVec3f(mOldUp, mUp ));

	gl::setMatrices( mCam );
 //   gl::rotate( mSceneRotation );

    
    
}

void borwnian_motionApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
    
    glLineWidth(mLineW);
    gl::color( ColorA( 1.0f, 1.0f, 1.0f, 1.0f ) );
    //	gl::drawSphere( Vec3f(1.0f, 0.0f, 0.0f), 2.0f, 8 );

    
    path.draw(interpolate);
}


CINDER_APP_BASIC( borwnian_motionApp, RendererGl )
