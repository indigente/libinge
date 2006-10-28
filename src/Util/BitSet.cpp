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

#include "BitSet.h"
#include <cstring>

using namespace InGE;

/**
 * Construtor
 */
BitSet::BitSet(){
	bitArray = new DWord[1];
	size = 1;
}

/**
 * Destrutor
 */
BitSet::~BitSet(){
		delete [] bitArray;
}

/**
 * Retorna o estado do bit indexado.
 * @param i - Índice do array de bits
 */
const bool BitSet::operator[](const unsigned int i){
	if( (i>>5) >= size  ) 
		return false;
		
	return bitArray[i >> 5] & (1  << (i & 31) );
}

// Ajusta o tamanho do array de bits
void BitSet::resize(const unsigned int n){
	unsigned int newSize = n >> 5;
	DWord *newBitArray = new DWord[newSize+1];
	
	if(bitArray){
		memcpy(newBitArray, bitArray, size << 2);
		delete [] bitArray;
	}

	size = newSize;
	bitArray = newBitArray;
}


/**
 * Define o bit indexado como ativo.
 * Redimenciona o tamanho do array de bits caso necessário
 * @param i -Índice do array de bits
 */
void BitSet::set(const unsigned int i){
	if((i>>5) >= size){
		this->resize(i);
	}

	bitArray[i>>5] |= (1<<(i & 31));
}

/**
 * Define o bit indexado como inativo.
 * Redimenciona o tamanho do array de bits caso necessário
 * @param i - Índice do array de bits
 */
void BitSet::unset(const unsigned int i){
	if((i>>5) >= size){
		this->resize(i);
	}

	bitArray[i>>5] &= ~(1<<(i & 31));
}


/***
 * Limpa toda a estrutura de vetor de bits 
 */
 void BitSet::clearAll(){
 	memset(bitArray, 0, sizeof(DWord)*size );
 }
