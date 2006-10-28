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
#ifndef FUSMSTATE_H
#define FUSMSTATE_H


namespace InGE{


	class FuSMStateUpdateInfo{};
	
	/**
	 * Classe de FuSMState
	 * Fornece uma interface para implementar de estados numa FuSM
	 * FuSM - Fuzzy-State Machine
	 * 
	 * @author Ivan Medeiros Monteiro
	 */
	class FuSMState{
		protected:
			int		m_type;
			float 	m_activationLevel;
		public:
			///Construtor
			FuSMState(int type=0) {m_type = type; m_activationLevel = 0.0f;}
			///Destrutor
			virtual ~FuSMState() {}
			
			/// Metodo executado enquanto o estado está ativo
			virtual void update(FuSMStateUpdateInfo &info){}
			/// Metodo executado no instante que entra no estado
			virtual void enter(){}
			/// Metodo executado no instante que se sai do estado
			virtual void exit(){}
			/// Metodo que reinicializa o estado
			virtual void init(){m_activationLevel = 0.0f;}
			/// Metodo que define o identificador de tipo do estado
			virtual void setType(int t){m_type = t;}
			/// Metodo que retorna o identificador de tipo do estado
			virtual int getType(){return m_type;}		
			/// Retorno o nivel do ativacao
			virtual float getActivationLevel() { return m_activationLevel;} 
			/// Define o nivel de ativacao
			virtual void setActivationLevel(float l){ m_activationLevel = l;}
	};
	
};
#endif // FUSMSTATE_H

