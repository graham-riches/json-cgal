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
#include "json.hpp"
#include "cgal_kernel_config.h"
#include "CGAL_Types.h"


TEST(JsonCGALTests, TestLoadInvalidFileReturnsFalse)
{
	JsonCGAL::JsonCGAL json_data;
	ASSERT_FALSE(json_data.load("invalid.json"));
}

TEST(JsonCGALTests, TestSettingPointsFromList)
{
	CGALTypes::Point points[] = { {1, 1}, {2, 2} };
	JsonCGAL::JsonCGAL json_data;
	json_data.set_points(points, sizeof(points));
	CGAL_list<JsonCGAL::Point> check_points = json_data.get_points();
	ASSERT_EQ(points[0].x, check_points[0].x());
}

TEST(JsonCGALTests, TestGettingPoints)
{
	JsonCGAL::JsonCGAL json_data;
	json_data.load("points.json");
	CGAL_list<JsonCGAL::Point> points = json_data.get_points();
	ASSERT_GE(points.size(), 0);
}

TEST(JsonCGALTests, TestDumpingPointsToFileWorks)
{
	JsonCGAL::JsonCGAL json_data;
	CGAL_list<JsonCGAL::Point> points;
	points.push_back(JsonCGAL::Point(1, 0));
	points.push_back(JsonCGAL::Point(-1, -1));
	json_data.set_points(points);
	ASSERT_TRUE(json_data.dump("test_dump.json"));
}

TEST(JsonCGALTests, TestingDumpingSegmentsToFileWorks)
{
	JsonCGAL::JsonCGAL json_data;
	CGAL_list<JsonCGAL::Segment> segments;
	segments.push_back(JsonCGAL::Segment(JsonCGAL::Point(0, 0), JsonCGAL::Point(-1, -1)));
	json_data.set_segments(segments);
	ASSERT_TRUE(json_data.dump("test_dump.json"));
}

TEST(JsonCGALTests, TestLoadingFromStringWorks)
{
	JsonCGAL::JsonCGAL create_json_data;
	JsonCGAL::JsonCGAL load_json_data;
	std::string test_string;
	CGAL_list<JsonCGAL::Point> points;
	points.push_back(JsonCGAL::Point(1, 0));
	points.push_back(JsonCGAL::Point(-1, -1));
	create_json_data.set_points(points);
	test_string = create_json_data.dump_to_string();
	load_json_data.load_from_string(test_string);
	CGAL_list<JsonCGAL::Point> parsed_points;
	parsed_points = load_json_data.get_points();
	ASSERT_EQ(parsed_points[0].x(), 1);
}

TEST(JsonCGALTests, TestDumpingToString)
{
	JsonCGAL::JsonCGAL json_data;
	std::string test_string;
	CGAL_list<JsonCGAL::Point> points;
	points.push_back(JsonCGAL::Point(1, 0));
	points.push_back(JsonCGAL::Point(-1, -1));
	json_data.set_points(points);
	test_string = json_data.dump_to_string();
	ASSERT_GE(test_string.length(), 1);
}

TEST(PointTests, TestEncodingPoint)
{
	JsonCGAL::Point p(-1, 0);
	nlohmann::json json = p.encode();
	ASSERT_GE(json.size(), 1);
}

TEST(SegmentTests, TestEncodingSegment)
{
	JsonCGAL::Segment s(Point_2(0, 0), Point_2(-1, -1));
	nlohmann::json json;
	json = s.encode();
	ASSERT_GE(json.size(), 1);
}

TEST(SegmentTests, TestDecodingManually)
{
	JsonCGAL::Segment s(Point_2(0, 0), Point_2(-1, -1));
	nlohmann::json json;
	json = s.encode();
	std::vector<double> coordinates;
	coordinates = json["points"][0]["coordinates"].get<std::vector<double>>();
	ASSERT_EQ(coordinates[0], 0);
}

TEST(LineTests, TestEncodingLines)
{
	JsonCGAL::Line l(JsonCGAL::Point(0, 0), JsonCGAL::Point(-1, 1));
	nlohmann::json json;
	json = l.encode();
	ASSERT_GE(json.size(), 1);
}