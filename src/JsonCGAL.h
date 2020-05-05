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
#include "JsonPoint.h"
#include "JsonLine.h"
#include "JsonSegment.h"
#include "CGAL_Types.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

namespace JsonCGAL
{	
	class JsonCGAL
	{
	private:
		void parse_json_container(nlohmann::json container);
		nlohmann::json create_json_container();
		CGAL_list<Point> _points;
		CGAL_list<Line> _lines;
		CGAL_list<Segment> _segments;
		
	public:
		bool load(std::string filename);
		bool load_from_string(std::string json_string);
		bool dump(std::string filename);
		std::string dump_to_string();

		/* accessors */
		CGAL_list<Point> get_points() { return this->_points; }
		void set_points( CGAL_list<Point> points ) { this->_points = points; }
		void set_points(CGALBaseTypes::BasePoint *points, int size);
		CGAL_list<Line> get_lines() { return this->_lines; }
		void set_lines(CGAL_list<Line> lines) { this->_lines = lines; }
		CGAL_list<Segment> get_segments() { return this->_segments; }
		void set_segments(CGAL_list<Segment> segments) { this->_segments = segments; }
	};
}

#endif /* __JSON_CGAL_H */