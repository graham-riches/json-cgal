/**
 * @file cgal_types.h
 * @author Graham Riches (graham.riches@live.com)
 * @brief contains wrapper types for python CGAL bindings
 * @version 0.1
 * @date 2020-05-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __CGAL_TYPES_H
#define __CGAL_TYPES_H

#include <vector>
#include "cgal_kernel_config.h"

namespace CGALTypes
{
    typedef struct
    {
        double x;
        double y;
    } Point;

    typedef struct
    {
        Point start;
        Point target;
    } Segment;

    typedef struct
    {
        Point start;
        Point target;
    } Line;

};

#endif /* __CGAL_TYPES_H */