#pragma once
#include <Framework.h>
#include "Doodle.h"
#include "Monster.h"
#include "Platform.h"
#include "Bullet.h"
#include "UI.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

int windowHeight{ 800 }, windowWidth{ 600 };

class MyFramework : public Framework 
{
	Sprite* background;
	Sprite* topScore;
	Sprite* endGame;
	Doodle* doodle;
	Platform* platform;
	Monster* monster;
	UI* ui;

	std::vector<Platform*> platforms;
	std::vector<Bullet*> bullets;
	std::vector<Monster*> monsterVec;

	int score = 0.f;
	int mouseX, mouseY;
	bool monsterIsExist = false;

	int TimeMonsterSpawn = 1000;
	int numberOfPlatforms = 0;

	bool gameOver = false, restartGame = false, game = true;

public:

	void SetWindowSize(int width, int height) 
	{
		windowHeight = height;
		windowWidth = width;
	}

	template <typename T>
	void MonsterCheck(T obj)
	{
		if (monsterIsExist)
		{
			monster->Update();
			monster->CheckCollision(obj);
			if (!monsterVec.empty() && monster->IsDead() == true)
			{
				monsterVec.erase(monsterVec.begin());
				monsterIsExist = false;
				if(!bullets.empty())
				{ 
					bullets.erase(bullets.begin());
				}
			}
		}
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		height = windowHeight;
		width = windowWidth;
		fullscreen = false;
	}

	virtual bool Init() 
	{
		int x, y{windowHeight};
		background = createSprite("../2022_win64/data/bck@2x.png");			// Init background
		setSpriteSize(background, windowWidth, windowHeight);

		topScore = createSprite("../2022_win64/data/top_score.png");		// Init background for UI
		setSpriteSize(topScore, windowWidth * 2, 75);

		endGame = createSprite("../2022_win64/data/endscr.png");			// EndGame Sprite

		ui = new UI(0, 0);
		
		showCursor(true);
		doodle = new Doodle(windowWidth / 2, windowHeight / 2); // create DoodlePlayer at center of the screen

		for (int i = 0; i < 15; i++)
		{
			x = rand() % (windowWidth - 100);
			y -= rand() % 200;
			platform = new Platform(x, y);
			platforms.push_back(platform);
		}

		return true;
	}

	void Close() 
	{

	}

	virtual bool Tick() {

		if (gameOver)								// Game over state
		{
			game = false;
			drawSprite(endGame,-20,0);
		}
		if (restartGame)							// Restart game state
		{
			int x, y{ windowHeight };
			game = true;
			gameOver = false;

			score = 0;								// Update score
			doodle->Reset();						// Doodle reset

			platforms.clear();						// Reset platforms
			for (int i = 0; i < 15; i++)
			{
				x = rand() % (windowWidth - 100);
				y -= rand() % 200;
				platform = new Platform(x, y);
				platforms.push_back(platform);
			}

			bullets.clear();						//Reset bullets

			monsterVec.clear();						// Reset monsters
			monsterIsExist = false;
			TimeMonsterSpawn = 1000;

			numberOfPlatforms = 0;

			restartGame = false;	
		}
		if (game)
		{
			float x, y;

			drawSprite(background, 0, 0);			// draw background

			for (int i = 0; i < 15; i++)			// draw platforms
			{
				platforms[i]->Draw();
			}

			doodle->Draw();							// draw doodle
			doodle->Update();						// functionality for doodle
			doodle->CheckCollision(platforms);		// if doodle collide with platforms


			if (doodle->GetY() <= doodle->GetHighestDoodlePoint())			// Camera settings
			{
				for (auto& p : platforms)
				{
					p->SetY(p->GetY() + abs(doodle->GetVelocity()));		// Changing platforms position

					if (p->GetY() > windowHeight)
					{
						x = (rand() % (windowWidth - 100));
						y = -windowHeight / 5.0;
						p->SetX(x);
						p->SetY(y);

						if (getTickCount() >= TimeMonsterSpawn && monsterIsExist == false)	// Spawn monsters
						{
							monsterIsExist = true;
							TimeMonsterSpawn += TimeMonsterSpawn;
							monster = new Monster(p->GetX(), p->GetY());
							monsterVec.push_back(monster);
							monster->AttachPlatform(p);
						}
					}
				}
				score += ((doodle->GetHighestDoodlePoint() - doodle->GetY()));				// Scoring distance in abstract units
				doodle->SetY(doodle->GetHighestDoodlePoint());
			}

			for (auto& b : bullets)
			{
				b->Update();
				b->Draw();
				MonsterCheck(b);

				if (b->GetIsOutOfScreen() == true)
				{
					bullets.erase(bullets.begin());
				}
			}

			MonsterCheck(doodle);

			for (auto& p : platforms)
			{
				p->Update();
				numberOfPlatforms++;
			}

			drawSprite(topScore, 0, 0);
			ui->DrawUI(score, numberOfPlatforms, doodle->GetLifes());

			numberOfPlatforms = 0;

			if (doodle->GetIsDead() == true)
			{
				gameOver = true;
			}
		}

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{
		mouseX = x;
		mouseY = y;
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased)
	{
		if (button == FRMouseButton::LEFT && !isReleased)
		{
			doodle->Fire(bullets, mouseX, mouseY);
		}
		if (button == FRMouseButton::RIGHT && !isReleased)
		{
			if(doodle->GetIsShield() == false)
			{
				doodle->ActivateShield(getTickCount());
			}
		}
	}

	virtual void onKeyPressed(FRKey k) {

		switch (k) 
		{
		case FRKey::LEFT:
			doodle->StartMovingLeft();
			break;
		case FRKey::RIGHT:
			doodle->StartMovingRight();
			break;
		case FRKey::UP:
			if (gameOver)
			{
				restartGame = true;
			}
			break;
		}

	}

	virtual void onKeyReleased(FRKey k) 
	{
		switch (k) {
		case FRKey::LEFT:
			doodle->StopMovingLeft();
			break;
		case FRKey::RIGHT:
			doodle->StopMovingRight();
			break;
		}
	}

	virtual const char* GetTitle() override
	{
		return "Doodle Jump Game";
	}

	~MyFramework()
	{
		delete background, topScore, endGame, doodle, platform, monster, ui;

		for (auto& p : platforms)
		{
			delete p;
		}
		for (auto& b : bullets)
		{
			delete b;
		}
		for (auto& m : monsterVec)
		{
			delete m;
		}
	}
};

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned>(time(nullptr)));

	std::cout << "Doodle Jump Game" << std::endl;
	std::cout << std::endl;
	std::cout << "Controls:" << std::endl;
	std::cout << "Move Left - <--" << std::endl;
	std::cout << "Move Right - -->" << std::endl;
	std::cout << "Shoot - LMB" << std::endl;
	std::cout << "Shield - RMB" << std::endl;
	std::cout << std::endl;
	std::cout << "UI: Score, Number of platforms, Lifes" << std::endl;

	MyFramework* FrameWork = new MyFramework;

	//Command-line window change size
	if (argc == 4 && std::string(argv[1]) == "-window") {
		FrameWork->SetWindowSize(std::stoi(argv[3]), std::stoi(argv[4]));
	}

	return run(FrameWork);
}
