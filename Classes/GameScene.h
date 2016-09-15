#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::LayerColor
{
public: 
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* sender);

	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
