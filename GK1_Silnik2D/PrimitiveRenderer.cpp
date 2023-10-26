#include "PrimitiveRenderer.h"
#include "Engine.h"
#define M_PI 3.14159265358979323846
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

void PrimitiveRenderer::DrawSFML(float angle)
{

}
void PrimitiveRenderer::DrawSingleLineSFML(sf::Vector2f posA, sf::Vector2f posB, float angle)
{
    GRUPA3::Engine2D::Engine* engine = (GRUPA3::Engine2D::Engine::GetSingleton(false));
    if (engine != NULL)
    {
        sf::RenderWindow* renderWindow = GRUPA3::Engine2D::Engine::GetSingleton(false)->Window;
        if (renderWindow != NULL)
        {
            // Stworzenie sf::RectangleShape
            float lineWidth = std::abs(posA.x - posB.x);
            float lineHeight = std::abs(posA.y - posB.y);

            sf::Vector2f lineSize(160, 5);
            sf::RectangleShape line(lineSize);
            line.setFillColor(Color);
            line.setOrigin(80,3);
            line.setRotation(angle);
            

            // Ustal pozycjê
            line.setPosition(std::min(posA.x, posB.x), posA.y);

            // Rendererowanie linii w oknie
            renderWindow->draw(line);
        }
    }
}

void PrimitiveRenderer::DrawCircle(sf::Vector2f center, float radius) {
    GRUPA3::Engine2D::Engine* engine = GRUPA3::Engine2D::Engine::GetSingleton(false);
    if (engine != NULL) {
        sf::RenderWindow* renderWindow = engine->Window;
        if (renderWindow != NULL) {
            float x = radius;
            float y = 0;
            float err = 0;

            while (x >= y) {
                // Rysuj piksele w czterech æwiartkach okrêgu
                sf::Vertex vertex1(sf::Vector2f(center.x + x, center.y + y), Color);
                sf::Vertex vertex2(sf::Vector2f(center.x + y, center.y + x), Color);
                sf::Vertex vertex3(sf::Vector2f(center.x - y, center.y + x), Color);
                sf::Vertex vertex4(sf::Vector2f(center.x - x, center.y + y), Color);

                sf::Vertex vertex5(sf::Vector2f(center.x - x, center.y - y), Color);
                sf::Vertex vertex6(sf::Vector2f(center.x - y, center.y - x), Color);
                sf::Vertex vertex7(sf::Vector2f(center.x + y, center.y - x), Color);
                sf::Vertex vertex8(sf::Vector2f(center.x + x, center.y - y), Color);

                renderWindow->draw(&vertex1, 1, sf::Points);
                renderWindow->draw(&vertex2, 1, sf::Points);
                renderWindow->draw(&vertex3, 1, sf::Points);
                renderWindow->draw(&vertex4, 1, sf::Points);
                renderWindow->draw(&vertex5, 1, sf::Points);
                renderWindow->draw(&vertex6, 1, sf::Points);
                renderWindow->draw(&vertex7, 1, sf::Points);
                renderWindow->draw(&vertex8, 1, sf::Points);

                err += 2 * (y + 1);
                if (2 * err > x) {
                    x -= 1;
                    err -= x * 2 + 1;
                }
                y += 1;
            }
        }
    }
}


void PrimitiveRenderer::DrawEllipse(sf::Vector2f center, float RX, float RY) {
    GRUPA3::Engine2D::Engine* engine = GRUPA3::Engine2D::Engine::GetSingleton(false);

    if (engine != NULL) {
        sf::RenderWindow* renderWindow = engine->Window;
        if (renderWindow != NULL) {
            float x, y, alpha, step = 0.01; // Krok dla k¹ta alpha
            for (alpha = 0; alpha < 2 * M_PI; alpha += step) {
                x = center.x + RX * cos(alpha);
                y = center.y + RY * sin(alpha);

                // Rysuj piksel na elipsie
                sf::Vertex pixel(sf::Vector2f(x, y), Color);
                renderWindow->draw(&pixel, 1, sf::Points);
            }
        }
    }
}

void PrimitiveRenderer::PointLine(std::vector < sf::Vector2f > points)
{
   

        if (points.size() < 2) {
            return;
        }

        for (size_t i = 0; i < points.size() - 1; ++i) {
            cout << points[i].x<<endl;
            DrawSingleLine(points[i],points[i+1]);
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
    // Dodaj rysowanie okrêgu w odpowiednim miejscu
    sf::Vector2f circleCenter(700.0f, 300.0f); // Przyk³adowe wspó³rzêdne œrodka okrêgu
    float circleRadius = 50.0f; // Przyk³adowy promieñ okrêgu
    DrawCircle(circleCenter, circleRadius);
    // Dodaj rysowanie elipsy w odpowiednim miejscu
    sf::Vector2f ellipseCenter(400.0f, 300.0f); // Przyk³adowe wspó³rzêdne œrodka elipsy
    float ellipseRX = 100.0f; // Pó³osi RX
    float ellipseRY = 50.0f;  // Pó³osi RY
    DrawEllipse(ellipseCenter, ellipseRX, ellipseRY);
}
void LineRenderer::DrawSFML(float angle)
{
    DrawSingleLineSFML(posA, posB, angle);
}