/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright � 2004 Indigente


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

#include "VolumeShadowManager.h"

using namespace InGE;
using namespace InGE;

VolumeShadowManager::VolumeShadowManager(){
	m_infinity = 100;
}

VolumeShadowManager::~VolumeShadowManager(){
}

void VolumeShadowManager::addShadowedModel(IModel *shadowedModel){
	m_vetShadowedModel.push_back(shadowedModel);
	setConnectivity(shadowedModel);
	calculatePlane(shadowedModel);
}
void VolumeShadowManager::addShadowEmiter(Vector4 *lightPos){
	m_vetShadowEmiter.push_back(lightPos);
}


void VolumeShadowManager::setConnectivity(IModel *shadowedModel){
//	shadowedModel->setConnectivity();
}

void VolumeShadowManager::calculatePlane(IModel *shadowedModel){
//	shadowedModel->calculatePlane();
}

void VolumeShadowManager::draw(){
	Drawer *drawer = Drawer::getInstance();
	for (unsigned int emiterIndex = 0; emiterIndex < m_vetShadowEmiter.size(); emiterIndex++){
		for (unsigned int modelIndex = 0; modelIndex < m_vetShadowedModel.size(); modelIndex++){
/*
		 	drawer->disable(InGE_LIGHTING);
			drawer->depthMask(GL_FALSE);
			drawer->depthFunc(InGE_LEQUAL);
		
			drawer->enable(InGE_STENCIL_TEST);
			drawer->colorMask(0, 0, 0, 0);
			drawer->stencilFunc(InGE_ALWAYS, 1, 0xffffffff);
		
			drawer->frontFace(InGE_CCW);
			drawer->stencilOp(InGE_KEEP, InGE_KEEP, InGE_INCR);
			
			m_vetShadowedModel[modelIndex]->castVolumeShadow(m_vetShadowEmiter[emiterIndex], m_infinity);

			drawer->frontFace(InGE_CW);
			drawer->stencilOp(InGE_KEEP, InGE_KEEP, InGE_DECR);

			m_vetShadowedModel[modelIndex]->castVolumeShadow(m_vetShadowEmiter[emiterIndex], m_infinity);

			drawer->frontFace(InGE_CCW);
			drawer->colorMask(1, 1, 1, 1);
		
			drawer->color(0.0f, 0.0f, 0.0f, 0.4f);
			drawer->enable(InGE_BLEND);
			drawer->blendFunc(InGE_SRC_ALPHA, InGE_ONE_MINUS_SRC_ALPHA);
			drawer->stencilFunc(InGE_NOTEQUAL, 0, 0xffffffff);
			drawer->stencilOp(InGE_KEEP, InGE_KEEP, InGE_KEEP);
			drawer->pushMatrix();
			drawer->loadIdentity();
			drawer->begin(InGE_TRIANGLE_STRIP);
				drawer->vertex(-0.1f, 0.1f,-0.10f);
				drawer->vertex(-0.1f,-0.1f,-0.10f);
				drawer->vertex( 0.1f, 0.1f,-0.10f);
				drawer->vertex( 0.1f,-0.1f,-0.10f);
			drawer->end();
			drawer->popMatrix();
			drawer->disable(InGE_BLEND);
		
			drawer->depthFunc(InGE_LEQUAL);
			drawer->depthMask(InGE_TRUE);
			drawer->enable(InGE_LIGHTING);
			drawer->disable(InGE_STENCIL_TEST);
			drawer->shadeModel(InGE_SMOOTH);*/
		}
	}
}
