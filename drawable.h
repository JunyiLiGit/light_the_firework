#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>
#include <string>
#include "vector2f.h"
#include "frame.h"
#include <algorithm> 
 
// Drawable is an Abstract Base Class (ABC) that
// specifies the methods that derived classes may
// and must have.
class Drawable {
public:
  Drawable(const std::string& n, const Vector2f& pos, const Vector2f& vel, const double &ag, const double &inc,const int& dep): 
    name(n), position(pos), velocity(vel), angle(ag), angleinc(inc),depth(dep) {}

  Drawable(const Drawable& s) : 
    name(s.name),position(s.position), velocity(s.velocity), angle(s.angle),angleinc(s.angleinc),depth(s.depth)
    { }

  virtual ~Drawable() {}

 const std::string& getName() const { return name; }
 void setName(const std::string& n) { name = n;    }
  

  virtual const Frame* getFrame() const = 0;

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;

  float X() const { return position[0]; }
  void X(float x) { position[0] = x;    }

  float Y() const { return position[1]; }
  void Y(float y) { position[1] = y;    }

  float velocityX() const  { return velocity[0]; }
  void velocityX(float vx) { velocity[0] = vx;   }
  float velocityY() const  { return velocity[1]; }
  void velocityY(float vy) { velocity[1] = vy;   }

  double getAngle() const {return angle;}
  void setAngle(const double& ag)  { angle = ag; }

  double getAngleInc() const {return angleinc;}
  void setAngleInc(const double& aginc)  { angleinc = aginc; }

  const Vector2f& getVelocity() const   { return velocity; }
  void setVelocity(const Vector2f& vel) { velocity = vel;  }
  const Vector2f& getPosition() const   { return position; }
  void setPosition(const Vector2f& pos) { position = pos;  }

  virtual bool collidedWith(const Drawable*) const { 
    throw std::string("No collidedWith");  
  }
  const int& getDepth() const { return depth; } 
  
  bool operator<(const Drawable& d) const {
      return getDepth() < d.getDepth();
  }
   

private:
  std::string name;
  Vector2f position;
  Vector2f velocity;
  double angle;
  double angleinc;
  int depth;
};







#endif
