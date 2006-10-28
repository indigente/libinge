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

#ifndef VECTOR3_H
#define VECTOR3_H
#include <cmath>
#include <iostream>

namespace InGE{
	
	/**
	 * Classe Vetor 3D 
	 * Possui diversas operações utilizadas entre vetores
	 * @author Ivan Medeiros Monteiro
	 */	
	class Vector3{
	  private:
		float m_v[3];
		
	  public:
		Vector3(const Vector3 &vet);
		Vector3(float x=0.0f, float y=0.0f, float z=0.0f);
		Vector3(float vet[3]);
		
		~Vector3(){}

		//Metodos Set
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void setXYZ(float x, float y, float z);

		//Metodos Get
		float getX() const;
		float getY() const;	
		float getZ() const;
		float& operator[] (const long i) { return m_v[i];	}	
		
		float getNorma() const; 			// Modulo/Norma do vetor
		float dot(const Vector3 &vet) const;		// Produto interno
		Vector3 cross(const Vector3 &vet) const;	// Produto vetorial
		Vector3 getVersor() const;			// Retor um versor
		float operator*(const Vector3 &vet) const;	// Produto Interno
		
		void normalize();

		//Metodos de Operações
		Vector3 operator+(const Vector3 &vet) const;
		Vector3 operator+=(const Vector3 &vet);
		Vector3 operator-(const Vector3 &vet) const;
		Vector3 operator-=(const Vector3 &vet);
		Vector3 operator*(float factor) const;
		Vector3 operator*=(float factor);
		Vector3 operator/(float factor) const;
		Vector3 operator/=(float factor);						
		Vector3 operator=(const Vector3 &vet);
		Vector3 *operator=(Vector3 *vet); 
		
		bool operator==(const Vector3 &vet) const;
		
		const float *toArray();
		
		void print();
	};

};
#endif // VECTOR3_H
