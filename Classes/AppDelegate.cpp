#include "AppDelegate.h"
#include "MainMenu.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() 
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) 
	{
        glview = GLViewImpl::createWithRect("Tetris", Rect(0, 0,578, 500));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(578, 500, ResolutionPolicy::SHOW_ALL);

    director->setDisplayStats(false);

    director->setAnimationInterval(1.0/ 60);

    FileUtils::getInstance()->addSearchPath("images");
	FileUtils::getInstance()->addSearchPath("fonts");

    auto scene = MainMenu::createScene();

    director->runWithScene(scene);
	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
