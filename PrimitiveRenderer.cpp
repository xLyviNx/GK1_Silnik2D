#include "PrimitiveRenderer.h"
#include "Engine.h"
#define M_PI 3.14159265358979323846

void PrimitiveRenderer::DrawSingleLine(sf::Vector2f A, sf::Vector2f B, float Width, sf::Color Color)
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
    if (Engine2D::Engine::GetSingleton(false) != NULL)
    {
        sf::RenderWindow* renderWindow = Engine2D::Engine::GetSingleton(false)->Window;
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
void PrimitiveRenderer::DrawSingleLineSFML(sf::Vector2f posA, sf::Vector2f posB, float angle, sf::Color color)
{
    if (Engine2D::Engine::GetSingleton(false) != NULL)
    {
        sf::RenderWindow* renderWindow = Engine2D::Engine::GetSingleton(false)->Window;
        if (renderWindow != NULL)
        {
            // Stworzenie sf::RectangleShape
            float lineWidth = std::abs(posA.x - posB.x);
            float lineHeight = std::abs(posA.y - posB.y);

            sf::Vector2f lineSize(160, 5);
            sf::RectangleShape line(lineSize);
            line.setFillColor(color);
            line.setOrigin(80, 3);
            line.setRotation(angle);


            line.setPosition(std::min(posA.x, posB.x), posA.y);

            renderWindow->draw(line);
        }
    }
}

void PrimitiveRenderer::DrawEllipse(sf::Vector2f center, float RX, float RY, sf::Color color)
{
    if (Engine2D::Engine::GetSingleton(false) != NULL && Engine2D::Engine::GetSingleton(false)->Window != NULL) {
        sf::VertexArray ellipse(sf::Points);
        float maxRadius = std::max(RX, RY);
        float step = 1.0f / maxRadius; // Krok zale¿ny od wiêkszego promienia
        for (float alpha = 0; alpha < 2 * M_PI; alpha += step) {
            float x = center.x + RX * cos(alpha);
            float y = center.y + RY * sin(alpha);
            ellipse.append(sf::Vertex(sf::Vector2f(x, y), color));
        }
        Engine2D::Engine::GetSingleton(false)->Window->draw(ellipse);
    }

}

void PrimitiveRenderer::DrawCircle(sf::Vector2f center, float radius, sf::Color color)
{
    if (Engine2D::Engine::GetSingleton(false) != nullptr)
    {
        sf::RenderWindow* renderWindow = Engine2D::Engine::GetSingleton(false)->Window;
        if (renderWindow != nullptr)
        {
            sf::VertexArray circle(sf::Points);
            float step = 1.0 / radius;
            for (float a = 0; a < M_PI / 4; a += step) {
                sf::Vector2f point(radius * cos(a), radius * sin(a));
                circle.append(sf::Vertex(center + point, color));
                circle.append(sf::Vertex(center + sf::Vector2f(point.y, point.x), color));
                circle.append(sf::Vertex(center + sf::Vector2f(-point.y, point.x), color));
                circle.append(sf::Vertex(center + sf::Vector2f(-point.x, point.y), color));
                circle.append(sf::Vertex(center - point, color));
                circle.append(sf::Vertex(center + sf::Vector2f(-point.y, -point.x), color));
                circle.append(sf::Vertex(center + sf::Vector2f(point.y, -point.x), color));
                circle.append(sf::Vertex(center + sf::Vector2f(point.x, -point.y), color));
            }
            renderWindow->draw(circle);
        }
    }
}

void PrimitiveRenderer::PointLine(std::vector < sf::Vector2f >* points, float Width, sf::Color Color)
{
    if (points == NULL || (*points).size() < 2) {
        return;
    }
    for (size_t i = 0; i < (*points).size() - 1; ++i)
    {
        //cout << (*points)[i].x << endl;
        PrimitiveRenderer::DrawSingleLine((*points)[i], (*points)[i + 1], Width, Color);
    }
}

PrimitiveRenderer::PrimitiveRenderer(sf::Color color, float width)
{
    this->Color = color;
    this->Width = width;
}

Point2D::Point2D(sf::Color color, float width, sf::Vector2f position)
{
    this->Color = color;
    this->Width = width;
    this->Position = position;
}

sf::Vector2f Point2D::getPosition()
{
    return Position;
}

void Point2D::setPosition(sf::Vector2f newPos)
{
    Position = newPos; 
}

void Point2D::DrawPointSFML()
{
    if (Engine2D::Engine::GetSingleton(false) != NULL)
    {
        sf::RenderWindow* renderWindow = Engine2D::Engine::GetSingleton(false)->Window;
        if (renderWindow != NULL)
        {
            sf::CircleShape pointShape(Width);  // Tworzenie punktu jako kó³ko
            pointShape.setFillColor(Color);
            pointShape.setPosition(Position);
            renderWindow->draw(pointShape);
        }
    }
}