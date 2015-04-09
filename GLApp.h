///============================================================================
///@file	GLApp.h
///@brief	Defines the Main OpenGL application class.
///			This class inherits from Application abstract class which
///			takes care of the windows creation and main render loop
///
///@author	Héctor Morales Piloni
///@date	November 13, 2006
///============================================================================

#ifndef GLAPP_H
#define GLAPP_H

#include "GraphicsApp.h"
#include "Geometry.h"
#include "Timer.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

class GLApp : public GraphicsApp
{
public:
	//-------------------------------------------------------------------------
	//Constructors and destructors
	//-------------------------------------------------------------------------
	GLApp();
	GLApp(LPSTR windowTitle, USHORT width, USHORT height);
	virtual ~GLApp();

	//-------------------------------------------------------------------------
	//Public methods
	//-------------------------------------------------------------------------
	virtual void InitGraphics();
	virtual void Render();
	virtual void RenderText(LPTSTR text);
	virtual bool ShutDown();
	virtual LRESULT DisplayWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

private:
	//-------------------------------------------------------------------------
	//Private methods
	//-------------------------------------------------------------------------
	void CreateShadowMap(GLfloat angle);
	void CreateTextureMatrix();
	void Reshape(int w,int h);
	void Zoom(GLfloat zoomFactor);

	//-------------------------------------------------------------------------
	//Private members
	//-------------------------------------------------------------------------
	HGLRC		m_hRC;		///> Handle to OpenGL Rendering Context
	Geometry	m_Geometry;	///> Used to draw all the geometry in the scene
	Timer		m_Timer;	///> GL Application timer
	GLdouble	m_CameraProjectionMatrix[16];	///> Camera projection matrix
	GLdouble	m_CameraViewMatrix[16];			///> Camera model-view matrix
	GLdouble	m_LightProjectionMatrix[16];	///> Light projection matrix
	GLdouble	m_LightViewMatrix[16];			///> Light model-view matrix
};

#endif