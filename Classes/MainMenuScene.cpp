#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;

cocos2d::Scene* MainMenuScene::createScene() {
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto rootNode = CSLoader::createNode("MainScene.csb");
	
	this->addChild(rootNode, 0);

	auto sprite = CCSprite::create("sprites/72.png");
	sprite->setAnchorPoint(Point(0, 0));
	sprite->setPosition(origin.x, origin.y);
	sprite->setScale(10);
	this->addChild(sprite, 1);

	if (sprite)
	{
		CCLOG("SHADER HAS ARRIVED!");
		GLProgram * p = new GLProgram();
		p->initWithFilenames("shaders/vertex/gray.vsh", "shaders/fragment/gray.fsh");
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

		p->link();
		p->updateUniforms();		
		
		sprite->setShaderProgram(p);
		
		p->release();
		//glUseProgram(p->getProgram());
	}
	
	//this->setColor(ccc3(225, 0, 225));
	
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->setEnabled(true);
	
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		CCLOG("TOUCH EVENT HAS ARRIVED");
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, GameScene::createScene()));
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void MainMenuScene::menuCloseCallback(Ref* ref) {
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

USING_NS_CC;
