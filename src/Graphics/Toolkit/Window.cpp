#include "Window.h"

using namespace InGE;

Window::Window(float x, float y, float width, float height){
	m_x = x;
	m_y = y;
	m_w = width;
	m_h = height;
}

Window::~Window(){
	for(list<IWidget*>::iterator it = m_widgets.begin(); it != m_widgets.end(); ++it){
		delete *it; //FIXME: deletar aqui mesmo?
	}
}

void Window::add(IWidget *w){
	m_widgets.push_back(w);
}

void Window::draw(float x, float y, float width, float height){
	float _x, _y;

	_x = m_x >= 0 ? x + m_x : (x+width) - m_w + m_x;
	_y = m_y >= 0 ? y + m_y : (y+height) - m_h + m_y;

	for(list<IWidget*>::iterator it = m_widgets.begin(); it != m_widgets.end(); ++it){
		(*it)->draw(_x, _y, m_w, m_h);
	}
}
