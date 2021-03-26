/*
 *  Copyright 2008-2013 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*! \file trivial_copy.h
 *  \brief Sequential copy algorithms for plain-old-data.
 */

#pragma once

#include <thrust/detail/config.h>
#include <cstring>
#include <thrust/system/detail/sequential/general_copy.h>

#if THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_CUDA
#include <cub/detail/target.cuh>
#endif

namespace thrust
{
namespace system
{
namespace detail
{
namespace sequential
{


template<typename T>
__host__ __device__
  T *trivial_copy_n(const T *first,
                    std::ptrdiff_t n,
                    T *result)
{
  T* return_value = NULL;

#if THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_CUDA
  NV_IF_TARGET(NV_IS_HOST, (
    std::memmove(result, first, n * sizeof(T));
    return_value = result + n;
  ), ( // NV_IS_DEVICE:
    return_value = thrust::system::detail::sequential::general_copy_n(first, n, result);
  ));
#else
  std::memmove(result, first, n * sizeof(T));
  return_value = result + n;
#endif

  return return_value;
} // end trivial_copy_n()


} // end namespace sequential
} // end namespace detail
} // end namespace system
} // end namespace thrust

