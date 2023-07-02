#ifndef SEGMENT_H
#define SEGMENT_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <GL/glut.h>

class Segment
{
public:
  cv::Vec2d a_;
  cv::Vec2d b_;

  Segment();
  Segment(cv::Vec2d a, cv::Vec2d b);
  ~Segment();

  std::vector<Segment> getChildren() const;
  bool isVisible();
  std::string toString();
private:
  bool isDistanceLessThanPixel();
};

#endif