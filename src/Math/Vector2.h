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

#ifndef VECTOR2_H
#define VECTOR2_H
#include <cmath>

namespace InGE{

	/**
	 * Classe Vetor 2D 
	 * Possui diversas operaï¿½ï¿½es utilizadas entre vetores
	 * @author Ivan Medeiros Monteiro
	 */
	class Vector2{
	  private:
		float v[2];
		
	 public:
	 	Vector2(const Vector2 &vet);
		Vector2(float x=0.0f, float y=0.0f);
		Vector2(float vet[2]);
		
		~Vector2(){}

		//Metodos Set	
		void setX(float x);
		void setY(float y);
		void setXY(float x=0.0f, float y=0.0f);
	
		//Metodos Get
		float getX() const;
		float getY() const;
		float& operator[] (const long i) { return v[i];	}
		
		float getNorma() const;				// Modulo/Norma do Vetor
		float dot(const Vector2 &vet) const;		// Produto Interno
		Vector2 getVersor() const;					// Retorna o versor
		float operator*(const Vector2 &vet) const;	// Produto Interno
		
		void normalize();
	
		//Metodos de Operaï¿½ï¿½es
		Vector2 operator+(const Vector2 &vet) const;
		Vector2 operator+=(const Vector2 &vet);
		Vector2 operator-(const Vector2 &vet) const;
		Vector2 operator-=(const Vector2 &vet);
		Vector2 operator*(float factor) const;
		Vector2 operator*=(float factor);
		Vector2 operator/(float factor) const;
		Vector2 operator/=(float factor);
		Vector2 operator=(const Vector2 &vet);
		Vector2 *operator=(Vector2 *vet);
		bool operator==(const Vector2 &vet) const;
		
		const float *toArray();
	};

};
#endif // VECTOR2_H
