#include "UI.h"

UI::UI(float x, float y) : Object(x, y)
{
	for (int i = 0; i < 10; i++)
	{
		std::string filename = "../2022_win64/data/" + std::to_string(i) + ".png";
		digitSprites[i] = createSprite(filename.c_str());
	}
}

void UI::DrawScore(int score)
{
    // SCORE
    float offset = 20.0f;
    int numDigits = (score == 0) ? 1 : static_cast<int>(log10(score) + 1);

    float x = 17 * numDigits;
    float y = 10;

    for (int i = 0; i < numDigits; ++i) {
        int digit = score % 10;
        score /= 10;

        Sprite* digitSprite = digitSprites[digit];
        drawSprite(digitSprite, x, y);

        x -= offset;
    }
}

void UI::DrawUI(int score, int numberPlatforms, int lifes)
{
    DrawScore(score);

    // PLATFORMS
    float x = windowWidth - 100.0f;
    float y = 10;

    for (int i = 0; i < 2; ++i) {

        int digit = numberPlatforms % 10;
        numberPlatforms /= 10;

        Sprite* digitSprite = digitSprites[digit];
        drawSprite(digitSprite, x, y);

        x -= 20;
    }

    // LIFES
    x = windowWidth - 50;
    Sprite* digitSprite = digitSprites[lifes];
    drawSprite(digitSprite, x, y);

}
