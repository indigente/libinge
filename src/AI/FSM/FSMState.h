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
#ifndef FSMSTATE_H
#define FSMSTATE_H

namespace InGE{

	class FSMStateUpdateInfo{};
	
	/**
	 * Classe FSMState
	 * Fornece uma inteface para implementacao de estados numa FSM
	 * Finite-State Machine
	 * 
	 * @author Ivan Medeiros Monteiro
	 */
	 class FSMState{
		protected:
			/// Tipo identificador do estado
			int m_type;
		public:
			/// Construtor
			FSMState(int type=0) {m_type = type;}
			/// Destrutor
			virtual ~FSMState() {}
			
			/// Metodo a ser executado ao entrar no estado
			virtual void enter(){}
			/// Metodo a ser executado ao sair do estado
			virtual void exit(){}
			/// Metodo chamado pelo laco de processamento
			virtual void update(const FSMStateUpdateInfo &info){}
			/// Metodo que reinicia o estado
			virtual void init(){}
			/// Metodo verifica condicao de mudanca de estado
			virtual int checkTransitions(){return 0;}
			/// Metodo que define o identificador de tipo do estado
			virtual void setType(int t){m_type = t;}
			/// Metodo que retorna o identificador de tipo do estado
			virtual int getType(){return m_type;}
			
	};

};
#endif // FSMSTATE_H
