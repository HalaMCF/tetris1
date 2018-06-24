#include"Level.h"
#include"Singular.h"
USING_NS_CC;
using namespace cocos2d::ui;
Scene* Diff::createscene()
{
	auto scene = Scene::create();
	auto layer = Diff::create();
	scene->addChild(layer);
	return scene;
}

bool Diff::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TTFConfig config("fonts/arial.ttf", 30);

	auto label = Label::createWithTTF("Level(1-10)", "fonts/arial.ttf", 36);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);
	
	auto label5 = Label::createWithTTF("D:+,A:-", "fonts/arial.ttf", 36);
	label5->setPosition(Vec2(visibleSize.width / 2,400));
	this->addChild(label5, 2);
	l = 1;
	auto label2 = Label::createWithTTF(config, "1");
	label2->setTag(111);
	label2->setPosition(Vec2(visibleSize.width / 2, 300));
	addChild(label2);
	
	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(36);

	MenuItemFont *Ok = MenuItemFont::create("Ok",CC_CALLBACK_1(Diff::Singular, this));
	Menu* menu = Menu::create(Ok, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, 200));
	this->addChild(menu);

	listener = EventListenerKeyboard::create();

	level = 1;
	listener->onKeyPressed = [&](EventKeyboard::KeyCode k, Event * e) 
	{
		if (k == EventKeyboard::KeyCode::KEY_D)
		{
			l++;
			if (l >= 1 && l <= 10)
			{
				level = l;
				Label* label3 = (Label*)this->getChildByTag(111);
				label3->setString(StringUtils::format("%d", l));
			}
			else if(l>10)
			{
				auto warn= Label::createWithTTF("NO MORE THAN 10 ", "fonts/arial.ttf", 50);
				warn->setColor(Color3B::RED);
				warn->setPosition(Vec2(293, 250));
				this->addChild(warn, 3);

				auto OK = MenuItemFont::create("OK", CC_CALLBACK_1(Diff::OK, this));
				OK->setColor(Color3B::RED);
				auto menu1 = Menu::create(OK, NULL);
				menu1->setPosition(Vec2::ZERO);
				OK->setPosition(Vec2(293, 150));

				addChild(menu1);
			}
		}
		else if (k == EventKeyboard::KeyCode::KEY_A)
		{
			if (l >= 1 && l <= 10)
			{
				l--;
				level = l;
				Label* label4 = (Label*)this->getChildByTag(111);
				label4->setString(StringUtils::format("%d", l));
			}
		}
	};
				
	

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}
void Diff::OK(Ref*obj)
{
	Scene * scene= Diff::createscene();
	Director::getInstance()->replaceScene(scene);
}
void Diff::Singular(Ref*obj)
{
	auto Sin = Sin::createScene();
	Director::getInstance()->pushScene(Sin);
}