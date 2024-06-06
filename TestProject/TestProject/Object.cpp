#include "Object.h"

void Object::Draw() const
{
    if (sprite)
    {
        drawSprite(sprite, x, y);
    }
}

bool Object::LoadSprite(const char* imagePath)
{
    sprite = createSprite(imagePath);
    return (sprite != nullptr);
}