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
#include "FuSMMachine.h"

using namespace InGE;
/// Construtor
FuSMMachine::FuSMMachine(int type){
	m_type = type;
}


/// Destrutor
FuSMMachine::~FuSMMachine(){
}


/// Atualiza a maquina de estado fuzzy
void FuSMMachine::updateMachine(FuSMStateUpdateInfo &info){
	vector<FuSMState *>		nonActivedStates;
	if(m_states.size() == 0) return;
	
	m_activatedStates.clear();
	for(unsigned int i=0; i<m_states.size(); i++){
		if(m_states[i]->getActivationLevel() > 0.0) 
			m_activatedStates.push_back(m_states[i]);
		else 
			nonActivedStates.push_back(m_states[i]);
	}
	
	for(unsigned int i=0; i<nonActivedStates.size();i++){
		nonActivedStates[i]->exit();
	}
	
	for(unsigned int i=0; i<m_activatedStates.size(); i++){
		m_activatedStates[i]->update(info);
	}
}



/// Adiciona novo estado fuzzy a FuSM
void FuSMMachine::addState(FuSMState *state){
	if(!state) return;
	
	m_states.push_back(state);	
}



/// Verifica se o estado está ativo
bool FuSMMachine::isActive(FuSMState *state){
	if(!state) return false;

	for(unsigned int i=0; i<m_activatedStates.size(); i++){
		if(state == m_activatedStates[i]) return true;
	}
	return false;
}



/// Reinicia a FuSM
void FuSMMachine::reset(){
	for(unsigned int i=0; i<m_states.size(); i++){
		m_states[i]->exit();
		m_states[i]->init();
	}
}

