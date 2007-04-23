/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://indigente.dcc.ufba.br

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
daeString COLLADA_VERSION = "1.4.1";
using namespace std;

// vector<Vector3 > &loadFloatArrayStride3(){
// 
// }

domSource *findSource(domMesh *pMesh, string id){
	domSource_Array sourceArray = pMesh->getSource_array();
	int count = sourceArray.getCount();
	for(int i = 0; i < count; i++){
		string sourceID =  sourceArray[i]->getId();
		if ( sourceID == id ) {
			cout << sourceID << " == " << id << endl;
			return sourceArray[i];
		} else {
			cout << "Num achei " << endl;
		}
 		
	}
	return NULL;
}

void loadMesh(domMesh *pMesh){
// 	cout << pMesh->getID() << endl;
	domVertices *pVertices = pMesh->getVertices();
	domSource *pSource = NULL;
// 	vector<Vector3 > position;
// 	vector<Vector3 > normal;
// 	vector<Vector2 > texCoord;
// 	vector<Vector2 > index;
	
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

int main( ){
	DAE *daeObject = new DAE;
	daeInt error;
	
	error = daeObject->load( "/home/nkbeto/Desktop/champignon.dae" );
	if ( error == DAE_OK ){
		cout << "Sucesso no load" << endl;
	} else {
		cout << "Falha no load" << endl;
	}
	
	daeDatabase* database = daeObject->getDatabase();
	
	int elemNum = database->getElementCount(NULL, COLLADA_ELEMENT_GEOMETRY, NULL);
	daeElement *pElement;
	for (int i = 0; i < elemNum; i++){
		database->getElement( (daeElement**)&pElement, i, NULL, COLLADA_ELEMENT_GEOMETRY, NULL );
		domGeometry *pGeom = NULL;
		pGeom = (domGeometry *)pElement;
		if (pGeom) {
			domMesh *pMesh = NULL;
			pMesh = pGeom->getMesh();
		
			if(pMesh){
				loadMesh(pMesh);
			}
		}
/*		daeElementRefArray children;
		pElement->getChildren( children );
		int childrenNum = children.getCount();
		
		for ( int i = 0; i < childrenNum; i++ ) {
			if ( !strcmp( children[i]->getTypeName(), "mesh" ) ) {
				loadMesh(children[i]);
			}
		}*/
	}
	//dae database->getCollection( 0 );
	
	error = daeObject->saveAs( "teste.xml", "file:///home/nkbeto/Desktop/teste.xml");
	if ( error == DAE_OK ){
		cout << "Sucesso no save" << endl;
	} else {
		cout << "Falha no save" << endl;
	}
}
