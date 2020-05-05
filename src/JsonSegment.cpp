/**
 * @file JsonSegment.cpp
 * @author Graham Riches (graham.riches@live.com)
 * @brief 
 * @version 0.1
 * @date 2020-05-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "json.hpp"
#include "JsonSegment.h"

namespace JsonCGAL
{
    /**
	 * @brief json encoding method for Segment class
	 * 
	 * @return nlohmann::json 
	 */
	nlohmann::json Segment::encode()
	{
		nlohmann::json json;
		json = { {"type", "segment"}, {"points", {this->source.encode(), this->target.encode()} } };
		return json;
	}
};
