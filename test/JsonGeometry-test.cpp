/**
 * @file JsonCGALUnitTests.cpp
 * @author Graham Riches (graham.riches@live.com)
 * @brief unit tests for the json geometry library
 * @version 0.1
 * @date 2020-04-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "gtest/gtest.h"
#include "JsonCGAL.h"
#include "JsonCGALTypes.h"
#include "json.hpp"
#include "cgal_kernel_config.h"
#include <boost/variant.hpp>
#include <boost/foreach.hpp>


TEST(JsonCGALTests, TestLoadInvalidFileReturnsFalse)
{
	JsonCGAL::JsonCGAL json_data;
	ASSERT_FALSE(json_data.load("invalid.json"));
}

TEST(JsonCGALTests, TestAddingAndGettingPoints)
{
	JsonCGAL::JsonCGAL json_data;
	CGAL_list<JsonCGAL::Point_2d> points;
	points.push_back(JsonCGAL::Point_2d(1, 0));
	points.push_back(JsonCGAL::Point_2d(-1, -1));
	json_data.add_objects(points);
	CGAL_list<JsonCGAL::Point_2d> points_validate = json_data.get_objects<JsonCGAL::Point_2d>(JsonCGAL::Point_2d());
	ASSERT_EQ(points[0].x(), points_validate[0].x());
}

TEST(JsonCGALTests, TestAddingAndGettingSegments)
{
	JsonCGAL::JsonCGAL json_data;
	CGAL_list<JsonCGAL::Segment_2d> segments;
	JsonCGAL::Point_2d start_point(-1, -1);
	JsonCGAL::Point_2d end_point(5, 5);
	segments.push_back(JsonCGAL::Segment_2d(start_point, end_point));
	json_data.add_objects(segments);
	CGAL_list<JsonCGAL::Segment_2d> segments_validate = json_data.get_objects<JsonCGAL::Segment_2d>(JsonCGAL::Segment_2d());
	JsonCGAL::Point_2d start_point_validate = segments_validate[0].start();
	JsonCGAL::Point_2d end_point_validate = segments_validate[0].target();
	ASSERT_EQ(start_point.x(), start_point_validate.x());
}

TEST(JsonCGALTests, TestMultipleVariantTypes)
{
	JsonCGAL::JsonCGAL json_data;
	CGAL_list<JsonCGAL::Point_2d> points;
	points.push_back(JsonCGAL::Point_2d(1, 0));
	points.push_back(JsonCGAL::Point_2d(-1, -1));
	json_data.add_objects(points);
	CGAL_list<JsonCGAL::Segment_2d> segments;
	segments.push_back(JsonCGAL::Segment_2d(JsonCGAL::Point_2d(0, 0), JsonCGAL::Point_2d(-1, -1)));
	json_data.add_objects(segments);
	CGAL_list<JsonCGAL::Point_2d> points_validate = json_data.get_objects<JsonCGAL::Point_2d>(JsonCGAL::Point_2d());
	CGAL_list<JsonCGAL::Segment_2d> segments_validate = json_data.get_objects<JsonCGAL::Segment_2d>(JsonCGAL::Segment_2d());
	ASSERT_EQ(points_validate[0].x(), points[0].x());
	ASSERT_GE(segments_validate.size(), 1);
}

TEST(JsonCGALTests, TestDumpingPointsToFileWorks)
{
	JsonCGAL::JsonCGAL json_data;
	CGAL_list<JsonCGAL::Point_2d> points;
	points.push_back(JsonCGAL::Point_2d(1, 0));
	points.push_back(JsonCGAL::Point_2d(-1, -1));
	json_data.add_objects(points);
	ASSERT_TRUE(json_data.dump("test_dump.json"));
}

TEST(JsonCGALTests, TestingDumpingSegmentsToFileWorks)
{
	JsonCGAL::JsonCGAL json_data;
	CGAL_list<JsonCGAL::Segment_2d> segments;
	segments.push_back(JsonCGAL::Segment_2d(JsonCGAL::Point_2d(0, 0), JsonCGAL::Point_2d(-1, -1)));
	json_data.add_objects(segments);
	ASSERT_TRUE(json_data.dump("test_dump.json"));
}

TEST(JsonCGALTests, TestLoadingFromStringWorks)
{
	JsonCGAL::JsonCGAL create_json_data;
	JsonCGAL::JsonCGAL load_json_data;
	std::string test_string;
	CGAL_list<JsonCGAL::Point_2d> points;
	points.push_back(JsonCGAL::Point_2d(1, 0));
	points.push_back(JsonCGAL::Point_2d(-1, -1));
	create_json_data.add_objects(points);
	test_string = create_json_data.dump_to_string();
	load_json_data.load_from_string(test_string);
	CGAL_list<JsonCGAL::Point_2d> points_validate = load_json_data.get_objects<JsonCGAL::Point_2d>(JsonCGAL::Point_2d());
	ASSERT_EQ(points_validate[0].x(), 1);
}

TEST(JsonCGALTests, TestDumpingToString)
{
	JsonCGAL::JsonCGAL json_data;
	std::string test_string;
	CGAL_list<JsonCGAL::Point_2d> points;
	points.push_back(JsonCGAL::Point_2d(1, 0));
	points.push_back(JsonCGAL::Point_2d(-1, -1));
	json_data.add_objects(points);
	test_string = json_data.dump_to_string();
	/* string length should at least include the word "point" */
	ASSERT_GE(test_string.length(), 5);
}

TEST(PointTests, TestEncodingPoint)
{
	JsonCGAL::Point_2d p(-1, 0);
	nlohmann::json json = p.encode();
	ASSERT_GE(json.size(), 1);
}

TEST(SegmentTests, TestEncodingSegment)
{
	JsonCGAL::Segment_2d s(JsonCGAL::Point_2d(0, 0), JsonCGAL::Point_2d(-1, -1));
	nlohmann::json json;
	json = s.encode();
	ASSERT_GE(json.size(), 1);
}

TEST(SegmentTests, TestDecodingManually)
{
	JsonCGAL::Segment_2d s(JsonCGAL::Point_2d(0, 0), JsonCGAL::Point_2d(-1, -1));
	nlohmann::json json;
	json = s.encode();
	std::vector<double> coordinates;
	coordinates = json["points"][0]["coordinates"].get<std::vector<double>>();
	ASSERT_EQ(coordinates[0], 0);
}

TEST(LineTests, TestEncodingLines)
{
	JsonCGAL::Line_2d l(JsonCGAL::Point_2d(0, 0), JsonCGAL::Point_2d(-1, 1));
	nlohmann::json json;
	json = l.encode();
	ASSERT_GE(json.size(), 1);
}