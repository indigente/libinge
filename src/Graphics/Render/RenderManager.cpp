/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://indigente.dcc.ufba.br

Copyright  2004 Indigente


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

#include "RenderManager.h"
#include "../Toolkit/ToolkitManager.h"
#include <iostream>
#include <CEGUI.h>

#if defined(CEGUI_VERSION_MINOR) && (CEGUI_VERSION_MINOR >= 5)
#include <RendererModules/OpenGLGUIRenderer/openglrenderer.h>
#else
#include <renderers/OpenGLGUIRenderer/openglrenderer.h>
#endif

using namespace std;

namespace InGE{
/**
 * Contrutor padrão
 * @param - Recebe uma camera
 */ 
	
// float ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
// float diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
// float specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
// float position[] = { 400.0f, 60.0f, 500.0f, 1.0f };
// 	
RenderManager::RenderManager(){
	m_pScene = NULL;
	
	CEGUI::OpenGLRenderer * renderer = new CEGUI::OpenGLRenderer (0);
	new CEGUI::System(renderer);

	ToolkitManager::getInstance();
}

RenderManager::~RenderManager(){
}


void RenderManager::addListener(Object3D *listener){
	if ( listener->getBlend() ) {
		m_listBlendingObjects.push_back(listener);
	} else {
		m_listOpaqueObjects.push_front(listener);
	}
}

void RenderManager::rmListener(string& entityID) {	
	list<Object3D*>::iterator itRL;
	bool removed = false;
	for(itRL = m_listOpaqueObjects.begin(); (itRL != m_listOpaqueObjects.end()) && (!removed); ++itRL) {
		if (*itRL){
			if ( (*itRL)->getId() == entityID) {
				m_listOpaqueObjects.erase(itRL);
				removed = true;
			}
		}
	}
	if (!removed){
		for(itRL = m_listBlendingObjects.begin(); (itRL != m_listBlendingObjects.end())  && (!removed); ++itRL) {
			if (*itRL){
				if ( (*itRL)->getId() == entityID) {
					m_listBlendingObjects.erase(itRL);
					removed = true;
				}
			}
		}
	}
}

void RenderManager::addWidget(IWidget *w){
	m_listWidget.push_back(w);
}

void RenderManager::setScene(IScene *scene){
	if(!scene) return ;
	m_pScene = scene;
}

void RenderManager::clear(){
	m_listOpaqueObjects.clear();
	m_listBlendingObjects.clear();
}

void RenderManager::render(ICamera *pCamera){
	Drawer *drawer = Drawer::getInstance();

	if(!pCamera) return;

	// Limpar o Buffer e carrega a matriz identidade
	drawer->clear();
	
	calcDinamicLights();
	
	// Posiciona a camera
	drawer->lookAt( pCamera->getPosition(), pCamera->getViewPoint(), pCamera->getUp());
	
	calcStaticLights();
	
	m_frustum.calculeFrustum();
	
	drawer->enable( InGE_CULL_FACE );
	drawer->cullFace( InGE_BACK );
	drawer->frontFace(InGE_CW);

	
	drawer->enableClientState(InGE_NORMAL_ARRAY);
	drawer->enableClientState(InGE_VERTEX_ARRAY);
	
	//Renderiza o Cen�io.
	if(m_pScene) m_pScene->renderLevel(pCamera->getPosition(), m_frustum);

	
	drawOpaqueObjects();
	drawBlendingObjects();
	
	drawGUI();


	// Troca o Buffer do Double Buffer
	drawer->swapBuffers();
	
}

IScene *RenderManager::pGetScene(){
	return m_pScene;
}

unsigned int RenderManager::getNumOfObject3D(){
	int size = m_listOpaqueObjects.size();
	size += m_listBlendingObjects.size();
	return size;
}

Object3D *RenderManager::pGetObject3D(string& entityID){
	list<Object3D*>::iterator itOb;
	for(itOb = m_listOpaqueObjects.begin(); itOb != m_listOpaqueObjects.end(); ++itOb) {
		if ( (*itOb)->getId() == entityID) {
			return *itOb;
		}
	}
	for(itOb = m_listBlendingObjects.begin(); itOb != m_listBlendingObjects.end(); ++itOb) {
		if ( (*itOb)->getId() == entityID) {
			return *itOb;
		}
	}
	return NULL;
}


void RenderManager::calcDinamicLights(){
}//TODO: Fazer todo o gerenciamento de luzes no motor
	
void RenderManager::calcStaticLights(){//TODO: Fazer todo o gerenciamento de luzes no motor
// 	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
// 	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
// 	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
// 	glLightfv(GL_LIGHT0, GL_POSITION, position);
}
	

void RenderManager::drawOpaqueObjects(){
	Drawer *drawer = Drawer::getInstance();

	// Varre o objetos inscritos para renderizacao
	list<Object3D*>::iterator itOb;
	int i = 0;
	for(itOb = m_listOpaqueObjects.begin();itOb != m_listOpaqueObjects.end(); itOb++){
		if (*itOb){
			Vector3 position = (*itOb)->getPosition();
//			if(m_frustum.isPointInFrustum(position) ){
				glLoadName(i++); //FIXME: Mudar para função em Drawer
				(*itOb)->draw();
				drawer->end();
// 		}
		}
	}
}

void RenderManager::drawBlendingObjects(){
	Drawer *drawer = Drawer::getInstance();
	// Varre o objetos inscritos para renderizacao
	list<Object3D*>::iterator itOb;
	int i = 0;
	for(itOb = m_listBlendingObjects.begin();itOb != m_listBlendingObjects.end(); itOb++){
		if (*itOb){
			Vector3 position = (*itOb)->getPosition();
//			if(m_frustum.isPointInFrustum(position) ){
				glLoadName(i++); //FIXME: Mudar para função em Drawer
				(*itOb)->draw();
				drawer->end();
// 		}
		}
	}
}

void RenderManager::drawGUI(){
	static double oldTicks = 0.001 * SDL_GetTicks();

	double ticks = 0.001 * SDL_GetTicks();
	CEGUI::System::getSingleton().injectTimePulse(static_cast<float>(ticks - oldTicks));
	oldTicks = ticks;

	Drawer *drawer = Drawer::getInstance();

	/* Old GUI Code */
        drawer->disable(GL_CULL_FACE);

        drawer->matrixMode(GL_MODELVIEW);
        drawer->pushMatrix();
        drawer->loadIdentity();

        drawer->matrixMode(GL_PROJECTION);
        drawer->pushMatrix();
        drawer->loadIdentity();
        SDL_Surface *surface = SDL_GetVideoSurface();
        int w = surface->w;
        int h = surface->h;

        float pos[] = { w/2, h/2, 600.0f, 0.0f };//FIXME: Armengue pra iluminação da GUI
        glLightfv(GL_LIGHT0, GL_POSITION, pos);//FIXME: Armengue pra iluminação da GUI

        drawer->ortho(0,w,h,0,0,1);

        list<IWidget*>::iterator itWdg;
        for(itWdg = m_listWidget.begin(); itWdg != m_listWidget.end(); ++itWdg) {
                (*itWdg)->draw(0, 0, w, h);
        }

        drawer->matrixMode(GL_PROJECTION);
        drawer->popMatrix();
        drawer->matrixMode(GL_MODELVIEW);
        drawer->popMatrix();
	/* end of Old Gui Code */

	drawer->pushAttrib(InGE_ENABLE_BIT);
	drawer->disable(InGE_CULL_FACE);
	CEGUI::System::getSingleton().renderGUI();
	drawer->popAttrib();
}

void RenderManager::rmWidget(string& name){
	list<IWidget*>::iterator itWdg;
	for(itWdg = m_listWidget.begin(); itWdg != m_listWidget.end(); ++itWdg) {
		if ((*itWdg)->getName() == name){
			m_listWidget.erase(itWdg);
			return;
		}
	}
}

unsigned int RenderManager::getNumOfWidget(){
	return m_listWidget.size();
}

IWidget *RenderManager::pGetWidget(string& widgetName){
	list<IWidget*>::iterator itWdg;
	for(itWdg = m_listWidget.begin(); itWdg != m_listWidget.end(); ++itWdg) {
		if ((*itWdg)->getName() == widgetName){
			return (*itWdg);
		}
	}
}

}
