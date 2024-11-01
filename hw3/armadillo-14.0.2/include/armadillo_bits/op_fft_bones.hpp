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



//! \addtogroup op_fft
//! @{



class op_fft_real
  : public traits_op_passthru
  {
  public:
  
  template<typename T1>
  inline static void apply( Mat< std::complex<typename T1::pod_type> >& out, const mtOp<std::complex<typename T1::pod_type>,T1,op_fft_real>& in );
  };



class op_fft_cx
  : public traits_op_passthru
  {
  public:
  
  template<typename T1>
  inline static void apply( Mat<typename T1::elem_type>& out, const Op<T1,op_fft_cx>& in );
  
  template<typename eT, bool inverse>
  inline static void apply_noalias(Mat<eT>& out, const Mat<eT>& X, const uword a, const uword b);
  };



class op_ifft_cx
  : public traits_op_passthru
  {
  public:
  
  template<typename T1>
  inline static void apply( Mat<typename T1::elem_type>& out, const Op<T1,op_ifft_cx>& in );
  };



//! @}
