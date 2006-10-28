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

#include "Vector3.h"


using namespace InGE;



 // Vector3

// Construtor do vetor 3D 
Vector3::Vector3(const Vector3 &vet){
	m_v[0] = vet.m_v[0];
	m_v[1] = vet.m_v[1];
	m_v[2] = vet.m_v[2];
}

Vector3::Vector3(float x, float y, float z){
	m_v[0] = x;
	m_v[1] = y;
	m_v[2] = z;
}

Vector3::Vector3(float vet[3]){
	m_v[0] = vet[0];
	m_v[1] = vet[1];
	m_v[2] = vet[2];
}

// Metodos SET/GET
void Vector3::setX(float x){ m_v[0] = x;}
void Vector3::setY(float y){ m_v[1] = y;}
void Vector3::setZ(float z){ m_v[2] = z;}
float Vector3::getX() const { return m_v[0]; }
float Vector3::getY() const { return m_v[1]; }
float Vector3::getZ() const { return m_v[2]; }

void Vector3::setXYZ(float x, float y, float z){ 
	m_v[0] = x;
	m_v[1] = y;
	m_v[2] = z;
} 
 
// Retorna o Modulo vetor 3D
float Vector3::getNorma() const{
	return sqrt(this->dot(*this));
}

// Produto interno do vetor 3D
float Vector3::dot(const Vector3 &vet) const{
	return m_v[0]*vet.m_v[0] + m_v[1]*vet.m_v[1] + m_v[2]*vet.m_v[2];
}



// Produto interno do vetor 3D
float Vector3::operator*(const Vector3 &vet) const{
	return this->dot(vet);
}

// Normaliv[2]a o vetor
void Vector3::normalize(){
	float norma = this->getNorma();

	if(norma == 0.0) return;
	
	m_v[0] /= norma;
	m_v[1] /= norma;
	m_v[2] /= norma;
}

/* Produto Vetorial
 * Retorna um vetor normal ao plano 
 * formado entros outros 2 vetor
 */
Vector3 Vector3::cross(const Vector3 &vet) const{
	return Vector3( m_v[1] * vet.m_v[2] - m_v[2] * vet.m_v[1],
			m_v[2] * vet.m_v[0] - m_v[0] * vet.m_v[2],
			m_v[0] * vet.m_v[1] - m_v[1] * vet.m_v[0] );
}

// Retorna um Versor do vetor 3D
Vector3 Vector3::getVersor() const{
	float norma = this->getNorma();
	return Vector3(m_v[0]/norma, m_v[1]/norma, m_v[2]/norma);
}

// Retorna a soma de 2 vetores
Vector3 Vector3::operator+(const Vector3 &vet) const{
	return Vector3(m_v[0]+vet.m_v[0], m_v[1]+vet.m_v[1], m_v[2]+vet.m_v[2]);
}


// Retorna o vetor somado ao argumento
Vector3 Vector3::operator+=(const Vector3 &vet){
	m_v[0] += vet.m_v[0];
	m_v[1] += vet.m_v[1];
	m_v[2] += vet.m_v[2];
	return *this;	
}

// Retorna a subtracao de 2 vetores
Vector3 Vector3::operator-(const Vector3 &vet) const{
	return Vector3(m_v[0]-vet.m_v[0], m_v[1]-vet.m_v[1], m_v[2]-vet.m_v[2]);
}

// Retorna o vetor subtraido do argumento
Vector3 Vector3::operator-=(const Vector3 &vet){
	m_v[0] -= vet.m_v[0];
	m_v[1] -= vet.m_v[1];
	m_v[2] -= vet.m_v[2];
	return *this;	
}


// Multiplicacao por escalar
Vector3 Vector3::operator*(float factor) const{
	return Vector3(m_v[0]*factor, m_v[1]*factor, m_v[2]*factor);
}

// Retorna o vetor multiplicado ao argumento
Vector3 Vector3::operator*=(float factor){
	m_v[0] *= factor;
	m_v[1] *= factor;
	m_v[2] *= factor;
	return *this;	
}


// Divisao por escalar
Vector3 Vector3::operator/(float factor) const{
	return Vector3(m_v[0]/factor, m_v[1]/factor, m_v[2]/factor);
}

// Retorna o vetor divido do argumento
Vector3 Vector3::operator/=(float factor){
	
	if(factor == 0.0f) return Vector3();
	
	m_v[0] /= factor;
	m_v[1] /= factor;
	m_v[2] /= factor;
	return *this;	
}


// Atribuicao
Vector3 Vector3::operator=(const Vector3 &vet){
	m_v[0] = vet.m_v[0];
	m_v[1] = vet.m_v[1];
	m_v[2] = vet.m_v[2];
	return *this;
}

// Atribuicao
Vector3 *Vector3::operator=(Vector3 *vet){
	m_v[0] = vet->m_v[0];
	m_v[1] = vet->m_v[1];
	m_v[2] = vet->m_v[2];
	return this;
}


bool Vector3::operator==(const Vector3 &vet) const{
	if( (m_v[0] == vet.m_v[0]) && (m_v[1] == vet.m_v[1]) && (m_v[2] == vet.m_v[2])) 
		return true;
	return false;
}

const float *Vector3::toArray(){
	return m_v;
}

void Vector3::print(){
	std::cout << "(" << m_v[0] << ", " << m_v[1] << ", " << m_v[2] << ")" << std::endl;
}
