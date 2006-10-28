// #ifndef BUTTON_H_
// #define BUTTON_H_
// #include "IWidget.h"
// #include "IButtonCommand.h"
// #include <list>
// 
// using std::list;
// 
// namespace InGE{
// 
// class Button : public InGE::IButtonCommand, public InGE::IWidget
// {
// 	protected:
// 		list<IButtonCommand*> m_command;
// 	public:
// 		Button();
// 		virtual ~Button();
// 		virtual void draw(unsigned int x, unsigned int y, int width, int height);
// 		virtual void onClicked();
// };
// 
// };
// 
// #endif /*BUTTON_H_*/
