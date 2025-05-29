#pragma once
#include <SFML/Graphics.hpp>

namespace bezier
{
class Point
{
  public:
    Point(const sf::Vector2f initialPosition);
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f &getPosition();
    void Render(sf::RenderWindow &window);

  private:
    sf::Vector2f mPosition;
    sf::CircleShape mDot;
};
} // namespace  bezier
