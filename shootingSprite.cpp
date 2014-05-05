#include "shootingSprite.h"
#include "gamedata.h"

ShootingSprite:: ShootingSprite(const string& n):

MultiSprite(n),
bulletName(Gamedata::getInstance().getXmlStr(n+"/Bullet")),
bullets(new Bullets(bulletName)),
minSpeed(Gamedata::getInstance().getXmlInt(bulletName+"/SpeedY")),
direction("right"),
scale(1)
{}



ShootingSprite:: ShootingSprite(const string& n, const Vector2f& pos, const Vector2f& vel):

MultiSprite(n,pos,vel),
bulletName(Gamedata::getInstance().getXmlStr(n+"/Bullet")),
bullets(new Bullets(bulletName)),
minSpeed(Gamedata::getInstance().getXmlInt(bulletName+"/SpeedY")),
direction("right"),
scale(1)
{}



ShootingSprite:: ShootingSprite(const ShootingSprite& s):
MultiSprite(s),
bulletName(s.bulletName),
bullets(s.bullets),
minSpeed(s.minSpeed),
direction(s.direction),
scale(s.scale)
{}





void ShootingSprite::shoot(){
	
	float x = X()+getFrame()->getWidth()/2-5;
	float y = Y()+getFrame()->getHeight();
	bullets->shoot(Vector2f(x,y), Vector2f(velocityX(), -(minSpeed+velocityY())));
	}
	
	
void ShootingSprite::playershoot(){
	
	float x = X()+getFrame()->getWidth()/2;
	float y = Y()+getFrame()->getHeight()/2;
	
    if(direction == string("right"))
    {bullets->shoot(Vector2f(x,y), Vector2f(-(minSpeed+velocityX()), 0));}
	
	if (direction == string("left")) 
	{bullets->shoot(Vector2f(x-100,y), Vector2f(minSpeed+velocityX(), 0));}

    if (direction == string("up"))
    {bullets->shoot(Vector2f(x-20,y-60), Vector2f(0,minSpeed+velocityY()));} 
	
	}


	
bool ShootingSprite::collideWith(const Drawable *obj) const {
	
	//std::cout<<"before bullet"<<std::endl;
	return bullets->collideWith(obj);
	
	}



	
void ShootingSprite::draw() const {
	
	MultiSprite::draw();
	bullets->draw(scale);
	
	}


void ShootingSprite::update(Uint32 ticks){
	
	//MultiSprite::update(ticks);
	bullets->update(ticks);
	
	}
