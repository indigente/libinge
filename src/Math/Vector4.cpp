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

#include "Vector4.h"


using namespace InGE;

 // Vector4 
 
// Contrutor do vetor 4D
Vector4::Vector4(const Vector4 &vet){
	v[0] = vet.v[0];
	v[1] = vet.v[1];
	v[2] = vet.v[2];
	v[3] = vet.v[3];
}

Vector4::Vector4(float x, float y, float z, float w){
	this->setX(x);
	this->setY(y);
	this->setZ(z);
	this->setW(w);
}

Vector4::Vector4(float vet[4]){
	v[0] = vet[0];
	v[1] = vet[1];
	v[2] = vet[2];
	v[3] = vet[3];
}

// Metodos SET/GET
void Vector4::setX(float x){ this->v[0] = x; }
void Vector4::setY(float y){ this->v[1] = y; }
void Vector4::setZ(float z){ this->v[2] = z; }
void Vector4::setW(float w){ this->v[3] = w; }
float Vector4::getX() const { return this->v[0]; }
float Vector4::getY() const { return this->v[1]; }
float Vector4::getZ() const { return this->v[2]; }
float Vector4::getW() const { return this->v[3]; }

void Vector4::setXYZW(float x, float y, float z, float w){ 
	this->v[0] = x;
	this->v[1] = y;
	this->v[2] = z;
	this->v[3] = w; 
}

// Retorna o Modulo vetor 4D
float Vector4::getNorma() const{
	return sqrt(this->dot(*this));
}

// Produto interno do vetor 4D
float Vector4::dot(const Vector4 &vet) const{
	return v[0]*vet.v[0] + v[1]*vet.v[1] + v[2]*vet.v[2] + v[3]*vet.v[3];
}

// Produto interno do vetor 4D
float Vector4::operator*(const Vector4 &vet) const{
	return this->dot(vet);
}

// Retorna um Versor do vetor 4D
Vector4 Vector4::getVersor() const{
	float norma = this->getNorma();
	return Vector4(v[0]/norma, v[1]/norma, v[2]/norma, v[3]/norma);
}

void Vector4::normalize(){
	float norma = this->getNorma();
	
	if(norma == 0.0f) return;
	
	v[0] /= norma;
	v[1] /= norma;
	v[2] /= norma;
	v[3] /= norma;
}

// Retorna a soma de 2 vetores
Vector4 Vector4::operator+(const Vector4 &vet) const{
	return Vector4(v[0]+vet.v[0], v[1]+vet.v[1], v[2]+vet.v[2],v[3]+vet.v[3]);
}


// Retorna o vetor somado ao argumento
Vector4 Vector4::operator+=(const Vector4 &vet){
	v[0] += vet.v[0];
	v[1] += vet.v[1];
	v[2] += vet.v[2];
	v[3] += vet.v[3];
	return *this;	
}

// Retorna a subtracao de 2 vetores
Vector4 Vector4::operator-(const Vector4 &vet) const{
	return Vector4(v[0]-vet.v[0], v[1]-vet.v[1], v[2]-vet.v[2], v[3]-vet.v[3]);
}

// Retorna o vetor subtraido do argumento
Vector4 Vector4::operator-=(const Vector4 &vet){
	v[0] -= vet.v[0];
	v[1] -= vet.v[1];
	v[2] -= vet.v[2];
	v[3] -= vet.v[3];
	return *this;	
}


// Multiplicacao por escalar
Vector4 Vector4::operator*(float factor) const{
	return Vector4(v[0]*factor, v[1]*factor, v[2]*factor, v[3]*factor);
}


// Retorna o vetor multiplicado ao argumento
Vector4 Vector4::operator*=(float factor){
	v[0] *= factor;
	v[1] *= factor;
	v[2] *= factor;
	v[3] *= factor;
	return *this;	
}


// Divisao por escalar
Vector4 Vector4::operator/(float factor) const{
	return Vector4(v[0]/factor, v[1]/factor, v[2]/factor, v[3]/factor);
}


// Retorna o vetor divido do argumento
Vector4 Vector4::operator/=(float factor){
	if(factor == 0.0f) return Vector4();
	
	v[0] /= factor;
	v[1] /= factor;
	v[2] /= factor;
	v[3] /= factor;
	return *this;	
}


// Atribuicao
Vector4 Vector4::operator=(const Vector4 &vet){
	v[0] = vet.v[0];
	v[1] = vet.v[1];
	v[2] = vet.v[2];
	v[3] = vet.v[3];
	
	return *this;
}

// Atribuicao
Vector4 *Vector4::operator=(Vector4 *vet){
	v[0] = vet->v[0];
	v[1] = vet->v[1];
	v[2] = vet->v[2];
	v[3] = vet->v[3];

	return this;	
}


bool Vector4::operator==(const Vector4 &vet) const{
	if( (v[0] == vet.v[0]) && (v[1] == vet.v[1]) && (v[2] == vet.v[2]) && (v[3] == vet.v[3])) 
		return true;
	return false;

}

const float *Vector4::toArray(){
	return v;
}
