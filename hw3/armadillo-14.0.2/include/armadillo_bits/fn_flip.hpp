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


//! \addtogroup fn_flip
//! @{



template<typename T1>
arma_warn_unused
arma_inline
typename enable_if2< is_arma_type<T1>::value, const Op<T1, op_flipud> >::result
flipud(const T1& X)
  {
  arma_debug_sigprint();
  
  return Op<T1, op_flipud>(X);
  }



template<typename T1>
arma_warn_unused
arma_inline
typename enable_if2< is_arma_type<T1>::value, const Op<T1, op_fliplr> >::result
fliplr(const T1& X)
  {
  arma_debug_sigprint();
  
  return Op<T1, op_fliplr>(X);
  }



template<typename T1>
arma_warn_unused
arma_inline
const SpOp<T1, spop_flipud>
flipud(const SpBase<typename T1::elem_type,T1>& X)
  {
  arma_debug_sigprint();
  
  return SpOp<T1, spop_flipud>(X.get_ref());
  }



template<typename T1>
arma_warn_unused
arma_inline
const SpOp<T1, spop_fliplr>
fliplr(const SpBase<typename T1::elem_type,T1>& X)
  {
  arma_debug_sigprint();
  
  return SpOp<T1, spop_fliplr>(X.get_ref());
  }



//! @}
