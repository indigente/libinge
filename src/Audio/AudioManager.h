/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://indigente.dcc.ufba.br

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

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "AudioSource.h"
#include "AudioBuffer.h"
#include "AudioListener.h"
#include <vector>

using namespace std;
namespace InGE{

class AudioManager {
private:
	AudioListener *listener;
	vector<AudioSource *> streamingSources;

protected:
	AudioManager();

public:
	static AudioManager *instance;

	virtual ~AudioManager();

	/**
	 * Throws an exception if an error occurred since the last alGetError() call.
	 */
	static void checkALError();
	/**
	 * Throws an exception if an error occurred since the last alutGetError() call.
	 */
	static void checkALUTError();

	static AudioManager *getInstance();
	virtual void init();
	virtual AudioSource *createSource();
	virtual AudioBuffer *createBuffer();
	virtual AudioListener *getListener();

	// streaming
	virtual void update();
// 	virtual void addSource(AudioSource *audioSource);
	virtual void addStreamingSource(AudioSource *source);
};

}
#endif // AUDIOMANAGER_H
