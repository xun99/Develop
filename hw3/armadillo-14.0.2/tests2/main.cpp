// SPDX-License-Identifier: Apache-2.0
// 
// Copyright 2015 Conrad Sanderson (http://conradsanderson.id.au)
// Copyright 2015 National ICT Australia (NICTA)
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


#include <armadillo>

//#define CATCH_CONFIG_MAIN  // catch.hpp will define main()
#define CATCH_CONFIG_RUNNER  // we will define main()
#include "catch.hpp"


int
main(int argc, char** argv)
  {
  Catch::Session session;
  
  const int returnCode = session.applyCommandLine(argc, argv);
  
  if(returnCode != 0)  { return returnCode; }
  
  std::cout << "Armadillo version: " << arma::arma_version::as_string() << '\n';
  
  // Use Catch2 command-line to set the random seed.
  // -rng-seed <'time'|number>
  // If a number is provided this is used directly as the seed.
  // Alternatively if the keyword 'time' is provided
  // then the result of calling std::time(0) is used.
  
  const size_t seed = session.config().rngSeed();
  
  srand((unsigned int) seed);
  arma::arma_rng::set_seed(seed);
  
  return session.run(argc, argv);
  }

