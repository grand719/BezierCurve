#include "CurveCreator.h"

namespace bezier
{
CurveCreator::CurveCreator() : mSelectedPoint{std::nullopt}, mIsDragging{false}
{
}

void CurveCreator::OnRightPress(sf::Vector2f &position)
{
    CreatPoint(position);
    CreateCubicBezier();
}

void CurveCreator::CreatPoint(sf::Vector2f &pointPostion)
{
    mPointsList.push_back(std::make_shared<Point>(pointPostion));
}

void CurveCreator::CreateCubicBezier()
{
    if (mPointsList.size() == 2)
    {
        sf::Vector2f point0 = mPointsList[0].get()->getPosition();
        sf::Vector2f point1 = mPointsList[1].get()->getPosition();

        mCubicBezierList.push_back(std::make_shared<CubicBezier>(point0, point0, point1, point1, true));
        mPointsList.clear();
    }
}

void CurveCreator::Render(sf::RenderWindow &window)
{
    for (const auto point : mPointsList)
    {
        point.get()->Render(window);
    }

    for (const auto curve : mCubicBezierList)
    {
        curve.get()->Render(window);
    }
}

void CurveCreator::Tick()
{
    for (const auto curve : mCubicBezierList)
    {
        curve.get()->Tick();
    }
}

void CurveCreator::OnMouseMove(sf::Vector2f &position)
{
    if (mIsDragging && mSelectedPoint != std::nullopt)
    {

        mSelectedPoint.value()->setPosition(position);
    }
}

void CurveCreator::OnLeftPress(sf::Vector2f &mousePos)
{
    const float hitRadius = 10.0f;
    for (const auto curve : mCubicBezierList)
    {
        auto controlPoints = curve.get()->getAllControlPoints();
        for (auto &pointRef : controlPoints)
        {
            bezier::Point &point = pointRef.get();
            sf::Vector2f pointPos = point.getPosition();
            float distance = std::sqrt(std::pow(mousePos.x - pointPos.x, 2) + std::pow(mousePos.y - pointPos.y, 2));
            if (distance <= hitRadius)
            {
                mIsDragging = true;
                mSelectedPoint = &point;
                break;
            }
        }
    }
}
void CurveCreator::OnMouseLeftRelease()
{
    mSelectedPoint = std::nullopt;
    mIsDragging = false;
}
} // namespace bezier
