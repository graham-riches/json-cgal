/**
 * @file JsonCGAL.h
 * @author Graham Riches (graham.riches@live.com)
 * @brief library for passing geometric data (point, segment, polygon, etc)
 *        from CGAL algorithms to a neutral file format (JSON). This enables
 *        data sharing between C++ and Python.
 * @version 0.1
 * @date 2020-04-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __JSON_CGAL_H
#define __JSON_CGAL_H

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <string>
#include <fstream>
#include <vector>

#include "json.hpp"
#include "cgal_kernel_config.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

namespace JsonCGAL
{	
   /**
    * \brief parent class for JSON wrapper for CGAL type classes
    */
   class JsonCGALBase
   {
      public:
         virtual nlohmann::json encode() = 0;
   };

   class Point_2d : public Kernel::Point_2, public JsonCGALBase
	{
		public:
			using Kernel::Point_2::Point_2;
			nlohmann::json encode();
	};

   class Line_2d : public Kernel::Line_2, public JsonCGALBase
	{
		public:
         using Kernel::Line_2::Line_2;
			nlohmann::json encode();
	};

   class Segment_2d : public Kernel::Segment_2, public JsonCGALBase
	{
		public:
			using Kernel::Segment_2::Segment_2;
			nlohmann::json encode();
	};

   class Weighted_point_2d : public Kernel::Weighted_point_2, public JsonCGALBase
   {
	   public:
		   using Kernel::Weighted_point_2::Weighted_point_2;
		   nlohmann::json encode();
   };

   class Vector_2d : public Kernel::Vector_2, public JsonCGALBase
   {
	   public:
		   using Kernel::Vector_2::Vector_2;
		   nlohmann::json encode();
   };

   class Direction_2d : public Kernel::Direction_2, public JsonCGALBase
   {
	   public:
		   using Kernel::Direction_2::Direction_2;
		   nlohmann::json encode();
   };

   class Ray_2d : public Kernel::Ray_2, public JsonCGALBase
   {
	   public:
		   using Kernel::Ray_2::Ray_2;
		   nlohmann::json encode();
   };

   class Triangle_2d : public Kernel::Triangle_2, public JsonCGALBase
   {
		public:
		   using Kernel::Triangle_2::Triangle_2;
		   nlohmann::json encode();
   };

   class Iso_rectangle_2d : public Kernel::Iso_rectangle_2, public JsonCGALBase
   {
	   public:
		   using Kernel::Iso_rectangle_2::Iso_rectangle_2;
		   nlohmann::json encode();
   };

   class Circle_2d : public Kernel::Circle_2, public JsonCGALBase
   {
	   public:
		   using Kernel::Circle_2::Circle_2;
		   nlohmann::json encode();
   };


   class JsonCGAL
   {
   private:
	   void parse_json_container(nlohmann::json container);
	   nlohmann::json create_json_container();
	   CGAL_list<Point_2d> _points;
	   CGAL_list<Line_2d> _lines;
	   CGAL_list<Segment_2d> _segments;

   public:
	   bool load(std::string filename);
	   bool load_from_string(std::string json_string);
	   bool dump(std::string filename);
	   std::string dump_to_string();

	   /* accessors */
	   CGAL_list<Point_2d> get_points() { return this->_points; }
	   void set_points(CGAL_list<Point_2d> points) { this->_points = points; }
	   CGAL_list<Line_2d> get_lines() { return this->_lines; }
	   void set_lines(CGAL_list<Line_2d> lines) { this->_lines = lines; }
	   CGAL_list<Segment_2d> get_segments() { return this->_segments; }
	   void set_segments(CGAL_list<Segment_2d> segments) { this->_segments = segments; }
   };
}

#endif /* __JSON_CGAL_H */