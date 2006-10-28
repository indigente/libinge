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
#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector4.h"

namespace InGE {

/**
	@author Beto <nkbeto@gmail.com>
*/
class Matrix4{
protected:
	Vector4 v[4];

public:
	Matrix4();
	Matrix4(const Vector4 &x, const Vector4 &y, const Vector4 &z, const Vector4 &w);
	Matrix4(const Vector4 vet[4]);
	Matrix4(float vet[16]);
	Matrix4(float vet[4][4]);

	~Matrix4();

	Vector4& operator[] (const long i) { return v[i]; }
	Matrix4 operator+(const Matrix4 &vet) const;
	Matrix4 operator-(const Matrix4 &vet) const;
	Matrix4 operator*(float factor) const;
	Vector4 operator*(Vector4 vet);
	Matrix4 operator/(float factor) const;
};

}
#endif
