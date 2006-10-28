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
#ifndef FSMMACHINE_H
#define FSMMACHINE_H
#include "FSMState.h"
#include <vector>

using std::vector;

namespace InGE{
	/**
	 * Classe FSMMachine
	 * Implementa um maquina de estato finito
	 * 
	 * @author Ivan Medeiros Monteiro
	 */
	class FSMMachine : public InGE::FSMState{
		protected: 
			/// Conjunto de estados da FSM
			vector<FSMState *>	m_states;
			/// Estado atual
			FSMState			*m_currentState;
			/// Estado padrao
			FSMState			*m_defaultState;
			/// Estado objetivo
			FSMState			*m_goalState;
			/// Identificado do estado alvo
			int					m_goalId;
			
			
		public:
			/// Construtor
			FSMMachine(int type=0);
			/// Destrutor
			virtual ~FSMMachine();
			
			/// Metodo que atualiza a FSM
			virtual void updateMachine(const FSMStateUpdateInfo &info);
			/// Metodo que adciona estado na FSM
			virtual void addState(FSMState *state);
			/// Metodo que define o estado padrao
			virtual void setDefaultState(FSMState *state);
			/// Metodo que define o identificado do estado objetivo
			virtual void setGoalId(int goalId);
			/// Metodo que verifica a existencia de transicao para o estado objetivo
			virtual bool hasTransitionState(int goalId);
			/// Metodo que reincializa a FSM
			virtual void reset();
			
	};

};
#endif // FSMMACHINE_H
