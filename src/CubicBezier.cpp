#include "CubicBezier.h"

namespace bezier
{

CubicBezier::CubicBezier(const sf::Vector2f &point0, const sf::Vector2f &point1, const sf::Vector2f &point2,
                         const sf::Vector2f &point3, const bool &shouldAnimate)
    : mPoint0{point0}, mPoint1{point1}, mPoint2{point2}, mPoint3{point3}, mPixel{sf::Vector2f{4.f, 4.f}},
      mShouldAnimate{shouldAnimate}, mT{0.f}, mControlPoint{sf::Vector2f{0.f, 0.f}}
{
    mPixel.setFillColor(sf::Color::Red);
    mPixel.setOrigin(sf::Vector2f{2.f, 2.f});
    mLines = sf::VertexArray{sf::PrimitiveType::Lines, 6};
}

void CubicBezier::Render(sf::RenderWindow &window)
{
    mShouldAnimate ? RenderAnimationInternal(window) : RenderInternal(window);
}

void CubicBezier::Tick()
{
    if (mShouldAnimate)
    {
        mT = mAnimationPosition / mAnimationSegments;

        mAnimationPosition += 1.f;
        if (mAnimationPosition >= mAnimationSegments)
        {
            mAnimationPosition = 0.f;
            mT = 0.f;
        }
    }
}

void CubicBezier::RenderAnimationInternal(sf::RenderWindow &window)
{

    for (float t = 0.f; t <= mT; t += 1.f / mAnimationSegments)
    {
        sf::Vector2f B =
            bezier2(mPoint0.getPosition(), mPoint1.getPosition(), mPoint2.getPosition(), mPoint3.getPosition(), t)
                .Final;

        mPixel.setPosition(B);
        window.draw(mPixel);
    }

    CubicBezierPoints points =
        bezier2(mPoint0.getPosition(), mPoint1.getPosition(), mPoint2.getPosition(), mPoint3.getPosition(), mT);

    mLines.clear();
    mLines.resize(12);
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

    mLines[6].position = points.P01;
    mLines[6].color = sf::Color::White;
    mLines[7].position = points.P12;
    mLines[7].color = sf::Color::White;

    mLines[8].position = points.P12;
    mLines[8].color = sf::Color::White;
    mLines[9].position = points.P23;
    mLines[9].color = sf::Color::White;

    mLines[10].position = points.P012;
    mLines[10].color = sf::Color::White;
    mLines[11].position = points.P123;
    mLines[11].color = sf::Color::White;

    window.draw(mLines);

    mPoint0.Render(window);
    mPoint1.Render(window);
    mPoint2.Render(window);
    mPoint3.Render(window);

    mControlPoint.setPosition(points.Final);
    mControlPoint.Render(window);
}

void CubicBezier::RenderInternal(sf::RenderWindow &window)
{
    float segments = 200;
    for (int i = 0; i <= segments; ++i)
    {
        float t = static_cast<float>(i) / segments;
        sf::Vector2f B =
            bezier2(mPoint0.getPosition(), mPoint1.getPosition(), mPoint2.getPosition(), mPoint3.getPosition(), t)
                .Final;

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

CubicBezierPoints CubicBezier::bezier2(sf::Vector2f &p0, sf::Vector2f &p1, sf::Vector2f &p2, sf::Vector2f &p3, float t)
{
    sf::Vector2f P01 = lerp(p0, p1, t);
    sf::Vector2f P12 = lerp(p1, p2, t);
    sf::Vector2f P23 = lerp(p2, p3, t);

    sf::Vector2f P012 = lerp(P01, P12, t);
    sf::Vector2f P123 = lerp(P12, P23, t);

    CubicBezierPoints points{P01, P12, P23, P012, P123, lerp(P012, P123, t)};

    return points;
}

} // namespace bezier
