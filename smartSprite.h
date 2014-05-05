#include <iostream>
#include "sprite.h"
#include "ioManager.h"

class SmartSprite : public Sprite {
public:
  SmartSprite(const std::string&, const Vector2f& pos, const Vector2f& vel, Drawable* p);
  void draw() const;
  void update(Uint32 ticks);
  void goLeft();
  void goRight();
  void goUp();
  void goDown();

  void incrSafeDistance() {++safeDistance; }
  void decrSafeDistance() { --safeDistance; }
  float getSafeDistance() { return safeDistance; }

private:	
  enum MODE {NORMAL, EVADE};
  IOManager& io;	
  const Drawable* enemy;
  float safeDistance;
  MODE currentMode;
  SmartSprite(const SmartSprite &);
  SmartSprite& operator=(const SmartSprite &rhs);
};
