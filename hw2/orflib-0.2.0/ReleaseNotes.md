ORFLIB Release Notes
====================

VERSION 0.2.0
-------------

### Additions

1. New file `orflib/exception.hpp`.  
	Definition of orf::Exception class and the ORF_ASSERT macro.

2. New folder `orflib/math/stats` to contain statistics related source files.

3. New files `orflib/math/stats/errorfunction.hpp` and `errorfunction.cpp`.  
	Definition of class ErrorFunction.

4. New files `orflib/math/stats/univariatedistribution.hpp` and `normaldistribution.hpp`.  
	Definition of `UnivariateDistribution` and `NormalDistribution` classes.

5. New folder `orflib/math/pricers` to contain pricing related source files.

6. New files `orflib/math/pricers/simplepricers.hpp` and `simplepricers.cpp`.  
	Definition of the functions fwdPrice(), digitalOptionBS() and europeanOptionBS().

7. New file `xlorflib/xlfunctions1.cpp`.  
	Added definition of the following functions:  
	xlOrfErf(), xlOrfInvErf(), xlOrfNormalCdf(), xlOrfNormalInvCdf(), xlOrfFwdPrice(), xlOrfDigiBS() and xlOrfEuroBS().

8. In file `xlorflib/xlregister1.cpp`  
	Added registration of Excel callable functions:   
	ORF.ERF, ORF.INVERF, ORF.NORMALCDF, ORF.NORMALINVCDF, ORF.FWDPRICE, ORF.DIGIBS, ORF.EUROBS.

9. New spreadsheet example `examples/Excel/orflib-0.2.0-examples.xlsx`  
	

### Modifications

1. Removed unnecessary file `orflib/empty.cpp`


VERSION 0.1.0
-------------

### Additions

1. New folder `orflib` with start-up code for the core library.

2. `orflib/orflib.vcxproj` VC++ project file, that builds the core library `orlib.lib`.

3. New folder `xlorflib` with start-up code for the Excel interface.

4. `xlorflib/xlorflib.vcxproj` VC++ project file, that builds the `xlorflib.xll` Excel add-in.

5. `orflib.sln` Visual Studio solution file, that contains the projects `orflib` and `xlorflib`.

6. This release notes file.

7. `.gitignore` file for managing which files to keep under revision control.
