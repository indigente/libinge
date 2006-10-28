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

#include "Water.h"
#include "../Base/TextureArray.h"

#include <cmath>

using namespace std;
using namespace InGE;

Water::Water(float sizeX,float sizeY,int divX,int divY,float ampl){
	m_ampl = ampl;
	m_divX = divX;
	m_divY = divY;
	m_sizeX = sizeX;
	m_sizeY = sizeY;

	this->setWater();

	TextureArray *textureArray = TextureArray::getInstance();
	textureArray->loadTexture("textures/agua.bmp",&id_texture);
}

Water::~Water(){
}

void Water::setWater(){
	int i,j;

	for (i=0;i<m_divY;i++)
		for (j=0;j<m_divX;j++){
			waterMesh[i][j].x = j*m_sizeX/m_divX;
			waterMesh[i][j].y = i*m_sizeY/m_divY;
			waterMesh[i][j].z = 0;
		}
}

void Water::waveWater(){
	int i,j;
	static float key=0;

	for (i=0;i<m_divY;i++){
		for (j=0;j<m_divX;j++)
			waterMesh[i][j].z = (sin((i+key)/1)*cos((j+key)/1)*m_ampl);
		key+=0.0003;
	}
}

void Water::draw(){
	Drawer *drawer = Drawer::getInstance();
	drawer->bindTexture(InGE_TEXTURE_2D,id_texture);

	int i,j;
	float u,v;
	float k,l;
	
	u=(float)1/m_divX;
	v=(float)1/m_divY;

	drawer->blendFunc(InGE_SRC_ALPHA,InGE_ONE_MINUS_SRC_ALPHA);
	drawer->enable(InGE_BLEND);
	drawer->color(1.0f,1.0f,1.0f,0.5f);
	drawer->begin(InGE_TRIANGLES);
	/*drawer->matrixMode(InGE_MODELVIEW);
	drawer->pushMatrix();
	drawer->loadIdentity();
	drawer->translate(0,0,200);*/
	
	for (i=0;i<m_divY-1;i++)
		for (j=0;j<m_divX-1;j++){
			k=(float)(j+1)/m_divX;
			l=(float)(i+1)/m_divY;

			drawer->texCoord(k,l);		drawer->vertex(waterMesh[i][j].x,waterMesh[i][j].y,waterMesh[i][j].z);
			drawer->texCoord(k,l+v);	drawer->vertex(waterMesh[i+1][j].x,waterMesh[i+1][j].y,waterMesh[i+1][j].z);
			drawer->texCoord(k+u,l);	drawer->vertex(waterMesh[i][j+1].x,waterMesh[i][j+1].y,waterMesh[i][j+1].z);
			drawer->texCoord(k+u,l);	drawer->vertex(waterMesh[i][j+1].x,waterMesh[i][j+1].y,waterMesh[i][j+1].z);
			drawer->texCoord(k,l+v);	drawer->vertex(waterMesh[i+1][j].x,waterMesh[i+1][j].y,waterMesh[i+1][j].z);
			drawer->texCoord(k+u,l+v);	drawer->vertex(waterMesh[i+1][j+1].x,waterMesh[i+1][j+1].y,waterMesh[i+1][j+1].z);
		}
		drawer->end();
		drawer->disable(InGE_BLEND);
		drawer->color(1.0f,1.0f,1.0f,1.0f);
		//drawer->popMatrix();
		this->waveWater();
}

Vector3 Water::getPosition(){
	return m_position;
}
