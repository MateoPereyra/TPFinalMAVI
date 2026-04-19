#include "Terrain.h"
#include "Spear.h"

using namespace sf;
using namespace std;

Terrain::Terrain(float x, float y, float w, float h, Texture& grassTex, Texture& dirtTex)
{
    float tileSize = 50.f;
    tBounds = FloatRect(x, y, w, h);

    for (float i = 0; i < w; i += tileSize)
    {
        float remaining = w - i;
        float tileW = min(remaining, tileSize); //espacio sobrante

        Sprite grass(grassTex);

        if (h <= 25.f) {
            grass.setTextureRect(IntRect(0, 0, 128, 64));
            grass.setScale(tileW / 128.f, 25.f / 64.f); //tileW en vez de 64.f fijo
        } else { //completo
            grass.setTextureRect(IntRect(0, 0, 128, 128));
            grass.setScale(tileW / 128.f, 64.f / 128.f);
        }

        grass.setPosition(x + i, y);
        parts.push_back(grass);
    }

    //Para dirt en Y
    if (h > tileSize)
    {
        for (float j = tileSize; j < h; j += tileSize)
        {
            float remainingH = h - j;
            float tileH = min(remainingH, tileSize);

            for (float i = 0; i < w; i += tileSize)
            {
                float remainingW = w - i;
                float tileW = min(remainingW, tileSize);

                Sprite dirt(dirtTex);
                dirt.setScale(tileW / 128.f, tileH / 128.f);
                dirt.setPosition(x + i, y + j);
                parts.push_back(dirt);
            }
        }
    }
}

void Terrain::render(RenderWindow& wnd)
{
    for (auto& p : parts)
        wnd.draw(p);
}

FloatRect Terrain::getBounds()
{
    return tBounds;
}

float Terrain::getTop()
{
    return tBounds.top;
}

float Terrain::getBottom()
{
    return tBounds.top + tBounds.height;
}

float Terrain::getLeft()
{
    return tBounds.left;
}

float Terrain::getRight()
{
    return tBounds.left + tBounds.width;
}