#pragma once
#include "Point.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace bezier
{

class CubicBezier
{
  public:
    CubicBezier(const sf::Vector2f &point0, const sf::Vector2f &point1, const sf::Vector2f &point2,
                const sf::Vector2f &point3, const bool &shouldAnimate);
    void Render(sf::RenderWindow &window);
    void Tick();
    std::vector<std::reference_wrapper<bezier::Point>> getAllControlPoints();

  private:
    sf::Vector2f lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t);
    sf::Vector2f bezier2(sf::Vector2f &p0, sf::Vector2f &p1, sf::Vector2f &p2, sf::Vector2f &p3, float t);

    void RenderInternal(sf::RenderWindow &window);
    void RenderAnimationInternal(sf::RenderWindow &window);

    bezier::Point mPoint0;
    bezier::Point mPoint1;
    bezier::Point mPoint2;
    bezier::Point mPoint3;

    bezier::Point mControlPoint;

    bool mShouldAnimate;

    float mT;
    float mAnimationPosition = 0.f;
    float mAnimationSegments = 200.f;

    sf::RectangleShape mPixel;
    sf::VertexArray mLines;
};
} // namespace bezier
