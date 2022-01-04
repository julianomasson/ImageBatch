# ImageBatch

This is my version of the http://www.imagebatch.org/ software. I didn't want to keep installing the old visual studio redistributable every time, so I created this version to maintain only the functions that I use and add the missing ones.  

### How do I get set up? ###

Use Visual Studio 2015 or newer and CMake.

Libraries  
- wxWidgest >= 3.1.5 - You need to build it using the project wx_vcXX.sln (XX is your visual studio version) wich is inside the "wxWidgets-3.1.5\build\msw" folder.  
- OpenCV >= 4.0.0 - You can download the binaries.  
- NSIS >= 3.08 - Used to create the installer.  

### Using the ImageBatch ###

![image](https://user-images.githubusercontent.com/47462118/148135526-cccb38aa-4ac5-4494-b980-5e3ca37262b1.png)

1. Select the input directory with the images ([BMP, JPEG, PNG and TIFF are supported on Windows](https://docs.opencv.org/4.5.5/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56)); 
2. Select the output directory or set the checkbox to use the input as output (the images will be overwritten);  
3. Select the operation in the notebook;  
4. Adjust the parameters;  
5. Press "Start".
