#include"Rank.h"
#include"MainMenu.h"
#include"Singular.h"
USING_NS_CC;
int score1, score2, score3;
Scene* Rank::createscene()
{
	auto scene = Scene::create();
	auto layer = Rank::create();
	scene->addChild(layer);
	return scene;
}

bool Rank::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TTFConfig config("fonts/arial.ttf", 20);

	auto label = Label::createWithTTF("Ranking List", "fonts/Marker Felt.ttf", 36);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto label2= Label::createWithTTF("1:", "fonts/Marker Felt.ttf", 20);
	label2->setPosition(Vec2(visibleSize.width*100/289,350));
	this->addChild(label2, 2);
	auto labelScore1 = Label::createWithTTF(config, StringUtils::format("%d", score1));
	labelScore1->setTag(111);
	labelScore1->setPosition(Vec2(visibleSize.width*130/289, 350));
	addChild(labelScore1);

	auto label3 = Label::createWithTTF("2:", "fonts/Marker Felt.ttf", 20);
	label3->setPosition(Vec2(visibleSize.width * 100 / 289, 300));
	this->addChild(label3, 3);
	auto labelScore2 = Label::createWithTTF(config, StringUtils::format("%d", score2));
	labelScore2->setTag(110);
	labelScore2->setPosition(Vec2(visibleSize.width * 130 / 289, 300));
	addChild(labelScore2);

	auto label4 = Label::createWithTTF("3:", "fonts/Marker Felt.ttf", 20);
	label4->setPosition(Vec2(visibleSize.width * 100 / 289, 250));
	this->addChild(label4, 4);	
	auto labelScore3 = Label::createWithTTF(config, StringUtils::format("%d", score3));
	labelScore3->setTag(109);
	labelScore3->setPosition(Vec2(visibleSize.width * 130 / 289, 250));
	addChild(labelScore3);

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(36);

	MenuItemFont *Back = MenuItemFont::create("Back",
		CC_CALLBACK_1(Rank::menuCallBack, this)
	);
	
	Menu* menu = Menu::create(Back ,NULL);
	menu->setPosition(Vec2(visibleSize.width * 143 / 289, 200));
	this->addChild(menu);
	return true;
}

void Rank::menuCallBack(Ref* obj)
{
	auto menu = MainMenu::createScene();
	Director::getInstance()->pushScene(menu);
}
