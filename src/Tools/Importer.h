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
/**
	@author Humberto Bandeira <nkbeto@gmail.com>
*/
#include <iostream>
#include <string>

//The main includes for the COLLADA DOM.
#include <dae.h>
//This include will import all the elements that we will need except the effect 
//elements.
#include <dom/domCOLLADA.h>
//This include will import all of the elements needed for profile_COMMON 
//effects.
#include <dom/domProfile_COMMON.h>
//This include imports a bunch of useful constant strings for types and element 
//names.
#include <dom/domConstants.h>

const daeString documentName	= "sampleCube.dae";
const daeString geometryID		= "cube";
const daeString materialID		= "texture_material";
const daeString materialSymbol	= "material";
const daeString imageID			= "texture-image";
const daeString effectID		= "simple_texture-fx";
const daeString texCoordSymbol	= "UVSET0";
const daeString visual_sceneID  = "default_scene";
