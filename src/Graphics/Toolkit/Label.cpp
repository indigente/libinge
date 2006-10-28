// #include "Label.h"
// #include <SDL/SDL.h>
// #include <SDL/SDL_ttf.h>
// #include "../Render/Drawer.h"
// 
// namespace InGE{
// 	
// bool Label::m_initialized = false;
// 
// /* Quick utility function for texture creation */
// static int power_of_two(int input){
// 	int value = 1;
// 
// 	while ( value < input ) {
// 		value <<= 1;
// 	}
// 	return value;
// }
// 	
// static unsigned int SDL_GL_LoadTexture(SDL_Surface *surface, float *texcoord){
// 	unsigned int texture;
// 	int w, h;
// 	SDL_Surface *image;
// 	SDL_Rect area;
// 	Uint32 saved_flags;
// 	Uint8  saved_alpha;
// 
// 	/* Use the surface width and height expanded to powers of 2 */
// 	w = power_of_two(surface->w);
// 	h = power_of_two(surface->h);
// 	texcoord[0] = 0.0f;			/* Min X */
// 	texcoord[1] = 0.0f;			/* Min Y */
// 	texcoord[2] = (float)surface->w / w;	/* Max X */
// 	texcoord[3] = (float)surface->h / h;	/* Max Y */
// 
// 	image = SDL_CreateRGBSurface(
// 			SDL_SWSURFACE,
// 			w, h,
// 			32,
// #if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
// 			0x000000FF, 
// 			0x0000FF00, 
// 			0x00FF0000, 
// 			0xFF000000
// #else
// 			0xFF000000,
// 			0x00FF0000, 
// 			0x0000FF00, 
// 			0x000000FF
// #endif
// 		       );
// 	if ( image == NULL ){
// 		return 0;
// 	}
// 
// 	/* Save the alpha blending attributes */
// 	saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
// 	saved_alpha = surface->format->alpha;
// 	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
// 		SDL_SetAlpha(surface, 0, 0);
// 	}
// 
// 	/* Copy the surface into the GL texture image */
// 	area.x = 0;
// 	area.y = 0;
// 	area.w = surface->w;
// 	area.h = surface->h;
// 	SDL_BlitSurface(surface, &area, image, &area);
// 
// 	/* Restore the alpha blending attributes */
// 	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
// 		SDL_SetAlpha(surface, saved_flags, saved_alpha);
// 	}
// 
// 	/* Create an OpenGL texture for the image */
// 	glGenTextures(1, &texture);
// 	glBindTexture(GL_TEXTURE_2D, texture);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// 	glTexImage2D(GL_TEXTURE_2D,
// 		     0,
// 		     GL_RGBA,
// 		     w, h,
// 		     0,
// 		     GL_RGBA,
// 		     GL_UNSIGNED_BYTE,
// 		     image->pixels);
// 	SDL_FreeSurface(image); /* No longer needed */
// 
// 	return texture;
// }
// 
// Label::Label(const string &s){
// 	setText(s);
// }
// 
// Label::~Label(){
// 	glDeleteTextures(1, &m_texture);
// }
// 
// bool Label::setText(const string &s){
// 	SDL_Surface *text;
// 	SDL_Color black = { 0xFF, 0xFF, 0xFF, 0 };
// 	
// 	if (!m_initialized) {
// 		if ( TTF_Init() < 0 ) {
// 			throw string("ERROR: TTF_Init()");
// 		}
// 		//atexit(TTF_Quit);
// 		m_initialized = true;
// 	}
// 	
// 	TTF_Font *font = TTF_OpenFont("font/Vera.ttf", 12); //FIXME: passar parametros
// 	if (font == NULL) { return false; } //FIXME: tratamento de erro
// 	TTF_SetFontStyle(font, TTF_STYLE_NORMAL); //FIXME: outros tipos de estilo
// 	text = TTF_RenderText_Blended(font, s.c_str(), black); //UTF-8?
// 	m_w = text->w;
// 	m_h = text->h;
// 	m_texture = SDL_GL_LoadTexture(text, m_texcoord); //FIXME: tratamento de erro
// 	SDL_FreeSurface(text);
// 	TTF_CloseFont(font);
// 	
// 	return true;
// }
// 
// bool Label::text(const string &s){
// 	glDeleteTextures(1, &m_texture);
// 	return setText(s);
// }
// 
// void Label::draw(unsigned int x, unsigned int y, int width, int height){
// 	int _x, _y;
// 
// 	_x = m_x >= 0 ? x + m_x : (x+width) - m_w + m_x;
// 	_y = m_y >= 0 ? (y+height) - m_h - m_y : y - m_y;
// 	
// 	// FIXME: As linhas a seguir sao testes
// 	m_texcoord[0] = 0.0;
// 	m_texcoord[1] = 0.0;
// 	m_texcoord[2] = 1.0;
// 	m_texcoord[3] = 1.0;
// 
// 	Drawer *drawer = Drawer::getInstance();
// 	drawer->bindTexture(InGE_TEXTURE_2D, m_texture);
// 	drawer->begin(GL_QUADS);
// 		drawer->texCoord(m_texcoord[0],m_texcoord[3]);
// 		drawer->vertex(_x, _y, 0);
// 		
// 		drawer->texCoord(m_texcoord[2],m_texcoord[3]);
// 		drawer->vertex(_x+m_w, _y, 0);
// 				
// 		drawer->texCoord(m_texcoord[2],m_texcoord[1]);
// 		drawer->vertex(_x+m_w, _y + m_h, 0);
// 		
// 		drawer->texCoord(m_texcoord[0],m_texcoord[1]);
// 		drawer->vertex(_x, _y + m_h, 0);		
// 	drawer->end();
// }
// 
// } //namespace InGE
