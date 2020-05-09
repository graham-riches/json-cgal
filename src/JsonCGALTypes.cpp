/**
 * \file JsonCGALTypes.cpp
 * \author Graham Riches (graham.riches@live.com)
 * \brief function definitions for CGAL wrapper class objects
 * \version 0.1
 * \date 2020-05-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "JsonCGALTypes.h"

namespace JsonCGAL
{
   /**
	 * \brief json encoding method for Point class
	 * 
	 * \return nlohmann::json 
	 */
	nlohmann::json Point_2d::encode()
	{
		nlohmann::json json;
		json = { {"type", "point"}, {"coordinates", {this->x(), this->y()} } };
		return json;
	}

   /**
	 * \brief json encoding method for Line class
	 * 
	 * \return nlohmann::json 
	 */
	nlohmann::json Line_2d::encode()
	{
		nlohmann::json json;
		Kernel::Point_2 point;
		point = this->point(0);
		Point_2d source(point.x(), point.y());
		point = this->point(1);
		Point_2d target(point.x(), point.y());
		json = { {"type", "line"}, {"points", {source.encode(), target.encode()} } };
		return json;
	}

   /**
	 * \brief json encoding method for Segment class
	 * 
	 * \return nlohmann::json 
	 */
	nlohmann::json Segment_2d::encode()
	{
		nlohmann::json json;
		Kernel::Point_2 point;
		point = this->source();
		Point_2d source(point.x(), point.y());
		point = this->target();
		Point_2d target(point.x(), point.y());
		json = { {"type", "segment"}, {"points", {source.encode(), target.encode()} } };
		return json;
	}

	/**
	 * \brief json encoding for Weighted_point class
	 * 
	 * \retval nlohmann::json 
	 */
	nlohmann::json Weighted_point_2d::encode()
	{
      nlohmann::json json;
      return json;
	}

	nlohmann::json Vector_2d::encode()
	{
      nlohmann::json json;
      return json;
	}

	nlohmann::json Direction_2d::encode()
	{
      nlohmann::json json;
      return json;
	}

	nlohmann::json Ray_2d::encode()
	{
      nlohmann::json json;
      return json;
	}

	nlohmann::json Triangle_2d::encode()
	{
      nlohmann::json json;
      return json;
	}

	nlohmann::json Iso_rectangle_2d::encode()
	{
      nlohmann::json json;
      return json;
	}

	nlohmann::json Circle_2d::encode()
	{
      nlohmann::json json;
      return json;
	}
};
