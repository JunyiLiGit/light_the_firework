#include "player.h"
#include "explodingSprite.h"
#include "smartSprite.h"
struct SpriteStruct : public Drawable {

SpriteStruct(const std::string& name)
	: 
	 Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/Loc/X"), 
                    Gamedata::getInstance().getXmlInt(name+"/Loc/Y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/SpeedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/SpeedY")),
	   0,0,
	   Gamedata::getInstance().getXmlInt(name+"/Depth")
           )
    ,sprite(new Sprite(name))
	, explodingSprite(new ExplodingSprite(*sprite))
	, theSprite(sprite)
	, exploded(false)
{	}

SpriteStruct(const string& name, const Vector2f& pos, const Vector2f& vel)
	: Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/Loc/X"), 
                    Gamedata::getInstance().getXmlInt(name+"/Loc/Y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/SpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"/SpeedY")), 
			0,0,
			Gamedata::getInstance().getXmlInt(name+"/Depth")
		  ) 
	,sprite(new Sprite(name,pos,vel))
	, explodingSprite(new ExplodingSprite(*sprite))
	, theSprite(sprite)
	, exploded(false)
{	}

SpriteStruct(const string& name, const Vector2f& pos, const Vector2f& vel,  Player* enemy)
	: Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/Loc/X"), 
                    Gamedata::getInstance().getXmlInt(name+"/Loc/Y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/SpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"/SpeedY")), 
			0,0,
			Gamedata::getInstance().getXmlInt(name+"/Depth")
		  ) 
	,sprite(new SmartSprite(name,pos,vel, enemy))
	, explodingSprite(new ExplodingSprite(*sprite))
	, theSprite(sprite)
	, exploded(false)
{	}

SpriteStruct(const SpriteStruct& s):
	Drawable(s),
	sprite(new Sprite(s.getName())),
	explodingSprite(new ExplodingSprite(*sprite)),
	theSprite(sprite),
	exploded(false) {

}


SpriteStruct& operator=(const SpriteStruct& s){
	
	if (this == &s) return *this;
	Drawable::operator=(s);
	delete sprite;
	delete explodingSprite;
	delete theSprite;
	sprite = new Sprite(s.getName());
	explodingSprite =new ExplodingSprite(*sprite);
	theSprite = sprite;
	exploded = false;
	return *this;
	}


~SpriteStruct(){
	
	delete  sprite;
	delete  explodingSprite;
	//delete  theSprite;
	
	}
	
void reset(){
	
	exploded=false;
	X(Gamedata::getInstance().getXmlInt(getName()+"/Loc/X"));
	Y(Gamedata::getInstance().getXmlInt(getName()+"/Loc/Y"));
	theSprite=sprite;
	static_cast<ExplodingSprite*>(explodingSprite)->reset(getPosition());
	
}
	

  const Frame* getFrame() const { return theSprite->getFrame(); }
  
  void draw() const { 
	theSprite->draw();
  }
  void update(Uint32 ticks) { 
	theSprite->update(ticks);
  }
  // This function will check to see if the player collided with theSprite
  // only if theSprite did not explode yet
  bool hit(const Player* player) {
	  // check if exploded
	  if (!exploded) {
			if ( player->newcollideWith((Drawable*)(theSprite) )){	  
			//std::cout << "I collided with " << theSprite->getName() << std::endl;
		  exploded = true;
		  Vector2f position(theSprite->getPosition());
		 // std::cout << "Ops" <<theSprite->getName() << std::endl;
		  
		   static_cast<ExplodingSprite*>(explodingSprite)->
          reset(position); 
          theSprite = explodingSprite;
          
         // std::cout <<theSprite->getName() << std::endl;
					return true;	
		  	
	}
	
}
	
	 return false;	
	
	  
  }


Sprite* sprite;
Sprite* explodingSprite;
Sprite* theSprite;
bool exploded;
};
