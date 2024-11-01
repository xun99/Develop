
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



//! \addtogroup glue_powext
//! @{



class glue_powext
  : public traits_glue_or
  {
  public:
  
  template<typename T1, typename T2> inline static void apply(Mat<typename T1::elem_type>& out, const Glue<T1,T2,glue_powext>& X);
  
  template<typename eT> inline static void apply(Mat<eT>& out, const Mat<eT>& A, const Mat<eT>& B);
  
  template<typename parent, unsigned int mode, typename T2> inline static Mat<typename parent::elem_type> apply(const subview_each1<parent,mode>& X, const Base<typename parent::elem_type,T2>& Y);
  
  //
  
  template<typename T1, typename T2> inline static void apply(Cube<typename T1::elem_type>& out, const GlueCube<T1,T2,glue_powext>& X);
  
  template<typename eT> inline static void apply(Cube<eT>& out, const Cube<eT>& A, const Cube<eT>& B);
  
  template<typename eT, typename T2> inline static Cube<eT> apply(const subview_cube_each1<eT>& X, const Base<eT,T2>& Y);
  };



class glue_powext_cx
  : public traits_glue_or
  {
  public:
  
  template<typename T1, typename T2> inline static void apply(Mat<typename T1::elem_type>& out, const mtGlue<typename T1::elem_type,T1,T2,glue_powext_cx>& X);
  
  template<typename T> inline static void apply(Mat< std::complex<T> >& out, const Mat< std::complex<T> >& A, const Mat<T>& B);
  
  template<typename parent, unsigned int mode, typename T2> inline static Mat<typename parent::elem_type> apply(const subview_each1<parent,mode>& X, const Base<typename T2::elem_type,T2>& Y);
  
  //
  
  template<typename T1, typename T2> inline static void apply(Cube<typename T1::elem_type>& out, const mtGlueCube<typename T1::elem_type,T1,T2,glue_powext_cx>& X);
  
  template<typename T> inline static void apply(Cube< std::complex<T> >& out, const Cube< std::complex<T> >& A, const Cube<T>& B);
  
  template<typename T, typename T2> inline static Cube< std::complex<T> > apply(const subview_cube_each1< std::complex<T> >& X, const Base<T,T2>& Y);
  };



//! @}
