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

#ifndef MATERIALINFO_H
#define MATERIALINFO_H

#include <string>
#include "../Render/Drawer.h"
#include "../../Math/Vector4.h"

namespace InGE{
	using std::string;

	/**
	 * Classe MaterialInfo 
	 * Mant� informa�es sobre materiais, 
	 * principalmente texturas
	 * @author Ivan Medeiros Monteiro
	 */
	class MaterialInfo{
	  private:
		string m_name;					// Nome da Textura
		string m_filename;				// Arquivo da Textura
		bool m_alpha;
		bool m_emissive;
		Vector4 m_color;				// Cor do objeto
		
		EnumDrawer m_face;
		Vector4 m_specular;
		int m_shininess;
		Vector4 m_emissiveColor;
		
		unsigned int m_textureId;	// Identificador de Textura
		
		float m_uTile;					// u tiling of texture  (Currently not used)
		float m_vTile;					// v tiling of texture  (Currently not used)
		float m_uOffset;				// u offset of texture  (Currently not used)
		float m_vOffset;				// v offset of texture  (Currently not used)
	  	
	  public:
	
		MaterialInfo();
		virtual ~MaterialInfo();

		//Metodos Set		
		void setTexture(string filename);
		void setId(int i);
		void setFace(const EnumDrawer& theValue);
		void setColor(const Vector4& theValue);
		void setSpecular(const Vector4& theValue);
		void setShininess(const int& theValue);
		void setEmissive(bool theValue);
		
		//Metodos Get		
		string getFileName();
		int getId();
		bool getBlend();
		EnumDrawer getFace() const;
		Vector4 getColor() const;
		Vector4 getSpecular() const;
		int getShininess() const;
		bool getEmissive() const;
	
	
		void apply(EnumDrawer textureChannel);

	
	

	
	
	
	
	
	};

}
#endif // MATERIALINFO_H
