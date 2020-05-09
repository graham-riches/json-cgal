/**
 * \file JsonCGAL.cpp
 * \author Graham Riches (graham.riches@live.com)
 * \brief library for passing geometric data (point, segment, polygon, etc)
 *        from CGAL algorithms to a neutral file format (JSON). This enables
 *        fast algorithms in C++ and plotting/display in python.
 * \version 0.1
 * \date 2020-04-29
 * 
 * \copyright Copyright (c) 2020
 * 
 */

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "JsonCGAL.h"
#include "JsonCGALMap.h"
#include "json.hpp"

namespace JsonCGAL
{
	/**
	* \brief parse a json data field into the appropriate class list
	*
	* \param container, a json geometry container
	*/
	void JsonCGAL::parse_json_container(nlohmann::json container)
	{		
		/* containers */
		std::vector<double> coordinates;
		CGAL_list<Point_2d> points;
		std::string datatype;
		nlohmann::json field;
		nlohmann::json point;
		nlohmann::json points_container;

		/* iterate over the json container */
		for (nlohmann::json::iterator it = container.begin(); it < container.end(); it++)
		{
			field = *it;
			datatype = field["type"].get<std::string>();
			
			switch (key_map[datatype])
			{
				case SupportedTypes::point_2:
					coordinates = field["coordinates"].get<std::vector<double>>();
					this->_objs.push_back(Point_2d(coordinates[0], coordinates[1]));
					break;

				case SupportedTypes::line_2:
					points_container = field["points"];
					for (nlohmann::json::iterator j = points_container.begin(); j < points_container.end(); j++)
					{
						point = *j;
						coordinates = point["coordinates"].get<std::vector<double>>();
						points.push_back(Point_2d(coordinates[0], coordinates[1]));
					}
					this->_objs.push_back(Line_2d(points[0], points[1]));
					break;

				case SupportedTypes::segment_2:
					points_container = field["points"];
					for (nlohmann::json::iterator j = points_container.begin(); j < points_container.end(); j++)
					{
						point = *j;
						coordinates = point["coordinates"].get<std::vector<double>>();
						points.push_back(Point_2d(coordinates[0], coordinates[1]));
					}
					this->_objs.push_back(Segment_2d(points[0], points[1]));
					break;

				default:
					std::cout << "JSON: unsupported CGAL data type " << std::endl;
					break;
			}
		}
		return;
	}

	/**
	* \brief pack a json geometry object into a json array container
	*
	* \returns a json geometry container
	*/
	nlohmann::json JsonCGAL::create_json_container()
	{
		/* create the container as an empty array */
		nlohmann::json container = nlohmann::json::array();

		BOOST_FOREACH(CGAL_object &obj, this->_objs)
		{
			container.push_back(boost::apply_visitor(JsonCGALPack(), obj));
		}
		return container;
	}


	/**
		* \brief parse a json geometry file into a json geometry object
		*
		* \param filename, the string filename to open
		* \return success/failure
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
	 * \brief parse input from a json string stream
	 * 
	 * \param json_string 
	 * \return true 
	 * \return false 
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
		* \brief dump a json geometry object into a file
		*
		* \param filename, the string filename/path to record to
		* \return success/failure
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
	* \brief dump a json geometry object to a string
	*
	* \param filename, the string filename/path to record to
	* \return success/failure
	*/
	std::string JsonCGAL::dump_to_string()
	{
		nlohmann::json container = this->create_json_container();
		std::string output = container.dump(4);
		return output;
	}
};
