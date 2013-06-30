//
//  MadBomberAppDelegate.cpp
//  MadBomber
//
//  Created by Eric Smith on 06/24/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MainGame.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  Director *pDirector = Director::sharedDirector();
  EGLView *pEGLView = EGLView::sharedOpenGLView();
  pDirector->setOpenGLView(pEGLView);

  Size screenSize = pEGLView->getFrameSize();
  Size designSize = Size(1024, 768);

  EGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);

  std::vector<std::string> searchPaths;

  if (screenSize.width > 768) {
    searchPaths.push_back("ipadhd");
    pDirector->setContentScaleFactor(screenSize.height / designSize.height);
  }
  FileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

  // turn on display FPS
  pDirector->setDisplayStats(true);

  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);

  // create a scene. it's an autorelease object
  Scene *pScene = MainGame::scene();

  // run
  pDirector->runWithScene(pScene);

  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  Director::sharedDirector()->stopAnimation();
  SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
  SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  Director::sharedDirector()->startAnimation();
  SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
  SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
