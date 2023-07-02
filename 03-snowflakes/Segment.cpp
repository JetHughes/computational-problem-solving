#include "Segment.h"
#include <iostream>
#include <GL/glut.h>

Segment::Segment() : a_(cv::Vec2d(-1,0)), b_(cv::Vec2d(1,0)){}

Segment::Segment(cv::Vec2d a, cv::Vec2d b) : a_(a), b_(b){}

Segment::~Segment() {}

// naming conventions
//             t
//             /\
//            /  \
//           /    \
// _________/      \_________
// a_  l(eft)      r(ight)   b_
//
// ab is the vector from a_ to b_

std::vector<Segment> Segment::getChildren() const{
  //get the length of the child segments i.e., the vector from a_ to l i.e., the vector l
  cv::Vec2d al = (b_ - a_) / 3;

  // Compute l, r, and t using ab
  cv::Vec2d l = a_ + al; //l is the vector al plus the vector a_
  cv::Vec2d r = b_ - al; //r is the vector b_ minus the vector al

  // Rotate ab by 60 degrees and translate it by l
  cv::Mat rm = cv::getRotationMatrix2D(cv::Point2f(0.0, 0.0), 60, 1.0);
  cv::Vec2d t = cv::Vec2d(rm.at<double>(0, 0) * al[0] + rm.at<double>(0, 1) * al[1],
                          rm.at<double>(1, 0) * al[0] + rm.at<double>(1, 1) * al[1]) + l;

  // Add the children to a std::vector and return them
  std::vector<Segment> children = {Segment(a_, l), Segment(l, t), Segment(t, r), Segment(r, b_)};
  return children;
}

bool Segment::isVisible(){
  if(isDistanceLessThanPixel()){
    std::cout << "distance less than pixel" << std::endl;
    return false;
  }

  // Can add other checks to allow for zooming if needed

  return true;
}

bool Segment::isDistanceLessThanPixel() {
  int viewportWidth = glutGet(GLUT_WINDOW_HEIGHT);
  int viewportHeight = glutGet(GLUT_WINDOW_WIDTH);
  double distance = sqrt(pow(a_[0] - b_[0], 2) + pow(a_[1] - b_[1], 2));
  double pixelSize = 2.0 / std::min(viewportWidth, viewportHeight);
  return distance < pixelSize;
}

std::string Segment::toString() {
  return "(x=" + std::to_string(a_[0]) + ", y=" + std::to_string(a_[1]) + "), (x=" + std::to_string(b_[0]) + ", y=" + std::to_string(b_[1]) + ")";
}
