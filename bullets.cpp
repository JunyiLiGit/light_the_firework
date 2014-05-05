#include <iostream>
#include <cmath>
#include "ioManager.h"
#include "gamedata.h"
#include "bullets.h"
#include "frameFactory.h"

CollisionStrategy* getStrategy(const string& name){
	std::string sName = Gamedata::Gamedata::getInstance().getXmlStr(name+"/Strategy");
	if (sName == "mid") return new MidPointCollisionStrategy;
	if (sName == "rec") return new RectangularCollisionStrategy;
	if (sName == "pix") return new PerPixelCollisionStrategy;
	throw std::string ("No strategy in getStrategy");
	
	
	}


Bullets:: ~Bullets(){
	
	
	std::list<Chunk*>::iterator iter = bulletList.begin();
	while(iter!= bulletList.end()){
		 
		 delete (*iter);
		++iter;
		
		
		}
	
	std::list<Chunk*>::iterator iter1 = freeList.begin();
	while(iter1!= freeList.end()){
		 
		 delete (*iter1);
		++iter1;
		
		
		}
	
	
	delete strategy;
}



Bullets::Bullets(const std::string& n):
Sprite(n),
name(n),
strategy(getStrategy(name)),
//bulletSurface(IOManager::getInstance().loadAndSet(Gamedata::getInstance().getXmlStr(name+"/File"),true)),
bulletFrame(FrameFactory::getInstance().getFrame(name)),
frameInterval(Gamedata::getInstance().getXmlInt(name+"/Interval")),
timeSinceLastFrame(0),
bulletList(),
freeList()
{}

Bullets::Bullets(const Bullets& b):
Sprite(b),
name(b.name),
strategy(b.strategy),
bulletFrame(b.bulletFrame),
frameInterval(b.frameInterval),
timeSinceLastFrame(b.timeSinceLastFrame),
bulletList(b.bulletList),
freeList(b.freeList)
{}



bool Bullets::collideWith(const Drawable* obj) const{
	//std::cout<<"before bullet"<<std::endl;
	std::list<Chunk*>::iterator ptr = bulletList.begin();
	while(ptr != bulletList.end()){
		if(strategy->execute(*(*ptr), *obj)){
			freeList.push_back(*ptr);
			ptr = bulletList.erase(ptr);
			
			//std::cout<<"bullet"<<std::endl;
			return true;
			
			}
			++ptr;
		}
		return false;
	}


void Bullets::shoot(const Vector2f&position, const Vector2f& velocity){
	
	
	if (timeSinceLastFrame>=frameInterval){
		
		if(freeList.empty()){
			Frame* newBulletFrame = FrameFactory::getInstance().getFrame(name);
			Chunk* b=new Chunk(name,position,velocity,newBulletFrame);
			bulletList.push_back(b);
		}
		else{
			Chunk* b = freeList.front();
			freeList.pop_front();
			b->reset();
			b->setVelocity(velocity);
			b->setPosition(position);
			bulletList.push_back(b);
		}
			timeSinceLastFrame = 0;
			}
		
	
	}
	
	
void Bullets::draw() const{
	
	std::list<Chunk*>::iterator ptr = bulletList.begin();
	while(ptr!= bulletList.end()){
		(*ptr)->draw();
		++ptr;
		//std::cout<<"draw"<<std::endl;
		
		}
	}
	
	
void Bullets::draw(const float scale) {
	
	std::list<Chunk*>::iterator ptr = bulletList.begin();
	while(ptr!= bulletList.end()){
		(*ptr)->draw(scale);
		++ptr;
		//std::cout<<"draw"<<std::endl;
		
		}
	}
	
void Bullets::update(Uint32 ticks){
	timeSinceLastFrame += ticks;
	std::list<Chunk*>::iterator ptr = bulletList.begin();
	while(ptr!= bulletList.end()){
		(*ptr)->update(ticks);
		if((*ptr)->goneTooFar()){
			freeList.push_back(*ptr);
			ptr = bulletList.erase(ptr);
			
			
			}
			else ++ptr;		
		
		}
	
	}



