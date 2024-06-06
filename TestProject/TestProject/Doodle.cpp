#include "Doodle.h"
#include <iostream>

static const int EDGE = -50;

Doodle::Doodle(float x, float y) : Object(x, y)
{
    originW = 60;
    originH = 60;
    this->LoadSprite(pathDoodleForward); 
    setSpriteSize(sprite, originW, originH); 
    Jump();
}

void Doodle::Jump()
{
    velocity = -jumpForce;
    isJumping = true;
    isFalling = false;
}

void Doodle::MoveLeft()  {  x--; }
void Doodle::MoveRight() {  x++; }

void Doodle::ActivateShield(unsigned int Tick)
{
    Shield = true;
    ShieldTime = Tick + 20000;
    shield = createSprite("../2022_win64/data/shield.png");
}

void Doodle::Update()
{
    if (Shield && getTickCount() < ShieldTime)
    {
        drawSprite(shield, x - 20, y - 20);
    }
    else
    {
        Shield = false;
    }

    if (isMovingLeft) 
    {
        MoveLeft();
    }
    if (isMovingRight) 
    {
        MoveRight();
    }

    y += velocity;
    velocity += gravity;


    if (velocity > 0)
    {
        isFalling = true;
        isJumping = false;
    }

    if (x <= EDGE)
    {
        x = windowWidth;
    }
    else if (x >= windowWidth)
    {
        x = EDGE;
    }

    if (y > windowHeight)
    {
        if (Shield == true)
        {
            Jump();
        }
        else if (lifes > 0)
        {
            lifes--;
            Jump();
        }
        else
        {
            isDead = true;
        }
    }
}

void Doodle::Fire(std::vector<Bullet*>& bullets, int mouseX, int mouseY)
{
    // Change sprite to FireForward
    isShooting = true;
    destroySprite(sprite);
    this->LoadSprite(pathDoodleForward);

    Bullet* bullet = new Bullet(this->x + 20, this->y, mouseX, mouseY);
    bullets.push_back(bullet);
}

void Doodle::CheckCollision(const std::vector<Platform*>& platforms)
{
    int platformLeft, platformRight, platformTop, platformBottom;
    int doodleLeft, doodleRight, doodleTop, doodleBottom;

    for (auto& platform : platforms)
    {
          doodleLeft = x + offset;
          doodleRight = x + originW - offset;
          doodleTop = y + offset;
          doodleBottom = y + originW - offset;

          platformLeft = platform->GetLeft();
          platformRight = platform->GetRight();
          platformTop = platform->GetTop();
          platformBottom = platform->GetBottom();

        // Перевіряємо, чи відбувається колізія
       if (doodleBottom >= platformTop && doodleTop <= platformTop && doodleLeft <= platformRight && doodleRight >= platformLeft)
       {
           if (isFalling)
           {
               isCollide = true;
               Jump();
           }
       }
    }
}

bool Doodle::CheckMonsterCollision(Monster* monster)
{
    int monsterLeft = monster->GetX();
    int monsterRight = monster->GetX() + monster->GetWidth();
    int monsterTop = monster->GetY();
    int monsterBottom = monster->GetY() + monster->GetHeight();

    if (y + originW - offset >= monsterTop && y + offset <= monsterTop && x + offset <= monsterRight && x + originW - offset >= monsterLeft)
    {
        if (isFalling)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Doodle::Reset()
{
    isDead = false;
    x = windowWidth / 2;
    y = windowHeight / 2;
    lifes = 5;
}

void Doodle::StartMovingRight()
{
    isMovingRight = true; 
    destroySprite(sprite); 
    sprite = createSprite(pathDoodleRight);
    setSpriteSize(sprite, originW, originH);
}

void Doodle::StartMovingLeft()
{
    isMovingLeft = true; 
    destroySprite(sprite);
    sprite = createSprite(pathDoodleLeft);
    setSpriteSize(sprite, originW, originH);
}
