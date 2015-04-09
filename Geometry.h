///============================================================================
///@file	Geometry.h
///@brief	Class used for rendering the geometry in the scene.
///
///@author	Héctor Morales Piloni
///@date	November 18, 2006
///============================================================================

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

class Geometry
{
public:
	//-------------------------------------------------------------------------
	//Constructors and destructors
	//-------------------------------------------------------------------------
	Geometry();

	//-------------------------------------------------------------------------
	//Public methods
	//-------------------------------------------------------------------------
	void Draw(GLfloat angle);
	void SetLights(GLfloat pos[]);
	void SetCameraPosition(GLfloat pos[]);
	void SetMaterials();
	void SetShadowTexture();
	void GetCameraPosition(GLfloat *pos) const;
	void GetLightPosition(GLfloat *pos) const;
	void Transpose4x4Matrix(GLdouble M[]);
	GLuint GetShadowTexObj() const;

	//-------------------------------------------------------------------------
	//Public members
	//-------------------------------------------------------------------------
	static const GLuint DEPTH_MAP_WIDTH  = 512;	///> Depth map width
	static const GLuint DEPTH_MAP_HEIGHT = 512;	///> Depth map height

private:
	//-------------------------------------------------------------------------
	//Private members
	//-------------------------------------------------------------------------
	GLuint m_DepthMap;		///> A shadow texture object
	GLfloat m_Light[3];		///> Light's position
	GLfloat m_Camera[3];	///> Camera's position
};

#endif
