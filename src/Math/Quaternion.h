/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004-2005 Indigente


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

#ifndef QUATERNION_H
#define QUATERNION_H
#include "Vector3.h"


#ifndef PI
	#define PI 3.141592653589793	
#endif

#define EPSILON 0.1


namespace InGE{
enum { X, Y, Z, W };
	/**
	 * Classe Quaternion
	 * Uma generaliza�o dos nmeros complexos.
	 * Em termos pr�icos, oferece mecanismo r�ido para 
	 * efetuar rota�es.
	 * @author Ivan Medeiros Monteiro
	 */
	class Quaternion{
	  private:
		float m_w;
		float m_x;
		float m_y;
		float m_z;
	  public:
		Quaternion( float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f);
		Quaternion( float degree, Vector3 axis);
		virtual ~Quaternion();

		//Metodos Get
		float getW() const;
		float getX() const;
		float getY() const;
		float getZ() const;
		
		//Metodos de Opera�es
		Quaternion operator+(const Quaternion &quat) const;
		Quaternion operator+=(const Quaternion &quat);
		Quaternion operator-(const Quaternion &quat) const;
		Quaternion operator-=(const Quaternion &quat);
		Quaternion operator*(const Quaternion &quat) const;
		Quaternion operator*=(const Quaternion &quat);
		Quaternion operator=(const Quaternion &quat);
		Quaternion *operator=(Quaternion *quat);
		bool operator==(Quaternion &quat);

		Quaternion conjugate();

		void matrixToQuaternion(float *matRot);
		void quaternionSlerp( Quaternion *from, Quaternion *to, float t);
		float *quaternionToMatrix();
		
		
	};

};
#endif // QUATERNION_H
