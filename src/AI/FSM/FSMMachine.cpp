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
#include "FSMMachine.h"

using namespace InGE;

///Construtor
FSMMachine::FSMMachine(int type){
	m_type = type;
}

/// Destrutor
FSMMachine::~FSMMachine(){
}

/// Metodo que atualiza a FSM
void FSMMachine::updateMachine(const FSMStateUpdateInfo &info){
	if(m_states.size() == 0) return ;
	
	if(!m_currentState) m_currentState = m_defaultState;
	if(!m_currentState) return;
	
	m_goalId = m_currentState->checkTransitions();
	
	if((m_goalId != m_currentState->getType()) && hasTransitionState(m_goalId)){
		m_currentState->exit();
		m_currentState = m_goalState;
		m_currentState->enter();
	}
	m_currentState->update(info);
}


/// Metodo que adciona estado na FSM
void FSMMachine::addState(FSMState *state){
	if(!state) return;
	
	m_states.push_back(state);
}


/// Metodo que define o estado padrao
void FSMMachine::setDefaultState(FSMState *state){
	if(!state) return;
	m_defaultState = state;
}


/// Metodo que define o identificado do estado objetivo
void FSMMachine::setGoalId(int goalId){
	m_goalId = goalId;
}


/// Metodo que verifica a existencia de transicao para o estado objetivo
bool FSMMachine::hasTransitionState(int goalId){
	if(m_states.size() == 0) return false;
	
	for(unsigned int i; i<m_states.size(); i++){
		if(m_states[i]->getType() == goalId){
			m_goalState = m_states[i];
			return true;
		}
	}
	return false;
}


/// Metodo que reincializa a FSM
void FSMMachine::reset(){
	this->exit();
	
	if(m_currentState) m_currentState->exit();
	
	for(unsigned int i=0; i<m_states.size(); i++)
		m_states[i]->init();
	
	if(m_currentState) m_currentState->enter();
}
