#include <iostream>
#include <iomanip>
#include "ioManager.h"
using std::string;

IOManager& IOManager::getInstance() {
  static IOManager io;
  return io;
}

IOManager::IOManager( ) :
  gdata( Gamedata::getInstance() ),
  viewWidth( gdata.getXmlInt("view/Width") ),
  viewHeight( gdata.getXmlInt("view/Height") ),
  MAX_STRING_SIZE( gdata.getXmlInt("maxStringSize") ),
    // The 3rd and 4th parameters are just as important as the first 2!
    screen(SDL_SetVideoMode(viewWidth, viewHeight, 32, SDL_DOUBLEBUF)),
    font( NULL ), 
    color(),
    inputString("")  
{
  if (screen == NULL) { 
    throw string("Unable to set video mode; screen is NULL in IOMAnager"); 
  }
  if ( TTF_Init() == -1 ) {
    throw string("TTF_Init failed: ") + TTF_GetError();
  }
  font = TTF_OpenFont(
         gdata.getXmlStr("font/File").c_str(), 
         gdata.getXmlInt("font/Size")
         );
  if ( !font ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  color.r = gdata.getXmlInt("font/Red");
  color.g = gdata.getXmlInt("font/Green");
  color.b = gdata.getXmlInt("font/Blue");
  color.unused = gdata.getXmlInt("font/Unused");
  SDL_EnableUNICODE( SDL_ENABLE );
  atexit(TTF_Quit);
}

SDL_Surface* IOManager::loadAndSet(const string& filename, bool setcolorkey) const {
  SDL_Surface *tmp = IMG_Load(filename.c_str());
  if (tmp == NULL) {
    throw string("Unable to load bitmap ")+filename;
  }
  if ( setcolorkey ) {
    Uint32 colorkey = SDL_MapRGB(tmp->format, 255, 0, 255);
    SDL_SetColorKey(tmp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
  }
  // Optimize the strip for fast display
  SDL_Surface *image = SDL_DisplayFormatAlpha(tmp);
  if (image == NULL) {
    image = tmp;
  } 
  else {
    SDL_FreeSurface(tmp);
  }
  return image;
}

void IOManager::printMessageAt(const string& msg, Uint32 x, Uint32 y) const {
   SDL_Rect dest = {x,y,0,0};
   SDL_Surface * stext = TTF_RenderText_Blended(font, msg.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageAt");
   }
}

void IOManager::printMessageAt(const string& msg, Uint32 x, Uint32 y, const string& fontname) const {
	TTF_Font * deadfont = TTF_OpenFont(
         gdata.getXmlStr(fontname+"/File").c_str(), 
         gdata.getXmlInt(fontname+"/Size")
         );
           SDL_Color deadcolor;
         deadcolor.r = gdata.getXmlInt(fontname+"/Red");
  deadcolor.g = gdata.getXmlInt(fontname+"/Green");
  deadcolor.b = gdata.getXmlInt(fontname+"/Blue");
   SDL_Rect dest = {x,y,0,0};
   SDL_Surface * stext = TTF_RenderText_Blended(deadfont, msg.c_str(), deadcolor);
   TTF_CloseFont(deadfont);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageAt");
   }
}


void IOManager::printMessageCenteredAt( const string& msg, Uint32 y) const {
   SDL_Surface *stext = TTF_RenderText_Blended(font, msg.c_str(), color);
   if (stext) {
     Uint32 x = ( viewWidth - stext->w ) / 2;
     SDL_Rect dest = {x,y,0,0};
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageCenteredAt");
   }
}

template <typename T>
void IOManager::printMessageValueAt(const string& msg, T value, 
     Uint32 x, Uint32 y) const {
   std::stringstream strm;
   std::string message = msg;
   strm << message << value << "\0";
   message = strm.str();
   SDL_Rect dest = {x,y,0,0};
   SDL_Surface *stext = 
       TTF_RenderText_Blended(font, message.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageValueAt");
   }
}

void IOManager::printStringAfterMessage( const string& msg,
       Uint32 x, Uint32 y ) const {
   printMessageAt(msg+inputString, x, y);
}

void IOManager::buildString(SDL_Event event) {
  if( inputString.size() <= MAX_STRING_SIZE) {
    unsigned ch = event.key.keysym.sym;
    if ( isalpha(ch) || isdigit(ch) || ch == ' ') {
      inputString += char(event.key.keysym.unicode);
    }
  }     
  if( event.key.keysym.sym == SDLK_BACKSPACE
      && inputString.length() > 0 ) {
      // remove a character from the end
      int length = inputString.size();
      inputString.erase( length - 1 );
  }
}

template void IOManager::
printMessageValueAt(const string& msg, unsigned long, Uint32, Uint32) const;

template void IOManager::
printMessageValueAt(const string& msg, float, Uint32, Uint32) const;

template void IOManager::
printMessageValueAt(const string& msg, unsigned, Uint32, Uint32) const;

template void IOManager::
printMessageValueAt(const string& msg, int, Uint32, Uint32) const;

