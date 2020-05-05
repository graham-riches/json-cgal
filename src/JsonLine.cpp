/**
 * @file JsonLine.cpp
 * @author Graham Riches (graham.riches@live.com)
 * @brief extends CGAL line class with json encoding
 * @version 0.1
 * @date 2020-05-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "JsonLine.h"
#include "cgal_kernel_config.h"


namespace JsonCGAL
{
	/**
	 * @brief json encoding method for Line class
	 * 
	 * @return nlohmann::json 
	 */
	nlohmann::json Line::encode()
	{
		nlohmann::json json;
		json = { {"type", "line"}, {"points", {this->source.encode(), this->target.encode()} } };
		return json;
	}
};
