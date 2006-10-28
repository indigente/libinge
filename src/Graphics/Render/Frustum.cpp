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

#include "Frustum.h"
#include "Drawer.h"

using namespace InGE;

Frustum::Frustum(){
}

Frustum::~Frustum(){
}

// Normaliza um plano dado.
void Frustum::normalizePlane(int side){
	float norma = sqrt( this->frustum[side][A] * this->frustum[side][A]
					  + this->frustum[side][B] * this->frustum[side][B] 
					  + this->frustum[side][C] * this->frustum[side][C] );					  

	this->frustum[side][A] /= norma;
	this->frustum[side][B] /= norma;
	this->frustum[side][C] /= norma;		
	this->frustum[side][D] /= norma;			
}		



// Calculo do Frustum
void Frustum::calculeFrustum(){
	float proj[16];
	float modl[16];
	float clip[16];
	
    // glGetFloatv() eh usado para extrair informacao sobre o mundo OpenGL.
	Drawer::getInstance()->getFloat( InGE_PROJECTION_MATRIX, proj );
	Drawer::getInstance()->getFloat( InGE_MODELVIEW_MATRIX, modl );

    // Now that we have our modelview and projection matrix, if we combine these 2 matrices,
    // it will give us our clipping planes.  To combine 2 matrices, we multiply them.


	// Combinacao da matriz de Modelview com a de Projection para gera a de clip.
	// A combinacao eh feita atraves da multiplicacao das duas matrizes.
	// [CLIP] = [MODL] X [PROJ]
	
    clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
    clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
    clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
    clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

    clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
    clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
    clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
    clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

    clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
    clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
    clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
    clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

    clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
    clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
    clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
    clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

    // Extrai o lado direito do Frustum
    this->frustum[RIGHT][A] = clip[ 3] - clip[ 0];
    this->frustum[RIGHT][B] = clip[ 7] - clip[ 4];
    this->frustum[RIGHT][C] = clip[11] - clip[ 8];
    this->frustum[RIGHT][D] = clip[15] - clip[12];

    // Normaliza o plano do lado direiro
    this->normalizePlane(RIGHT);

	 // Extrai o lado esquerdo do Frustum
    this->frustum[LEFT][A] = clip[ 3] + clip[ 0];
    this->frustum[LEFT][B] = clip[ 7] + clip[ 4];
    this->frustum[LEFT][C] = clip[11] + clip[ 8];
    this->frustum[LEFT][D] = clip[15] + clip[12];

    // Normaliza o plano do lado esquerdo
    this->normalizePlane(LEFT);

	 // Extrai a parte de baixo do Frustum
    this->frustum[BOTTOM][A] = clip[ 3] + clip[ 1];
    this->frustum[BOTTOM][B] = clip[ 7] + clip[ 5];
    this->frustum[BOTTOM][C] = clip[11] + clip[ 9];
    this->frustum[BOTTOM][D] = clip[15] + clip[13];

    // Normaliza o plano da parte de baixo
    this->normalizePlane(BOTTOM);

	 // Extrai a parte de cima do Frustum
    this->frustum[TOP][A] = clip[ 3] - clip[ 1];
    this->frustum[TOP][B] = clip[ 7] - clip[ 5];
    this->frustum[TOP][C] = clip[11] - clip[ 9];
    this->frustum[TOP][D] = clip[15] - clip[13];

    // Normaliza o plano da parte de cima
    this->normalizePlane(TOP);

	 // Extrai a parte de traz do Frustum
    this->frustum[BACK][A] = clip[ 3] - clip[ 2];
    this->frustum[BACK][B] = clip[ 7] - clip[ 6];
    this->frustum[BACK][C] = clip[11] - clip[10];
    this->frustum[BACK][D] = clip[15] - clip[14];

    // Normaliza o plano da parte de traz
    this->normalizePlane(BACK);

	 // Extrai a parte da frente do Frustum
    this->frustum[FRONT][A] = clip[ 3] + clip[ 2];
    this->frustum[FRONT][B] = clip[ 7] + clip[ 6];
    this->frustum[FRONT][C] = clip[11] + clip[10];
    this->frustum[FRONT][D] = clip[15] + clip[14];

    // Normaliza o plano da parte da frente
    this->normalizePlane(FRONT);
	
}


// Verifica se um ponto pertence ao frustum
bool Frustum::isPointInFrustum(float x, float y, float z){
	/* Note: Por questao de legibilidade o prefixo this-> foi 
	 * omitido no atributo frustum
	 */
    for(int i = 0; i < 6; i++ )
        if(frustum[i][A] * x + frustum[i][B] * y + frustum[i][C] * z + frustum[i][D] <= 0)
            return false;

    return true;
}


// Verifica se uma esfera pertence ao frustum
bool Frustum::isSphereInFrustum(float x, float y, float z, float radius){
	/* Note: Por questao de legibilidade o prefixo this-> foi 
	 * omitido no atributo frustum
	 */
    for(int i = 0; i < 6; i++ )
        if(frustum[i][A] * x + frustum[i][B] * y + frustum[i][C] * z + frustum[i][D] <= -radius)
            return false;

    return true;
}

// Verifica se um cubo pertence ao frustum 
bool Frustum::isCubeInFrustum(float x, float y, float z, float size){
	/* Note: Por questao de legibilidade o prefixo this-> foi 
	 * omitido no atributo frustum
	 */
    for(int i = 0; i < 6; i++ ) {
        if(frustum[i][A] * (x - size) + frustum[i][B] * (y - size) + frustum[i][C] * (z - size) + frustum[i][D] > 0)continue;
        if(frustum[i][A] * (x + size) + frustum[i][B] * (y - size) + frustum[i][C] * (z - size) + frustum[i][D] > 0)continue;
        if(frustum[i][A] * (x - size) + frustum[i][B] * (y + size) + frustum[i][C] * (z - size) + frustum[i][D] > 0)continue;
        if(frustum[i][A] * (x + size) + frustum[i][B] * (y + size) + frustum[i][C] * (z - size) + frustum[i][D] > 0)continue;
        if(frustum[i][A] * (x - size) + frustum[i][B] * (y - size) + frustum[i][C] * (z + size) + frustum[i][D] > 0)continue;
        if(frustum[i][A] * (x + size) + frustum[i][B] * (y - size) + frustum[i][C] * (z + size) + frustum[i][D] > 0)continue;
        if(frustum[i][A] * (x - size) + frustum[i][B] * (y + size) + frustum[i][C] * (z + size) + frustum[i][D] > 0)continue;
        if(frustum[i][A] * (x + size) + frustum[i][B] * (y + size) + frustum[i][C] * (z + size) + frustum[i][D] > 0)continue;

        return false;
    }
    return true;
}


// Verifica se um caixa pertence ao frustum
bool Frustum::isBoxInFrustum(float x, float y, float z, float x2, float y2, float z2){
	/* Note: Por questao de legibilidade o prefixo this-> foi 
	 * omitido no atributo frustum
	 */
    for(int i = 0; i < 6; i++ ) {
        if(frustum[i][A] * x  + frustum[i][B] * y  + frustum[i][C] * z  + frustum[i][D] > 0)  continue;
        if(frustum[i][A] * x2 + frustum[i][B] * y  + frustum[i][C] * z  + frustum[i][D] > 0)  continue;
        if(frustum[i][A] * x  + frustum[i][B] * y2 + frustum[i][C] * z  + frustum[i][D] > 0)  continue;
        if(frustum[i][A] * x2 + frustum[i][B] * y2 + frustum[i][C] * z  + frustum[i][D] > 0)  continue;
        if(frustum[i][A] * x  + frustum[i][B] * y  + frustum[i][C] * z2 + frustum[i][D] > 0)  continue;
        if(frustum[i][A] * x2 + frustum[i][B] * y  + frustum[i][C] * z2 + frustum[i][D] > 0)  continue;
        if(frustum[i][A] * x  + frustum[i][B] * y2 + frustum[i][C] * z2 + frustum[i][D] > 0)  continue;
        if(frustum[i][A] * x2 + frustum[i][B] * y2 + frustum[i][C] * z2 + frustum[i][D] > 0)  continue;

        return false;
    }
    return true;	
}

