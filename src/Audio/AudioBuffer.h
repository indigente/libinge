/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004-2006 Indigente


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

#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <AL/al.h>

namespace InGE{

class AudioManager;
class AudioSource;

class AudioBuffer{
private:
	ALuint number;
	ALuint getNumber() const { return number; } // Especifico para OpenAL

protected:
	AudioBuffer();

public:
	friend class InGE::AudioManager;
	friend class InGE::AudioSource;

	virtual ~AudioBuffer();
	virtual void setData(void *data);
	virtual void loadFile(char *filename);
	virtual unsigned int getFrequency();
	virtual unsigned int getBitDepth();
	virtual unsigned int getChannels();
	virtual unsigned int getSize();
};

};

#endif // AUDIOBUFFER_H
