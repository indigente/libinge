/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://twiki.im.ufba.br/bin/view/Indigente

Copyright © 2004-2005 Indigente


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
#ifndef MSGTYPEENUM_H_
#define MSGTYPEENUM_H_


namespace InGE{

	enum MsgTypeEnum{ 
		/*
		  eh necessario definir os tipos de mensagens que podem existir.
		  tendo conhecimento de cada um dos padroes de mensagens, ao ser chamado
		  o LogManager, basta informar: tipo de mensagem e parametros. o LogManager
		  se encarregará de formatar a mensagem (inclusive sendo capaz de selecionar
		  o idioma no qual a mesma sera exibida)
		*/
		
		/* Error Messages */
		InGE_MSG_ERROR_bli0=0,
		InGE_MSG_ERROR_bli2,
		/* Info Messages */
		InGE_MSG_LOADING_bli1,
		InGE_MSG_ETC_bli2
	};

};

#endif /*MSGTYPEENUM_H_*/
