/**
 * @file JsonCGAL.h
 * @author Graham Riches (graham.riches@live.com)
 * @brief library for passing geometric data (point, segment, polygon, etc)
 *        from CGAL algorithms to a neutral file format (JSON). This enables
 *        data sharing between C++ and Python.
 * @version 0.1
 * @date 2020-04-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __JSON_CGAL_H
#define __JSON_CGAL_H

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <string>
#include <fstream>
#include <vector>

#include "json.hpp"
#include "JsonCGALMap.h"
#include "JsonCGALTypes.h"
#include "cgal_kernel_config.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

namespace JsonCGAL
{	
   /* main object container class */
   class JsonCGAL
   {
   private:
	   void parse_json_container(nlohmann::json container);
	   nlohmann::json create_json_container();
	   CGAL_list<JsonCGALBase *> _objs;

   public:
	   bool load(std::string filename);
	   bool load_from_string(std::string json_string);
	   bool dump(std::string filename);
	   std::string dump_to_string();
      ~JsonCGAL()
      {
         for (CGAL_list<JsonCGALBase*>::iterator it = this->_objs.begin(); it < this->_objs.end(); it++)
         {
            delete(*it);
         }
      }

	   template <class T>
	   CGAL_list<T> get_objects( T object )
	   {
		   CGAL_list<T> container;
         for (CGAL_list<JsonCGALBase*>::iterator it = this->_objs.begin(); it < this->_objs.end(); it++)
         {
            if ((*it)->getType() == object.getType())
            {
               T& obj = dynamic_cast<T&>(*(*it));
               container.push_back(obj);
            }
         }
		   return container;
	   };
      
      template <class T>
      void add_objects(CGAL_list<T> objects)
	   {
         T *new_obj;
		   for (CGAL_list<T>::iterator it = objects.begin(); it < objects.end(); it++)
		   {
            new_obj = new T;
            *new_obj = *it;
			   this->_objs.push_back(new_obj);
		   }
		   return;
	   };
   };
};


#endif /* __JSON_CGAL_H */