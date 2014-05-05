#ifndef __SHOOTINGSPRITE_H__
#define __SHOOTINGSPRITE_H__
#include <string>
#include <iostream>
#include "multisprite.h"
#include "bullets.h"



class ShootingSprite: public MultiSprite{
	
public:
  ShootingSprite(const string& n);
  ShootingSprite(const string& n, const Vector2f& pos, const Vector2f& vel);
  ShootingSprite(const ShootingSprite& s);
  virtual void update(Uint32 ticks);
  virtual void draw() const;
  virtual void shoot();
  virtual void playershoot();
  virtual bool collideWith(const Drawable*) const;
  Bullets* getBullets() const {return bullets;}
  float getScale() const {return scale;}
  void setScale(float s) { scale=s;} 
  const string& getDirection() const {return direction;}
  void setDirection(const string& s) { direction = s;}
  virtual ~ShootingSprite(){ delete bullets;}
  
private:
   std::string bulletName;
   Bullets* bullets;
   float minSpeed;
   string direction;
   float scale;
   ShootingSprite& operator=(const ShootingSprite&);
	
	};
#endif
