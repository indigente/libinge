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


#ifndef VECTOR4_H
#define VECTOR4_H
#include <cmath>

namespace InGE{

	/**
	 * Vetor 4D 
	 * Possui diversas operações utilizadas entre vetores
	 * @author Ivan Medeiros Monteiro
	 */	
	class Vector4{
	  private:
		float v[4];

	  public:
	  	Vector4(const Vector4 &vet);
		Vector4(float x=0.0f,float y=0.0f, float z=0.0f, float w=0.0f);
		Vector4(float vet[4]);	
		
		~Vector4(){}

		//Metodos Set
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void setW(float w);
		void setXYZW(float x, float y, float z, float w);
			
		//Metodos Get
		float getX() const;
		float getY() const;	
		float getZ() const;
		float getW() const;
		float& operator[] (const long i) { return v[i];	}

		float getNorma() const;						// Modulo/Norma do vetor
		float dot(const Vector4 &vet) const;		// Produto interno
		Vector4 getVersor() const;						// Retorna um versor
		float operator*(const Vector4 &vet) const;	// Produto Interno	
		
		void normalize();	

		//Metodos de Operações
		Vector4 operator+(const Vector4 &vet) const;
		Vector4 operator+=(const Vector4 &vet);
		Vector4 operator-(const Vector4 &vet) const;
		Vector4 operator-=(const Vector4 &vet);
		Vector4 operator*(float factor) const;
		Vector4 operator*=(float factor);
		Vector4 operator/(float factor) const;
		Vector4 operator/=(float factor);
		Vector4 operator=(const Vector4 &vet);
		Vector4 *operator=(Vector4 *vet);
		bool operator==(const Vector4 &vet) const;

		const float *toArray();
	};

};
#endif // VECTOR4_H
