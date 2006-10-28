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
#include "Spline.h"
#include "Matrix4.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <iostream>

#define min(A,B) ((A<B) ? (A):(B))

using std::cout;
using std::endl;

namespace InGE {

float interpolating[4][4] = {
		{1,        0,       0,       0      },
		{-5.0/6.0, 3,      -3.0/2.0, 1.0/3.0},
		{1.0/3.0, -3.0/2.0, 3,      -5.0/6.0},
		{0,        0,       0,       1      }
	};
float bspline[4][4] = {
		{1.0/6.0, 2.0/3.0, 1.0/6.0, 0      },
		{0,       2.0/3.0, 1.0/3.0, 0      },
		{0,       1.0/3.0, 2.0/3.0, 0      },
		{0,       1.0/6.0, 2.0/3.0, 1.0/6.0}
	};

Spline::Spline(InGE_Spline_Type type, float u, float v, vector<Vector3> data)
{
	m_type = type;
	m_step = 3;
	m_u = u;
	m_v = v;
	Vector4 vet4;
	if (type == InGE_BSPLINE) {
		m_step = 1;
		m_data.push_back(data[0]);//FIXME: menino feio, deve ter uma solucao melhor.
		for ( int i = 0; i + 3 < data.size(); i+=1 ) {
			m_data.pop_back();
			for(int j = 0; j < 4; ++j){
				Vector3 vet3;
				for(int k = 0; k < 3; ++k){
					vet3[k] = data[ i ][k]*bspline[j][0]
						+ data[i+1][k]*bspline[j][1]
						+ data[i+2][k]*bspline[j][2]
						+ data[i+3][k]*bspline[j][3];
				}
				m_data.push_back(vet3);
			}
		}
	} else if (type == InGE_INTERPOLATING) {
		m_data.push_back(data[0]);
		for ( int i = 0; i + 3 < data.size(); i+=3 ) {
			for(int j = 1; j < 4; ++j){
				Vector3 vet3;
				for(int k = 0; k < 3; ++k){
					vet3[k] = data[ i ][k]*interpolating[j][0]
						+ data[i+1][k]*interpolating[j][1]
						+ data[i+2][k]*interpolating[j][2]
						+ data[i+3][k]*interpolating[j][3];
				}
				m_data.push_back(vet3);
			}
		}
	} else {
		m_data = data;
	}
}


Spline::~Spline()
{
}

//evaluate a point on the B spline
Vector3 Spline::p(int i, float t) {
	Vector3 point(0,0,0);

	point += m_data[i]*((1-t)*(1-t)*(1-t));
	point += m_data[i+1]*(3*t*(1-t)*(1-t));
	point += m_data[i+2]*(3*t*t*(1-t));
	point += m_data[i+3]*(t*t*t);
	return point;
}

Vector3 Spline::evaluate(float t)
{
	if(isValid(t)) { //FIXME: Assert()
		float normalized = (t - m_u)/(m_v - m_u); // intervalo 0 a 1
		int ncurves = (m_data.size()-1)/3; //FIXME: B-spline é diferente.
		float patch_size = (m_v - m_u) / ncurves;
		int patch = (int) (normalized / patch_size);
		if (patch >= ncurves) --patch;
		float value = (normalized - patch*patch_size)/patch_size;
		//return p(0, t); //FIXME: identificar a curva
		return p(3*patch, value);
	}
}

void Spline::draw()
{
	Vector3 v;
	
	
	/*glEnable(GL_MAP1_VERTEX_3);
	glMap1f(GL_MAP1_VERTEX_3, m_u, m_v, 3, 4, (float*) &m_data[0]);
	glMapGrid1f(20, m_u, m_v);
	glEvalMesh1(GL_LINE, 0, 20);*/
	//cout << "chamou" << endl;

	glColor3f(0.0, 0.0, 1.0);
	glPointSize(7.0);
	glBegin(GL_POINTS);
	for( int i = 0; i < m_data.size(); ++i ) {
		glVertex3fv((float*) &(m_data[i]));
	}
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	for( int i = 0; i < m_data.size(); ++i ) {
		glVertex3fv((float*) &(m_data[i]));
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i <= 100; ++i){
		v = evaluate(i/100.0);
		//cout << "(" << v[0] << ";" << v[1] << ";" << v[2] << ") ";
		glVertex3fv((float*) &v);
	}
	glEnd();
	//cout << endl;
	glColor4f(1.0, 1.0, 1.0, 1.0);
}

float Spline::getStart(){
	return m_u;
}

float Spline::getEnd(){
	return m_v;
}

}

