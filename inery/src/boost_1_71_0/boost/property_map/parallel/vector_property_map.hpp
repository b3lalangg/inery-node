// Copyright (C) Vladimir Prus 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/graph/vector_property_map.html for
// documentation.
//

#ifndef BOOST_PROPERTY_MAP_PARALLEL_VECTOR_PROPERTY_MAP_HPP_VP_2003_03_04
#define BOOST_PROPERTY_MAP_PARALLEL_VECTOR_PROPERTY_MAP_HPP_VP_2003_03_04

#include <boost/property_map/property_map.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <boost/property_map/parallel/distributed_property_map.hpp>
#include <boost/property_map/parallel/local_property_map.hpp>

namespace boost {

/** Distributed vector property map.
 *
 * This specialization of @ref vector_property_map builds a
 * distributed vector property map given the local index maps
 * generated by distributed graph types that automatically have index
 * properties. 
 *
 * This specialization is useful when creating external distributed
 * property maps via the same syntax used to create external
 * sequential property maps.
 */
template<typename T, typename ProcessGroup, typename GlobalMap, 
         typename StorageMap>
class vector_property_map<T, 
                          local_property_map<ProcessGroup, GlobalMap,
                                             StorageMap> >
  : public parallel::distributed_property_map<
             ProcessGroup, GlobalMap, vector_property_map<T, StorageMap> >
{
  typedef vector_property_map<T, StorageMap> local_iterator_map;

  typedef parallel::distributed_property_map<ProcessGroup, GlobalMap, 
                                             local_iterator_map> inherited;

  typedef local_property_map<ProcessGroup, GlobalMap, StorageMap> index_map_type;

public:
  vector_property_map(const index_map_type& index = index_map_type())
    : inherited(index.process_group(), index.global(),
                local_iterator_map(index.base())) { }

  vector_property_map(unsigned inital_size, 
                      const index_map_type& index = index_map_type())
    : inherited(index.process_group(),  index.global(),
                local_iterator_map(inital_size, index.base())) { }
};

/** Distributed vector property map.
 *
 * This specialization of @ref vector_property_map builds a
 * distributed vector property map given the local index maps
 * generated by distributed graph types that automatically have index
 * properties. 
 *
 * This specialization is useful when creating external distributed
 * property maps via the same syntax used to create external
 * sequential property maps.
 */
template<typename T, typename ProcessGroup, typename GlobalMap, 
         typename StorageMap>
class vector_property_map<
        T, 
        parallel::distributed_property_map<
          ProcessGroup,
          GlobalMap,
          StorageMap
        >
      > 
  : public parallel::distributed_property_map<
             ProcessGroup, GlobalMap, vector_property_map<T, StorageMap> >
{
  typedef vector_property_map<T, StorageMap> local_iterator_map;

  typedef parallel::distributed_property_map<ProcessGroup, GlobalMap, 
                                             local_iterator_map> inherited;

  typedef parallel::distributed_property_map<ProcessGroup, GlobalMap, 
                                             StorageMap>
    index_map_type;

public:
  vector_property_map(const index_map_type& index = index_map_type())
    : inherited(index.process_group(), index.global(),
                local_iterator_map(index.base())) { }

  vector_property_map(unsigned inital_size, 
                      const index_map_type& index = index_map_type())
    : inherited(index.process_group(), index.global(),
                local_iterator_map(inital_size, index.base())) { }
};

}

#endif // BOOST_PROPERTY_MAP_PARALLEL_VECTOR_PROPERTY_MAP_HPP_VP_2003_03_04