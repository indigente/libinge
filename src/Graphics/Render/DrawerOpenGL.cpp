/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004 Indigente 


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
 
#include "DrawerOpenGL.h"
#include <iostream>
using namespace std;

using namespace InGE;

DrawerOpenGL::DrawerOpenGL(){

}

DrawerOpenGL::~DrawerOpenGL(){
}


//Clausula usada no inicio de modelos geometricos
void DrawerOpenGL::begin(EnumDrawer e){
	glBegin(e);
}

//Limpa o buffer
void DrawerOpenGL::clear(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
	glLoadIdentity(); 			
}

//Define cor atual
void DrawerOpenGL::color(float r, float g, float b){
	glColor3f(r,g,b);
}
void DrawerOpenGL::color(Vector3 &vet){
	glColor3fv(vet.toArray());
}
void DrawerOpenGL::color(float r, float g, float b, float a){
	glColor4f(r,g,b,a);
}
void DrawerOpenGL::color(Vector4 &vet){
	glColor4fv(vet.toArray());	
}
	
		
		
void DrawerOpenGL::end(){
	glEnd();		
}



// Seta a Camera
void DrawerOpenGL::lookAt(Vector3 pos, Vector3 view, Vector3 up){
	gluLookAt(pos.getX(),  pos.getY(),  pos.getZ(),
		  view.getX(), view.getY(), view.getZ(),
		  up.getX(),   up.getY(),   up.getZ());	
}



//Especifica qual pilha de matriz eh alvo das operacoes		
void DrawerOpenGL::matrixMode(EnumDrawer e){
	glMatrixMode(e);
}



//Guarda na pilha a Matriz atual
void DrawerOpenGL::pushMatrix(){
	glPushMatrix();
}



//Pega da pilha a Matrix de projecao
void DrawerOpenGL::popMatrix(){
	glPopMatrix();
}




//Operacao de translacao
void DrawerOpenGL::translate(float x, float y, float z){
	glTranslatef(x,y,z);
}
void DrawerOpenGL::translate(Vector3 &vet){
	glTranslatef(vet.getX(), vet.getY(), vet.getZ());
}



//Operacao de rotacao
void DrawerOpenGL::rotate(float angle, float x, float y, float z){
	glRotatef(angle, x,y,z);
}
void DrawerOpenGL::rotate(float angle, Vector3 &vet){
	glRotatef(angle, vet.getX(), vet.getY(), vet.getZ());
}
void DrawerOpenGL::rotate( Vector4 &vet ){
	glRotatef(vet[0], vet[1], vet[2], vet[3]);
}


// Troca de Buffer do Double Buffer
void DrawerOpenGL::swapBuffers(){
	SDL_GL_SwapBuffers();
}


void DrawerOpenGL::texCoord(float x, float y){
	glTexCoord2f(x,y);
}	

void DrawerOpenGL::texCoord(Vector2 &vet){
	glTexCoord2fv(vet.toArray());
}			

void DrawerOpenGL::vertex(float x, float y, float z){
	glVertex3f(x,y,z);
}

void DrawerOpenGL::vertex(Vector3 &vet){
	glVertex3fv(vet.toArray());
}

void DrawerOpenGL::normal(float x, float y, float z){
	glNormal3f(x,y,z);
}

void DrawerOpenGL::normal(Vector3 &vet){
	glNormal3fv(vet.toArray());
}
	
//Habilita e desabilita capacidades do Drawer
void DrawerOpenGL::enable(EnumDrawer cap){
	glEnable(cap);
}

void DrawerOpenGL::disable(EnumDrawer cap){
	glDisable(cap);
}	

//habilita e desabilita Luz especifica
void DrawerOpenGL::enableLight(int i){
	glEnable(GL_LIGHT0+i);
}
void DrawerOpenGL::disableLight(int i){
	glDisable(GL_LIGHT0+i);
}
		
//habilita e desabilita plano de corte
void DrawerOpenGL::enableClipPlane(int i){
	glEnable(GL_CLIP_PLANE0 + i);
}
void DrawerOpenGL::disableClipPlane(int i){
	glDisable(GL_CLIP_PLANE0 + i);
}

/**
 * Define tamanho do ponto
 */
void DrawerOpenGL::pointSize(float size){
	glPointSize(size);
}

/**
 * Define grossura da linha
 */
void DrawerOpenGL::lineWidth(float size){
	glLineWidth(size);
}
// Gera um ID para textura
void DrawerOpenGL::genTextures(int n, unsigned int *id){
	glGenTextures(n, id);
}

// Associa o ID da textura com seu tipo
void DrawerOpenGL::bindTexture(EnumDrawer target, unsigned int id){
	glBindTexture(target, id);
}

//Constroi Mipmaps de 2 dimensoes
void DrawerOpenGL::build2DMipmaps(EnumDrawer trgt, int iFrmt, int w, int h, EnumDrawer frmt, EnumDrawer tp, const void *data){
	gluBuild2DMipmaps(trgt, iFrmt, w, h, frmt, tp, data);
}
//Constroi Textura de 2 dimensoes
void DrawerOpenGL::texImage2D(EnumDrawer target, int level, int internalFormat, int width, int height, int border, EnumDrawer format, EnumDrawer type, const void *pixels){
	glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
}

void DrawerOpenGL::texSubImage2D(EnumDrawer target, int level, int xoffset, int yoffset, int width, int height, EnumDrawer format, EnumDrawer type, const void *pixels){
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

//Especifica parametros para a textura
void DrawerOpenGL::texParameter(EnumDrawer trgt, EnumDrawer pname,	int param){
	glTexParameteri(trgt, pname, param);
}

void DrawerOpenGL::texEnv(EnumDrawer target, EnumDrawer pname, int param ){
	glTexEnvi(target, pname, param);
}

void DrawerOpenGL::fog(EnumDrawer pname, float param){
	glFogf(pname, param);
}

void DrawerOpenGL::fog(EnumDrawer pname, int param){
	glFogi(pname, param);
}


void DrawerOpenGL::fog(EnumDrawer pname, Vector4 param){
	glFogfv(pname, param.toArray());
}

void DrawerOpenGL::hint(EnumDrawer target, EnumDrawer mode){
	glHint(target, mode);
}

void DrawerOpenGL::shadeModel(EnumDrawer target){
	glShadeModel(target);
}

void DrawerOpenGL::clearColor(float r,float g,float b,float a){
	glClearColor(r,g,b,a);
}

void DrawerOpenGL::ortho(float left, float right, float bottom, float top, float near, float far){
	glOrtho(left, right, bottom, top, near, far);
}

void DrawerOpenGL::viewport(int x,int y,unsigned int width,unsigned int height){
	glViewport(x,y,width,height);
}

void DrawerOpenGL::loadIdentity(){
	glLoadIdentity();
}

void DrawerOpenGL::perspective(float fovy,float aspect,float zNear,float zFar){
	gluPerspective(fovy, aspect, zNear, zFar);
}

void DrawerOpenGL::light(EnumDrawer target, EnumDrawer pname, float params){
	glLightf(target, pname, params);
}
void DrawerOpenGL::light(EnumDrawer target, EnumDrawer pname, Vector4 &params){
	glLightfv(target, pname, params.toArray());
}

/**
 * Especifica um parametro do modelo de light
 * @param pname Especifica o tipo de parametro
 * @param param Valor do parametro
 */
void DrawerOpenGL::lightModel(EnumDrawer pname, EnumDrawer param){
	glLightModeli(pname, param);
}

/**
 * Especifica paramenteros do material para o modelo de luz 
 * @param face Especifica a face que deve ser usada
 * @param pname Especifica o tipo de parametro
 * @param param Valor do parametro
 */
void DrawerOpenGL::material(EnumDrawer face, EnumDrawer pname, EnumDrawer param){
	glMateriali(face, pname, param);
}

/**
 * Especifica paramenteros do material para o modelo de luz 
 * @param face Especifica a face que deve ser usada
 * @param pname Especifica o tipo de parametro
 * @param param Valor do parametro
 */
void DrawerOpenGL::material(EnumDrawer face, EnumDrawer pname, Vector4 &params){
	glMaterialfv(face, pname, params.toArray());
}
/**
* Multiplica a matrix atual pela matrix especificada
* @param m Points to 16 consecutive values that are used as the elements of a 4�4 column-major matrix.
*/	
void DrawerOpenGL::multMatrix(const float *m){
	glMultMatrixf( m );
}

/**
* Multiplica a matrix atual pela matrix especificada
* @param m Points to 16 consecutive values that are used as the elements of a 4�4 column-major matrix.
*/	
void DrawerOpenGL::multMatrix(const double *m){
	glMultMatrixd( m );
}


void DrawerOpenGL::pixelStore(EnumDrawer pname, float param){
	glPixelStoref(pname,param);
}

void DrawerOpenGL::pixelStore(EnumDrawer pname, int param){
	glPixelStorei(pname,param);
}


/**
* Empilha o atributo servidor.
* @param mask Especifica a mascara que indica qual atributo para salvar.
*/	
void DrawerOpenGL::pushAttrib(EnumDrawer mask){
	glPushAttrib( mask );
}

/**
* Desempilha o atributo servidor.
* @param mask Especifica a mascara que indica qual atributo para salvar.
*/	
void DrawerOpenGL::popAttrib(){
	glPopAttrib();
}

/**
* Define frente e fundo da face de um poligono
* @param mode Especifica a orienta��o da frente da face de um poligono. INGE_CW(Hor�rio) e INGE_CCW(Anti-hor�io) s�o aceitos. O valor inicial � INGE_CCW;
*/	
void DrawerOpenGL::frontFace(EnumDrawer mode){
	glFrontFace( mode );
}

/**
 * Ativa maquina de estado
 * @param cap
 */
void DrawerOpenGL::enableClientState(EnumDrawer cap){
	glEnableClientState(cap);
}

/**
 * Desativa maquina de estado
 * @param cap
 */
void DrawerOpenGL::disableClientState(EnumDrawer cap){
	glDisableClientState(cap);
}

/**
 * Ativa maquina de estado de textura
 * @param texture
 */
void DrawerOpenGL::clientActiveTextureARB(EnumDrawer texture){
	glClientActiveTextureARB(texture);
}

void DrawerOpenGL::activeTextureARB(EnumDrawer texture){
	glActiveTextureARB(texture);
}


void DrawerOpenGL::getDouble(EnumDrawer pname, double *param ){
	glGetDoublev(pname, param);
}


void DrawerOpenGL::getFloat(EnumDrawer pname, float *param ){
	glGetFloatv(pname, param);
}


void DrawerOpenGL::getInteger(EnumDrawer pname, int *param){
	glGetIntegerv(pname, param);
}



void DrawerOpenGL::vertexPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr){
	glVertexPointer(size, type, stride, ptr);
}

void DrawerOpenGL::texCoordPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr){
	glTexCoordPointer(size, type, stride, ptr);
}

void DrawerOpenGL::colorPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr){
	glColorPointer(size, type, stride, ptr);
}

void DrawerOpenGL::normalPointer(EnumDrawer type, unsigned int stride, const void *ptr){
	glNormalPointer(type, stride, ptr);
}

void DrawerOpenGL::drawElements(EnumDrawer mode, unsigned int count, EnumDrawer type, const void *ptr){
	glDrawElements(mode, count, type, ptr);	
}

void DrawerOpenGL::drawArrays(EnumDrawer mode, int first, unsigned int count){
	glDrawArrays(mode, first, count);
}

void DrawerOpenGL::cullFace(EnumDrawer mode){
	glCullFace(mode);
}

void DrawerOpenGL::depthMask(EnumDrawer flag){
	glDepthMask(flag);
}

void DrawerOpenGL::colorMask(EnumDrawer red, EnumDrawer green, EnumDrawer blue, EnumDrawer alpha){
	glColorMask(red, green, blue, alpha);
}

void DrawerOpenGL::stencilFunc(EnumDrawer func, EnumDrawer ref, EnumDrawer mask){
	glStencilFunc(func, ref, mask);
}
		
void DrawerOpenGL::stencilOp(EnumDrawer fail, EnumDrawer zfail, EnumDrawer zpass ){
	glStencilOp(fail, zfail, zpass);
}

void DrawerOpenGL::blendFunc(EnumDrawer sfactor, EnumDrawer dfactor){
	glBlendFunc(sfactor, dfactor);
}

void DrawerOpenGL::depthFunc(EnumDrawer func){
	glDepthFunc(func);
}

void DrawerOpenGL::polygonMode(EnumDrawer face, EnumDrawer mode){
	glPolygonMode(face,mode);
}
void DrawerOpenGL::clearDepth(float depth){
	glClearDepth(depth);
}

void DrawerOpenGL::map( EnumDrawer target, float u1, float u2, int stride, int order, vector<Vector3> points){
	glMap1f(target, u1, u2, stride, order, &(points[0][0]));
}
/*void DrawerOpenGL::map( EnumDrawer target, double u1, double u2, int stride, int order, vector<Vector3> points){
	glMap1d(target, u1, u2, stride, order, &(points[0][0]));
}*/
void DrawerOpenGL::map( EnumDrawer target, float u1, float u2, int ustride, int uorder, float v1, float v2, int vstride, int vorder, vector<Vector3> points){
	glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, &(points[0][0]));
}
/*void DrawerOpenGL::map( EnumDrawer target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, vector<Vector3> points){
	glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, &(points[0]));
}*/

void DrawerOpenGL::mapGrid( int un, float u1, float u2 ){
	glMapGrid1f( un, u1, u2 );
}
void DrawerOpenGL::mapGrid( int un, double u1, double u2 ){
	glMapGrid1d( un, u1, u2 );
}

void DrawerOpenGL::mapGrid( int un, float u1, float u2, int vn, float v1, float v2 ){
	glMapGrid2f( un, u1, u2, vn, v1, v2);
}
void DrawerOpenGL::mapGrid( int un, double u1, double u2, int vn, double v1, double v2 ){
	glMapGrid2d( un, u1, u2, vn, v1, v2);
}

void DrawerOpenGL::evalCoord(float u){
	glEvalCoord1f( u );
}
void DrawerOpenGL::evalCoord(double u){
	glEvalCoord1d( u );
}

void DrawerOpenGL::evalCoord(float u, float v){
	glEvalCoord2f( u, v );
}
void DrawerOpenGL::evalCoord(double u, double v){
	glEvalCoord2d( u, v );
}

void DrawerOpenGL::evalMesh(EnumDrawer mode, int i1, int i2){
	glEvalMesh1( mode, i1, i2 );
}

void DrawerOpenGL::evalMesh(EnumDrawer mode, int i1, int i2, int j1, int j2){
	glEvalMesh2( mode, i1, i2, j1, j2 );
}
