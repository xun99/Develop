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



//! \addtogroup op_sp_nonzeros
//! @{



template<typename T1>
inline
void
op_sp_nonzeros::apply(Mat<typename T1::elem_type>& out, const SpToDOp<T1, op_sp_nonzeros>& X)
  {
  arma_debug_sigprint();
  
  typedef typename T1::elem_type eT;
  
  const SpProxy<T1> P(X.m);
  
  const uword N = P.get_n_nonzero();
  
  out.set_size(N,1);
  
  if(N == 0)  { return; }
  
  if(is_SpMat<typename SpProxy<T1>::stored_type>::value)
    {
    const unwrap_spmat<typename SpProxy<T1>::stored_type> U(P.Q);
    
    arrayops::copy(out.memptr(), U.M.values, N);
    
    return;
    }
  
  if(is_SpSubview<typename SpProxy<T1>::stored_type>::value)
    {
    const SpSubview<eT>& sv = reinterpret_cast< const SpSubview<eT>& >(P.Q);
    
    if(sv.n_rows == sv.m.n_rows)
      {
      const SpMat<eT>& m   = sv.m;
      const uword      col = sv.aux_col1;
      
      arrayops::copy(out.memptr(), &(m.values[ m.col_ptrs[col] ]), N);
      
      return;
      }
    }
  
  eT* out_mem = out.memptr();
  
  typename SpProxy<T1>::const_iterator_type it = P.begin();
  
  for(uword i=0; i<N; ++i)  { out_mem[i] = (*it); ++it; }
  }



//! @}
