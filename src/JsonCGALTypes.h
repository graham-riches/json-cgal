/**
 * \file JsonCGALTypes.h
 * \author Graham Riches (graham.riches@live.com)
 * \brief class definitions for CGAL wrapper objects
 * \version 0.1
 * \date 2020-05-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __JSON_CGAL_TYPES_H
#define __JSON_CGAL_TYPES_H

#include "JsonCGALMap.h"
#include "cgal_kernel_config.h"
#include "json.hpp"

namespace JsonCGAL
{
   /**
    * \brief parent class for JSON wrapper for CGAL type classes
    */
   class JsonCGALBase
   {
      public:
         virtual nlohmann::json encode() = 0;
		   virtual enum SupportedTypes::SupportedTypes getType() = 0;
   };

   class Point_2d : public Kernel::Point_2, public JsonCGALBase
	{
		public:
			using Kernel::Point_2::Point_2;
			nlohmann::json encode();
			enum SupportedTypes::SupportedTypes getType() { return SupportedTypes::point_2; }
	};

   class Line_2d : public Kernel::Line_2, public JsonCGALBase
	{
		public:
			using Kernel::Line_2::Line_2;
			nlohmann::json encode();
			enum SupportedTypes::SupportedTypes getType() { return SupportedTypes::line_2; }
	};

   class Segment_2d : public Kernel::Segment_2, public JsonCGALBase
	{
		public:
			using Kernel::Segment_2::Segment_2;
			nlohmann::json encode();
			enum SupportedTypes::SupportedTypes getType() { return SupportedTypes::segment_2; }
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

};

#endif