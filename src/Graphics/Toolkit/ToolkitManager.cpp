#include "ToolkitManager.h"
#include <CEGUI.h>
#include <CEGUIDefaultResourceProvider.h>

using namespace InGE;

ToolkitManager *ToolkitManager::m_instance = 0;

ToolkitManager::ToolkitManager() {
	setResourcesDirectory("gui");
}

ToolkitManager *ToolkitManager::getInstance() {
	if (!m_instance)
		m_instance = new ToolkitManager();
	return m_instance;
}

void ToolkitManager::setResourcesDirectory(char *dir) {
	char buf[256];

	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
	
	sprintf(buf, "%s/schemes/", dir);
	rp->setResourceGroupDirectory("schemes", buf);
	sprintf(buf, "%s/imagesets/", dir);
	rp->setResourceGroupDirectory("imagesets", buf);
	sprintf(buf, "%s/fonts/", dir);
	rp->setResourceGroupDirectory("fonts", buf);
	sprintf(buf, "%s/layouts/", dir);
	rp->setResourceGroupDirectory("layouts", buf);
	sprintf(buf, "%s/looknfeel/", dir);
	rp->setResourceGroupDirectory("looknfeels", buf);
	sprintf(buf, "%s/lua_scripts/", dir);
	rp->setResourceGroupDirectory("lua_scripts", buf);
	#ifdef CEGUI_WITH_XERCES
	sprintf(buf, "%s/XMLRefSchema/", dir);
	rp->setResourceGroupDirectory("schemas", buf);
	#endif
	
	CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	#ifdef CEGUI_WITH_XERCES
	CEGUI::XercesParser::setSchemaDefaultResourceGroup("schemas");
	#endif
}


