#include "CubicBezier.h"
#include "stdio.h"
#include <SFML/Graphics.hpp>

sf::Vector2f lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t)
{
    return sf::Vector2f{(1 - t) * a.x + t * b.x, (1 - t) * a.y + t * b.y};
}

sf::Vector2f bezier2(sf::Vector2f &p0, sf::Vector2f &p1, sf::Vector2f &p2, sf::Vector2f &p3, float t)
{
    sf::Vector2f P01 = lerp(p0, p1, t);
    sf::Vector2f P12 = lerp(p1, p2, t);
    sf::Vector2f P23 = lerp(p2, p3, t);

    sf::Vector2f P012 = lerp(P01, P12, t);
    sf::Vector2f P123 = lerp(P12, P23, t);

    return lerp(P012, P123, t);
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CMake SFML Project");
    window.setFramerateLimit(60);
    sf::Vector2f P0 = {100.f, 500.f};
    sf::Vector2f P1 = {100.f, 200.f};
    sf::Vector2f P2 = {300.f, 200.f};
    sf::Vector2f P3 = {350.f, 500.f};
    bool isDragging = false;
    bezier::CubicBezier curve{P0, P1, P2, P3};

    std::optional<bezier::Point *> selectedPoint = std::nullopt;
    for (const auto &element : curve.getAllControlPoints())
    {
        printf("Test: %f, %f\n", element.get().getPosition().x, element.get().getPosition().y);
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto *mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
            {

                if (mouseClick->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos =
                        window.mapPixelToCoords(sf::Vector2i(mouseClick->position.x, mouseClick->position.y));

                    const float hitRadius = 10.0f;

                    auto controlPoints = curve.getAllControlPoints();
                    for (auto &pointRef : controlPoints)
                    {
                        bezier::Point &point = pointRef.get();
                        sf::Vector2f pointPos = point.getPosition();
                        float distance =
                            std::sqrt(std::pow(mousePos.x - pointPos.x, 2) + std::pow(mousePos.y - pointPos.y, 2));
                        if (distance <= hitRadius)
                        {
                            isDragging = true;
                            selectedPoint = &point;
                            break;
                        }
                    }
                }
            }
            else if (const auto *mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseReleased->button == sf::Mouse::Button::Left)
                {
                    isDragging = false;
                    selectedPoint = nullptr;
                }
            }
            else if (const auto *mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDragging && selectedPoint != std::nullopt)
                {
                    selectedPoint.value()->setPosition(
                        sf::Vector2f{mouseMoved->position.x * 1.f, mouseMoved->position.y * 1.f});
                }
            }
        }

        window.clear();
        curve.Render(window);
        window.display();
    }
}
