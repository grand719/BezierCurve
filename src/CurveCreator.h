#pragma once

#include "CubicBezier.h"
#include "Point.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace bezier
{
class CurveCreator
{
  public:
    CurveCreator();
    void OnRightPress(sf::Vector2f &position);
    void Render(sf::RenderWindow &window);
    void Tick();

    void OnMouseMove(sf::Vector2f &position);
    void OnLeftPress(sf::Vector2f &position);
    void OnMouseLeftRelease();

  private:
    void CreatPoint(sf::Vector2f &pointPostion);
    void CreateCubicBezier();

    std::vector<std::shared_ptr<CubicBezier>> mCubicBezierList;
    std::vector<std::shared_ptr<Point>> mPointsList;
    std::optional<bezier::Point *> mSelectedPoint;
    bool mIsDragging;
};
} // namespace bezier
