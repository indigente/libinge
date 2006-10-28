/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004-2005 Indigente


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

#include "Quaternion.h"
#include <math.h>

using namespace InGE;

/**
 * Construtor
 * @param float w
 * @param float x
 * @param float y
 * @param float z
 */
Quaternion::Quaternion( float w, float x, float y, float z){
	m_w = w;
	m_x = x;
	m_y = y;
	m_z = z;
}

/*
Construtor
 * @param float i - X do vertice que será rotacionado
 * @param float j - Y do vertice que será rotacionado
 * @param float k - Z do vertice que será rotacionado
 * @param float degree - Ângulo de rotação em graus
 */
Quaternion::Quaternion( float degree, Vector3 axis){
	float result, angle;
	
	
	angle = ( (degree / 360.0f ) *  PI );
	result = sin( angle );

	// Equacoes de transformacao
	// i,j,k sao componentes do vetor de rotacao
	// degree eh o angulo de rotacao.
	
	axis.normalize();
	
	m_w = cos(angle);
	m_x = axis[0] * result;
	m_y = axis[1] * result;
	m_z = axis[2] * result;
}


/**
 * Destrutor
 */
Quaternion::~Quaternion()
{}

float Quaternion::getW() const{
	return m_w;
}

float Quaternion::getX() const{
	return m_x;
}

float Quaternion::getY() const{
	return m_y;
}

float Quaternion::getZ() const{
	return m_z;
}

// Retorna a soma de 2 Quaternions
Quaternion Quaternion::operator+(const Quaternion &quat) const{
	return Quaternion(m_w + quat.getW(), m_x + quat.getX(), m_y + quat.getY(), m_z + quat.getZ());
}

// Retorna o Quaternion somado ao argumento
Quaternion Quaternion::operator+=(const Quaternion &quat){
	m_w += quat.getW();
	m_x += quat.getX();
	m_y += quat.getY();
	m_z += quat.getZ();
	return *this;	
}
// Retorna a subtracao de 2 Quaternions
Quaternion Quaternion::operator-(const Quaternion &quat) const{
	return Quaternion(m_w - quat.getW(), m_x - quat.getX(), m_y - quat.getY(), m_z - quat.getZ());
}

// Retorna o Quaternion subtraido do argumento
Quaternion Quaternion::operator-=(const Quaternion &quat){
	m_w -= quat.getW();
	m_x -= quat.getX();
	m_y -= quat.getY();
	m_z -= quat.getZ();
	return *this;	
}

// Retorna a multiplicação de 2 Quaternions
Quaternion Quaternion::operator*(const Quaternion &quat) const{
	return Quaternion(m_w * quat.getW() - m_x * quat.getX() - m_y * quat.getY() - m_z * quat.getZ(),
					  m_w * quat.getW() + m_x * quat.getX() + m_y * quat.getY() - m_z * quat.getZ(),
					  m_w * quat.getW() - m_x * quat.getX() + m_y * quat.getY() + m_z * quat.getZ(),
					  m_w * quat.getW() + m_x * quat.getX() - m_y * quat.getY() + m_z * quat.getZ());
}

// Retorna o Quaternion multiplicado ao argumento
Quaternion Quaternion::operator*=(const Quaternion &quat){
	m_w = m_w * quat.getW() - m_x * quat.getX() - m_y * quat.getY() - m_z * quat.getZ();
	m_x = m_w * quat.getW() + m_x * quat.getX() + m_y * quat.getY() - m_z * quat.getZ();
	m_y = m_w * quat.getW() - m_x * quat.getX() + m_y * quat.getY() + m_z * quat.getZ();
	m_z = m_w * quat.getW() + m_x * quat.getX() - m_y * quat.getY() + m_z * quat.getZ();
	return *this;	
}

Quaternion Quaternion::operator=(const Quaternion &quat){
	m_w = quat.getW();
	m_x = quat.getX();
	m_y = quat.getY();
	m_z = quat.getZ();
	return *this;
}

Quaternion *Quaternion::operator=(Quaternion *quat){
	m_w = quat->getW();
	m_x = quat->getX();
	m_y = quat->getY();
	m_z = quat->getZ();
	return this;
}

bool Quaternion::operator==(Quaternion &quat){
	m_x = quat.getX();
	m_y = quat.getY();
	m_z = quat.getZ();


	if((m_w == quat.getW()) && (m_x == quat.getX()) && (m_y == quat.getY()) && (m_z == quat.getZ())) 
		return true;
	
	return false;
}

Quaternion Quaternion::conjugate(){
	return Quaternion(m_w, -m_x, -m_y, -m_z);
}

/**
 *  Cria matriz de rotação
 * @param float *mat - Matriz a ser transformada
 */
float *Quaternion::quaternionToMatrix(){
    //     ¦        2     2                                              ¦
    //     ¦ 1 - (2y  + 2z )   2xy + 2zw         2xz - 2yw          0    ¦
    //     ¦                                                             ¦
    //     ¦                          2     2                            ¦
    // M = ¦ 2xy - 2zw         1 - (2x  + 2z )   2zy + 2xw          0    ¦
    //     ¦                                                             ¦
    //     ¦                                            2     2          ¦
    //     ¦ 2xz + 2yw         2yz - 2xw         1 - (2x  + 2y )    0    ¦
    //     ¦                                                             ¦
    //     ¦                                                             ¦
    //     ¦ 0                 0                 0                  1    |                                                   ¦
    //     ¦                                                             ¦
	float *mat = new float[16];

    // Primeira linha da matriz
    mat[ 0] = 1.0f - 2.0f * ( m_y * m_y + m_z * m_z );
    mat[ 1] = 2.0f * ( m_x * m_y - m_w * m_z );
    mat[ 2] = 2.0f * ( m_x * m_z + m_w * m_y );
    mat[ 3] = 0.0f;

    // Segunda linha da matriz
    mat[ 4] = 2.0f * ( m_x * m_y + m_w * m_z );
    mat[ 5] = 1.0f - 2.0f * ( m_x * m_x + m_z * m_z );
    mat[ 6] = 2.0f * ( m_y * m_z - m_w * m_x );
    mat[ 7] = 0.0f;

    // Terceira linha da matriz
    mat[ 8] = 2.0f * ( m_x * m_z - m_w * m_y );
    mat[ 9] = 2.0f * ( m_y * m_z + m_w * m_x );
    mat[10] = 1.0f - 2.0f * ( m_x * m_x + m_y * m_y );
    mat[11] = 0.0f;

    // Quarta linha da matriz
    mat[12] = 0;
    mat[13] = 0;
    mat[14] = 0;
    mat[15] = 1.0f;
    return mat;
}

void Quaternion::matrixToQuaternion(float *matRot){
	float	trace, s, q[4];
	int		i, j, k;
	int		nxt[3] = { 1, 2, 0 };  

	trace = matRot[0] + matRot[4] + matRot[8];

	// check la diagonale
	if( trace > 0.0 ){
		s = (float)sqrt( trace + 1.0 );
		m_w = s / 2.0f;
		s = 0.5f / s;

		m_x = (matRot[7] - matRot[5]) * s;
		m_y = (matRot[2] - matRot[6]) * s;
		m_z = (matRot[3] - matRot[1]) * s;
	}else{                
		// la diagonale est negative
		i = 0;
		if( matRot[4] > matRot[0] ) i = 1;
		if( matRot[8] > matRot[ (i * 3) + i ] ) i = 2;
		j = nxt[i];
		k = nxt[j];

		s = (float)sqrt( (matRot[ (i * 3) + i ] - (matRot[ (j * 3) + j ] + matRot[ (k * 3) + k ])) + 1.0 );

		q[i] = s * (float)0.5;

		if( s != 0.0 )
			s = 0.5f / s;

		q[3] = (matRot[ (k * 3) + j ] - matRot[ (j * 3) + k ]) * s;
		q[j] = (matRot[ (j * 3) + i ] + matRot[ (i * 3) + j ]) * s;
		q[k] = (matRot[ (k * 3) + i ] + matRot[ (i * 3) + k ]) * s;

		m_x = q[0];
		m_y = q[1];
		m_z = q[2];
		m_w = q[3];
	}
}

void Quaternion::quaternionSlerp(Quaternion *from,Quaternion *to, float t){
	float	to1[4];
	float	theta, cos_theta, sin_theta, scale0, scale1;


	// on calcule le cosinus
	cos_theta = (from->getX() * to->getX()) + (from->getY() * to->getY())
			  + (from->getZ() * to->getZ()) + (from->getW() * to->getW());

	// on ajuste les signes (si necessaire)
	if( cos_theta < 0.0 ){
		cos_theta = -cos_theta;
		to1[0] = -to->getX();
		to1[1] = -to->getY();
		to1[2] = -to->getZ();
		to1[3] = -to->getW();
	}else{
		to1[0] = to->getX();
		to1[1] = to->getY();
		to1[2] = to->getZ();
		to1[3] = to->getW();
	}

	// on calcule les coeffs
	if( (1.0 - cos_theta) > EPSILON ){
		// cas standard (slerp)
		theta      = (float)acos( cos_theta );
		sin_theta  = (float)sin( theta );
		scale0     = (float)sin( (1.0 - t) * theta ) / sin_theta;
		scale1     = (float)sin( t * theta ) / sin_theta;

	}else{
		// les quaternions "from" et "to" sont trÃ¨s proches
		// donc on peut faire une interpolation linÃ©aire simple
		scale0 = 1.0f - t;
		scale1 = t;
	}

	// on calcule les valeurs finales
	m_x = scale0 * from->getX() + scale1 * to1[0];
	m_y = scale0 * from->getY() + scale1 * to1[1];
	m_z = scale0 * from->getZ() + scale1 * to1[2];
	m_w = scale0 * from->getW() + scale1 * to1[3];
}
