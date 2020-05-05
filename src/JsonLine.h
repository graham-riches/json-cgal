/**
 * @file JsonLine.h
 * @author Graham Riches (graham.riches@live.com)
 * @brief line class that extends the functionality of the CGAL Line_2 with json encoding
 * @version 0.1
 * @date 2020-05-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __JSON_LINE_H
#define __JSON_LINE_h

#include "cgal_kernel_config.h"
#include "json.hpp"
#include "JsonPoint.h"

namespace JsonCGAL
{
    class Line : public Line_2
	{
		public:
			Point source;
			Point target;
			Line() : Line_2() {}
			Line(const Point &p, const Point &q) : Line_2{ p, q }, source{ p }, target{ q } {}
			nlohmann::json encode();
	};
};

#endif /* __JSON_LINE_H */
