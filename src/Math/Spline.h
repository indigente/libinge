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
#ifndef INGESPLINE_H
#define INGESPLINE_H

#include <vector>
#include "Vector3.h"
#include "../Graphics/Render/IRenderListener.h"

using std::vector;

namespace InGE {

/**
	@author Beto <nkbeto@gmail.com>
*/

enum InGE_Spline_Type{
	InGE_BEZIER,
	InGE_BSPLINE,
	InGE_INTERPOLATING
};

/**
@param type Tipo de Curva (Bezier, B-Spline, Interpolating)
@param u Inicio do intervalo
@param v Final do intervalo
@param data Conjunto de pontos de controle da curva.
*/
class Spline : public InGE::IRenderListener {
protected:
	vector<Vector3> m_data;
	InGE_Spline_Type m_type;
	float m_u, m_v;
	unsigned int m_step;


	Vector3 p(int i, float t);
public:
	Spline(InGE_Spline_Type type, float u, float v, vector<Vector3> data);
	~Spline();

	Vector3 evaluate(float t);
	bool isValid(float t) { return (m_u <= t && t <= m_v); } //Retorna TRUE enquanto U <= t <= V
	float getStart();
	float getEnd();
	void setU(float u) { m_u = u; }
	void setV(float v) { m_v = v; }
	virtual void draw();

	virtual Vector3 getPosition(){};
	virtual bool getBlend(){};
	
	virtual PhysicalGeom *pGetPhysicalGeom() {};
};

}

#endif
