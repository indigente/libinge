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

#include "Vertex.h"

#include <iostream>
using namespace std;

using namespace InGE;
using namespace InGE;

// Construtor do vetor 3D 
Vertex::Vertex(const Vertex &vet){
	m_position = vet.m_position;
	m_normal = vet.m_normal;
	m_texCoord = vet.m_texCoord;
}

Vertex::Vertex(Vector3 &position, const Vector3 &normal, const Vector2 &texCoord){
	m_position = position;
	m_normal = normal;
	m_texCoord = texCoord;
}


Vertex::Vertex(float pX, float pY, float pZ, float nX, float nY, float nZ, float tU, float tV){
	m_position[0] = pX;
	m_position[1] = pY;
	m_position[2] = pZ;
	m_normal[0] = nX;
	m_normal[1] = nY;
	m_normal[2] = nZ;
	m_texCoord[0] = tU;
	m_texCoord[1] = tV;
}

Vertex::Vertex(float pos[3],float nor[3],float tex[2]){
	this->setPX(pos[0]);
	this->setPY(pos[1]);
	this->setPZ(pos[2]);
	this->setNX(nor[0]);
	this->setNY(nor[1]);
	this->setTU(tex[0]);
	this->setTV(tex[1]);
}

Vertex::~Vertex()
{}

//Metodos Set
void  Vertex::setPX (float pX){
	m_position[0] = pX;
}
void  Vertex::setPY (float pY){
	m_position[1] = pY;
}
void  Vertex::setPZ (float pZ){
	m_position[2] = pZ;
}

void  Vertex::setPosition (float pX, float pY, float pZ){
	m_position[0] = pX;
	m_position[1] = pY;
	m_position[2] = pZ;
}

void  Vertex::setPosition (const Vector3 &position){
	m_position = position;
}

void  Vertex::setNX (float nX){
	m_normal[0] = nX;
}
void  Vertex::setNY (float nY){
	m_normal[1] = nY;
}
void  Vertex::setNormal (float nX, float nY, float nZ){
	m_normal[0] = nX;
	m_normal[1] = nY;
	m_normal[2] = nZ;
}

void  Vertex::setNormal (const Vector3 &normal){
	m_normal = normal;
}

void  Vertex::setTU (float tU){
	m_texCoord[0] = tU;
}
void  Vertex::setTV (float tV){
	m_texCoord[1] = tV;
}
void  Vertex::setTexCoord (float tU, float tV){
	m_texCoord[0] = tU;
	m_texCoord[1] = tV;
}

void  Vertex::setTexCoord(const Vector2 &texCoord){
	m_texCoord = texCoord;
}
    
//Metodos Get
float  Vertex::getPX (){
	return m_position[0];
}
float  Vertex::getPY (){
	return m_position[1];
}
float  Vertex::getPZ (){
	return m_position[2];
}

Vector3 *Vertex::getPosition(){
	return &m_position;
	
}

float  Vertex::getNX (){
	return m_normal[0];
}

float  Vertex::getNY (){
	return m_normal[1];
}

float  Vertex::getNZ (){
	return m_normal[2];
}

Vector3 *Vertex::getNormal(){
	return &m_normal;
}

float  Vertex::getTU (){
	return m_texCoord[0];
}
float  Vertex::getTV (){
	return m_texCoord[1];
}

Vector2 *Vertex::getTexCoord (){
	return &m_texCoord;
}

float *Vertex::getPositionOffset(){
	return &m_position[0];
}

float *Vertex::getTextureOffset(){
	return &m_texCoord[0];
}

float *Vertex::getNormalOffset(){
	return &m_normal[0];
}

//Metodos Operadores
Vertex Vertex::operator+(const Vertex &vert) const{
	Vertex vertRet;
	vertRet = *this;
	vertRet.m_position += vert.m_position;
	vertRet.m_texCoord += vert.m_texCoord;						
	vertRet.m_normal += vert.m_normal;						
	return vertRet;
};

Vertex Vertex::operator-(const Vertex &vert) const{
	Vertex vertRet;
	vertRet = *this;
	vertRet.m_position -= vert.m_position;
	vertRet.m_texCoord -= vert.m_texCoord;						
	vertRet.m_normal -= vert.m_normal;						
	return vertRet;
}

// Multiplicacao por escalar
Vertex Vertex::operator*(float f) const{
	Vertex vertRet;
	vertRet = *this;
	vertRet.m_position *= f;
	vertRet.m_texCoord *= f;						
	vertRet.m_normal *= f;						
	return vertRet;
};

Vertex &Vertex::operator=(const Vertex &vert){
	m_position = vert.m_position;
	m_normal = vert.m_normal;
	m_texCoord = vert.m_texCoord;
	return *this;
}

Vertex *Vertex::operator=( Vertex *vert){
	m_position = vert->m_position;
	m_normal = vert->m_normal;
	m_texCoord = vert->m_texCoord;
	return this;
}

Vertex &Vertex::operator+=(const Vertex &vert){
	m_position += vert.m_position;
	m_texCoord += vert.m_texCoord;						
	m_normal += vert.m_normal;						
	return *this;
};
Vertex &Vertex::operator-=(const Vertex &vert){
	m_position -= vert.m_position;
	m_texCoord -= vert.m_texCoord;						
	m_normal -= vert.m_normal;						
	return *this;
};
Vertex &Vertex::operator*=(float f){
	m_position *= f;
	m_texCoord *= f;						
	m_normal *= f;						
	return *this;
};		

