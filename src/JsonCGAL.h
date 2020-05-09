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
#include <boost/variant.hpp>
#include <boost/foreach.hpp>

#include "json.hpp"
#include "JsonCGALMap.h"
#include "JsonCGALTypes.h"
#include "cgal_kernel_config.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

namespace JsonCGAL
{	
   /* multi-object boost variant type for holding CGAL objects */
   typedef boost::variant<Point_2d, Segment_2d, Line_2d> CGAL_object;

   /* boost visitor class for unpacking objects */
   class JsonCGALUnpack : public boost::static_visitor<enum SupportedTypes::SupportedTypes>
   {
		public:
			enum SupportedTypes::SupportedTypes operator() (Point_2d   obj) const { return obj.getType(); }
			enum SupportedTypes::SupportedTypes operator() (Line_2d    obj) const { return obj.getType(); }
			enum SupportedTypes::SupportedTypes operator() (Segment_2d obj) const { return obj.getType(); }
   };

   /* boost visitor class for packing objects */
   class JsonCGALPack : public boost::static_visitor<nlohmann::json>
   {
		public:
			nlohmann::json operator() (Point_2d   obj) const { return obj.encode(); }
			nlohmann::json operator() (Line_2d    obj) const { return obj.encode(); }
			nlohmann::json operator() (Segment_2d obj) const { return obj.encode(); }
   };
 
   /* main object container class */
   class JsonCGAL
   {
   private:
	   void parse_json_container(nlohmann::json container);
	   nlohmann::json create_json_container();
	   CGAL_list<CGAL_object> _objs;

   public:
	   bool load(std::string filename);
	   bool load_from_string(std::string json_string);
	   bool dump(std::string filename);
	   std::string dump_to_string();

	   template <class T>
	   CGAL_list<T> get_objects( T object )
	   {
		   CGAL_list<T> container;
		   SupportedTypes::SupportedTypes objectType;

		   BOOST_FOREACH(CGAL_object &obj, this->_objs)
		   {
			   objectType = boost::apply_visitor(JsonCGALUnpack(), obj);
			   if (objectType == object.getType())
			   {
				   container.push_back(boost::get<T>(obj));
			   }
		   }
		   return container;
	   };
      
       template <class T>
       void add_objects(CGAL_list<T> objects)
	   {
		   for (CGAL_list<T>::iterator it = objects.begin(); it < objects.end(); it++)
		   {
			   this->_objs.push_back(*it);
		   }
		   return;
	   };
	   
   };
};


#endif /* __JSON_CGAL_H */