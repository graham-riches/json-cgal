/**
 * @file JsonPoint.cpp
 * @author Graham Riches (graham.riches@live.com)
 * @brief Point class for extending CGAL types with JSON encoding/decoding
 * @version 0.1
 * @date 2020-05-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "JsonPoint.h"
#include "json.hpp"

namespace JsonCGAL
{
    /**
	 * @brief json encoding method for Point class
	 * 
	 * @return nlohmann::json 
	 */
	nlohmann::json Point::encode()
	{
		nlohmann::json json;
		json = { {"type", "point"}, {"coordinates", {this->x(), this->y()} } };
		return json;
	}
};
