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

#ifndef BITSET_H
#define BITSET_H

namespace InGE{
	typedef unsigned int DWord;

	/**
	 * Array de Bits
	 * @author Ivan Medeiros Monteiro
	 */
	class BitSet{
	  private:
		DWord *bitArray;
		unsigned int size;


	  public:
	
		BitSet();
		~BitSet();
		
		const bool operator[](const unsigned int i);


		void set(const unsigned int i);
		void unset(const unsigned int i);
		void resize(const unsigned int n);
		void clearAll();
	};


};
#endif // BITSET_H

