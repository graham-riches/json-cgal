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
         static JsonCGALBase *object_factory(nlohmann::json container);
         virtual nlohmann::json encode() = 0;
         virtual enum SupportedTypes::SupportedTypes getType() = 0;
   };

   class Point_2d : public Kernel::Point_2, public JsonCGALBase
	{
      private:
         std::string obj_type = "point_2";
		public:
			using Kernel::Point_2::Point_2;
         Point_2d decode_factory(nlohmann::json container);
			nlohmann::json encode();
			enum SupportedTypes::SupportedTypes getType() { return key_map[this->obj_type]; }
	};

   class Line_2d : public Kernel::Line_2, public JsonCGALBase
	{
      private:
         std::string obj_type = "line_2";
		public:
			using Kernel::Line_2::Line_2;
			nlohmann::json encode();
         enum SupportedTypes::SupportedTypes getType() { return key_map[this->obj_type]; }
	};

   class Segment_2d : public Kernel::Segment_2, public JsonCGALBase
	{
      private:
         std::string obj_type = "segment_2";
		public:
			using Kernel::Segment_2::Segment_2;
			nlohmann::json encode();
			enum SupportedTypes::SupportedTypes getType() { return key_map[this->obj_type]; }
	};

   class Weighted_point_2d : public Kernel::Weighted_point_2, public JsonCGALBase
   {
      private:
         std::string obj_type = "weighted_point_2";
	   public:
		   using Kernel::Weighted_point_2::Weighted_point_2;
		   nlohmann::json encode();
         enum SupportedTypes::SupportedTypes getType() { return key_map[this->obj_type]; }
   };

   class Vector_2d : public Kernel::Vector_2, public JsonCGALBase
   {
      private:
         std::string obj_type = "vector_2";
	   public:
		   using Kernel::Vector_2::Vector_2;
		   nlohmann::json encode();
         enum SupportedTypes::SupportedTypes getType() { return key_map[this->obj_type]; }
   };

   class Direction_2d : public Kernel::Direction_2, public JsonCGALBase
   {
      private:
         std::string obj_type = "direction_2";
	   public:
		   using Kernel::Direction_2::Direction_2;
		   nlohmann::json encode();
         enum SupportedTypes::SupportedTypes getType() { return key_map[this->obj_type]; }
   };

   class Ray_2d : public Kernel::Ray_2, public JsonCGALBase
   {
      private:
         std::string obj_type = "ray_2";
	   public:
		   using Kernel::Ray_2::Ray_2;
		   nlohmann::json encode();
         enum SupportedTypes::SupportedTypes getType() { return key_map[this->obj_type]; }
   };

   class Triangle_2d : public Kernel::Triangle_2, public JsonCGALBase
   {
      private:
         std::string obj_type = "triangle_2";
		public:
		   using Kernel::Triangle_2::Triangle_2;
		   nlohmann::json encode();
         enum SupportedTypes::SupportedTypes getType() { return key_map[this->obj_type]; }
   };

   class Iso_rectangle_2d : public Kernel::Iso_rectangle_2, public JsonCGALBase
   {
      private:
         std::string obj_type = "iso_rectangle_2";
	   public:
		   using Kernel::Iso_rectangle_2::Iso_rectangle_2;
		   nlohmann::json encode();
         enum SupportedTypes::SupportedTypes getType() { return key_map[this->obj_type]; }
   };

   class Circle_2d : public Kernel::Circle_2, public JsonCGALBase
   {
      private:
         std::string obj_type = "circle_2";
	   public:
		   using Kernel::Circle_2::Circle_2;
		   nlohmann::json encode();
         enum SupportedTypes::SupportedTypes getType() { return key_map[this->obj_type]; }
   };

};

#endif