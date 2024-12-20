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



//! \addtogroup op_unique
//! @{



template<typename T1>
inline
bool
op_unique::apply_helper(Mat<typename T1::elem_type>& out, const Proxy<T1>& P, const bool P_is_row)
  {
  arma_debug_sigprint();
  
  typedef typename T1::elem_type eT;
  
  const uword n_elem = P.get_n_elem();
  
  if(n_elem == 0)
    {
    if(P_is_row)
      {
      out.set_size(1,0);
      }
    else
      {
      out.set_size(0,1);
      }
    
    return true;
    }
  
  if(n_elem == 1)
    {
    const eT tmp = (Proxy<T1>::use_at) ? P.at(0,0) : P[0];
    
    out.set_size(1, 1);
    
    out[0] = tmp;
    
    return true;
    }
  
  Mat<eT> X(n_elem, 1, arma_nozeros_indicator());
  
  eT* X_mem = X.memptr();
  
  if(Proxy<T1>::use_at == false)
    {
    typename Proxy<T1>::ea_type Pea = P.get_ea();
    
    for(uword i=0; i<n_elem; ++i)
      {
      const eT val = Pea[i];
      
      if(arma_isnan(val))  { out.soft_reset(); return false; }
      
      X_mem[i] = val;
      }
    }
  else
    {
    const uword n_rows = P.get_n_rows();
    const uword n_cols = P.get_n_cols();
    
    for(uword col=0; col < n_cols; ++col)
    for(uword row=0; row < n_rows; ++row)
      {
      const eT val = P.at(row,col);
      
      if(arma_isnan(val))  { out.soft_reset(); return false; }
      
      (*X_mem) = val;  X_mem++;
      }
    
    X_mem = X.memptr();
    }
  
  arma_unique_comparator<eT> comparator;
  
  std::sort( X.begin(), X.end(), comparator );
  
  uword N_unique = 1;
  
  for(uword i=1; i < n_elem; ++i)
    {
    const eT a = X_mem[i-1];
    const eT b = X_mem[i  ];
    
    const eT diff = a - b;
    
    if(diff != eT(0)) { ++N_unique; }
    }
  
  if(P_is_row)
    {
    out.set_size(1, N_unique);
    }
  else
    {
    out.set_size(N_unique, 1);
    }
  
  eT* out_mem = out.memptr();
  
  if(n_elem > 0)  { (*out_mem) = X_mem[0];  out_mem++; }
  
  for(uword i=1; i < n_elem; ++i)
    {
    const eT a = X_mem[i-1];
    const eT b = X_mem[i  ];
    
    const eT diff = a - b;
    
    if(diff != eT(0))  { (*out_mem) = b;  out_mem++; }
    }
  
  return true;
  }



template<typename T1>
inline
void
op_unique::apply(Mat<typename T1::elem_type>& out, const Op<T1, op_unique>& in)
  {
  arma_debug_sigprint();
  
  const Proxy<T1> P(in.m);
  
  const bool all_non_nan = op_unique::apply_helper(out, P, false);
  
  arma_conform_check( (all_non_nan == false), "unique(): detected NaN" );
  }



template<typename T1>
inline
void
op_unique_vec::apply(Mat<typename T1::elem_type>& out, const Op<T1, op_unique_vec>& in)
  {
  arma_debug_sigprint();
  
  const Proxy<T1> P(in.m);
  
  const bool P_is_row = (T1::is_xvec) ? bool(P.get_n_rows() == 1) : bool(T1::is_row);
  
  const bool all_non_nan = op_unique::apply_helper(out, P, P_is_row);
  
  arma_conform_check( (all_non_nan == false), "unique(): detected NaN" );
  }



//! @}
