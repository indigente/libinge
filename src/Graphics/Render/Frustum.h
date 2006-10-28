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

#ifndef FRUSTUM_H
#define FRUSTUM_H
#include "../../Math/Vector3.h"

#include <GL/gl.h>
#include <cmath>

namespace InGE{


	// Classe Frustum
	class Frustum{
	  private:
	  	
	  	float frustum[6][4];  	//Definicoes do Frustum
	  	
	  	// Enumeracao para os lado do Frustum
	  	enum FrustumSide{
		    RIGHT   = 0,        // O lado direito do frustum
		    LEFT    = 1,        // O lado esquerdo do frustum
		    BOTTOM  = 2,        // O lado de baixo do frustum
		    TOP     = 3,        // O lado de cima do frustum
		    BACK    = 4,        // O lado de traz do frustum
		    FRONT   = 5         // O lado da frente do frustum
	  	};

		// Enumeracao para os dados do Plano
		enum PlaneData {
		    A = 0,              // O Valor X da normal ao plano
		    B = 1,              // O Valor Y da normal ao plano
		    C = 2,              // O Valor Z da normal ao plano
		    D = 3               // A distancia do Plano pra origem
		};

		// Metodo de normalizacao, usado no calculo do Frustum
		void normalizePlane(int side);
	  	
	  public:
	
		Frustum();
		virtual ~Frustum();
		// Calculo do Frustum
		void calculeFrustum();

		// Verifcacoes de Pertinencias.
		bool isPointInFrustum(float x, float y, float z);
		bool isPointInFrustum(Vector3 &v){
			return isPointInFrustum(v[0],v[1],v[2]);
		}
		
		bool isSphereInFrustum(float x, float y, float z, float radius);
		bool isSphereInFrustum(Vector3 &v, float radius){
			return isSphereInFrustum(v[0],v[1],v[2], radius);
		}
		
		bool isCubeInFrustum(float x, float y, float z, float size);		
		bool isCubeInFrustum(Vector3 &v, float size){
			return isCubeInFrustum(v[0],v[1],v[2], size);			
		}
		
		bool isBoxInFrustum(float x, float y, float z, float x2, float y2, float z2);
		bool isBoxInFrustum(Vector3 &v1, Vector3 &v2){
			return isBoxInFrustum(v1[0],v1[1],v1[2],v2[0],v2[1],v2[2]);
		}
	};

};
#endif // FRUSTUM_H
