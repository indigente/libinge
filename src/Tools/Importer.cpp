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
daeString COLLADA_VERSION = "1.4";
using namespace 
std;

int main( ){
	DAE *daeObject = new DAE;
	daeInt error;
	
	error = daeObject->load( "/home/nkbeto/Desktop/champignon.dae" );
	if ( error == DAE_OK ){
	cout << "Sucesso no load" << endl;
	} else {
	cout << "Falha no load" << endl;
	}
	
	cout << "Versão = " <<  daeObject->getDomVersion() << endl;
	daeDatabase* database = daeObject->getDatabase();
	cout << "N. Coleções = " << database->getCollectionCount() << endl;
	cout << "N. Documentos = " << database->getDocumentCount() << endl;
	
	/*int max = database->getTypeCount();
	cout << "N. Tipo = " << max << endl;
	for (int i = 0; i < max; i++){
		cout << "Nome do tipo " << i << " é "<< database->getTypeName( i ) << endl;
	}*/
	
	int elemNum = database->getElementCount(NULL, COLLADA_ELEMENT_GEOMETRY, NULL);
	cout << "N. Elemento = " << elemNum << endl;
	daeElement *pElement;
	for (int i = 0; i < elemNum; i++){
		database->getElement( (daeElement**)&pElement, i, NULL, COLLADA_ELEMENT_GEOMETRY, NULL );
 		cout << "ID do Elemento " << i << " é " << pElement->getID() << endl;
		
		daeMemoryRef mem = pElement->getAttributeValue( "float_array" );
		
		
	}
	//dae database->getCollection( 0 );
	
	error = daeObject->saveAs( "teste.xml", "file:///home/nkbeto/Desktop/teste.xml");
	if ( error == DAE_OK ){
	cout << "Sucesso no save" << endl;
	} else {
	cout << "Falha no save" << endl;
	}
}
