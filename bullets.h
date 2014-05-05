#ifndef __BULLETS_H__
#define __BULLETS_H__
#include <list>
#include "chunk.h"
#include "sprite.h"
#include "collisionStrategy.h"


class Bullets : public Sprite{
	
public:
  
  Bullets(const std::string&);
  Bullets(const Bullets&);
  ~Bullets();
  void draw() const;
  void draw(const float scale);
  void update(Uint32 ticks);
  void shoot(const Vector2f& pos, const Vector2f& vel);
  
  unsigned int bulletCount() const {return bulletList.size();}
  unsigned int freeCount() const {return freeList.size();}
  bool shooting() const {return bulletList.empty();}
  bool collideWith(const Drawable* obj) const;

  
private:
  std::string name;
  CollisionStrategy* strategy;
  //SDL_Surface *bulletSurface;
  Frame* bulletFrame;
  float frameInterval;
  float timeSinceLastFrame;
  mutable std::list<Chunk*> bulletList;
  mutable std::list<Chunk*> freeList;
  
  Bullets& operator=(const Bullets&);
	
	
	};
	
#endif
