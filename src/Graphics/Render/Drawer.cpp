/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright � 2004 Indigente


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

#include "Drawer.h"

using namespace InGE;

Drawer *Drawer::drawer = 0;

/**
 * Devolve um instancia unica da classe
 */
Drawer *Drawer::getInstance(){
	if(!drawer)
		Drawer::drawer = new DrawerOpenGL();
	
	return Drawer::drawer;
}

/**
 * Define OpenGL como pacote grafico atual
 */
void Drawer::setDrawerOpenGL(){
	if(Drawer::drawer) delete drawer;
	Drawer::drawer = new DrawerOpenGL();
}

/*
 * Clausula usada no inicio de modelos geometricos
 * @param e Enumeracao usada para definir formas
 */
void Drawer::begin(EnumDrawer e){
	Drawer::drawer->begin(e);
} 

/**
 * Limpa o buffer
 */
void Drawer::clear(){
	Drawer::drawer->clear();
}	

/**
 * Define cor atual
 */
void Drawer::color(float r, float g, float b){
	Drawer::drawer->color(r,g,b);
}

/**
 * Define cor atual
 * @param vet Vetor com componentes R, G, B
 */
void Drawer::color(Vector3 &vet){
	Drawer::drawer->color(vet);
}

/**
 * Define cor atual
 * @param a Canal alfa
 */
void Drawer::color(float r, float g, float b, float a){
	Drawer::drawer->color(r,g,b,a);
}

/**
 * Define cor atual
 * @param vet Vetor com componentes R, G, B, A (alfa)
 */
void Drawer::color(Vector4 &vet){
	Drawer::drawer->color(vet);	
}

/**
 * Clausula usada no final de modelos geometricos
 */
void Drawer::end(){
	Drawer::drawer->end();		
}

/**
 * Ajusta a camera
 * @param pos Posicao da camera
 * @param view Alvo da camera (em coordenadas globais)
 * @param up Vetor que aponta para cima, em relacao `a camera
 */
void Drawer::lookAt(Vector3 pos, Vector3 view, Vector3 up){
	Drawer::drawer->lookAt(pos,view,up);
}

/**
 * Especifica qual pilha de matriz eh alvo das operacoes
 * @param e Enumeracao usada para definir formas
 */
void Drawer::matrixMode(EnumDrawer e){
	Drawer::drawer->matrixMode(e);
}

/**
 * Guarda na pilha a matriz atual
 */
void Drawer::pushMatrix(){
	Drawer::drawer->pushMatrix();
}

/**
 * Pega da pilha a matrix de projecao
 */
void Drawer::popMatrix(){
	Drawer::drawer->popMatrix();
}

/**
 * Operacao de translacao
 */
void Drawer::translate(float x, float y, float z){
	Drawer::drawer->translate(x,y,z);
}

/**
 * Operacao de translacao
 */
void Drawer::translate(Vector3 &vet){
	Drawer::drawer->translate(vet);
}

/**
 * Operacao de rotacao
 * @param angle Angulo de rotacao
 * @param x Componente X do eixo de rotacao
 * @param y Componente Y do eixo de rotacao
 * @param z Componente Z do eixo de rotacao
 */
void Drawer::rotate(float angle, float x, float y, float z){
	Drawer::drawer->rotate(angle, x,y,z);
}

/**
 * Operacao de rotacao
 * @param angle Angulo de rotacao
 * @param vet Eixo de rotacao
 */
void Drawer::rotate(float angle, Vector3 &vet){
	Drawer::drawer->rotate(angle, vet);
}
/**
 * Operacao de rotacao
 * @param vet Angulo e Eixo de rotacao
 */
void Drawer::rotate( Vector4 &vet ){
	Drawer::drawer->rotate( vet );
}
/**
 * Alterna entre buffers do Double Buffer
 */
void Drawer::swapBuffers(){
	Drawer::drawer->swapBuffers();
}

/**
 * Define coordenada de textura
 */
void Drawer::texCoord(float x, float y){
	Drawer::drawer->texCoord(x,y);
}

/**
 * Define coordenada de textura
 */
void Drawer::texCoord(Vector2 &vet){
	Drawer::drawer->texCoord(vet);
}

/**
 * Define Vertice de um modelo geometrico atraves de suas coordenadas
 */
void Drawer::vertex(float x, float y, float z){
	Drawer::drawer->vertex(x,y,z);
}

/**
 * Define Vertice de um modelo geometrico atraves de suas coordenadas
 * @param vet Coordenadas do vertice
 */
void Drawer::vertex(Vector3 &vet){
	Drawer::drawer->vertex(vet);
}


/**
 * Define Vetor normal atual
 */
void Drawer::normal(float x, float y, float z){
	Drawer::drawer->normal(x,y,z);
}

/**
 * Define tamanho do ponto
 */
void Drawer::pointSize(float size){
	Drawer::drawer->pointSize(size);
}

/**
 * Define grossura da linha
 */
void Drawer::lineWidth(float size){
	Drawer::drawer->lineWidth(size);
}
/**
 * Define Vetor normal atual
 * @param vet Coordenadas da normal
 */
void Drawer::normal(Vector3 &vet){
	Drawer::drawer->normal(vet);
}

/**
 * Habilita capacidades do Drawer
 */
void Drawer::enable(EnumDrawer cap){
	Drawer::drawer->enable(cap);
}

/**
 * Desabilita capacidades do Drawer
 */
void Drawer::disable(EnumDrawer cap){
	Drawer::drawer->disable(cap);
}

/**
 * Habilita luz especifica
 * @param i ID da luz
 */
void Drawer::enableLight(int i){
	Drawer::drawer->enableLight(i);
}

/**
 * Desabilita luz especifica
 * @param i ID da luz
 */
void Drawer::disableLight(int i){
	Drawer::drawer->disableLight(i);
}
		
/**
 * Habilita plano de corte
 * @param i ID do plano de corte
 */
void Drawer::enableClipPlane(int i){
	Drawer::drawer->enableClipPlane(i);
}

/**
 * Habilita plano de corte
 * @param i ID do plano de corte
 */
void Drawer::disableClipPlane(int i){
	Drawer::drawer->disableClipPlane(i);
}
	
/**
 * Gera um ID para texturas
 * @param n Quantidade de texturas desejadas
 * @param id Ponteiro para um inteiro que recebera o ID
 */
void Drawer::genTextures(int n, unsigned int *id){
	Drawer::drawer->genTextures(n, id);
}

/**
 * Associa o ID da textura com seu tipo
 * @param target Tipo de textura
 * @param id ID da textura
 */
void Drawer::bindTexture(EnumDrawer target, unsigned int id){
	Drawer::drawer->bindTexture(target, id);
}

/**
 * Constroi Mipmaps de 2 dimensoes
 * @param trgt Tipo de textura alvo. Deve ser InGE_TEXTURE_2D.
 * @param iFrmt Quantidade de componentes de cor na textura (1, 2, 3 ou 4)
 * @param w Largura da imagem
 * @param h Altura da imagem
 * @param frmt Formato do pixel
 *   InGE_COLOR_INDEX, InGE_RED, InGE_GREEN, InGE_BLUE, InGE_ALPHA,
 *   InGE_RGB, InGE_RGBA, InGE_LUMINANCE ou InGE_LUMINANCE_ALPHA)
 * @param tp Tipo de dados utilizado em data (InGE_UNSIGNED_BYTE, InGE_BYTE,
 *   InGE_BITMAP, InGE_UNSIGNED_SHORT, InGE_SHORT, InGE_UNSIGNED_INT,
 *   InGE_INT ou InGE_FLOAT) 
 * @param data Ponteiro para a imagem na memoria
 */
void Drawer::build2DMipmaps(EnumDrawer trgt, int iFrmt, int w, int h, EnumDrawer frmt, EnumDrawer tp, const void *data){
	Drawer::drawer->build2DMipmaps(trgt, iFrmt, w, h, frmt, tp, data);
}

/**
 * Constroi Textura de 2 dimensoes
 * @param target Tipo de textura alvo. Deve ser InGE_TEXTURE_2D.
 * @param level Level of Details (LOD)
 * @param internalFormat Quantidade de componentes de cor na textura (1, 2, 3 ou 4)
 * @param width Largura da imagem
 * @param height Altura da imagem
 * @param border Borda da imagem
 * @param format Formato do pixel 
 * @param type Tipo de dados utilizado em data (InGE_UNSIGNED_BYTE, InGE_BYTE,
 *   InGE_BITMAP, InGE_UNSIGNED_SHORT, InGE_SHORT, InGE_UNSIGNED_INT,
 *   InGE_INT ou InGE_FLOAT) 
 * @param pixels Ponteiro para a imagem na memoria
 */
void Drawer::texImage2D(EnumDrawer target, int level, int internalFormat, int width, int height, int border, EnumDrawer format, EnumDrawer type, const void *pixels){
	Drawer::drawer->texImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
}

/**
 * Constroi Textura de 2 dimensoes
 * @param target Tipo de textura alvo. Deve ser InGE_TEXTURE_2D.
 * @param level Level of Details (LOD)
 * @param xoffset Inicio em X da imagem
 * @param yoffset Inicio em Y da imagem
 * @param width Largura da imagem
 * @param height Altura da imagem
 * @param format Formato do pixel 
 * @param type Tipo de dados utilizado em data (InGE_UNSIGNED_BYTE, InGE_BYTE,
 *   InGE_BITMAP, InGE_UNSIGNED_SHORT, InGE_SHORT, InGE_UNSIGNED_INT,
 *   InGE_INT ou InGE_FLOAT) 
 * @param pixels Ponteiro para a imagem na memoria
 */
void Drawer::texSubImage2D(EnumDrawer target, int level, int xoffset, int yoffset, int width, int height, EnumDrawer format, EnumDrawer type, const void *pixels){
	Drawer::drawer->texSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}
/**
 * Especifica parametros para a textura
 * @param target Tipo de textura alvo. Deve ser InGE_TEXTURE_1D ou
 *   InGE_TEXTURE_2D.
 * @param pname Tipo de parametro
 * @param param Valor do parametro
 */
void Drawer::texParameter(EnumDrawer target, EnumDrawer pname,	int param){
	Drawer::drawer->texParameter(target, pname, param);
}

/**
 * Especifica parametros de ambiente para a textura
 * @param target Tipo de textura alvo. Deve ser InGE_TEXTURE_ENV.
 * @param pname Tipo de parametro
 * @param param Valor do parametro
 */
void Drawer::texEnv(EnumDrawer target, EnumDrawer pname, int param ){
	Drawer::drawer->texEnv(target, pname, param);
}

/**
 * Especifica um parametro de fog
 * @param pname Especifica o tipo de parametro
 * @param param Valor do parametro
 */
void Drawer::fog(EnumDrawer pname, float param){
	Drawer::drawer->fog(pname, param);
}

/**
 * Especifica um parametro de fog
 * @param pname Especifica o tipo de parametro
 * @param param Valor do parametro
 */
void Drawer::fog(EnumDrawer pname, int param){
	Drawer::drawer->fog(pname, param);
}

/**
 * Especifica um parametro de fog
 * @param pname Especifica o tipo de parametro
 * @param param Valor do parametro
 */
void Drawer::fog(EnumDrawer pname, Vector4 param){
	Drawer::drawer->fog(pname, param);
}

/**
 * Especifica sugestoes de implementacao da renderizacao.
 * @param target Tipo de comportamento a ser controlado (InGE_FOG_HINT, 
 *   InGE_LINE_SMOOTH_HINT, InGE_PERSPECTIVE_CORRECTION_HINT, 
 *   InGE_POINT_SMOOTH_HINT ou InGE_POLYGON_SMOOTH_HINT)
 * @param mode Comportamento desejado (GL_FASTEST, GL_NICEST ou GL_DONT_CARE)
 */
void Drawer::hint(EnumDrawer target, EnumDrawer mode){
	Drawer::drawer->hint(target, mode);
}

/**
 * Escolhe entre sombreamento flat e smooth.
 * @param target Tecnica de sombreamento (GL_FLAT ou GL_SMOOTH). O padrao e'
 *   GL_SMOOTH.
 */ 
void Drawer::shadeModel(EnumDrawer target){
	Drawer::drawer->shadeModel(target);
}

/**
 * Especifica a cor utilizada quando se deseja limpar algum buffer, atraves
 *   de componentes R, G, B e A (alfa).
 */
void Drawer::clearColor(float r,float g,float b,float a){
	Drawer::drawer->clearColor(r,g,b,a);
}

void Drawer::ortho(float left, float right, float bottom, float top, float near, float far){
	Drawer::drawer->ortho(left, right, bottom, top, near, far);
}

/**
 * Especifica parametros de visualizacao (viewport)
 * Os parametros devem ser especificados em coordenadas da tela
 * @param x Coordenada da extremidade esquerda da viewport
 * @param y Coordenada da extremidade inferior da viewport
 * @param width Largura da viewport
 * @param height Altura da viewport
 */
void Drawer::viewport(int x,int y,unsigned int width,unsigned int height){
	Drawer::drawer->viewport(x,y,width,height);
}

/**
 * Carrega a matriz identidade
 */
void Drawer::loadIdentity(){
	Drawer::drawer->loadIdentity();
}

/**
 * Define a perspectiva utilizada
 * @param fovy Angulo de abertura da visualizacao (field of view)
 * @param aspect Razao entre largura e altura
 * @param zNear Plano proximo (near)
 * @param zFar Plano distante (far)
 */
void Drawer::perspective(float fovy,float aspect,float zNear,float zFar){
	Drawer::drawer->perspective(fovy, aspect, zNear, zFar);
}
/**
 * Especifica um parametro de light
 * @param pname Especifica o tipo de parametro
 * @param params Valor do parametro
 */
void Drawer::light(EnumDrawer target, EnumDrawer pname, float params){
	Drawer::drawer->light(target, pname, params);
}

/**
 * Especifica um parametro de light
 * @param pname Especifica o tipo de parametro
 * @param param Valor do parametro
 */
void Drawer::light(EnumDrawer target, EnumDrawer pname, Vector4 &params){
	Drawer::drawer->light(target, pname, params);
}

/**
 * Especifica um parametro do modelo de light
 * @param pname Especifica o tipo de parametro
 * @param param Valor do parametro
 */
void Drawer::lightModel(EnumDrawer pname, EnumDrawer param){
	Drawer::drawer->lightModel(pname, param);
}

/**
 * Especifica paramenteros do material para o modelo de luz 
 * @param face Especifica a face que deve ser usada
 * @param pname Especifica o tipo de parametro
 * @param param Valor do parametro
 */
void Drawer::material(EnumDrawer face, EnumDrawer pname, EnumDrawer param){
	Drawer::drawer->material(face, pname, param);
}

/**
 * Especifica paramenteros do material para o modelo de luz 
 * @param face Especifica a face que deve ser usada
 * @param pname Especifica o tipo de parametro
 * @param param Valor do parametro
 */
void Drawer::material(EnumDrawer face, EnumDrawer pname, Vector4 &params){
	Drawer::drawer->material(face, pname, params);
}
/**
* Multiplica a matrix atual pela matrix especificada
* @param m Pontos para 16 valores consecutivos que s�o usados como elementos de uma matrix 4�4.
*/	
void Drawer::multMatrix(const float *m){
	Drawer::drawer->multMatrix( m );
}
/**
* Multiplica a matrix atual pela matrix especificada
* @param m Pontos para 16 valores consecutivos que s�o usados como elementos de uma matrix 4�4.
*/	
void Drawer::multMatrix(const double *m){
	Drawer::drawer->multMatrix( m );
}

void Drawer::pixelStore(EnumDrawer pname, float param){
	Drawer::drawer->pixelStore(pname,param);
}

void Drawer::pixelStore(EnumDrawer pname, int param){
	Drawer::drawer->pixelStore(pname,param);
}


/**
* Empilha o atributo servidor.
* @param mask Especifica a mascara que indica qual atributo para salvar.
*/	
void Drawer::pushAttrib(EnumDrawer mask){
	Drawer::drawer->pushAttrib( mask );
}

/**
* Desempilha o atributo servidor.
* @param mask Especifica a mascara que indica qual atributo para salvar.
*/	
void Drawer::popAttrib(){
	Drawer::drawer->popAttrib();
}

/**
* Define frente e fundo da face de um poligono
* @param mode Especifica a orienta��o da frente da face de um poligono. INGE_CW(Hor�rio) e INGE_CCW(Anti-hor�rio) s�o aceitos. O valor inicial � INGE_CCW;
*/	
void Drawer::frontFace(EnumDrawer mode){
	Drawer::drawer->frontFace( mode );
}
/**
 * Ativa maquina de estado
 * @param cap
 */
void Drawer::enableClientState(EnumDrawer cap){
	Drawer::drawer->enableClientState(cap);
}
/**
 * Desativa maquina de estado
 * @param cap
 */
void Drawer::disableClientState(EnumDrawer cap){
	Drawer::drawer->disableClientState(cap);
}
/**
 * Ativa maquina de estado de textura
 * @param texture
 */
void Drawer::clientActiveTextureARB(EnumDrawer texture){
	Drawer::drawer->clientActiveTextureARB(texture);
}

void Drawer::activeTextureARB(EnumDrawer texture){
	Drawer::drawer->clientActiveTextureARB(texture);
}


void Drawer::getDouble(EnumDrawer pname, double *param ){
	Drawer::drawer->getDouble(pname, param);
}


void Drawer::getFloat(EnumDrawer pname, float *param ){
	Drawer::drawer->getFloat(pname, param);
}


void Drawer::getInteger(EnumDrawer pname, int *param){
	Drawer::drawer->getInteger(pname, param);
}



void Drawer::vertexPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr){
	Drawer::drawer->vertexPointer(size, type, stride, ptr);
}

void Drawer::texCoordPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr){
	Drawer::drawer->texCoordPointer(size, type, stride, ptr);
}

void Drawer::colorPointer(int size, EnumDrawer type, unsigned int stride, const void *ptr){
	Drawer::drawer->colorPointer(size, type, stride, ptr);
}

void Drawer::normalPointer(EnumDrawer type, unsigned int stride, const void *ptr){
	Drawer::drawer->normalPointer(type, stride, ptr);
}

void Drawer::drawElements(EnumDrawer mode, unsigned int count, EnumDrawer type, const void *ptr){
	Drawer::drawer->drawElements(mode, count, type, ptr);	
}

void Drawer::drawArrays(EnumDrawer mode, int first, unsigned int count){
	Drawer::drawer->drawArrays(mode, first, count);
}

void Drawer::cullFace(EnumDrawer mode){
	Drawer::drawer->cullFace(mode);
}

void Drawer::depthMask(EnumDrawer flag){
	Drawer::drawer->depthMask(flag);
}

void Drawer::colorMask(EnumDrawer red, EnumDrawer green, EnumDrawer blue, EnumDrawer alpha){
	Drawer::drawer->colorMask(red, green, blue, alpha);
}

void Drawer::stencilFunc(EnumDrawer func, EnumDrawer ref, EnumDrawer mask){
	Drawer::drawer->stencilFunc(func, ref, mask);
}
		
void Drawer::stencilOp(EnumDrawer fail, EnumDrawer zfail, EnumDrawer zpass ){
	Drawer::drawer->stencilOp(fail, zfail, zpass);
}

void Drawer::blendFunc(EnumDrawer sfactor, EnumDrawer dfactor){
	Drawer::drawer->blendFunc(sfactor, dfactor);
}

void Drawer::depthFunc(EnumDrawer func){
	Drawer::drawer->depthFunc(func);
}

void Drawer::polygonMode(EnumDrawer face, EnumDrawer mode){
	Drawer::polygonMode(face,mode);
}
void Drawer::clearDepth(float depth){
	Drawer::clearDepth(depth);
}

void Drawer::map( EnumDrawer target, float u1, float u2, int stride, int order, vector<Vector3> points){
	Drawer::map(target, u1, u2, stride, order, points);
}
/*void Drawer::map( EnumDrawer target, double u1, double u2, int stride, int order, vector<Vector3> points){
	Drawer::map(target, u1, u2, stride, order, points);
}*/
void Drawer::map( EnumDrawer target, float u1, float u2, int ustride, int uorder, float v1, float v2, int vstride, int vorder, vector<Vector3> points){
	Drawer::map(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}
/*void Drawer::map( EnumDrawer target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, vector<Vector3> points){
	Drawer::map(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}*/

void Drawer::mapGrid( int un, float u1, float u2 ){
	Drawer::mapGrid( un, u1, u2 );
}
void Drawer::mapGrid( int un, double u1, double u2 ){
	Drawer::mapGrid( un, u1, u2 );
}

void Drawer::mapGrid( int un, float u1, float u2, int vn, float v1, float v2 ){
	Drawer::mapGrid( un, u1, u2, vn, v1, v2);
}
void Drawer::mapGrid( int un, double u1, double u2, int vn, double v1, double v2 ){
	Drawer::mapGrid( un, u1, u2, vn, v1, v2);
}

void Drawer::evalCoord(float u){
	Drawer::evalCoord( u );
}
void Drawer::evalCoord(double u){
	Drawer::evalCoord( u );
}

void Drawer::evalCoord(float u, float v){
	Drawer::evalCoord( u, v );
}
void Drawer::evalCoord(double u, double v){
	Drawer::evalCoord( u, v );
}

void Drawer::evalMesh(EnumDrawer mode, int i1, int i2){
	Drawer::evalMesh( mode, i1, i2 );
}

void Drawer::evalMesh(EnumDrawer mode, int i1, int i2, int j1, int j2){
	Drawer::evalMesh( mode, i1, i2, j1, j2 );
}
