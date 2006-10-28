/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004 Indigente


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

#include "Vector2.h"


using namespace InGE;

 //Vector2

/**
 * Construtor de Vetor de duas dimensoes
 */ 
Vector2::Vector2(const Vector2 &vet){
	v[0] = vet.v[0];
	v[1] = vet.v[1];
}
/**
 * Construtor de Vetor de duas dimensoes
 */ 
Vector2::Vector2(float x, float y){
	this->setX(x);
	this->setY(y);
}
/**
 * Construtor de Vetor de duas dimensoes
 */ 
Vector2::Vector2(float vet[2]){
	v[0] = vet[0];
	v[1] = vet[1];
}

// Metodos SET/GET
void Vector2::setX(float x){ this->v[0] = x;}
void Vector2::setY(float y){ this->v[1] = y;}
float Vector2::getX() const { return this->v[0]; }
float Vector2::getY() const { return this->v[1]; }

void Vector2::setXY(float x, float y){ 
	this->v[0] = x;
	this->v[1] = y;
}

// Retorna o Modulo vetor 2D
float Vector2::getNorma() const{
	return sqrt(this->dot(*this));
}

// Produto interno do vetor 2D
float Vector2::dot(const Vector2 &vet) const{
	return v[0]*vet.v[0] + v[1]*vet.v[1];
}

// Produto interno do vetor 2D
float Vector2::operator*(const Vector2 &vet) const{
	return this->dot(vet);
}

// Retorna um Versor do vetor 2D
Vector2 Vector2::getVersor() const{
	float norma = this->getNorma();
	return Vector2(v[0]/norma, v[1]/norma);
}

void Vector2::normalize(){
	float norma = this->getNorma();
	
	if(norma == 0.0f);
	
	v[0] /= norma;
	v[1] /= norma;
}


// Retorna a soma de 2 vetores
/**
 * Operador de soma entre Vector2
 * @param Vector2 vet - Vector2 a ser somado
 * @return Retorna o Vector2 somado
 */
Vector2 Vector2::operator+(const Vector2 &vet) const{
	return Vector2(v[0]+vet.v[0], v[1]+vet.v[1]);
}

// Retorna o vetor somado ao argumento
Vector2 Vector2::operator+=(const Vector2 &vet){
	v[0] += vet.v[0];
	v[1] += vet.v[1];
	return *this;	
}

// Retorna a subtracao de 2 vetores
Vector2 Vector2::operator-(const Vector2 &vet) const{
	return Vector2(v[0]-vet.v[0], v[1]-vet.v[1]);
}

// Retorna o vetor subtraido do argumento
Vector2 Vector2::operator-=(const Vector2 &vet){
	v[0] -= vet.v[0];
	v[1] -= vet.v[1];
	return *this;	
}

// Multiplicacao por escalar
Vector2 Vector2::operator*(float factor) const{
	return Vector2(v[0]*factor, v[1]*factor);
}

// Retorna o vetor multiplicado ao argumento
Vector2 Vector2::operator*=(float factor){
	v[0] *= factor;
	v[1] *= factor;
	return *this;	
}

// Divisao por escalar
Vector2 Vector2::operator/(float factor) const{
	return Vector2(v[0]/factor, v[1]/factor);
}

// Retorna o vetor divido do argumento
Vector2 Vector2::operator/=(float factor){
	if(factor == 0.0f) return Vector2();
	v[0] /= factor;
	v[1] /= factor;
	return *this;	
}


Vector2 Vector2::operator=(const Vector2 &vet){
	v[0] = vet.v[0];
	v[1] = vet.v[1];
	
	return *this;
}

Vector2 *Vector2::operator=(Vector2 *vet){
	v[0] = vet->v[0];
	v[1] = vet->v[1];
	
	return this;
}

bool Vector2::operator==(const Vector2 &vet) const{
	if((v[0] == vet.v[0]) && (v[1] == vet.v[1])) 
		return true;
	
	return false;
}

const float *Vector2::toArray(){
	return v;
}
