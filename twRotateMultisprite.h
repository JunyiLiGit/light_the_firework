#ifndef TWMULTISPRITE__H
#define TWMULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"

class TWRotateMultiSprite : public Drawable {
public:
  TWRotateMultiSprite(const std::string&);
  TWRotateMultiSprite(const TWRotateMultiSprite&);
  virtual ~TWRotateMultiSprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
      if (!flag){return frames[currentFrame];}
	  else {return framesMirror[currentFrame];} 
  }

protected:
  const std::vector<Frame *> frames;
  const std::vector<Frame *> framesMirror;

  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  bool flag;

  void advanceFrame(Uint32 ticks);
};
#endif
