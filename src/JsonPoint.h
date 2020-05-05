/**
 * @file JsonPoint.h
 * @author Graham Riches (graham.riches@live.com)
 * @brief point class that extends the functionality of the CGAL Point_2 with json encoding
 * @version 0.1
 * @date 2020-05-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __JSON_POINT_H
#define __JSON_POINT_H

#include "cgal_kernel_config.h"
#include "json.hpp"

namespace JsonCGAL
{
    class Point : public Point_2
	{
		public:
			using Point_2::Point_2;
			nlohmann::json encode();
	};
};


#endif /* __JSON_POINT_H */
