#include "MainMenu.h"
#include "Remote.h"
#include <algorithm>
USING_NS_CC;
using namespace std;
Scene* Net::createScene()
{
	auto scene = Scene::create();
	auto layer = Net::create();
	scene->addChild(layer);
	return scene;
}

bool Net::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Sprite *bg = Sprite::create("white.png");
	bg->setAnchorPoint(Vec2::ZERO);
	bg->setPosition(Vec2::ZERO);
	this->addChild(bg);

	TTFConfig config("fonts/arial.ttf", 15);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto label = Label::createWithTTF("W:Turn tetris", "fonts/arial.ttf", 15);
	label->setColor(Color3B::BLACK);
	label->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 33 / 50));
	this->addChild(label, 1);

	auto label1 = Label::createWithTTF("S:Accelerate", "fonts/arial.ttf", 15);
	label1->setColor(Color3B::BLACK);
	label1->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 37 / 50));
	this->addChild(label1, 2);

	auto label2 = Label::createWithTTF("SCORE:", "fonts/arial.ttf", 15);
	label2->setColor(Color3B::BLACK);
	label2->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 41 / 50));
	this->addChild(label2, 3);
	score = 0;
	auto labelScore = Label::createWithTTF(config, "0");
	labelScore->setColor(Color3B::BLACK);
	labelScore->setTag(111);
	labelScore->setPosition(Vec2(visibleSize.width * 4 / 5, 385));
	addChild(labelScore);

	auto label3 = Label::createWithTTF("LEVEL:", "fonts/arial.ttf", 15);
	label3->setColor(Color3B::BLACK);
	label3->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 9 / 10));
	this->addChild(label3, 4);
	level = 1;
	auto labelLevel = Label::createWithTTF(config, StringUtils::format("%d", level));
	labelLevel->setColor(Color3B::BLACK);
	labelLevel->setTag(110);
	labelLevel->setPosition(visibleSize.width * 4 / 5, visibleSize.height * 433 / 500);
	addChild(labelLevel);

	auto label4 = Label::createWithTTF("A:Towards left", "fonts/arial.ttf", 15);
	label4->setColor(Color3B::BLACK);
	label4->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 29 / 50));
	this->addChild(label4, 5);

	auto label5 = Label::createWithTTF("D:Towards right", "fonts/arial.ttf", 15);
	label5->setColor(Color3B::BLACK);
	label5->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 1 / 2));
	this->addChild(label5, 6);

	auto label7 = Label::createWithTTF("NextTetris", "fonts/arial.ttf", 15);
	label7->setColor(Color3B::BLACK);
	label7->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 17 / 50));
	this->addChild(label7, 8);

	speed = 1.0f;
	
	line = 0;

	listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [&](EventKeyboard::KeyCode k, Event * e)
	{
		if (CurShape)
		{
			switch (k)
			{
			case EventKeyboard::KeyCode::KEY_A:
				Left();
				break;
			case EventKeyboard::KeyCode::KEY_D:
				Right();
				break;
			case EventKeyboard::KeyCode::KEY_W:
				TurnShape();
				break;
			case EventKeyboard::KeyCode::KEY_S:
				TowardsDown();
				break;
			default:
				break;
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);




	SetNext();
	scheduleOnce(schedule_selector(Net::PushNext), 0.1f);

	return true;
}


void Net::SetNext()
{
	srand(time(NULL));
	int type = rand() % 7;

	auto s = Shape::create(type);
	s->setPosition(Vec2(430, 100));
	addChild(s);

	NextShape = s;
}


void Net::PushNext(float t)
{
	CurShape = NextShape;
	CurShape->setPosition(BLOCK_SIZE * Vec2(5, 30));
	CurShape->SetRow(5);
	CurShape->SetCol(30);

	SetNext();

	if (isGameOver())
	{
		gameOver();
		return;
	}

	log("%f", speed);
	schedule(schedule_selector(Net::Down), speed);
}

void Net::Down(float t)
{
	if (checkBorder(1))
	{
		CurShape->Down();
	}
	else
	{
		unschedule(schedule_selector(Net::Down));
		SetMap();
		int num = CalClearNum();
		if (num > 0)
		{
			BlockClear();
			AddScore(num);
		}
		scheduleOnce(schedule_selector(Net::PushNext), 0.1f);
	}
}

void Net::Left()
{
	if (checkBorder(2))
	{
		CurShape->Left();
	}
}

void Net::Right()
{
	if (checkBorder(3))
	{
		CurShape->Right();
	}
}

void Net::TowardsDown()
{
	unschedule(schedule_selector(Net::Down));
	schedule(schedule_selector(Net::Down), 0.0f);
}

void Net::TurnShape()
{
	if (CurShape->CanTurn())
	{
		CurShape->TurnShape();
	}
}

bool Net::checkBorder(int type)
{
	auto blocks = CurShape->GetBlocks();
	int fx = CurShape->GetRow();
	int fy = CurShape->GetCol();

	for (auto b : blocks)
	{
		int x = b->GetRow();
		int y = b->GetCol();

		switch (type)
		{
		case 1:
			if (fy + y - 1 < 0 || map[fx + x - 1][fy + y - 1])
				return false;
			break;
		case 2:
			if (fx + x - 1 < 1 || map[fx + x - 2][fy + y])
				return false;
			break;
		case 3:
			if (fx + x + 1 > BOARD_WIDTH || map[fx + x][fy + y])
				return false;
			break;
		case 4:
			if (fy + y - 1 < 0 || map[fx + x - 1][fy + y - 1])
				return false;
			break;
		default:
			break;
		}
	}

	return true;
}

void Net::SetMap()
{
	auto shape_blocks = CurShape->GetBlocks();
	int fx = CurShape->GetRow();
	int fy = CurShape->GetCol();

	for (auto b : shape_blocks)
	{
		int x = b->GetRow();
		int y = b->GetCol();

		map[fx + x - 1][fy + y] = 1;

		auto new_b = Block::create();
		new_b->SetBlockType(b->GetBlockType());
		new_b->setPosition(BLOCK_SIZE * Vec2(fx + x, fy + y));
		new_b->SetRow(fx + x);
		new_b->SetCol(fy + y);
		this->addChild(new_b);
		blocks.pushBack(new_b);
	}

	CurShape->removeFromParent();
	CurShape = nullptr;
}

int Net::CalClearNum()
{
	for (int j = 0; j <BOARD_HEIGHT; ++j)
	{
		bool flag = true;
		for (int i = 0; i <BOARD_WIDTH; ++i)
		{
			if (!map[i][j])
			{
				flag = false;
				break;
			}
		}

		if (flag)
		{
			clearlines.push_back(j);
		}
	}

	return clearlines.size();
}

void Net::BlockClear()
{
	for (int t = 0; t != clearlines.size(); ++t)
	{
		int j = clearlines.at(t);
		for (int i = 0; i != blocks.size();)
		{
			Block* b = blocks.at(i);
			if (b->GetCol() == j)
			{
				b->removeFromParent();
				blocks.erase(i);
			}
			else
			{
				i++;
			}
		}

		for (int i = 0; i != blocks.size(); ++i)
		{
			Block* b = blocks.at(i);
			if (b->GetCol() > j)
			{
				int x = b->GetRow();
				int y = b->GetCol();
				b->setPosition(BLOCK_SIZE * Vec2(x, y - 1));
				b->SetCol(y - 1);
			}
		}

		for (int k = j; k != BOARD_HEIGHT - 1; ++k)
		{
			for (int i = 0; i < BOARD_WIDTH; ++i)
			{
				map[i][k] = map[i][k + 1];
			}
		}
		for (int i = 0; i != BOARD_WIDTH; ++i)
		{
			map[i][BOARD_HEIGHT - 1] = 0;
		}

		for (int k = t + 1; k != clearlines.size(); ++k)
		{
			if (clearlines.at(k) > j)
			{
				clearlines[k]--;
			}
		}
	}

	clearlines.clear();
}

void Net::AddScore(int num)
{
	switch (num)
	{
	case 1:
		score += 20 * (level + 1);
		break;
	case 2:
		score += 60 * (level + 1);
		break;
	case 3:
		score += 150 * (level + 1);
		break;
	case 4:
		score += 400 * (level + 1);
		break;
	default:
		break;
	}

	Label* label = (Label*)this->getChildByTag(111);
	label->setString(StringUtils::format("%d", score));

	line += num;
	if (line / 10 >= level && line / 10 < 10)
	{
		level++;
	}

	label = (Label*)this->getChildByTag(110);
	label->setString(StringUtils::format("%d", level));

	switch (level)
	{
	case 1:
		speed = 1.0f;
		break;
	case 2:
		speed = 0.8f;
		break;
	case 3:
		speed = 0.6f;
		break;
	case 4:
		speed = 0.4f;
		break;
	case 5:
		speed = 0.2f;
		break;
	case 6:
		speed = 0.1f;
		break;
	case 7:
		speed = 0.05f;
		break;
	case 8:
		speed = 0.01f;
		break;
	case 9:
		speed = 0.005f;
		break;
	case 10:
		speed = 0.0001f;
		break;
	default:
		break;
	}
}

bool Net::isGameOver()
{
	int fx = CurShape->GetRow();
	int fy = CurShape->GetCol();
	int i = 0;
	auto bs = CurShape->GetBlocks();

	for (auto b : bs)
	{
		int x = b->GetRow();
		int y = b->GetCol();

		if (map[fx + x - 1][fy + y])
		{
			return true;
		}
	}
	return false;
}

void Net::gameOver()
{

	if (i == 2)
	{
		auto label = Label::createWithTTF("You win", "fonts/arial.ttf", 50);
		label->setColor(Color3B::RED);
		label->setPosition(Vec2(250, 250));
		this->addChild(label);
	}

	this->unscheduleAllSelectors();
	_eventDispatcher->removeEventListener(listener);
}


