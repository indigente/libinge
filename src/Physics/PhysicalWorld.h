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
#ifndef PHYSICALWORLD_H
#define PHYSICALWORLD_H
#include "../Math/Vector3.h"
#include <ode/ode.h>



namespace InGE{
	

	class PhysicalWorld{
		private:
			dWorldID	m_worldId;
			
		public:

			PhysicalWorld();
			~PhysicalWorld();
			
			// Ajusta gravidade no mundo fisico
			void setGravity(const Vector3 &v);
			// Retorna a gravidade do mundo fisico
			Vector3 getGravity();

			// Controle de correcao de erros
			void  setERP(float erp);
			float getERP();
			void  setCFM(float cfm);
			float getCFM();
			
			// Set e Get para o padrao dos parametros a criacao de novos corpos
			void  setAutoDisableFlag(int autoDisable);
			int   getAutoDisableFlag();
			void  setAutoDisableLinearThreshold(float linearThreshold);
			float getAutoDisableLinearThreshold();
			void  setAutoDisableAngularThreshold(float angularThreshold);
			float getAutoDisableAngularThreshold();
			void  setAutoDisableSteps(int steps);
			int   getAutoDisableSteps();
			void  setAutoDisableTime(float time);
			float getAutoDisableTime();
			
			void setAutoEnableDepthSF1(int autoEnableDepth);
			int  getAutoEnableDepthSF1();
			
			// converter impulso em forca 
			Vector3 impulseToForce(int stepSize, Vector3 impulse);
			
			void  step(float stepSize);
			void  quickStep(float stepSize);
			void  stepFast1(float stepSize, int maxIterations);

			void  setQuickStepNumIterations(int num);
			int   getQuickStepNumIterations();
			void  setContactMaxCorrectingVel(float vel);
			float getContactMaxCorrectingVel();
			void  setContactSurfaceLayer(float depth);
			float getContactSurfaceLayer();
			
			dWorldID getId();
			
		
	};

};
#endif // PHYSICALWORLD_H
