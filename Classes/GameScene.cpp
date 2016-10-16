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

	auto sprite = CCSprite::create("sprites/72.png");
	sprite->setPosition3D(Vec3(visibleSize.width/2, visibleSize.height/2, 0.0));

	//this->setCameraMask((unsigned short)CameraFlag::USER2, true);
	this->addChild(sprite);
	/*auto camera = Camera::createPerspective(60, (float)visibleSize.width / visibleSize.height, 1.0, 1000);
	camera->setCameraFlag(CameraFlag::USER2);
	camera->setPosition3D(Vec3(visibleSize.width / 2, visibleSize.height / 2, 1000.0));
	camera->lookAt(sprite->getPosition3D(), Vec3(0.0, 0.0, 0.0));
	this->addChild(camera);
	*/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->setEnabled(true);
	auto followAction = Follow::create(sprite, Rect::ZERO);
	
	this->runAction(followAction);
	

	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		
		auto actionMove = MoveTo::create(1, touch->getLocation());
		sprite->runAction(actionMove);
		
		/*sprite->setPosition3D(Vec3(position.x+touch->getDelta().x, position.y+touch->getDelta().y, 0.0));
		/*camera->setPosition3D(Vec3(touch->getLocation().x, touch->getLocation().y, 10.0));
		camera->lookAt(sprite->getPosition3D(), Vec3(0.0, 0.0, 0.0));*/
		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::menuCloseCallback(Ref* ref){
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}

USING_NS_CC;
