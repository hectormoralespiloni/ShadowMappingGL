///============================================================================
///@file	Geometry.cpp
///@brief	Class used for rendering the geometry in the scene.
///
///@author	Héctor Morales Piloni
///@date	November 18, 2006
///============================================================================

#include "Geometry.h"

///----------------------------------------------------------------------------
///Default constructor
///----------------------------------------------------------------------------
Geometry::Geometry() : m_DepthMap(0)
{
}

///----------------------------------------------------------------------------
///Draw the objects in the scene
///@param	angle - used to animate part of the geometry
///----------------------------------------------------------------------------
void Geometry::Draw(GLfloat angle)
{
	//Display lists for the objects
	static GLuint BaseList=0, SphereList=0, ConeList=0, TorusList=0;

	//create Base display list if needed
	if(!BaseList)
	{
		BaseList = glGenLists(1);
		glNewList(BaseList, GL_COMPILE);
		{
			glColor3f(0.0, 0.0, 1.0);
			glPushMatrix();

			glScalef(7.0, 0.3, 7.0);
			glutSolidCube(1.0);

			glPopMatrix();
		}
		glEndList();
	}

	//Create torus display list if needed
	if(!TorusList)
	{
		TorusList=glGenLists(1);
		glNewList(TorusList, GL_COMPILE);
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glPushMatrix();

			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glutSolidTorus(0.3, 1.0, 24, 48);

			glPopMatrix();
		}
		glEndList();
	}

	//create Spheres display list if needed
	if(!SphereList)
	{
		SphereList = glGenLists(1);
		glNewList(SphereList, GL_COMPILE);
		{
			glColor3f(0.0, 1.0, 0.0);
			glPushMatrix();

			glTranslatef(0.5f, 2.0f, 0.5f);
			glutSolidSphere(0.2, 24, 24);

			glTranslatef(-1.0f, 0.0f, 0.0f);
			glutSolidSphere(0.2, 24, 24);

			glTranslatef(0.0f, 0.0f,-1.0f);
			glutSolidSphere(0.2, 24, 24);

			glTranslatef(1.0f, 0.0f, 0.0f);
			glutSolidSphere(0.2, 24, 24);

			glPopMatrix();
		}
		glEndList();
	}

	//create Cone display list if needed
	if(!ConeList)
	{
		ConeList = glGenLists(1);
		glNewList(ConeList, GL_COMPILE);
		{
			glColor3f(1.0, 1.0, 0.0);
			glPushMatrix();

			glTranslatef(2.0, 0.0, 2.0);
			glRotatef(-90, 1.0, 0.0, 0.0);
			glutSolidCone(0.3, 2.0, 25, 25);

			glTranslatef(-4.0, 0.0, 0.0);
			glutSolidCone(0.3, 2.0, 25, 25);

			glTranslatef(0.0, 4.0, 0.0);
			glutSolidCone(0.3, 2.0, 25, 25);

			glTranslatef(4.0, 0.0, 0.0);
			glScalef(1.0, 1.0, 1.5);
			glutSolidCone(0.3, 2.0, 25, 25);

			glPopMatrix();
		}
		glEndList();
	}

	//draw objects
	glCallList(BaseList);
	glCallList(TorusList);
	glCallList(ConeList);

	//animate and draw spheres
	glPushMatrix();
	glRotatef(angle, 0.0, 1.0, 0.0);
	glCallList(SphereList);
	glPopMatrix();

}

///----------------------------------------------------------------------------
///Set the lights in the scene
///----------------------------------------------------------------------------
void Geometry::SetLights(GLfloat pos[])
{
	//define the light position
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	//enable lighting and light0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

///----------------------------------------------------------------------------
///Set the materials of the objects in the scene
///----------------------------------------------------------------------------
void Geometry::SetMaterials()
{
	GLfloat white[4] = {1.0, 1.0, 1.0};

	//set object color as material color
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//enable color material state
	glEnable(GL_COLOR_MATERIAL);

	//enable specular lighting
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.f);
}

///----------------------------------------------------------------------------
///Sets the camera position.
///@param	pos[] - the camera position (x,y,z)
///----------------------------------------------------------------------------
void Geometry::SetCameraPosition(GLfloat pos[])
{
	m_Camera[0] = pos[0];
	m_Camera[1] = pos[1];
	m_Camera[2] = pos[2];
}

///----------------------------------------------------------------------------
///Gets the camera position.
///@param	pos[] - the returned camera position (x,y,z)
///----------------------------------------------------------------------------
void Geometry::GetCameraPosition(GLfloat *pos) const
{
	pos[0] = m_Camera[0];
	pos[1] = m_Camera[1];
	pos[2] = m_Camera[2];
}

///----------------------------------------------------------------------------
///Gets the light position.
///@param	pos[] - the returned light position (x,y,z)
///----------------------------------------------------------------------------
void Geometry::GetLightPosition(GLfloat *pos) const
{
	pos[0] = m_Light[0];
	pos[1] = m_Light[1];
	pos[2] = m_Light[2];
}

///----------------------------------------------------------------------------
///Set textures for shadow maps
///----------------------------------------------------------------------------
void Geometry::SetShadowTexture()
{
	//generate the texture name
	glGenTextures(1, &m_DepthMap);

	//the first time we call this function initializes the 2D texture 
	//object with NULL texture image
	glBindTexture(GL_TEXTURE_2D, m_DepthMap);

	//specify the 2D texture image
	glTexImage2D(GL_TEXTURE_2D,			//target must be GL_TEXTURE_2D
				 0,						//LOD number
				 GL_DEPTH_COMPONENT,	//number of color components
				 DEPTH_MAP_WIDTH,		//width
				 DEPTH_MAP_HEIGHT,		//height
				 0,						//border
				 GL_DEPTH_COMPONENT,	//format of pixel data
				 GL_UNSIGNED_BYTE,		//type of pixel data
				 NULL);					//pointer to image data in memory

	//set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//enable needed states
	glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);
    glEnable(GL_TEXTURE_GEN_Q);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
}

///----------------------------------------------------------------------------
///GetShadowTextObj()
///@returns the current shadow texture objectID
///----------------------------------------------------------------------------
GLuint Geometry::GetShadowTexObj() const
{
	return m_DepthMap;
}

///----------------------------------------------------------------------------
///Computes the transposed matrix of the given 4x4 matrix
///@param	m - an array of floats representing the matrix (16 values)
///----------------------------------------------------------------------------
void Geometry::Transpose4x4Matrix(GLdouble M[16])
{
    GLdouble  tmp;
	#define Swap(a, b)	tmp = a; a = b; b = tmp
		Swap(M[1],  M[4]);
		Swap(M[2],  M[8]);
		Swap(M[3],  M[12]);
		Swap(M[6],  M[9]);
		Swap(M[7],  M[13]);
		Swap(M[11], M[14]);
	#undef Swap
}
