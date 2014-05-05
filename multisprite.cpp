#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

void MultiSprite::reset(){
	
	X(Gamedata::getInstance().getXmlInt(getName()+"/Loc/X")); 
	Y(Gamedata::getInstance().getXmlInt(getName()+"/Loc/Y"));
	velocityX(Gamedata::getInstance().getXmlInt(getName()+"/SpeedX"));
	velocityY(Gamedata::getInstance().getXmlInt(getName()+"/SpeedY"));
	scale=1;
	
	}


MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/Loc/X"), 
                    Gamedata::getInstance().getXmlInt(name+"/Loc/Y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/SpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"/SpeedY")), 
			0,0,
			Gamedata::getInstance().getXmlInt(name+"/Depth")
		  ),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/Width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/Height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/Frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/FrameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  scale(1)
{ }



MultiSprite::MultiSprite(const string& n, const Vector2f& pos, const Vector2f& vel):
  Drawable(n, pos, vel, 0,0,Gamedata::getInstance().getXmlInt(n+"/Depth")), 
  frames( FrameFactory::getInstance().getFrames(n) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/Width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/Height")),
  
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(n+"/Frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(n+"/FrameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  scale(1)
{ }



MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s), 
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  scale(s.scale)
  { }

void MultiSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y,scale);
}




void MultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  

}


