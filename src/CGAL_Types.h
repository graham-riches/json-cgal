/**
 * @file cgal_types.h
 * @author Graham Riches (graham.riches@live.com)
 * @brief contains more primative CGAL types for extending the module
 *        functionality with lower-level faster binding types.
 * @version 0.1
 * @date 2020-05-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __CGAL_TYPES_H
#define __CGAL_TYPES_H

#include "cgal_kernel_config.h"

namespace CGALBaseTypes
{
    typedef struct
    {
        double x;
        double y;
    } BasePoint;

    typedef struct
    {
        BasePoint start;
        BasePoint target;
    } BaseSegment;

    typedef struct
    {
        BasePoint start;
        BasePoint target;
    } BaseLine;

};

#endif /* __CGAL_TYPES_H */