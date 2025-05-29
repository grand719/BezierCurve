#include "Point.h"

namespace bezier
{
Point::Point(sf::Vector2f initialPosition) : mPosition{initialPosition}, mDot{6.f}
{
    mDot.setPosition(mPosition);
    mDot.setOrigin(sf::Vector2f{6.f, 6.f});
    mDot.setFillColor(sf::Color::Blue);
}

void Point::setPosition(const sf::Vector2f &position)
{
    mPosition = position;
    mDot.setPosition(mPosition);
};

sf::Vector2f &Point::getPosition()
{
    return mPosition;
};

void Point::Render(sf::RenderWindow &window)
{
    window.draw(mDot);
};

} // namespace bezier
