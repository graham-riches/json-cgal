/**
 * @file JsonCGAL.cpp
 * @author Graham Riches (graham.riches@live.com)
 * @brief library for passing geometric data (point, segment, polygon, etc)
 *        from CGAL algorithms to a neutral file format (JSON). This enables
 *        fast algorithms in C++ and plotting/display in python.
 * @version 0.1
 * @date 2020-04-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "JsonCGAL.h"
#include "json.hpp"

namespace JsonCGAL
{
	/* enumeration of supported CGAL types that are parsed as json keys*/
	namespace SupportedTypes
	{
		enum SupportedTypes
		{
			point,
			line,
			segment,
		};
	};
	

	/* create the json string key to enum mapping */
	static std::map<std::string, SupportedTypes::SupportedTypes> key_map = { {"point", SupportedTypes::point}, {"line", SupportedTypes::line}, {"segment", SupportedTypes::segment} };

	
	/**
	 * @brief create a points array based on a pointer to an array of CGAL points
	 * 
	 * @param points 
	 * @param size 
	 */
	void JsonCGAL::set_points(CGALTypes::Point *points, int size)
	{
		this->_points.clear();
		this->_points.reserve(size);
		for (int i=0; i<size; i++)
		{
			this->_points.push_back(Point(points->x, points->y));
			points++;
		}
	}


	/**
	* @brief parse a json data field into the appropriate class list
	*
	* @param container, a json geometry container
	*/
	void JsonCGAL::parse_json_container(nlohmann::json container)
	{		
		/* containers */
		std::vector<double> coordinates;
		CGAL_list<Point> points;
		std::string datatype;
		nlohmann::json field;
		nlohmann::json point;

		/* iterate over the json container */
		for (nlohmann::json::iterator it = container.begin(); it < container.end(); it++)
		{
			field = *it;
			datatype = field["type"].get<std::string>();
			
			switch (key_map[datatype])
			{
				case SupportedTypes::point:
					coordinates = field["coordinates"].get<std::vector<double>>();
					this->_points.push_back(Point(coordinates[0], coordinates[1]));
					break;

				case SupportedTypes::line:
					for (nlohmann::json::iterator j = field.begin(); j < field.end(); j++)
					{
						point = *j;
						coordinates = point["coordinates"].get<std::vector<double>>();
						points.push_back(Point(coordinates[0], coordinates[1]));
					}
					this->_lines.push_back(Line(points[0], points[1]));
					break;

				case SupportedTypes::segment:
					for (nlohmann::json::iterator j = field.begin(); j < field.end(); j++)
					{
						point = *j;
						coordinates = point["coordinates"].get<std::vector<double>>();
						points.push_back(Point(coordinates[0], coordinates[1]));
					}
					this->_segments.push_back(Segment(points[0], points[1]));
					break;

				default:
					std::cout << "JSON: unsupported CGAL data type " << std::endl;
					break;
			}
		}
		return;
	}

	/**
	* @brief pack a json geometry object into a json array container
	*
	* @returns a json geometry container
	*/
	nlohmann::json JsonCGAL::create_json_container()
	{
		Point point;
		Line line;
		Segment segment;

		/* create the container as an empty array */
		nlohmann::json container = nlohmann::json::array();
		
		/* encode the points */
		for (CGAL_list<Point>::iterator it = this->_points.begin(); it < this->_points.end(); it++)
		{
			point = *it;
			container.push_back(point.encode());
		}
		/* encode the lines */
		for (CGAL_list<Line>::iterator it = this->_lines.begin(); it < this->_lines.end(); it++)
		{
			line = *it;
			container.push_back(line.encode());
		}
		/* encode the segments */
		for (CGAL_list<Segment>::iterator it = this->_segments.begin(); it < this->_segments.end(); it++)
		{
			segment = *it;
			container.push_back(segment.encode());
		}

		return container;
	}


	/**
		* @brief parse a json geometry file into a json geometry object
		*
		* @param filename, the string filename to open
		* @return success/failure
	*/
	bool JsonCGAL::load(std::string filename)
	{
		nlohmann::json json_data;
		std::ifstream infile;
		infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			infile.open(filename.c_str());

			try
			{
				infile >> json_data;
			}
			catch (nlohmann::json::parse_error& e)
			{
				/* caught invalid json formatting error */
				std::cout << "message: " << e.what() << '\n'
						  << "exception id: " << e.id << '\n'
						  << "byte position of error: " << e.byte << std::endl;
				return false;
			}

			this->parse_json_container(json_data);
		}
		catch (std::ifstream::failure except)
		{
			/* TODO: print the exception details*/
			std::cout << "Exception while loading file " << std::endl;
			return false;
		}
		return true;
	}

	/**
	 * @brief parse input from a json string stream
	 * 
	 * @param json_string 
	 * @return true 
	 * @return false 
	 */
	bool JsonCGAL::load_from_string(std::string json_string)
	{
		nlohmann::json json_data;
		try
		{
			json_data = nlohmann::json::parse(json_string);
		}
		catch (nlohmann::json::parse_error& e)
		{
			/* caught invalid json formatting error */
			std::cout << "message: " << e.what() << '\n'
						<< "exception id: " << e.id << '\n'
						<< "byte position of error: " << e.byte << std::endl;
			return false;
		}
		this->parse_json_container(json_data);
		return true;
	}

	/**
		* @brief dump a json geometry object into a file
		*
		* @param filename, the string filename/path to record to
		* @return success/failure
	*/
	bool JsonCGAL::dump(std::string filename)
	{
		nlohmann::json container;
		std::ofstream outfile;
		outfile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		try
		{
			outfile.open(filename.c_str());

			/* make the container an empty array */
			container = this->create_json_container();

			outfile << std::setw(4) << container << std::endl;

		}
		catch (std::ofstream::failure except)
		{
			/* TODO: print the exception trace */
			std::cout << "Exception while dumping to file " << std::endl;
			return false;
		}
		return true;
	}

	/**
	* @brief dump a json geometry object to a string
	*
	* @param filename, the string filename/path to record to
	* @return success/failure
	*/
	std::string JsonCGAL::dump_to_string()
	{
		nlohmann::json container = this->create_json_container();
		std::string output = container.dump(4);
		return output;
	}
}
