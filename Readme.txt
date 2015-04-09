
SHADOW MAPPING GL (Nov-2006)
----------------------------

1. SUMMARY 
	This demo performs a classic shadow mapping using OpenGL.

2. REQUIREMENTS TO RUN THE EXE
	-OpenGL runtimes installed (glu32.dll, glut32.dll)
	
3. HOW TO PLAY THE DEMO
	-+/- => Zoom the camera
	
4. HOW TO COMPILE
	In order to compile this demo you will need:
	-Microsoft Visual Studio 2005.

	-Microsoft Platform SDK (only needed if using VS Express Edition).
 	In order to setup Visual C++ 2005 Express Edition with the Microsoft 
 	platform SDK you probably need to read this: 
 	http://msdn.microsoft.com/vstudio/express/visualc/usingpsdk/

	-Microsoft Windows OpenGL 1.2+ libraries for linking (glu32.lib).
 	This should be already present in your VS installation.

	-OpenGL Utility Toolkit (GLUT) for Win32 which can be dowloaded from: 
 	http://www.xmission.com/~nate/glut.html

5. CODE STURCTURE
	The main program creates and starts an instance of a GLApp which 
	inherits from the abstract class GraphicsApp (which is used in 
	other of my demos either with OpenGL or DX).

	"GraphicsApp" creates the main windows application loop and the 
	window display (i.e. the basic windows stuff).
 
	"GLApp" takes care of processing the messages, initialize the OpenGL
	engine and render the demo scene.

	"Geometry" class methods are called from GLApp and they take care
	or rendering the actual scene, set lights and cameras and
	materials. 

	"Timer" class by Adam Hoult which handles all timing functionality 
	such as counting the number of frames per second, etc.	


