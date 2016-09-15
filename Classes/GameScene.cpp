#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

cocos2d::Scene* GameScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init() {
	if( !Layer::init() || !LayerColor::initWithColor(Color4B(225, 0, 225, 225))){
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setColor(ccc3(225, 0, 225));
}

void GameScene::menuCloseCallback(Ref* ref){
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}

USING_NS_CC;
