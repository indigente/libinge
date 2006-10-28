/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004-2006 Indigente


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
#include "CameraSpline.h"
//FIXME: retirar as tres linhas abaixo
#include <iostream>
using std::cerr;
using std::endl;

using namespace InGE;

CameraSpline::CameraSpline(Spline *pPosition, Spline *pViewPoint ,float speed){
	m_position.setXYZ (0.0f, 0.0f, 0.0f);
	m_viewPoint.setXYZ(0.0f, 1.0f, 0.0f);
	m_up.setXYZ       (0.0f, 0.0f, 1.0f);
	
	m_speed = speed;

	m_pVolumeInfo = new VolumeInfo( Vector3(0,0,0),Vector3(0,0,0),m_position,30);
	
	if (pPosition){
		m_pPositionSpline = pPosition;
	} else {
		m_pPositionSpline = NULL;
	}
	
	if (pViewPoint){
		m_pViewPontSpline = pViewPoint;
	} else {
		m_pViewPontSpline = NULL;
	}
}


CameraSpline::~CameraSpline(){
	if (m_pPositionSpline)
		delete m_pPositionSpline;
	if (m_pViewPontSpline)
		delete m_pViewPontSpline;
	if (m_pVolumeInfo)
		delete m_pVolumeInfo;
}

/**
 * @return Retorna a posição da camera
 */
Vector3 CameraSpline::getPosition(){
	if (m_pPositionSpline)
		m_position = m_pPositionSpline->evaluate( interpolation(1) );
	
	return m_position;
}

/**
 * @return Retorna o ponto para o qual a camera olha
 */
Vector3 CameraSpline::getViewPoint(){
	if (m_pViewPontSpline)
		m_viewPoint = m_pViewPontSpline->evaluate( interpolation(0) );
	
	return m_viewPoint;
}

/**
 * Calcula a interpolação
 * @param bool select - seleciona se calcuará a interpolação de Position ou ViewPoint
 * @return Retorna a interpolação
 */
float CameraSpline::interpolation(bool select){
	// Tempo atual
	float currentTime = SDL_GetTicks();
	static float timePosition = currentTime;
	static float timeViewPoint = currentTime;
	
	// Tempo passado entre inicio e o tempo atual
	float elapsedTime = currentTime - timePosition;
	
	float t;
	if (select){
		t = elapsedTime + m_pPositionSpline->getStart();
		t = ( (t/ 10000) * m_speed );
		
		if (t > m_pPositionSpline->getEnd() ){
			timePosition = currentTime;
			t = 0;
		}
	} else {
		t = elapsedTime + m_pViewPontSpline->getStart();
		t = ( (t/ 10000) * m_speed );

		if (t > m_pViewPontSpline->getEnd() ){
			timePosition = currentTime;
			t = 0;
		}
	}
	return t;	
}
