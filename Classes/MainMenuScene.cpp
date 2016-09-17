#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "SettingsScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;

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
	rootNode->setAnchorPoint(Point(origin.x, origin.y));
	rootNode->setPosition(origin.x, origin.y);
	rootNode->setContentSize(visibleSize);

	CCLOG("ABOUT TO SCALE!");

	auto mainPageView = rootNode->getChildByName("mainPageView");
	mainPageView->setAnchorPoint(Point(origin.x, origin.y));
	mainPageView->setPosition(origin.x, origin.y);
	//mainPageView->setContentSize(visibleSize);
	mainPageView->setScaleX(visibleSize.width / mainPageView->getContentSize().width);
	mainPageView->setScaleY(visibleSize.height / mainPageView->getContentSize().height);

	auto mainBgScene = rootNode->getChildByName("bgVolcano");
	mainBgScene->setScaleX(visibleSize.width / mainBgScene->getContentSize().width);
	mainBgScene->setScaleY(visibleSize.height / mainBgScene->getContentSize().height);
	/*Vector<Node*> children = rootNode->getChildren();

	for (int i = 0; i < children.size(); i++) {
		CCLOG("%s", children.at(i)->getName().c_str());
	}*/

	ui::Helper::doLayout(rootNode);
	this->addChild(rootNode, 0);
	
	if (mainBgScene)
	{		
		CCLOG("SHADER HAS ARRIVED!");
		GLProgram * p = new GLProgram();
		p->initWithFilenames("shaders/vertex/gray.vsh", "shaders/fragment/gray.fsh");
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
		p->link();
		p->updateUniforms();		
		mainBgScene->setShaderProgram(p);
		p->release();
	}
	
	auto startButton = static_cast<cocos2d::ui::Button*>(mainPageView->getChildByName("panel1")->getChildByName("startBtn"));
	auto settingsButton = static_cast<cocos2d::ui::Text*>(mainPageView->getChildByName("panel2")->getChildByName("settingsBtn"));

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->setEnabled(true);
	
	startButton->addTouchEventListener(this, toucheventselector(MainMenuScene::gameStart));
	settingsButton->addTouchEventListener(this, toucheventselector(MainMenuScene::gameSettings));
	return true;
}

void MainMenuScene::gameStart(Ref *pSender, int type)
{
	switch (type)
	{
	case 0:
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, GameScene::createScene()));
		break;
	default:
		// TODO
		break;
	}
}

void MainMenuScene::gameSettings(Ref *pSender, int type)
{
	switch (type)
	{
	case 0:
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, SettingsScene::createScene()));
		break;
	default:
		// TODO
		break;
	}
}

void MainMenuScene::menuCloseCallback(Ref* ref) {
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

USING_NS_CC;
