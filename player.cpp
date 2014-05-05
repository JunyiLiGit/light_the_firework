#include "player.h"
#include "ioManager.h"
#include "frameFactory.h"

Player::~Player() {

 // delete twoway;
	
  for (unsigned i = 0; i < strategies.size(); ++i) {
    delete strategies[i];
  }
}


void Player::reset(){
	
	
	forward=false;
	back=false;
	up=false;
	down=false;
	flag=false;
	physics = true;
	count=2;
	score=0;
	X(Gamedata::getInstance().getXmlInt("fire/Loc/X")); 
	Y(Gamedata::getInstance().getXmlInt("fire/Loc/Y"));
	velocityX(Gamedata::getInstance().getXmlInt("fire/SpeedX"));
	velocityY(Gamedata::getInstance().getXmlInt("fire/SpeedY"));
	flagStop=true;
	
	}


Player::Player(const std::string& name) :
	ShootingSprite(name),
	frames( FrameFactory::getInstance().getFrames(name) ),
	worldWidth(Gamedata::getInstance().getXmlInt("world/Width")),
    worldHeight(Gamedata::getInstance().getXmlInt("world/Height")),
    frameWidth(frames[0]->getWidth()),
    frameHeight(frames[0]->getHeight()),
    count(2),
	forward(false),
	back(false),
	up(false),
	down(false),
	flagStop(false),
	flag(false),
	physics(true),
	score(0),
	strategies(),
  strategy( NULL )
	{
		stop();
        strategies.push_back( new MidPointCollisionStrategy );
        strategies.push_back( new RectangularCollisionStrategy );
        strategies.push_back( new PerPixelCollisionStrategy );
        strategy = strategies[0];	
			}

 
void Player::update(Uint32 ticks) {
	
	int rangeY =worldHeight-frameHeight;
    int rangeX =worldWidth-frameWidth;
    
   advanceFrame(ticks);
   
   
   ShootingSprite::update(ticks);
	
	
	
	if (!flagStop){
	  
	  if (up && count>0)
	  
	 { velocityY(velocityY()-95);
		 --count;
		 physics = true;

		  }
	if (physics) {
		float deltaT =  0.05;
		Vector2f accel = Vector2f(0,60);
		Vector2f vnew = getVelocity() + accel* deltaT;
         setPosition(getPosition() + vnew * deltaT);
	     setVelocity(vnew);
	}
			if (forward) {
		 X(X()+8.0); flag=true;
	}
	       if (back) {
		 X(X()-8.0); flag=false;
	}
		
	}
	else{
		score = 0;
		
		}

	
	
   
   // Collision Check with edge
	  
	if (  Y() < 0) {
    velocityY( 0);
    Y(0);
    
     }

 
     if ( Y() > rangeY) {
     velocityY(0);
     velocityX(0);
     Y(rangeY);
     count=2;
     //std::cout<<"hit the ground"<<std::endl;
     //std::cout<<velocityY()<<std::endl;
     physics = false;
  }
  //else std::cout << "height = " << Y() << std::endl;
  
  if (  X() < 0) {
     velocityX( 0 );
     X(0);	
  }
  if (  X() > rangeX) {
     velocityX( 0 );
	 X( rangeX);
}

	forward = back = up = down = false;
	
}

void Player::start() {flagStop  = false;}

void Player::stop() { flagStop=true;}

void Player::draw() const {
	
	ShootingSprite::draw();
	 
	IOManager::getInstance().printMessageValueAt("player score: ", getScore(), 300, 30);
}




 
