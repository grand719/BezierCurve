#include "CubicBezier.h"
#include "CurveCreator.h"
#include "stdio.h"
#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CMake SFML Project");
    window.setFramerateLimit(60);

    bezier::CurveCreator creator{};

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

                if (mouseClick->button == sf::Mouse::Button::Right)
                {
                    sf::Vector2f mousePos =
                        window.mapPixelToCoords(sf::Vector2i(mouseClick->position.x, mouseClick->position.y));

                    creator.OnRightPress(mousePos);
                }

                if (mouseClick->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos =
                        window.mapPixelToCoords(sf::Vector2i(mouseClick->position.x, mouseClick->position.y));
                    creator.OnLeftPress(mousePos);
                }
            }
            else if (const auto *mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseReleased->button == sf::Mouse::Button::Left)
                {
                    creator.OnMouseLeftRelease();
                }
            }
            else if (const auto *mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    sf::Vector2f mousePos =
                        window.mapPixelToCoords(sf::Vector2i(mouseMoved->position.x, mouseMoved->position.y));
                    creator.OnMouseMove(mousePos);
                }
            }
        }

        window.clear();
        creator.Render(window);
        window.display();
    }
}
