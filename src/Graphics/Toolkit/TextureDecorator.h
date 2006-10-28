/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright  2004-2006 Indigente


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
#ifndef TEXTUREDECORATOR_H_
#define TEXTUREDECORATOR_H_

#include <string>
#include "IWidget.h"
#include "../Base/MaterialInfo.h"
#include "../Model/IModel.h"
#include "../Base/Mesh.h"

using std::string;

namespace InGE{

class TextureDecorator : public InGE::IWidget
{
protected:
	IWidget 			*m_widget;
	MaterialInfo 	*m_matInfo;
	Mesh 				*m_pMesh;

public:
	TextureDecorator(const string &filename, IWidget *w);
	virtual ~TextureDecorator();
	virtual void draw(float x, float y, float width, float height);
	
	void setWidget(IWidget *w);
// 	void setTexture(float textureID);
	virtual void move(float x, float y);
	virtual void resize(float width, float height);
};

};

#endif /*TEXTUREDECORATOR_H_*/
