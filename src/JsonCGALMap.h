/**
 * \file JsonCGALMap.h
 * \author Graham Riches (graham.riches@live.com)
 * \brief contains the string to enum mapping for the json CGAL library
 * \version 0.1
 * \date 2020-05-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __JSON_CGAL_MAP_H
#define __JSON_CGAL_MAP_H

#include <map>
#include <string>

namespace JsonCGAL
{
   /* enumeration of supported CGAL types that are parsed as json keys*/
	namespace SupportedTypes
	{
		enum SupportedTypes
		{
			point_2,
			line_2,
			segment_2,
			weighted_point_2,
			vector_2,
			direction_2,
			ray_2,
			triangle_2,
			iso_rectangle_2,
			circle_2,
		};
	};
	
	/* create the json string key to enum mapping */
	static std::map<std::string, SupportedTypes::SupportedTypes> key_map = 
   { 
      {"point_2", SupportedTypes::point_2},                   {"line_2", SupportedTypes::line_2},         {"segment_2", SupportedTypes::segment_2},
      {"weighted_point_2", SupportedTypes::weighted_point_2}, {"vector_2", SupportedTypes::vector_2},     {"direction_2", SupportedTypes::direction_2},
      {"ray_2", SupportedTypes::ray_2},                       {"triangle_2", SupportedTypes::triangle_2}, {"iso_rectangle_2", SupportedTypes::iso_rectangle_2},
      {"circle_2", SupportedTypes::circle_2},
   };


};

#endif /* __JSON_CGAL_MAP_H */

