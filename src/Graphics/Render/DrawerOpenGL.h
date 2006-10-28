/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004 Indigente


This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/

#ifndef DRAWEROPENGL_H
#define DRAWEROPENGL_H

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <SDL/SDL.h>


#include "enumDrawer.h"
#include "Drawer.h"
#include "../../Math/Vector2.h"
#include "../../Math/Vector3.h"
#include "../../Math/Vector4.h"


namespace InGE{

	using namespace InGE;
	
	// Camada entre o motor e OpenGL
	// Implementacao inline
	class DrawerOpenGL : public InGE::Drawer {
	  private:
		GLenum convert2GLenum(EnumDrawer e);
	  public:
  		DrawerOpenGL();
		virtual ~DrawerOpenGL();

		//Clausula usada no inicio de modelos geometricos
		void begin(EnumDrawer e);

		//Limpa o buffer
		void clear();

		//Define cor atual
		void color(float r, float g, float b);
		void color(Vector3 &vet);
		void color(float r, float g, float b, float a);
		void color(Vector4 &vet);		
		
		//Clausula usada no final de modelos geometricos
		void end();

		// Seta a Camera
		void lookAt(Vector3 pos, Vector3 view, Vector3 up);

		//Especifica qual pilha de matriz eh alvo das operacoes		
		void matrixMode(EnumDrawer e);

		//Guarda na pilha a Matriz atual
		void pushMatrix();

		//Pega da pilha a Matrix de projecao
		void popMatrix();		

		//Operacao de translacao
		void translate(float x, float y, float z);
		void translate(Vector3 &vet);

		//Operacao de rotacao
		void rotate(float angle, float x, float y, float z);
		void rotate(float angle, Vector3 &vet);
		void rotate( Vector4 &vet );
		
		// Troca de Buffer do Double Buffer
		void swapBuffers();

		// Seta coordenada de textura
		void texCoord(float x, float y);
		void texCoord(Vector2 &vet);

		// Define Vertice de um modelo geometric
		void vertex(float x, float y, float z);
		void vertex(Vector3 &vet);

		// Define Vetor normal atual
		void normal(float x, float y, float z);
		void normal(Vector3 &vet);

		//Habilita e desabilita capacidades do OpenGL
		void enable(EnumDrawer cap);
		void disable(EnumDrawer cap);

		//habilita e desabilita Luz especifica
		void enableLight(int i);
		void disableLight(int i);
		
		//habilita e desabilita plano de corte
		void enableClipPlane(int i);
		void disableClipPlane(int i);

		// Gera um ID para textura
		void genTextures(int n, unsigned int *id);
		// Associa o ID da textura com seu tipo
		void bindTexture(EnumDrawer target, unsigned int id);
		//Constroi Mipmaps de 2 dimensoes
		void build2DMipmaps(	EnumDrawer target, 
					int internalFormat, 
					int width, 
					int height, 
					EnumDrawer format, 
					EnumDrawer type, 
					const void *data);
		
		void texImage2D(EnumDrawer target,
				int level,
				int internalFormat,
				int width,
				int height,
				int border,
				EnumDrawer format,
				EnumDrawer type,
				const void *pixels);
		
		void texSubImage2D(EnumDrawer target,
				   int level,
				   int xoffset,
				   int yoffset,
				   int width,
				   int height,
				   EnumDrawer format,
				   EnumDrawer type,
				   const void *pixels);
		
		//Especifica parametros para a textura
		void texParameter(EnumDrawer target,
				EnumDrawer pname,
				int param);
		void texEnv(EnumDrawer target, EnumDrawer pname, int param );

		void fog(EnumDrawer pname, float param);
		void fog(EnumDrawer pname, int param);
		void fog(EnumDrawer pname, Vector4 param);		
		void hint(EnumDrawer target, EnumDrawer mode);		
		
		void shadeModel(EnumDrawer target);
		void clearColor(float r,float g,float b,float a);
		void ortho(float left, float right, float bottom, float top, float near, float far);
		void viewport(int x,int y,unsigned int width,unsigned int height);
		void loadIdentity();
		void perspective(float fovy,float aspect,float zNear,float zFar);
		
		void pointSize(float size);
		void lineWidth(float size);
		
		void light(EnumDrawer target, EnumDrawer pname, float params);
		void light(EnumDrawer target, EnumDrawer pname, Vector4 &params);

		void lightModel(EnumDrawer pname, EnumDrawer param);
		void material(EnumDrawer face, EnumDrawer pname, EnumDrawer param);		
		void material(EnumDrawer face, EnumDrawer pname, Vector4 &params);		

		void multMatrix(const float *m);
		void multMatrix(const double *m);
		
		void pixelStore(EnumDrawer pname, float param);
		void pixelStore(EnumDrawer pname, int param);
		
		void pushAttrib(EnumDrawer mask);
		void popAttrib();
		
		void frontFace(EnumDrawer mode);
		
		void enableClientState(EnumDrawer cap);
		void disableClientState(EnumDrawer cap);
		void clientActiveTextureARB(EnumDrawer texture);		
		void activeTextureARB(EnumDrawer texture);	
		
		void getDouble(EnumDrawer pname, double *param );
		void getFloat(EnumDrawer pname, float *param );		
		void getInteger(EnumDrawer pname, int *param);		

		void vertexPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr);
		void texCoordPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr);
		void colorPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr);
		void normalPointer(EnumDrawer type, unsigned int stride, const void *ptr);		

		void drawElements(EnumDrawer mode, unsigned int count, EnumDrawer type, const void *ptr);
		void drawArrays(EnumDrawer mode, int first, unsigned int count);	
		
		void cullFace(EnumDrawer mode);		
						
		void colorMask(EnumDrawer red, EnumDrawer green, EnumDrawer blue, EnumDrawer alpha);
		void depthMask(EnumDrawer flag);
		void depthFunc(EnumDrawer func);
		void blendFunc(EnumDrawer sfactor, EnumDrawer dfactor);	
		void stencilFunc(EnumDrawer func, EnumDrawer ref, EnumDrawer mask);
		void stencilOp(EnumDrawer fail, EnumDrawer zfail, EnumDrawer zpass );
		void polygonMode(EnumDrawer face, EnumDrawer mode);
		void clearDepth(float depth);
		
		void map( EnumDrawer target, float u1, float u2, int stride, int order, vector<Vector3> points);
		//void map( EnumDrawer target, double u1, double u2, int stride, int order, vector<Vector3> points);
		
		void map( EnumDrawer target, float u1, float u2, int ustride, int uorder, float v1, float v2, int vstride, int vorder, vector<Vector3> points);
		//void map( EnumDrawer target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, vector<Vector3> points);
		
		void mapGrid( int un, float u1, float u2 );
		void mapGrid( int un, double u1, double u2 );
		
		void mapGrid( int un, float u1, float u2, int vn, float v1, float v2 );
		void mapGrid( int un, double u1, double u2, int vn, double v1, double v2 );
		
		void evalCoord(float u);
		void evalCoord(double u);
		
		void evalCoord(float u, float v);
		void evalCoord(double u, double v);
		
		void evalMesh(EnumDrawer mode, int i1, int i2);
		void evalMesh(EnumDrawer mode, int i1, int i2, int j1, int j2);

	};

};


#endif // DRAWEROPENGL_H
