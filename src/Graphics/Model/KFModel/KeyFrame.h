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

#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <vector>
#include <string>

#include "../../Base/Mesh.h"
#include "../../Base/MeshDecorator/ConcreteMesh.h"
#include "Md3/Tag.h"

namespace InGE{
using std::vector;
using std::string;

	class KeyFrame{
		private:
			string		m_name;
			vector<Tag *>	m_vetTag;
			vector<Mesh *>	m_vetMesh;
			vector<bool >	m_vetDrawFlag;
			VolumeInfo	m_volumeInfo;
			
		public:

		KeyFrame();
		~KeyFrame();
	
		void setName(string name);

		void addTag(Tag *pTag);
		void addMesh(Mesh *mesh);	
		void setVolumeInfo(sBoundVolume &boundVolume);
		void setVolumeInfo(VolumeInfo volumeInfo);

		string				getName();
		unsigned int		getNumMesh();
		unsigned int		getNumTag();
		bool					getMeshDrawFlag(int index);
		Tag					*pGetTag(int index);
		Mesh					*getMesh(int index);
		VolumeInfo			*pGetVolumeInfo();

		KeyFrame *interpolate(KeyFrame *nextFrame, float interpolationToNextFrame);
		
	};
	
};
#endif // KEYFRAME_H
