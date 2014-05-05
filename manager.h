#include <list>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "health.h"
#include "player.h"
#include "sound.h"
#include "explodingSprite.h"
#include "shootingSprite.h"
#include "spriteStruct.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  std::vector<World*> worlds;
  Viewport& viewport;
  Hud hud;
  Health bar;
  

  std::vector<Drawable*> sprites;
  std::vector<ShootingSprite*> shootingRains;
 

  Player *player;
  
 
  bool makeVideo;
  int frameCount;
  int currentSprite;
  std::string username;
  std::string title;
  int frameMax;
  bool hudFlag;
  bool die;
  bool win;
  bool pastmountain;
  bool stopRight;
  bool stopLeft;
  SDLSound sound;

 
  bool checkNumber(const std::string&) const;

  void draw() const;
 const string checkForCollisions() ;
  void update();
  void init();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};


class DepthGreater {
public:
	bool operator()(const Drawable* lhs, const Drawable* rhs) {
		return lhs->getDepth() > rhs->getDepth();	
	}
};




