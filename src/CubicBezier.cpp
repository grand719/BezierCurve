#include "CubicBezier.h"

namespace bezier
{

CubicBezier::CubicBezier(const sf::Vector2f &point0, const sf::Vector2f &point1, const sf::Vector2f &point2,
                         const sf::Vector2f &point3)
    : mPoint0{point0}, mPoint1{point1}, mPoint2{point2}, mPoint3{point3}, mPixel{sf::Vector2f{4.f, 4.f}}
{
    mPixel.setFillColor(sf::Color::Red);
    mPixel.setOrigin(sf::Vector2f{2.f, 2.f});
    mLines = sf::VertexArray{sf::PrimitiveType::Lines, 6};
}

void CubicBezier::Render(sf::RenderWindow &window)
{
    float segments = 200;
    for (int i = 0; i <= segments; ++i)
    {
        float t = static_cast<float>(i) / segments;
        sf::Vector2f B =
            bezier2(mPoint0.getPosition(), mPoint1.getPosition(), mPoint2.getPosition(), mPoint3.getPosition(), t);

        mPixel.setPosition(B);
        window.draw(mPixel);
    }

    mLines.clear();
    mLines.resize(6);
    mLines[0].position = mPoint0.getPosition();
    mLines[0].color = sf::Color::White;
    mLines[1].position = mPoint1.getPosition();
    mLines[1].color = sf::Color::White;

    mLines[2].position = mPoint1.getPosition();
    mLines[2].color = sf::Color::White;
    mLines[3].position = mPoint2.getPosition();
    mLines[3].color = sf::Color::White;

    mLines[4].position = mPoint2.getPosition();
    mLines[4].color = sf::Color::White;
    mLines[5].position = mPoint3.getPosition();
    mLines[5].color = sf::Color::White;
    window.draw(mLines);

    mPoint0.Render(window);
    mPoint1.Render(window);
    mPoint2.Render(window);
    mPoint3.Render(window);
}

std::vector<std::reference_wrapper<bezier::Point>> CubicBezier::getAllControlPoints()
{
    return {mPoint0, mPoint1, mPoint2, mPoint3};
}

sf::Vector2f CubicBezier::lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t)
{
    return sf::Vector2f{(1 - t) * a.x + t * b.x, (1 - t) * a.y + t * b.y};
}

sf::Vector2f CubicBezier::bezier2(sf::Vector2f &p0, sf::Vector2f &p1, sf::Vector2f &p2, sf::Vector2f &p3, float t)
{
    sf::Vector2f P01 = lerp(p0, p1, t);
    sf::Vector2f P12 = lerp(p1, p2, t);
    sf::Vector2f P23 = lerp(p2, p3, t);

    sf::Vector2f P012 = lerp(P01, P12, t);
    sf::Vector2f P123 = lerp(P12, P23, t);

    return lerp(P012, P123, t);
}

} // namespace bezier
