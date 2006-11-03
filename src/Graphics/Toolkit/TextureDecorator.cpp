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

#include "TextureDecorator.h"
#include "../Render/Drawer.h"
#include "../Base/TextureArray.h"
#include "../Model/Primitive/Plane.h"
#include "../Base/Mesh.h"
#include "../Base/MeshDecorator/ConcreteMesh.h"
#include "../Base/MeshDecorator/AlphaBlend.h"
#include "../Base/MeshDecorator/MovieTex.h"

using namespace InGE;

TextureDecorator::TextureDecorator(const string &filename, IWidget *widget){
	m_widget = widget;
	m_w = widget->getWidth();
	m_h = widget->getHeight();
	
	
	m_pMesh = new ConcreteMesh();
	if(filename.find(".mpg", filename.size() - 4) != string::npos){
		m_pMesh = new MovieTex(m_pMesh, filename, true, 32);
	} else {
		m_matInfo = new MaterialInfo();
		m_matInfo->setTexture(filename);
	 	m_pMesh->addMaterial(*m_matInfo);
		
		if (m_matInfo->getBlend()){
			m_pMesh = new AlphaBlend(m_pMesh);
		}
	}

	m_pMesh->setDrawMode(InGE_POLYGON);
	m_pMesh->setFrontFace(InGE_CW);

	m_pMesh->addVertex( Vertex(  m_x,  m_y + m_h, 0.0, 		0.0, 0.0, 1.0, 0, 1 ) );
	m_pMesh->addVertex( Vertex(  m_x,  m_y, 0.0,					0.0, 0.0, 1.0, 0, 0 ) );
	m_pMesh->addVertex( Vertex( m_x + m_w, m_y, 0.0, 			0.0, 0.0, 1.0, 1, 0 ) );
	m_pMesh->addVertex( Vertex( m_x + m_w,  m_y + m_h, 0.0,	0.0, 0.0, 1.0, 1, 1 ) );

	//Face 1
	m_pMesh->addDrawIndex(0);
	m_pMesh->addDrawIndex(1);
	m_pMesh->addDrawIndex(2);
	m_pMesh->addDrawIndex(3);
}

TextureDecorator::~TextureDecorator(){
	if (m_pMesh) delete m_pMesh;
	delete m_widget; //FIXME: melhorar lugar pra desalocar?
}

void TextureDecorator::draw(float x, float y, float width, float height){
	m_pMesh->draw();
	
	//Draw the widget
	if (m_widget)
		m_widget->draw(x, y, width, height);
}

void TextureDecorator::setWidget(IWidget *w) {
	m_widget = w;
}

void TextureDecorator::move(float x, float y) {
	m_x = x;
	m_y = y;
	Vertex *pVertex;
	Vector3 *pPosition;
	for (int index = 0; index < m_pMesh->getNumVertex(); index++){
		pVertex = m_pMesh->getVertex( index );
		pVertex->setPX( pVertex->getPX() + x );
		pVertex->setPY( pVertex->getPY() + y );
	}
	
	if (m_widget)
		m_widget->move(x,y);
}

void TextureDecorator::resize(float width, float height) {
	m_w = width;
	m_h = height;
	if (m_widget)
		m_widget->resize(width,height);
}
