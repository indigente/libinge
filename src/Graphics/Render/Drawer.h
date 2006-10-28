/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004-2006 Indigente


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

#ifndef DRAWER_H
#define DRAWER_H

#include "enumDrawer.h"
#include <vector>
#include "../../Math/Vector4.h"
#include "../../Math/Vector3.h"
#include "../../Math/Vector2.h"


namespace InGE{

using std::vector;

	/**
	 *  Responsavel por fazer a interface com o pacote grafico
	 */
	class Drawer{
	  protected:
		static Drawer *drawer;	  

		//Construtor
		Drawer(){}
	  public:
	
		//Devolve um instancia unica da classe.
		static Drawer *getInstance();

		//Destrutor
		virtual ~Drawer() {}
		
		//Seta OpenGL como pacote grafico atual
		void setDrawerOpenGL();


		//Clausula usada no inicio de modelos geometricos
		virtual void begin(EnumDrawer e);
		
		//Limpa o buffer
		virtual void clear();
		
		//Define cor atual
		virtual void color(float r, float g, float b);
		virtual void color(Vector3 &vet);
		virtual void color(float r, float g, float b, float a);
		virtual void color(Vector4 &vet);

		//Clausula usada no final de modelos geometricos		
		virtual void end();

		//Ajusta a camera
		virtual void lookAt(Vector3 pos, Vector3 view, Vector3 up);

		//Especifica qual pilha de matriz eh alvo das operacoes		
		virtual void matrixMode(EnumDrawer e);

		//Guarda na pilha a Matriz atual
		virtual void pushMatrix();

		//Pega da pilha a Matrix de projecao
		virtual void popMatrix();		

		//Operacao de translacao
		virtual void translate(float x, float y, float z);
		virtual void translate(Vector3 &vet);

		//Operacao de rotacao
		virtual void rotate(float angle, float x, float y, float z);
		virtual void rotate(float angle, Vector3 &vet);
		virtual void rotate( Vector4 &vet );
		
		// Troca de Buffer do Double Buffer		
		virtual void swapBuffers();  
		
		// Seta coordenada de textura
		virtual void texCoord(float x, float y);
		virtual void texCoord(Vector2 &vet);
		
		// Define Vertice de um modelo geometrico
		virtual void vertex(float x, float y, float z);
		virtual void vertex(Vector3 &vet);
		
		// Define Vetor normal atual
		virtual void normal(float x, float y, float z);
		virtual void normal(Vector3 &vet);
		
		//Habilita e desabilita capacidades do Drawer
		virtual void enable(EnumDrawer cap);
		virtual void disable(EnumDrawer cap);
		
		//habilita e desabilita Luz especifica
		virtual void enableLight(int i);
		virtual void disableLight(int i);
		
		//habilita e desabilita plano de corte
		virtual void enableClipPlane(int i);
		virtual void disableClipPlane(int i);

		// Gera um ID para textura
		virtual void genTextures(int n, unsigned int *id);
		// Associa o ID da textura com seu tipo
		virtual void bindTexture(EnumDrawer target, unsigned int id);
		//Constroi Mipmaps de 2 dimensoes
		virtual void build2DMipmaps(	EnumDrawer target, 
						int internalFormat, 
						int width, 
						int height, 
						EnumDrawer format, 
						EnumDrawer type, 
						const void *data);
		//Especifica parametros para a textura
		virtual void texParameter(EnumDrawer target,
									EnumDrawer pname,
									int param);
		virtual void texEnv(EnumDrawer target, EnumDrawer pname, int param );
		
		virtual void texImage2D(EnumDrawer target,
					int level,
					int internalFormat,
					int width,
					int height,
					int border,
					EnumDrawer format,
					EnumDrawer type,
					const void *pixels);
		
		virtual void texSubImage2D(EnumDrawer target,
					   int level,
					   int xoffset,
					   int yoffset,
					   int width,
					   int height,
					   EnumDrawer format,
					   EnumDrawer type,
					   const void *pixels);

		//Especifica paramatros de neblina
		virtual void fog(EnumDrawer pname, float param);
		virtual void fog(EnumDrawer pname, int param);
		virtual void fog(EnumDrawer pname, Vector4 param);		
		virtual void hint(EnumDrawer target, EnumDrawer mode);
		
		virtual void shadeModel(EnumDrawer target);
		virtual void clearColor(float r,float g,float b,float a);
		virtual void ortho(float left, float right, float bottom, float top, float near, float far);
		virtual void viewport(int x,int y,unsigned int width,unsigned int height);
		virtual void loadIdentity();
		virtual	void perspective(float fovy,float aspect,float zNear,float zFar);
		
		virtual	void pointSize(float size);
		virtual void lineWidth(float size);

		virtual void light(EnumDrawer target, EnumDrawer pname, float params);
		virtual void light(EnumDrawer target, EnumDrawer pname, Vector4 &params);
		
		virtual void lightModel(EnumDrawer pname, EnumDrawer param);
		virtual void material(EnumDrawer face, EnumDrawer pname, EnumDrawer param);
		virtual void material(EnumDrawer face, EnumDrawer pname, Vector4 &params);
		
		virtual void multMatrix(const float *m);
		virtual void multMatrix(const double *m);
		
		virtual void pixelStore(EnumDrawer pname, float param);
		virtual void pixelStore(EnumDrawer pname, int param);
		
		virtual void pushAttrib(EnumDrawer mask);
		virtual void popAttrib();
		virtual void frontFace(EnumDrawer mode);
		
		virtual void enableClientState(EnumDrawer cap);
		virtual void disableClientState(EnumDrawer cap);		
		virtual void clientActiveTextureARB(EnumDrawer texture);
		virtual void activeTextureARB(EnumDrawer texture);		

		virtual void getDouble(EnumDrawer pname, double *param );
		virtual void getFloat(EnumDrawer pname, float *param );		
		virtual void getInteger(EnumDrawer pname, int *param);	
		
		virtual void vertexPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr);
		virtual void texCoordPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr);
		virtual void colorPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr);
		virtual void normalPointer(EnumDrawer type, unsigned int stride, const void *ptr);		
		virtual void drawElements(EnumDrawer mode, unsigned int count, EnumDrawer type, const void *ptr);
		virtual void drawArrays(EnumDrawer mode, int first, unsigned int count);			
		
		virtual void cullFace(EnumDrawer mode);
		
		virtual void depthMask(EnumDrawer flag);
		virtual void colorMask(EnumDrawer red, EnumDrawer green, EnumDrawer blue, EnumDrawer alpha);
		virtual void depthFunc(EnumDrawer func);
		virtual void blendFunc(EnumDrawer sfactor, EnumDrawer dfactor);
		virtual void stencilFunc(EnumDrawer func, EnumDrawer ref, EnumDrawer mask);
		virtual void stencilOp(EnumDrawer fail, EnumDrawer zfail, EnumDrawer zpass );
		
		virtual void polygonMode(EnumDrawer face, EnumDrawer mode);
		virtual void clearDepth(float depth);
		
		virtual void map( EnumDrawer target, float u1, float u2, int stride, int order, vector<Vector3> points);
		//virtual void map( EnumDrawer target, double u1, double u2, int stride, int order, vector<Vector3> points);
		
		virtual void map( EnumDrawer target, float u1, float u2, int ustride, int uorder, float v1, float v2, int vstride, int vorder, vector<Vector3> points);
		//virtual void map( EnumDrawer target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, vector<Vector3> points);
		
		virtual void mapGrid( int un, float u1, float u2 );
		virtual void mapGrid( int un, double u1, double u2 );
		
		virtual void mapGrid( int un, float u1, float u2, int vn, float v1, float v2 );
		virtual void mapGrid( int un, double u1, double u2, int vn, double v1, double v2 );
		
		virtual void evalCoord(float u);
		virtual void evalCoord(double u);
		
		virtual void evalCoord(float u, float v);
		virtual void evalCoord(double u, double v);
		
		virtual void evalMesh(EnumDrawer mode, int i1, int i2);
		virtual void evalMesh(EnumDrawer mode, int i1, int i2, int j1, int j2);
	};


};

#include "DrawerOpenGL.h"

#endif // DRAWER_H
