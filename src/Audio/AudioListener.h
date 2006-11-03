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

#ifndef AUDIOLISTENER_H
#define AUDIOLISTENER_H

#include "../Math/Vector3.h"
#include "../Entities/IEntity.h"
//#include "AudioManager.h"

namespace InGE{

class AudioManager;

class AudioListener : public InGE::IEntity {
protected:
	AudioListener();
	
public:
	friend class InGE::AudioManager;

	virtual ~AudioListener();

	virtual void setGain(float gain);
	virtual float getGain();
	
	/* Estes metodos agora sao herdados de IEntity */
	virtual void setVelocity(const Vector3 &velocity);
	virtual Vector3 getVelocity();
	virtual void setPosition(const Vector3 &position);
	virtual Vector3 getPosition();
	virtual void setDirection(const Vector3 &orientation);
	virtual Vector3 getDirection();
	/* */
	virtual TiXmlElement	*entity2xml();
};

};

#endif // AUDIOLISTENER_H
