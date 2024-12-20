// SPDX-License-Identifier: Apache-2.0
// 
// Copyright 2008-2016 Conrad Sanderson (http://conradsanderson.id.au)
// Copyright 2008-2016 National ICT Australia (NICTA)
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ------------------------------------------------------------------------


//! \addtogroup fn_all
//! @{



template<typename T1>
arma_warn_unused
inline
typename
enable_if2
  <
  is_arma_type<T1>::value && resolves_to_vector<T1>::yes,
  bool
  >::result
all(const T1& X)
  {
  arma_debug_sigprint();
  
  return op_all::all_vec(X);
  }



template<typename T1>
arma_warn_unused
arma_inline
typename
enable_if2
  <
  is_arma_type<T1>::value && resolves_to_vector<T1>::no,
  const mtOp<uword, T1, op_all>
  >::result
all(const T1& X)
  {
  arma_debug_sigprint();
  
  return mtOp<uword, T1, op_all>(X, 0, 0);
  }



template<typename T1>
arma_warn_unused
arma_inline
typename
enable_if2
  <
  is_arma_type<T1>::value,
  const mtOp<uword, T1, op_all>
  >::result
all(const T1& X, const uword dim)
  {
  arma_debug_sigprint();
  
  return mtOp<uword, T1, op_all>(X, dim, 0);
  }



//! for compatibility purposes: allows compiling user code designed for earlier versions of Armadillo
template<typename T>
arma_warn_unused
arma_inline
typename
enable_if2
  <
  is_supported_elem_type<T>::value,
  bool
  >::result
all(const T& val)
  {
  return (val != T(0));
  }



//! @}
