Project xlwtest
===============

This project depends on the `xlw` third party library.  
Make sure that you have unzipped the provided `xlw-20.8.5.zip` file inside your `Develop` folder.


How to adjust the include and library paths
-------------------------------------------

* Open the `scratch.sln` solution file in Visual Studio 2022.
* Open the `xlwtest` project property pages.
* At the top of the Property Pages form, set "Configuration" to "All Configurations" and "Platform" to "All Platforms".
* Go to Configuration Properties -> C/C++
* Set "Additional Include Directories" to `PathToDevelopFolder/xlw-20.8.5/xlw/include`  
Paths relative to this project file will also work. For example `../../xlw-20.8.5/xlw/include`  
* Go to Configuration Properties -> Linker
* Set "Additional Library Directories" to `PathToDevelopFolder/xlw-20.8.5/xlw/lib/$(PlatformTarget)`  
The above information is saved in the project file `xlwtest.vcxproj`.  
After saving the project properties you can now select a Configuration (Debug|Release)  and a Platform (x64|x86) 
and build it by pressing F7

How to configure debugging with Excel
-------------------------------------
These settings allow us to start Excel from inside Visual Studio, load the .xll produced by the project into the Excel session and connect it to the C++ debugger.  
All this happens by simply pressing F5 in Visual Studio.

* From Visual Studio open the `xlwtest` project property pages.
* At the top of the Property Pages form, set "Configuration" to "All Configurations" and "Platform" to "All Platforms".
* Go to Configuration Properties -> Debugging  
	For 64-bit Excel, choose the `x64` platform version of the `xlwtest` project.  
	For 32-bit Excel, choose the `x86` platform version of the `xlwtest` project.  	
* Set "Command" to the path to your `excel.exe` executable.  
	The Excel 2016 executable is commonly found in  
	`C:/Program Files/Microsoft Office/root/Office16/excel.exe`  
	
* Set "Command Arguments" to "$(TargetPath)" and click OK.

The above information is *not* saved in the `xlwtest.vcxproj` but in the user-specific XML file `xlwtest.vcxproj.user`.

When you hit F5, Visual Studio may pop-up a dialog window saying that there is no Debugging Information for Excel.  
Check the "Don't show this dialog again" box and click Yes.

If Excel pops-up a security notice and you want to suppress it for ever, you need to reduce Excel's security settings.  
This is done in Excel by going to  
File -> Options -> Trust Center -> Trust Center Settings -> Add-ins  
Make sure all boxes are unchecked.
