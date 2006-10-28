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

#ifndef VERTEX_H
#define VERTEX_H
#include "../../Math/Vector2.h"
#include "../../Math/Vector3.h"

namespace InGE{
	/**
	 * Classe KFVertex
	 * Cont�m todas informa��es que um Modelo KeyFrame pode precisar de um v�rtice, posi��o, normal e coordenada de textura.
	 * Possui diversas opera��es utilizadas entre vetores. 
	 * @author Humberto Bandeira
	 */	
	
	class Vertex {
	private:
		Vector3 m_position;
		Vector3 m_normal;
		Vector2 m_texCoord;
	
	public:
		Vertex(const Vertex &vet);
		Vertex(float pX=0.0f, float pY=0.0f, float pZ=0.0f, float nX=0.0f, float nY=0.0f, float nZ=0.0f, float tU=0.0f, float tV=0.0f);
		Vertex(float pos[3],float nor[3],float tex[2]);
		Vertex(Vector3 &position, const Vector3 &normal, const Vector2 &texCoord);
		~Vertex();
	
		//Metodos Set
		void  setPX (float pX);
		void  setPY (float pY);
		void  setPZ (float pZ);
		void  setPosition (float pX, float pY, float pZ);
		void  setPosition (const Vector3 &position);
		void  setNX (float nX);
		void  setNY (float nY);
		void  setNZ (float nZ);
		void  setNormal (float nX, float nY, float nZ);
		void  setNormal (const Vector3 &normal);
		void  setTU (float tX);
		void  setTV (float tY);
		void  setTexCoord (float tX, float tY);
		void  setTexCoord (const Vector2 &texCoord);
	    
	    //Metodos Get
		float  getPX();
		float  getPY();
		float  getPZ();
		Vector3 *getPosition();
		float  getNX();
		float  getNY();
		float  getNZ();
		Vector3 *getNormal();
		float  getTU();
		float  getTV();
		Vector2 *getTexCoord();
		float *getPositionOffset();
		float *getTextureOffset();
		float *getNormalOffset();

		//Metodos Operadores
		Vertex operator+(const Vertex &vert) const;
		Vertex &operator+=(const Vertex &vert);
		
		Vertex operator-(const Vertex &vert) const;
		Vertex &operator-=(const Vertex &vert);
		
		Vertex operator*(float factor) const;
		Vertex &operator*=(float factor);
		
		Vertex &operator=(const Vertex &vet);
		Vertex *operator=(Vertex *vet); 
		
	};

};
#endif // VERTEX_H
