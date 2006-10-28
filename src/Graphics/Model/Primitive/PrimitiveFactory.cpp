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

#include "PrimitiveFactory.h"
using namespace InGE;
using namespace std;

PrimitiveFactory *PrimitiveFactory::m_pPrimitiveFactory = 0;

/**
 * Construtor
 */
PrimitiveFactory::PrimitiveFactory(){
 	m_loadedPrimitives.clear();
}

/**
 * @return Retorna a classe para ser usada
 */
PrimitiveFactory *PrimitiveFactory::getInstance(){
	if(!m_pPrimitiveFactory)
		m_pPrimitiveFactory = new PrimitiveFactory();
		
	return m_pPrimitiveFactory;
}

/**
 * Destrutor
 */
PrimitiveFactory::~PrimitiveFactory(){
	if(m_pPrimitiveFactory) delete m_pPrimitiveFactory;
}

int PrimitiveFactory::findPrimitiveFactory(string name){
	for( unsigned int i = 0; i < m_loadedPrimitives.size(); i++ ){
		if( m_loadedPrimitives[i]->getName() == name ){
			return i;
		}
	}
	return -1;
}

IModel	*PrimitiveFactory::getPrimitive(int index){
	return m_loadedPrimitives[index];
}

IModel	*PrimitiveFactory::getPrimitive(string name){
	int index = findPrimitiveFactory(name);
	if (index != -1)
		return m_loadedPrimitives[index];
	return NULL;
}

void PrimitiveFactory::rmPrimitive(int index){
	delete m_loadedPrimitives[index];
	
	std::vector<IModel *>::iterator it;
	it = m_loadedPrimitives.begin() + index;
	
	m_loadedPrimitives.erase( it );
}

void PrimitiveFactory::rmPrimitive(string name){
	int index = findPrimitiveFactory(name);
	if (index != -1){
		delete m_loadedPrimitives[index];
		std::vector<IModel *>::iterator it;
		it = m_loadedPrimitives.begin() + index;
		
		m_loadedPrimitives.erase( it );
	}
}

IModel 	*PrimitiveFactory::loadPrimitive(string name, int shape, float scale, string filenameTex){
	int index = findPrimitiveFactory(name);
	if (index != -1){
		return m_loadedPrimitives[index];
	} else {
		IModel *primitive;
		switch (shape) {
			case InGE_PRIMITIVE_BOX :
				primitive = this->loadBox(name, scale, filenameTex);
				m_loadedPrimitives.push_back(primitive);
				break;
				
			case InGE_PRIMITIVE_PLANE :
				primitive = this->loadPlane(name, scale, filenameTex);
				m_loadedPrimitives.push_back(primitive);
				break;
				
			case InGE_PRIMITIVE_SPHERE :
				break;
			default:
				break;
		}
		return primitive;
	}
}

Plane	*PrimitiveFactory::loadPlane(string name, float scale, string filenameTex){
	Mesh *pMesh=new ConcreteMesh();
	if(filenameTex.find(".mpg", filenameTex.size() - 4) != string::npos){
		pMesh = new MovieTex(pMesh, filenameTex, true, 32);
	}else {
		MaterialInfo texture;
		texture.setTexture(filenameTex);
		pMesh->addMaterial(texture);
		if (texture.getBlend()){
			pMesh = new AlphaBlend(pMesh);
		}
	} 
	if (false){//fazer o roll
		pMesh = new RollTexture( pMesh, 0.00001, 0.0001 );
	}
	
	pMesh->setName(name);
	pMesh->setDrawMode(InGE_POLYGON);
	pMesh->setFrontFace(InGE_CW);

		

	pMesh->addVertex( Vertex(  scale,  scale,  0.0, 0.0, 0.0, 1.0, 0, 0 ) );
	pMesh->addVertex( Vertex(  scale, -scale,  0.0, 0.0, 0.0, 1.0, 0, 1 ) );
	pMesh->addVertex( Vertex( -scale, -scale,  0.0, 0.0, 0.0, 1.0, 1, 1 ) );
	pMesh->addVertex( Vertex( -scale,  scale,  0.0, 0.0, 0.0, 1.0, 1, 0 ) );


	//Face 1
	pMesh->addDrawIndex(0);
	pMesh->addDrawIndex(1);
	pMesh->addDrawIndex(2);
	pMesh->addDrawIndex(3);
	
	
	return new Plane( pMesh );
}

Box 	*PrimitiveFactory::loadBox(string name, float scale, string filenameTex){
	MaterialInfo texture;
	texture.setTexture(filenameTex);

	Mesh *pMesh = new ConcreteMesh();
	if (texture.getBlend()){
		pMesh = new AlphaBlend(pMesh);
	}else{
		pMesh = new MovieTex(new ConcreteMesh(), "/home/fehler/Desktop/sbgames2005/14671-arquitetura-ffpp.mpg", true);
	}
	if (false){//fazer o roll
		pMesh = new RollTexture( pMesh, 0.00001, 0.0001 );
	}
	if (false){
		MaterialInfo mask;
		mask.setTexture("texturas/cruz-mask.bmp");
		pMesh = new Mask(pMesh, mask);
	}
	if (false){
		MaterialInfo multi;
		multi.setTexture("texturas/mult2.bmp");
		pMesh = new MultiTexture(pMesh, multi);
	}
	if (false) {
		MaterialInfo lightmap;
		lightmap.setTexture("texturas/teste-lightmap.tga");
	
		vector<Vector2 > vetLightmap;
		vetLightmap.push_back( Vector2(1,0) );
		vetLightmap.push_back( Vector2(1,1) );
		vetLightmap.push_back( Vector2(0,1) );
		vetLightmap.push_back( Vector2(0,0) );
	
		pMesh = new Lightmap(pMesh, lightmap.getId(), vetLightmap);
	}


	pMesh->setName(name);
	pMesh->setDrawMode(InGE_QUADS);
	pMesh->setFrontFace(InGE_CW);

	pMesh->addMaterial(texture);
	

	//Face 1
	pMesh->addVertex( Vertex(  scale,  scale,  scale,  1.0,  0.0,  0.0, 1, 0 ) );
	pMesh->addVertex( Vertex(  scale,  scale, -scale,  1.0,  0.0,  0.0, 1, 1 ) );
	pMesh->addVertex( Vertex(  scale, -scale, -scale,  1.0,  0.0,  0.0, 0, 1 ) );
	pMesh->addVertex( Vertex(  scale, -scale,  scale,  1.0,  0.0,  0.0, 0, 0 ) );

	//Face 2
	pMesh->addVertex( Vertex( -scale, -scale,  scale, -1.0,  0.0,  0.0, 1, 0 ) );
	pMesh->addVertex( Vertex( -scale, -scale, -scale, -1.0,  0.0,  0.0, 1, 1 ) );
	pMesh->addVertex( Vertex( -scale,  scale, -scale, -1.0,  0.0,  0.0, 0, 1 ) );
	pMesh->addVertex( Vertex( -scale,  scale,  scale, -1.0,  0.0,  0.0, 0, 0 ) );

	//Face 3
	pMesh->addVertex( Vertex(  scale,  scale,  scale,  0.0,  0.0,  1.0, 0, 0 ) );
	pMesh->addVertex( Vertex(  scale, -scale,  scale,  0.0,  0.0,  1.0, 0, 1 ) );
	pMesh->addVertex( Vertex( -scale, -scale,  scale,  0.0,  0.0,  1.0, 1, 1 ) );
	pMesh->addVertex( Vertex( -scale,  scale,  scale,  0.0,  0.0,  1.0, 1, 0 ) );

	//Face 4
	pMesh->addVertex( Vertex( -scale,  scale, -scale,  0.0,  0.0, -1.0, 1, 0 ) );
	pMesh->addVertex( Vertex( -scale, -scale, -scale,  0.0,  0.0, -1.0, 1, 1 ) );
	pMesh->addVertex( Vertex(  scale, -scale, -scale,  0.0,  0.0, -1.0, 0, 1 ) );
	pMesh->addVertex( Vertex(  scale,  scale, -scale,  0.0,  0.0, -1.0, 0, 0 ) );
	
	//Face 5
	pMesh->addVertex( Vertex( -scale,  scale,  scale,  0.0,  1.0,  0.0, 1, 0 ) );
	pMesh->addVertex( Vertex( -scale,  scale, -scale,  0.0,  1.0,  0.0, 1, 1 ) );
	pMesh->addVertex( Vertex(  scale,  scale, -scale,  0.0,  1.0,  0.0, 0, 1 ) );
	pMesh->addVertex( Vertex(  scale,  scale,  scale,  0.0,  1.0,  0.0, 0, 0 ) );
	
	//Face 6
	pMesh->addVertex( Vertex(  scale, -scale,  scale,  0.0, -1.0,  0.0, 1, 0 ) );
	pMesh->addVertex( Vertex(  scale, -scale, -scale,  0.0, -1.0,  0.0, 1, 1 ) );
	pMesh->addVertex( Vertex( -scale, -scale, -scale,  0.0, -1.0,  0.0, 0, 1 ) );
	pMesh->addVertex( Vertex( -scale, -scale,  scale,  0.0, -1.0,  0.0, 0, 0 ) );
	
	//Face 1
	pMesh->addDrawIndex(0);
	pMesh->addDrawIndex(1);
	pMesh->addDrawIndex(2);
	pMesh->addDrawIndex(3);

	//Face 2
	pMesh->addDrawIndex(4);
	pMesh->addDrawIndex(5);
	pMesh->addDrawIndex(6);
	pMesh->addDrawIndex(7);

	//Face 3
	pMesh->addDrawIndex(8);
	pMesh->addDrawIndex(9);
	pMesh->addDrawIndex(10);
	pMesh->addDrawIndex(11);

	//Face 4
	pMesh->addDrawIndex(12);
	pMesh->addDrawIndex(13);
	pMesh->addDrawIndex(14);
	pMesh->addDrawIndex(15);

	//Face 5
	pMesh->addDrawIndex(16);
	pMesh->addDrawIndex(17);
	pMesh->addDrawIndex(18);
	pMesh->addDrawIndex(19);

	//Face 6
	pMesh->addDrawIndex(20);
	pMesh->addDrawIndex(21);
	pMesh->addDrawIndex(22);
	pMesh->addDrawIndex(23);
	
	return new Box( pMesh );
}

