/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004-2006 Indigente


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
#include "Matrix4.h"

namespace InGE {

Matrix4::Matrix4()
{
}

Matrix4::Matrix4(const Vector4 &x,const Vector4 &y, const Vector4 &z, const Vector4 &w) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

Matrix4::Matrix4(const Vector4 vet[4]) {
	v[0] = vet[0];
	v[1] = vet[1];
	v[2] = vet[2];
	v[3] = vet[3];
}

Matrix4::Matrix4(float vet[16]) {
	v[0] = Vector4(&vet[0]);
	v[0] = Vector4(&vet[4]);
	v[0] = Vector4(&vet[8]);
	v[0] = Vector4(&vet[12]);
}

Matrix4::Matrix4(float vet[4][4]) {
	v[0] = Vector4(vet[0]);
	v[0] = Vector4(vet[1]);
	v[0] = Vector4(vet[2]);
	v[0] = Vector4(vet[3]);
}


Matrix4::~Matrix4()
{
}

Vector4 Matrix4::operator*(Vector4 vet)
{
	return Vector4(v[0][0]*vet[0] + v[1][0]*vet[1] + v[2][0]*vet[2] + v[3][0]*vet[3],
			v[0][1]*vet[0] + v[1][1]*vet[1] + v[2][1]*vet[2] + v[3][1]*vet[3],
			v[0][2]*vet[0] + v[1][2]*vet[1] + v[2][2]*vet[2] + v[3][2]*vet[3],
			v[0][3]*vet[0] + v[1][3]*vet[1] + v[2][3]*vet[2] + v[3][3]*vet[3]);
}

}
