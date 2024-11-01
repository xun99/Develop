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



//! \addtogroup op_shift
//! @{



template<typename T1>
inline
void
op_shift_vec::apply(Mat<typename T1::elem_type>& out, const Op<T1,op_shift_vec>& in)
  {
  arma_debug_sigprint();
  
  typedef typename T1::elem_type eT;
  
  const quasi_unwrap<T1> U(in.m);
  
  const uword len = in.aux_uword_a;
  const uword neg = in.aux_uword_b;
  
  const uword dim = (T1::is_xvec) ? uword(U.M.is_rowvec() ? 1 : 0) : uword((T1::is_row) ? 1 : 0);
  
  if(U.is_alias(out))
    {
    Mat<eT> tmp;
    
    op_shift::apply_noalias(tmp, U.M, len, neg, dim);
    
    out.steal_mem(tmp);
    }
  else
    {
    op_shift::apply_noalias(out, U.M, len, neg, dim);
    }
  }



template<typename eT>
inline
void
op_shift::apply_noalias(Mat<eT>& out, const Mat<eT>& X, const uword len, const uword neg, const uword dim)
  {
  arma_debug_sigprint();
  
  arma_conform_check_bounds( ((dim == 0) && (len >= X.n_rows)), "shift(): shift amount out of bounds" );
  arma_conform_check_bounds( ((dim == 1) && (len >= X.n_cols)), "shift(): shift amount out of bounds" );
  
  if(len == 0)  { out = X; return; }
  
  out.copy_size(X);
  
  const uword X_n_rows = X.n_rows;
  const uword X_n_cols = X.n_cols;
  
  if(dim == 0)
    {
    if(neg == 0)
      {
      for(uword col=0; col < X_n_cols; ++col)
        {
              eT* out_ptr = out.colptr(col);
        const eT*   X_ptr =   X.colptr(col);
        
        for(uword out_row=len, row=0; row < (X_n_rows - len); ++row, ++out_row)
          {
          out_ptr[out_row] = X_ptr[row];
          }
        
        for(uword out_row=0, row=(X_n_rows - len); row < X_n_rows; ++row, ++out_row)
          {
          out_ptr[out_row] = X_ptr[row];
          }
        }
      }
    else
    if(neg == 1)
      {
      for(uword col=0; col < X_n_cols; ++col)
        {
              eT* out_ptr = out.colptr(col);
        const eT*   X_ptr =   X.colptr(col);
        
        for(uword out_row=0, row=len; row < X_n_rows; ++row, ++out_row)
          {
          out_ptr[out_row] = X_ptr[row];
          }
        
        for(uword out_row=(X_n_rows-len), row=0; row < len; ++row, ++out_row)
          {
          out_ptr[out_row] = X_ptr[row];
          }
        }
      }
    }
  else
  if(dim == 1)
    {
    if(neg == 0)
      {
      if(X_n_rows == 1)
        {
              eT* out_ptr = out.memptr();
        const eT*   X_ptr =   X.memptr();
        
        for(uword out_col=len, col=0; col < (X_n_cols - len); ++col, ++out_col)
          {
          out_ptr[out_col] = X_ptr[col];
          }
        
        for(uword out_col=0, col=(X_n_cols - len); col < X_n_cols; ++col, ++out_col)
          {
          out_ptr[out_col] = X_ptr[col];
          }
        }
      else
        {
        for(uword out_col=len, col=0; col < (X_n_cols - len); ++col, ++out_col)
          {
          arrayops::copy( out.colptr(out_col), X.colptr(col), X_n_rows );
          }
        
        for(uword out_col=0, col=(X_n_cols - len); col < X_n_cols; ++col, ++out_col)
          {
          arrayops::copy( out.colptr(out_col), X.colptr(col), X_n_rows );
          }
        }
      }
    else
    if(neg == 1)
      {
      if(X_n_rows == 1)
        {
              eT* out_ptr = out.memptr();
        const eT*   X_ptr =   X.memptr();
        
        for(uword out_col=0, col=len; col < X_n_cols; ++col, ++out_col)
          {
          out_ptr[out_col] = X_ptr[col];
          }
        
        for(uword out_col=(X_n_cols-len), col=0; col < len; ++col, ++out_col)
          {
          out_ptr[out_col] = X_ptr[col];
          }
        }
      else
        {
        for(uword out_col=0, col=len; col < X_n_cols; ++col, ++out_col)
          {
          arrayops::copy( out.colptr(out_col), X.colptr(col), X_n_rows );
          }
        
        for(uword out_col=(X_n_cols-len), col=0; col < len; ++col, ++out_col)
          {
          arrayops::copy( out.colptr(out_col), X.colptr(col), X_n_rows );
          }
        }
      }
    }
  }



//! @}
