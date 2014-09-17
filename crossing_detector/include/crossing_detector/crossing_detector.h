/*
 * Crossing detector from lama_msgs/PlaceProfile.msg
 */

#ifndef _CROSSING_DETECTOR_CROSSING_DETECTOR_H_
#define _CROSSING_DETECTOR_CROSSING_DETECTOR_H_

#include <cmath>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Polygon_2.h>

#include <ros/ros.h>
#include <geometry_msgs/Polygon.h>

#include <lama_msgs/Crossing.h>
#include <lama_msgs/Frontier.h>
#include <lama_msgs/PlaceProfile.h>
#include <lama_msgs/place_profile_utils.h>

namespace lama {
namespace crossing_detector {

using std::vector;
using lama_msgs::Crossing;
using lama_msgs::PlaceProfile;
using lama_msgs::Frontier;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef Delaunay::Face_iterator Face_iterator;
//typedef Delaunay::Vertex Vertex;
typedef CGAL::Polygon_2<K> Polygon;

class CrossingDetector
{
  public:

    CrossingDetector(const double frontier_width, const double max_frontier_angle=0.785);

    Crossing crossingDescriptor(const PlaceProfile& profile, const bool normalize=false);
    vector<Frontier> frontiers(const PlaceProfile& profile, const bool normalize=false);

    double getFrontierWidth() const {return frontier_width_;}
    void setFrontierWidth(const double value) {frontier_width_ = std::fabs(value);}

    double getMaxFrontierAngle() const {return max_frontier_angle_;}
    void setMaxFrontierAngle(const double value) {max_frontier_angle_ = std::fabs(value);}

    PlaceProfile getPlaceProfile() const {return place_profile_;}

  private:

    vector<Point> delaunayInput(const PlaceProfile& profile) const;
    vector<Frontier> frontiers_() const;

    double frontier_width_;  //!> Min. frontier width, i.e. space turough which a robot can go (m).
    double max_frontier_angle_;  //!> Max. angle between frontier and line from robot to frontier (rad).
                                 //!> 0 means that the angle between the line from robot to frontier middle
                                 //!> and the frontier is 90 deg.

    PlaceProfile place_profile_;  //!> PlaceProfile used to compute the crossing.

};

} // namespace crossing_detector
} // namespace lama

#endif // _CROSSING_DETECTOR_CROSSING_DETECTOR_H_
