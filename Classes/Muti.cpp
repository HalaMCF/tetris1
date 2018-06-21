#include"Muti.h"
#include"PauseScene.h"
USING_NS_CC;

Scene* muti::createscene()
{	
	auto scene = Scene::create();
	auto layer = muti::create();
	scene->addChild(layer);
	return scene;
}

bool muti::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	TTFConfig config("fonts/arial.ttf", 15);
	
	Sprite *bg = Sprite::create("white1.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
	this->addChild(bg);
	
	auto label1 = Label::createWithTTF("SCORE:", "fonts/arial.ttf", 15);
	label1->setColor(Color3B::BLACK);
	label1->setPosition(Vec2(visibleSize.width * 2/ 5, 410));
	this->addChild(label1, 1);
	MyScore = 0;
	auto labelScore = Label::createWithTTF(config, "0");
	labelScore->setColor(Color3B::BLACK);
	labelScore->setTag(111);
	labelScore->setPosition(Vec2(visibleSize.width * 2/ 5, 385));
	addChild(labelScore);

	auto label2 = Label::createWithTTF("SCORE:", "fonts/arial.ttf", 15);
	label2->setColor(Color3B::BLACK);
	label2->setPosition(Vec2(visibleSize.width * 10/ 11, 410));
	this->addChild(label2, 2);
	ReScore = 0;
	auto labelScore1 = Label::createWithTTF(config, "0");
	labelScore1->setColor(Color3B::BLACK);
	labelScore1->setTag(111);
	labelScore1->setPosition(Vec2(visibleSize.width * 10/11, 385));
	addChild(labelScore1);

	auto label3 = Label::createWithTTF("LEVEL:", "fonts/arial.ttf", 15);
	label3->setColor(Color3B::BLACK);
	label3->setPosition(Vec2(visibleSize.width * 2 / 5, visibleSize.height * 9 / 10));
	this->addChild(label3, 3);
	MyLevel = 1;
	auto labelLevel = Label::createWithTTF(config, StringUtils::format("%d", MyLevel));
	labelLevel->setColor(Color3B::BLACK);
	labelLevel->setTag(110);
	labelLevel->setPosition(visibleSize.width * 2 / 5, visibleSize.height * 433 / 500);
	addChild(labelLevel);
	
	auto label4 = Label::createWithTTF("LEVEL:", "fonts/arial.ttf", 15);
	label4->setColor(Color3B::BLACK);
	label4->setPosition(Vec2(visibleSize.width * 10/ 11, visibleSize.height * 9 / 10));
	this->addChild(label4, 4);
	ReLevel = 1;
	auto labelLevel1 = Label::createWithTTF(config, StringUtils::format("%d", ReLevel));
	labelLevel1->setColor(Color3B::BLACK);
	labelLevel1->setTag(110);
	labelLevel1->setPosition(visibleSize.width * 10 / 11, visibleSize.height * 433 / 500);
	addChild(labelLevel1);
	
	auto menuItemPause = MenuItemFont::create("Pause", CC_CALLBACK_1(muti::menuCallBack, this));
	menuItemPause->setColor(Color3B::BLACK);
	menuItemPause->setTag(2);

	auto menu = Menu::create(menuItemPause,  NULL);
	menu->setPosition(Vec2::ZERO);
	menuItemPause->setPosition(Vec2(visibleSize.width * 2 / 5, visibleSize.height * 1 / 10));
	addChild(menu);

	ReLine = 0, MyLine = 0;
	ReSpeed = 1, MySpeed = 1;
	return true;
}
void muti::menuCallBack(Ref* obj)
{
	auto target = (Node *)obj;
	Scene * scene = Pause::createScene();
	this->addChild(scene);
	Director::getInstance()->pause();
}
