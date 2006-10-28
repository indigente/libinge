/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

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

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include "../Camera/ICamera.h"
#include "../World/IScene.h"
#include "../Toolkit/Window.h"
#include "../../Entities/Object3D.h"
#include "Frustum.h"




#include "Drawer.h"

#include <list>


namespace InGE{

	using std::list;
	using namespace InGE;

class RenderManager{
	private:
		Frustum		m_frustum;
		IScene		*m_pScene;
		list<Object3D *>	m_listOpaqueObjects;
		list<Object3D *>	m_listBlendingObjects;
		list<IWidget *>	m_listWidget;
		
		void calcDinamicLights();
		void calcStaticLights();
		
		void drawOpaqueObjects();
		void drawBlendingObjects();
		void drawGUI();
		
	public:
		RenderManager( );
		virtual ~RenderManager();
			
		void setCamera();
		
		void clear();
		
		void addListener(Object3D *listener);
		void addWidget(IWidget *w);
		void setScene(IScene *scene);
		
		void rmListener(string& listenerId);
		void rmWidget(string& name);
		
		IScene *pGetScene();
		
		unsigned int getNumOfObject3D();
		Object3D *pGetObject3D(string& listenerId);
		unsigned int getNumOfWidget();
		IWidget *pGetWidget(string& widgetName);
		
		void render(ICamera *camera);
	};

};
#endif // RENDERMANAGER_H
