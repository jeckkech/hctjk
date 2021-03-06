#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void gameStart(cocos2d::Ref* pSender, int type);
	void gameSettings(cocos2d::Ref* pSender, int type);
	void menuCloseCallback(cocos2d::Ref* sender);

	CREATE_FUNC(MainMenuScene);
};

#endif // __MAINMENU_SCENE_H__
