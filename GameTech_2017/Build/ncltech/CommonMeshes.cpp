#include "CommonMeshes.h"
#include <nclgl\OBJMesh.h>

Mesh* CommonMeshes::m_pPlane	= NULL;
Mesh* CommonMeshes::m_pCube		= NULL;
Mesh* CommonMeshes::m_pCube_groud = NULL;

Mesh* CommonMeshes::m_pSphere	= NULL;
Mesh* CommonMeshes::m_pSphereballtower = NULL;
Mesh* CommonMeshes::m_pSphereball = NULL;
Mesh* CommonMeshes::m_pSphereballshoot = NULL;


GLuint CommonMeshes::m_CheckerboardTex = 0;
GLuint CommonMeshes::m_CheckerboardTex1 = 0;
GLuint CommonMeshes::m_CheckerboardTexball = 0;
GLuint CommonMeshes::m_CheckerboardTexballshoot = 0;

GLuint CommonMeshes::m_groud = 0;


void CommonMeshes::InitializeMeshes()
{
	if (m_pPlane == NULL)
	{


		m_CheckerboardTex = SOIL_load_OGL_texture(TEXTUREDIR"ballF.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		
		glBindTexture(GL_TEXTURE_2D, m_CheckerboardTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
		glBindTexture(GL_TEXTURE_2D, 0);

		m_CheckerboardTex1 = SOIL_load_OGL_texture(TEXTUREDIR"checkerboard.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

		glBindTexture(GL_TEXTURE_2D, m_CheckerboardTex1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
		glBindTexture(GL_TEXTURE_2D, 0);


		m_CheckerboardTexball = SOIL_load_OGL_texture(TEXTUREDIR"ballS.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

		glBindTexture(GL_TEXTURE_2D, m_CheckerboardTexball);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
		glBindTexture(GL_TEXTURE_2D, 0);

		m_CheckerboardTexballshoot = SOIL_load_OGL_texture(TEXTUREDIR"ballshoot.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

		glBindTexture(GL_TEXTURE_2D, m_CheckerboardTexballshoot);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
		glBindTexture(GL_TEXTURE_2D, 0);

		m_groud = SOIL_load_OGL_texture(TEXTUREDIR"target.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

		glBindTexture(GL_TEXTURE_2D, m_groud);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //No linear interpolation to get crisp checkerboard no matter the scalling
		glBindTexture(GL_TEXTURE_2D, 0);


		m_pPlane = Mesh::GenerateQuadTexCoordCol(Vector2(2.f, 2.f), Vector2(0.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_pCube = new OBJMesh(MESHDIR"cube.obj");
		m_pCube_groud = new OBJMesh(MESHDIR"cube.obj");
		m_pSphere = new OBJMesh(MESHDIR"sphere.obj");
		m_pSphereballtower= new OBJMesh(MESHDIR"sphere.obj");
		m_pSphereball = new OBJMesh(MESHDIR"sphere.obj");
		m_pSphereballshoot = new OBJMesh(MESHDIR"sphere.obj");

		m_pPlane->SetTexture(m_CheckerboardTex);

		m_pCube->SetTexture(m_CheckerboardTex1);

		m_pCube_groud->SetTexture(m_groud);

		m_pSphere->SetTexture(m_CheckerboardTex);
		m_pSphereballtower->SetTexture(m_CheckerboardTex1);

		m_pSphereball->SetTexture(m_CheckerboardTexball);
		m_pSphereballshoot->SetTexture(m_CheckerboardTexballshoot);

	}
}

void CommonMeshes::ReleaseMeshes()
{
	if (m_pPlane != NULL)
	{
		glDeleteTextures(1, &m_CheckerboardTex);
		delete m_pPlane;
		delete m_pCube;
		delete m_pSphere;
	}

	m_pPlane = NULL;
}