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
#include <string>

namespace JsonCGAL
{
   JsonCGALBase *JsonCGALBase::object_factory(nlohmann::json container)
   {
      std::vector<double> coordinates;
      CGAL_list<Point_2d> points;
      std::string datatype;
      nlohmann::json point;
      nlohmann::json points_container;
      datatype = container["type"].get<std::string>();

      switch (key_map[datatype])
      {
      case SupportedTypes::point_2:
         coordinates = container["coordinates"].get<std::vector<double>>();
         return new Point_2d(coordinates[0], coordinates[1]);

      case SupportedTypes::segment_2:
         points_container = container["points"];
         for (nlohmann::json::iterator j = points_container.begin(); j < points_container.end(); j++)
         {
            point = *j;
            coordinates = point["coordinates"].get<std::vector<double>>();
            points.push_back(Point_2d(coordinates[0], coordinates[1]));
         }
         return new Segment_2d(points[0], points[1]);

      case SupportedTypes::line_2:
         points_container = container["points"];
         for (nlohmann::json::iterator j = points_container.begin(); j < points_container.end(); j++)
         {
            point = *j;
            coordinates = point["coordinates"].get<std::vector<double>>();
            points.push_back(Point_2d(coordinates[0], coordinates[1]));
         }
         return new Line_2d(points[0], points[1]);

      default:
         std::cerr << "JsonCGAL Error: invalid object type specifier" << std::endl;
         return new Point_2d;
      }
   }

   /**
	 * \brief json encoding method for Point class
	 * 
	 * \return nlohmann::json 
	 */
	nlohmann::json Point_2d::encode()
	{
		nlohmann::json json;
		json = { {"type", this->obj_type}, {"coordinates", {this->x(), this->y()} } };
		return json;
	}

   Point_2d Point_2d::decode_factory(nlohmann::json container)
   {
      std::vector<double> coordinates;
      coordinates = container["coordinates"].get<std::vector<double>>();
      return Point_2d(coordinates[0], coordinates[1]);
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
		json = { {"type", this->obj_type}, {"points", {source.encode(), target.encode()} } };
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
		json = { {"type", this->obj_type}, {"points", {source.encode(), target.encode()} } };
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
