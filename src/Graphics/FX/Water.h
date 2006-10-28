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

#ifndef WATER_H
#define WATER_H
#include "../../Math/Vector3.h"
#include "../Render/IRenderListener.h"
#include "../Render/Drawer.h"

namespace InGE{


typedef struct s_ponto
{
        float x;
        float y;
        float z;
} ponto;

class Water : public InGE::IRenderListener{
protected:
	float m_sizeX;
	float m_sizeY;
	int m_divX;
	int m_divY;
	float m_ampl;
	unsigned int id_texture;
	Vector3 m_position;
	ponto waterMesh[15][15];
	
	void waveWater();
	void setWater();
	
public:

	Water(float sizeX,float sizeY,int divX,int divY,float ampl);
	virtual ~Water();
	
	void draw();
	Vector3 getPosition();
};


};
#endif // WATER_H
