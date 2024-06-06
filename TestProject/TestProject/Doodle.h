#pragma once
#include <Framework.h>
#include "Object.h"
#include "Platform.h"
#include "Monster.h"
#include "Bullet.h"
#include <vector>

extern int windowWidth, windowHeight;

class Sprite;

class Doodle : public Object{
private:

    Sprite* shield;

    bool isMovingLeft{ false }, isMovingRight{ false };
    bool isFalling, isJumping;
    bool isShooting;
    bool isDead = false;

    int lifes = 5;

    double velocity{ 0.0 }, gravity{ 0.008 };
    float jumpForce = 2;
    float offset = 15;

    bool isCollide;
    float highestDoodlePoint = windowHeight / 2;

    bool Shield = false;
    unsigned int ShieldTime;

    const char pathDoodleForward[34] = "../2022_win64/data/bunny-puca.png";
    const char pathDoodleLeft[34] = "../2022_win64/data/bunny-left.png";
    const char pathDoodleRight[35] = "../2022_win64/data/bunny-right.png";

public:

    Doodle(float x, float y);
    ~Doodle() {}

    float GetX() { return x; }
    float GetY() { return y; }
    void SetX(float newX) { x = newX; }
    void SetY(float newY) { y = newY; }
    float GetWidth() { return originW; }
    float GetHeight() { return originH; }
    bool GetIsFalling() { return isFalling; }
    float GetVelocity() { return velocity; }
    bool GetIsCollide() { return isCollide; }
    int GetLifes() { return lifes; }
    bool GetIsShield() { return Shield; }
    float GetHighestDoodlePoint() { return highestDoodlePoint; }
    bool GetIsDead() { return isDead; }
    void DoodleDead() { isDead = true; }
    void SetHighestDoodlePoint(float newHighestDoodlePoint) {  highestDoodlePoint = newHighestDoodlePoint;  }

    void Jump();

    void StartMovingLeft();
    void MoveLeft();
    void StartMovingRight();
    void MoveRight();
    void StopMovingLeft() { isMovingLeft = false; }
    void StopMovingRight() { isMovingRight = false; }

    void ActivateShield(unsigned int Tick);

    void Update() override;
    void Fire(std::vector<Bullet*>& bullets, int mouseX, int mouseY);

    void CheckCollision(const std::vector<Platform*>& platforms);
    bool CheckMonsterCollision(Monster* monster);

    void IsShooting() {  }
    void Reset();
};