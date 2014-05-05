#include "twMultisprite.h"
#include "gamedata.h"
#include "frameFactory.h"

void TWMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

TWMultiSprite::TWMultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/Loc/X"), 
                    Gamedata::getInstance().getXmlInt(name+"/Loc/Y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/SpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"/SpeedY")),
			0,0,
			Gamedata::getInstance().getXmlInt(name+"/Depth")
		   ),
  frames( FrameFactory::getInstance().getFrames(name+"left") ),
  framesMirror( FrameFactory::getInstance().getFrames(name+"right") ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/Width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/Height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/Frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/FrameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  flag(false),
  flagStop(false)

{ }

TWMultiSprite::TWMultiSprite(const TWMultiSprite& s) :
  Drawable(s), 
  frames(s.frames),
  framesMirror(s.framesMirror),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  flag(s.flag),
  flagStop(s.flagStop)
  { }

void TWMultiSprite::draw() const { 

  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());

 if (!flag)
 { frames[currentFrame]->draw(x, y);}
 else 
 {   
	 framesMirror[currentFrame]-> draw(x,y);}
}


void TWMultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
  if (!flagStop) {
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);}
  

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
    Y(0);
    
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
    Y(worldHeight-frameHeight);
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
    flag = true;
    X(0);	
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
	flag = false;
	X( worldWidth-frameWidth);
  }  

}

//void TWMultiSprite::right() { X(X()+4.0); flag=true;}
//void TWMultiSprite::left() { X(X()-4.0); flag=false;}
//void TWMultiSprite::up() { velocityY(velocityY()-575.0);}
//void TWMultiSprite::down() { velocityY(velocityY()+5.0);}
//void TWMultiSprite::stop() { flagStop=true;}
	
	
