#ifndef twMultisprite__H
#define twMultisprite__H
#include <string>
#include <vector>
#include "drawable.h"

class TWMultiSprite : public Drawable {
public:
friend class Player;
  TWMultiSprite(const std::string&);
  TWMultiSprite(const TWMultiSprite&);
  virtual ~TWMultiSprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  //void right();
  //void left();
  //void up();
  //void down();
  //void stop();
  virtual const Frame* getFrame() const { 
      if (!flag){return frames[currentFrame];}
	  else {return framesMirror[currentFrame];} 
  }

protected:
  const std::vector<Frame *> frames;
  const std::vector<Frame *> framesMirror;

  int worldWidth;
  int worldHeight;

  unsigned int currentFrame;
  unsigned int numberOfFrames;
  unsigned int frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  bool flag;
  bool flagStop;

  void advanceFrame(Uint32 ticks);
};
#endif
