/**
 * @file JsonSegment.h
 * @author Graham Riches (graham.riches@live.com)
 * @brief segment class that extends the functionality of the CGAL Segment_2 with json encoding
 * @version 0.1
 * @date 2020-05-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __JSON_SEGMENT_H
#define __JSON_SEGMENT_H

#include "cgal_kernel_config.h"
#include "JsonPoint.h"

namespace JsonCGAL
{
    class Segment : public Segment_2
	{
		public:
			Point source;
			Point target;
			Segment() : Segment_2() {}
			Segment(const Point &p, const Point &q) : Segment_2{ p, q }, source{ p }, target{ q } {}
			nlohmann::json encode();
	};
};


#endif /* __JSON_SEGMENT_H */
