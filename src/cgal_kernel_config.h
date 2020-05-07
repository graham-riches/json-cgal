/**
 * \file cgal_kernel_config.h
 * \author Graham Riches (graham.riches@live.com)
 * \brief configure the CGAL kernel to be used.
 * \version 0.1
 * \date 2020-05-03
 * 
 * \copyright Copyright (c) 2020
 * 
 */

#ifndef __CGAL_KERNEL_CONFIG
#define __CGAL_KERNEL_CONFIG

#include <CGAL/Simple_cartesian.h>

/* setup the CGAL kernel */
typedef CGAL::Simple_cartesian<double> Kernel;

/* create a generic container for holding geometry objects */
template<typename T>
using CGAL_list = std::vector<T>;

#endif