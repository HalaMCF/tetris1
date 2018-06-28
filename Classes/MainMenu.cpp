#include "MainMenu.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Tetris", "fonts/Marker Felt.ttf", 36);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);


	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(24);

	MenuItemFont *Singular = MenuItemFont::create("Singular",CC_CALLBACK_1(MainMenu::menuSingular, this));
	MenuItemFont *Mutiplayer = MenuItemFont::create("Mutiplayer", CC_CALLBACK_1(MainMenu::menuMuti, this));
	MenuItemFont *Rank = MenuItemFont::create("Ranking List",CC_CALLBACK_1(MainMenu::menuRank, this));
	MenuItemFont *Exit = MenuItemFont::create("Exit",CC_CALLBACK_1(MainMenu::menuExit, this));


	Menu* menu = Menu::create(Singular,Mutiplayer,Rank, Exit, NULL);
	menu->alignItemsVertically();
	this->addChild(menu);
	return true;
}

void MainMenu::menuSingular(Ref*pSender)
{
	auto Di = Diff::createscene();
	Director::getInstance()->pushScene(Di);
}
void MainMenu::menuMuti(Ref*pSender)
{
	auto Mut = muti::createScene();
	Director::getInstance()->pushScene(Mut);
}
void MainMenu::menuRank(Ref*pSender)
{
	auto Ran = Rank::createscene();
	Director::getInstance()->pushScene(Ran);
}
void MainMenu::menuExit(Ref*pSender)
{
#if(1)
	exit(0);
#endif
}