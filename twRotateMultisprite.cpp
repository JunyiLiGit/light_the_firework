#include "twRotateMultisprite.h"
#include "gamedata.h"
#include "frameFactory.h"

void TWRotateMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

TWRotateMultiSprite::TWRotateMultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/Loc/X"), 
                    Gamedata::getInstance().getXmlInt(name+"/Loc/Y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"SpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"SpeedY")),
           (Gamedata::getInstance().getXmlInt(name+"/Angle")),
           (Gamedata::getInstance().getXmlInt(name+"/increase")),
           Gamedata::getInstance().getXmlInt(name+"/Depth")
		   ),
  frames( FrameFactory::getInstance().getFrames(name+"/left") ),
  framesMirror( FrameFactory::getInstance().getFrames(name+"/right") ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/Width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/Height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/leftFrames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/FrameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  flag(false)
{ }

TWRotateMultiSprite::TWRotateMultiSprite(const TWRotateMultiSprite& s) :
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
  flag( s.flag)
  { }

void TWRotateMultiSprite::draw() const { 

  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  double angle = getAngle();

 if (!flag)
 { frames[currentFrame]->draw(x, y, angle);}
 else 
 {   
	 framesMirror[currentFrame]-> draw(x,y, angle);}
}


void TWRotateMultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  
  setAngle(getAngle() + getAngleInc() );

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
    
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
    flag = true;	
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
	flag = false;
  }  

}
