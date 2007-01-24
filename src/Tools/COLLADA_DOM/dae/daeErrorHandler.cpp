/*
 * Copyright 2006 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */

#include <dae/daeErrorHandler.h>
#include <modules/stdErrPlugin/stdErrPlugin.h>

daeErrorHandler *daeErrorHandler::_instance = NULL;
daeBool daeErrorHandler::_default = false;

daeErrorHandler::daeErrorHandler() {
}

daeErrorHandler::~daeErrorHandler() {
	if (_instance != NULL && _default ) {
		delete _instance;
		_instance = 0;
	}
}

void daeErrorHandler::setErrorHandler( daeErrorHandler *eh ) {
	if ( _instance != NULL && _default ) {
		delete _instance;
	}
	_instance = eh;
}

daeErrorHandler *daeErrorHandler::get() {
	if ( _instance == NULL ) {
		_instance = new stdErrPlugin();
		_default = true;
	}
	return _instance;
}
