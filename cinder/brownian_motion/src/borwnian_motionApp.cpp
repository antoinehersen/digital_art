#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "cinder/Vector.h"
#include "cinder/ImageIO.h"
#include "cinder/Utilities.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"
#include "cinder/Rand.h"
#include "cinder/Font.h"

//#include "cinder/qtime/MovieWriter.h"


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
    void keyDown( KeyEvent event );
	void update();
	void draw();
    void resetScreen();

    
    bool everySecond();
    float interpolate;
    Vec3f interVec3f(Vec3f from, Vec3f to);
    float interf(float from, float to);
    
//    qtime::MovieWriter	mMovieWriter;
//    Font mFont;

    
    // PARAMS
	params::InterfaceGl	mParams;
	
	// CAMERA
    bool cameraFollow;
	CameraPersp			mCam;
	Quatf				mSceneRotation;
	Vec3f				mEye, mCenter, mUp;
    Vec3f				mOldEye, mOldCenter, mOldUp;
    
	float				mCameraDistance;
    float upFactor;
    
    float               mLineW;
    float duration;

    float lastTime;
    
    Vec3f lastLast, prevPoint, newPoint;
    
    Path path;
    
    bool useFullScreen;
};


typedef borwnian_motionApp bm;

void bm::prepareSettings( Settings *settings ){
    settings->setWindowSize( 1280, 720 );
	settings->setFrameRate( 30.0f );
}

void borwnian_motionApp::setup(){
    Rand::randomize();
    gl::enableAdditiveBlending();
    useFullScreen = true;
   setFullScreen(useFullScreen);
    
    duration = 20.0f;
    
	// SETUP CAMERA
    cameraFollow = true;
	mCameraDistance = -3.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f::zero();
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 0.1f, 200000.0f );
    
    mOldCenter = mCenter;
    mOldUp = mUp;
    mOldEye = mEye;
    
    mLineW = 1.0f;
    path.m_alpha = 0.12f;
    upFactor = 2.5f;
    
    lastLast = Vec3f(0,0,0);
    prevPoint = Vec3f(0,0,1);
    newPoint = Vec3f(0,1,1);
    
    // SETUP PARAMS
	mParams = params::InterfaceGl( "Brownian", Vec2i( 200, 300 ) );
	mParams.addParam( "Scene Rotation", &mSceneRotation, "opened=1" );
	mParams.addSeparator();
	mParams.addParam( "Eye Distance", &mCameraDistance, "min=-20.0 max=20 step=0.5" );
    mParams.addParam( "Alpha", &path.m_alpha, "min=0.0 max=1.0 step=0.05 keyIncr=q keyDecr=e" );
    mParams.addParam( "Line Width", &mLineW, "min=0.0 max=5.0 step=0.05 " );
    mParams.addParam( "Up Factor", &upFactor, "min=0.5 max=5.0 step=0.05 " );
    mParams.addParam( "Duration", &duration, "min=0.1 max=50.0 step=0.1 " );
    mParams.setOptions(""," iconified=true");;
    
 //   mFont = Font( "Arial", 12.0f );

    
    path.setup();
    
    path.add_node();
    
    for(int i =0 ; i< 200000; i++) {
        path.add_node();
    }

    
    lastTime = getElapsedSeconds() - 100 ;
    
//    
//    string path = getSaveFilePath();
//	if( path.empty() )
//		return; // user cancelled save
//    
//    
//	qtime::MovieWriter::Format format;
//	if( qtime::MovieWriter::getUserCompressionSettings( &format) ) {
//		mMovieWriter = qtime::MovieWriter( path, getWindowWidth(), getWindowHeight(), format );
//	}
}

void  borwnian_motionApp::resetScreen() {
    setFullScreen(useFullScreen);    

    mCam.setPerspective( 75.0f, getWindowAspectRatio(), 0.1f, 200000.0f );

}


void borwnian_motionApp::mouseDown( MouseEvent event )
{
    //    for(int i =0 ; i< 100; i++) {
    //        path.add_node();
    //x    }
    // path.perturbe();
}

void borwnian_motionApp::keyDown( KeyEvent event )
{
    if( event.getCode() == KeyEvent::KEY_ESCAPE ) {
        // useFullScreen= false;
        // reset();
	} else if( event.getCode() == KeyEvent::KEY_q ) {
        //     mCapture.stop();
        //    exit(0);
    }  else if( event.getCode() == KeyEvent::KEY_c ) {
        cameraFollow = !cameraFollow;
        mCenter = path.last();
        
    } else if( event.getCode() == KeyEvent::KEY_SPACE ) {
        float distance = mCameraDistance* Rand::randInt(20);
        
        mEye =  distance*(newPoint - prevPoint) + newPoint + mUp *upFactor;
        
    }  else if (event.getCode() == KeyEvent::KEY_ESCAPE ) {
        useFullScreen= false;
        resetScreen();
    } else if (event.getCode() == KeyEvent::KEY_f) {
        useFullScreen = ! useFullScreen;
    resetScreen();
    }
}

bool borwnian_motionApp::everySecond() {
    float time = getElapsedSeconds();
    
    
    
    if ( time >= lastTime + duration ) {
        lastTime = time;
        interpolate = 0;
        return true;
    }
    interpolate = (time - lastTime) / duration;
    
    interpolate = easeInOutQuad( interpolate);
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
    
    if (cameraFollow) {
        
        if (everySecond()) {
            lastLast = prevPoint;
            prevPoint = path.last();
            path.add_node();
            mOldCenter = mCenter;
            mOldUp = mUp;
            mOldEye = mEye;
            
            newPoint = path.last();
            mCenter = newPoint;
            mUp = (lastLast - prevPoint).cross( newPoint - prevPoint) ;
            Vec3f s = mUp + mOldUp;
            if (fabs(s.x) < 0.01f && fabs(s.y) < 0.01f && fabs(s.z) < 0.01 ) {
                mUp = - mUp;
            }
            float distance = mCameraDistance - Rand::randInt(15) ;
            if ( Rand::randInt(10) == 0 ) {
                distance *= Rand::randInt(20);
            }
            mEye =  distance*(newPoint - prevPoint) + newPoint + mUp *upFactor;
        }  
        
        
        mCam.lookAt( interVec3f(mOldEye,mEye),
                    interVec3f(mOldCenter,mCenter),
                    interVec3f(mOldUp, mUp ));
        
        gl::setMatrices( mCam );
    } else {
        path.add_node();
        
        mEye			= Vec3f( 0.0f, 0.0f, 50*mCameraDistance );
        //        mCenter			= Vec3f::zero();
        mUp				= Vec3f::yAxis();
        mCam.lookAt( mEye, mCenter, mUp);
        gl::setMatrices( mCam );
        gl::rotate( mSceneRotation );
    }
    
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
    
    std::cout << getAverageFps() << std::endl;


    
//    // add this frame to our movie
//	if( mMovieWriter )
//		mMovieWriter.addFrame( copyWindowSurface() );
}


CINDER_APP_BASIC( borwnian_motionApp, RendererGl )
