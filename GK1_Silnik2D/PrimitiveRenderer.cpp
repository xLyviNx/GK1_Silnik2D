#include "PrimitiveRenderer.h"
#include "Engine.h"
LineRenderer::LineRenderer(sf::Color color, float width, sf::Vector2f positionA, sf::Vector2f positionB) : PrimitiveRenderer(color, width)
{
	this->posA = positionA;
	this->posB = positionB;
}

void PrimitiveRenderer::DrawSingleLine(sf::Vector2f A, sf::Vector2f B)
{

    int x1 = A.x;
    int y1 = A.y;
    int x2 = B.x;
    int y2 = B.y;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    GRUPA3::Engine2D::Engine* engine = (GRUPA3::Engine2D::Engine::GetSingleton(false));
    if (engine != NULL)
    {
        sf::RenderWindow* renderWindow = GRUPA3::Engine2D::Engine::GetSingleton(false)->Window;
        if (renderWindow != NULL)
        {

            while (x1 != x2 || y1 != y2)
            {
                for (int i = 0; i < Width; i++)
                {
                    for (int j = 0; j < Width; j++)
                    {
                        sf::Vertex pixel(sf::Vector2f(x1 + i, y1 + j), Color);
                        renderWindow->draw(&pixel, 1, sf::Points);
                    }
                }

                int err2 = 2 * err;
                if (err2 > -dy)
                {
                    err -= dy;
                    x1 += sx;
                }
                if (err2 < dx)
                {
                    err += dx;
                    y1 += sy;
                }
            }
        }
   }
}
void PrimitiveRenderer::Draw()
{

}

void PrimitiveRenderer::DrawSFML()
{

}
void PrimitiveRenderer::DrawSingleLineSFML()
{
    GRUPA3::Engine2D::Engine* engine = (GRUPA3::Engine2D::Engine::GetSingleton(false));
    if (engine != NULL)
    {
        sf::RenderWindow* renderWindow = GRUPA3::Engine2D::Engine::GetSingleton(false)->Window;
        if (renderWindow != NULL)
        {
            float lineWidth = std::abs(posB.x - posB.x);
            float lineHeight = std::abs(posA.y - posA.y);

            // Stworzenie sf::RectangleShape
            sf::RectangleShape line(sf::Vector2f(lineWidth, lineHeight));
            line.setFillColor(Color);

            // Ustal pozycjê
            if (startPoint.x < endPoint.x)
                line.setPosition(startPoint.x, startPoint.y);
            else
                line.setPosition(endPoint.x, endPoint.y);
        }
    }
}
PrimitiveRenderer::PrimitiveRenderer(sf::Color color, float width)
{
	this->Color = color;
	this->Width = width;

}
void LineRenderer::Draw()
{
    DrawSingleLine(posA, posB);
}