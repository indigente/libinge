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


#include "Importer.h"
using namespace std;
using namespace InGE;

InGE::Importer::Importer(string filename){
	m_pDaeObject = new DAE;
	daeInt error;
	
	error = m_pDaeObject->load( filename.c_str() );
	
	if ( error == DAE_OK ){
		cout << "Sucesso no load" << endl;
	} else {
		cout << "Falha no load" << endl;
	}
	
	m_pDaeDatabase = m_pDaeObject->getDatabase();
	
}

int InGE::Importer::getNumElem(daeString type){
		if (m_pDaeDatabase){
		return m_pDaeDatabase->getElementCount(NULL, type, NULL);
	} else {
		return 0;
	}
}

int InGE::Importer::getNumElem(daeString name, daeString type, daeString file){
	if (m_pDaeDatabase){
		return m_pDaeDatabase->getElementCount(name, type, file);
	} else {
		return 0;
	}
}

bool InGE::Importer::importModel(daeString type){
// 	int elemNum = getNumElem(NULL, COLLADA_ELEMENT_GEOMETRY, NULL);
	int elemNum = getNumElem(type);

	daeElement *pElement;
	for (int i = 0; i < elemNum; i++){
		m_pDaeDatabase->getElement( (daeElement**)&pElement, i, NULL, COLLADA_ELEMENT_GEOMETRY, NULL );
		domGeometry *pGeom = NULL;
		pGeom = (domGeometry *)pElement;
		if (pGeom) {
// 			loadGeom(pGeom);
			domMesh *pMesh = NULL;
			pMesh = pGeom->getMesh();
		
			if(pMesh){
				loadMesh(pMesh);
			}
		}
	}
}

domSource *InGE::Importer::findSource(domMesh *pMesh, string id){
	domSource_Array sourceArray = pMesh->getSource_array();
	int count = sourceArray.getCount();
	for(int i = 0; i < count; i++){
		string sourceID =  sourceArray[i]->getId();
		if ( sourceID == id ) {
// 			cout << sourceID << " == " << id << endl;
			return sourceArray[i];
		} else {
			cout << "Num achei " << endl;
		}
	}
	return NULL;
}

/**
 * This method loads the one mesh from the COLLADA_DOM into the Class Mesh of InGE.
 * @param pMesh Pointer to mesh in COLLADA_DOM
 */
void InGE::Importer::loadMesh(domMesh *pMesh){
 	cout << pMesh->getID() << endl;
	domVertices *pVertices = pMesh->getVertices();
	domSource *pSource = NULL;
//	vector<Vector3 > position;
//	vector<Vector3 > normal;
//	vector<Vector2 > texCoord;
//	vector<Vector2 > index;
	
	if (pVertices) {
		domInputLocal_Array inputArray = pVertices->getInput_array();
		int inputCount =  inputArray.getCount();
		
		for(int i = 0; i < inputCount; i++){
			if ( !strcmp( inputArray[i]->getSemantic(), "POSITION" ) ) {
 				pSource = findSource(pMesh, inputArray[i]->getSource().getID());
//  				position = loadFloatArrayStride3(pSource);
				
			} else if ( !strcmp( inputArray[i]->getSemantic(), "NORMAL" ) ) {
				pSource = findSource(pMesh, inputArray[i]->getSource().getID());
//  				normal = loadFloatArrayStride3(pSource);
			}
		}
	}
	domTriangles *pTriangles = pMesh->getTriangles_array()[0];
	if (pTriangles){
		domInputLocalOffset_Array inputArray = pTriangles->getInput_array();
		int inputCount =  inputArray.getCount();
		
		for(int i = 0; i < inputCount; i++){
			cout << inputArray[i]->getSemantic() << endl;
			 if ( !strcmp( inputArray[i]->getSemantic(), "TEXCOORD" ) ) {
				 pSource = findSource(pMesh, inputArray[i]->getSource().getID());
// 				 texCoord = loadFloatArrayStride2(pSource);
			 }
		}
		
		domP *pP = pTriangles->getP();
// 		pP->get
	}
}

bool InGE::Importer::saveCOLLADA(string filename, string filedir){
	daeInt error;
	error = m_pDaeObject->saveAs(filename.c_str(), filedir.c_str());
	if ( error == DAE_OK ){
		cout << "Sucesso no save" << endl;
	} else {
		cout << "Falha no save" << endl;
	}

}

int main( ){
	Importer *importer = new Importer( "/home/nkbeto/Desktop/champignon.dae" );

	importer->importModel(COLLADA_ELEMENT_GEOMETRY);
	importer->saveCOLLADA( "teste.xml", "file:///home/nkbeto/Desktop/teste.xml");
		
}
