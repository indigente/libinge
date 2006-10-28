// #ifndef LABEL_H_
// #define LABEL_H_
// #include "IWidget.h"
// #include <string>
// 
// using std::string;
// 
// namespace InGE{
// 
// class Label : public InGE::IWidget{
// 	protected:
// 		unsigned int m_texture;
// 		float m_texcoord[4];
// 		static bool m_initialized;
// 		
// 		bool setText(const string &s);
// 		
// 	public:
// 		Label(const string &s);
// 		virtual ~Label();
// 		virtual void draw(unsigned int x, unsigned int y, int width, int height);
// 		
// 		bool text(const string &s);
// };
// 
// }
// 
// #endif /*LABEL_H_*/
