#include <iostream>
#include "rectangle.hpp"
#include "shape.hpp"
#include <string>
#include "base_types.hpp"
#include <iomanip>

namespace
{
  void makeIsoScale(demehin::Shape* shapes[], size_t shp_cnt, double scale_k, demehin::point_t& scale_pt)
  {
    for (size_t i = 0; i < shp_cnt; i++)
    {
      demehin::rectangle_t old_fr_rect = shapes[i]->getFrameRect();
      shapes[i]->move(scale_pt);
      demehin::rectangle_t new_fr_rect = shapes[i]->getFrameRect();
      demehin::point_t move_vector;
      move_vector.x_ = (new_fr_rect.pos_.x_ - old_fr_rect.pos_.x_) / scale_k;
      move_vector.y_ = (new_fr_rect.pos_.y_ - old_fr_rect.pos_.y_) / scale_k;
      shapes[i]->scale(scale_k);
      shapes[i]->move(move_vector.x_, move_vector.y_);
    }
  }

  double getFrRectArea(const demehin::rectangle_t& fr_rect)
  {
    return fr_rect.width_ * fr_rect.height_;
  }

  double getFrRectAreaSum(demehin::Shape* shapes[], size_t shp_cnt)
  {
    double area_sum = 0;
    for (size_t i = 0; i < shp_cnt; i++)
    {
      demehin::rectangle_t fr_rect = shapes[i]->getFrameRect();
      area_sum += getFrRectArea(fr_rect);
    }
    return area_sum;
  }

  void getFrRectCords(demehin::rectangle_t& fr_rect, double& lbx, double& lby, double& rtx, double& rty)
  {
    lbx = fr_rect.pos_.x_ - fr_rect.width_ / 2;
    lby = fr_rect.pos_.y_ - fr_rect.height_ / 2;
    rtx = fr_rect.pos_.x_ + fr_rect.width_ / 2;
    rty = fr_rect.pos_.y_ + fr_rect.height_ / 2;
  }

  void printFrRectCords(demehin::Shape* shapes[], size_t shp_cnt)
  {
    for (size_t i = 0; i < shp_cnt; i++)
    {
      double lbx = 0, lby = 0, rtx = 0, rty = 0;
      demehin::rectangle_t fr_rect = shapes[i]->getFrameRect();
      getFrRectCords(fr_rect, lbx, lby, rtx, rty);
      std::cout << lbx << " " << lby << " " << rtx << " " << rty << " ";
    }
    std::cout << "\n";
  }
}

int main()
{
  demehin::Shape* shapes[10000] = {};
  size_t shp_cnt = 0;
  double scale_k = 0;
  demehin::point_t scale_pt;

  std::string shape_name;
  while (std::cin >> shape_name)
  {
    if (shape_name == "RECTANGLE")
    {
      double lbx = 0, lby = 0;
      double rtx = 0, rty = 0;
      std::cin >> lbx;
      std::cin >> lby;
      std::cin >> rtx;
      std::cin >> rty;
      demehin::Rectangle* rect = new demehin::Rectangle(lbx, lby, rtx, rty);
      std::cout << rect->getArea() << "\n";
      shapes[shp_cnt++] = rect;
      shape_name = "";
    }
    else if (shape_name == "SCALE")
    {
      double x = 0;
      double y = 0;
      std::cin >> x;
      std::cin >> y;
      std::cin >> scale_k;
      scale_pt.x_ = x;
      scale_pt.y_ = y;
      break;
    }
  }

  //double old_sum_area = 0;
  //double new_sum_area = 0;
  //for (size_t i = 0; i < shp_cnt; i++)
  //{
    //demehin::rectangle_t old_fr_rect = shapes[i]->getFrameRect();
    //shapes[i]->move(scale_pt);
    //demehin::rectangle_t new_fr_rect = shapes[i]->getFrameRect();
    //demehin::point_t move_vector;
    //move_vector.x_ = (new_fr_rect.pos_.x_ - old_fr_rect.pos_.x_) / scale_k;
    //move_vector.y_ = (new_fr_rect.pos_.y_ - old_fr_rect.pos_.y_) / scale_k;
    //shapes[i]->scale(scale_k);
    //shapes[i]->move(move_vector.x_, move_vector.y_);
  //}

  std::cout << std::fixed;
  std::cout << std::setprecision(1);
  std::cout << std::showpoint;
  double sum_area = getFrRectAreaSum(shapes, shp_cnt);
  std::cout << sum_area << " ";
  printFrRectCords(shapes, shp_cnt);

  makeIsoScale(shapes, shp_cnt, scale_k, scale_pt);

  sum_area = getFrRectAreaSum(shapes, shp_cnt);
  std::cout << sum_area << " ";
  printFrRectCords(shapes, shp_cnt);

  //for (size_t i = 0; i < shp_cnt; i++)
  //{
    //demehin::point_t fr_lb;
    //demehin::point_t fr_rt;
    //demehin::rectangle_t fr_rect = shapes[i]->getFrameRect();
    //fr_rt.x_ = fr_rect.pos_.x_ + fr_rect.width_ / 2;
    //fr_rt.y_ = fr_rect.pos_.y_ + fr_rect.height_ / 2;
    //fr_lb.x_ = fr_rect.pos_.x_ - fr_rect.width_ / 2;
    //fr_lb.y_ = fr_rect.pos_.y_ - fr_rect.width_ / 2;
    //std::cout << shapes[i]->getArea() << " " << fr_lb.x_ << " " << fr_lb.y_ << " " << fr_rt.x_ << " " << fr_rt.y_ << "\n";
  //}
}
