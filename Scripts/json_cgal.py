# -*- coding: utf-8 -*-
"""
\brief python side json parser for json CGAL geometry schema
\author: Graham Riches
\date: Sat May  2 07:54:07 2020
\description
    parse a CGAL json format into python types.
"""

import json
import jsonschema


class Point_2:
    """ representation of a 2D CGAL point """
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def encode(self):
        return {'type': 'point_2', 'coordinates': [self.x, self.y]}


class Segment_2:
    """ representation of a 2D CGAL segment """
    def __init__(self, p: Point_2, q: Point_2):
        self.p = p
        self.q = q

    def encode(self):
        return {'type': 'segment_2', 'points': [self.p.encode(),
                                              self.q.encode()]}


class Line_2:
    """ representation of a 2D CGAL line """
    def __init__(self, p: Point_2, q: Point_2):
        self.p = p
        self.q = q

    def encode(self):
        return {'type': 'line_2', 'points': [self.p.encode(),
                                              self.q.encode()]}


class JsonCGAL:
    def __init__(self):
        self.points = []
        self.lines = []
        self.segments = []

        # load the schema when the object is created
        self._schema = None
        self.load_schema()

    def load_schema(self):
        """ load the format schema """
        try:
		    path = os.path.dirname(__file__)
            schema_path = os.path.join(path, 'schema.json')
            with open(schema_path, 'r') as schema_file:
                self._schema = json.loads(schema_file.read())
        except FileNotFoundError as file_error:
            print(file_error)

    def validate_format(self, json_data: str):
        """ validate the json file matches the schema """
        try:
            jsonschema.validate(instance=json_data, schema=self._schema)
            return True
        except jsonschema.exceptions.ValidationError as ValidationError:
            print('Invalid json format: {}'.format(ValidationError))
            return False

    def load(self, filepath):
        """ load in the json file, validate, and parse """
        try:
            with open(filepath, 'r') as read_file:
                json_data = read_file.read()
                self.decode(json_data)
        except Exception as caught_exception:
            print('ERROR: {}'.format(caught_exception))

    def decode(self, json_data: str):
        """ convert string data to json """
        try:
            if not self.validate_format(json_data):
                return
            objs = json.loads(json_data, object_hook=self.decoder)
            if objs is not None:
                self.points = [obj for obj in objs if type(obj) == Point_2]
                self.segments = [obj for obj in objs if type(obj) == Segment_2]
                self.lines = [obj for obj in objs if type(obj) == Line_2]
        except Exception as caught_exception:
            print('ERROR: {}'.format(caught_exception))

    def encode(self):
        """ encode data as json string """
        objs = []
        objs.extend(self.points)
        objs.extend(self.lines)
        objs.extend(self.segments)
        json_data = [obj.encode() for obj in objs]
        return json.dumps(json_data, indent=3)

    def dump(self, filepath):
        """ dump json geometry data to a file """
        try:
            with open(filepath, 'w') as json_file:
                json_file.write(self.encode())
        except Exception as caught_exception:
            print('ERROR: {}'.format(caught_exception))

    def decoder(self, obj):
        """
        hook for json parsing to create class members directly
        from json
        """
        if 'type' in obj:
            if obj['type'] == 'point_2':
                return Point_2(*obj['coordinates'])
            elif obj['type'] == 'segment_2':
                return Segment_2(*obj['points'])
            elif obj['type'] == 'line_2':
                return Line_2(*obj['points'])


if __name__ == '__main__':
    json_geo = JsonCGAL()
    json_geo.load('points.json')
    segment = Segment_2(Point_2(1, 0), Point_2(-1, 1))
    json_geo.segments = [segment]
    json_geo.dump('test.json')
