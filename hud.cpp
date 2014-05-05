#include "hud.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "viewport.h"
#include "clock.h"


Hud::Hud() :
	start(Vector2f(10, 10)),
  	totalLength(250),
	thick(14),
	chunkCount(0),
	freeCount(0)
	{}
Hud::Hud(const Hud& hud) :
	start(hud.start),
  	totalLength(hud.totalLength),
	thick(14),
	chunkCount(0),
	freeCount(0)
	
{}

void Hud::draw() const {
	
  SDL_Surface* surface = IOManager::getInstance().getScreen();
	 
  Draw_AALine(surface, start[0], start[1]+totalLength/2,
                       start[0]+totalLength, start[1]+totalLength/2,
			start[0]+totalLength-14, 0xff, 0xff, 0xff,0x64);
			
	
  // Two Horizontal lines
  Draw_AALine(surface, start[0], start[1],
                      start[0]+totalLength, start[1],
                      2.0, 0xff, 0x00, 0x00,0xff);
	
  Draw_AALine(surface, start[0], start[1]+totalLength,
                      start[0]+totalLength, start[1]+totalLength,
                      2.0, 0xff, 0x00, 0x00,0xff);
  // Two Vertical lines
  Draw_AALine(surface, start[0], start[1],
                      start[0], start[1]+totalLength,
                      2.0, 0xff, 0x00, 0x00,0xff);
  Draw_AALine(surface, start[0]+totalLength, start[1],
                      start[0]+totalLength, start[1]+totalLength,
                      2.0, 0xff, 0x00, 0x00,0xff);
	displayText();
   // bar.draw();	
}
void Hud::displayText() const{
	//IOManager::getInstance().printMessageValueAt("Seconds: ", Clock::getInstance().getSeconds(), 70, 20);
  	//IOManager::getInstance().printMessageValueAt("fps: ", Clock::getInstance().getAvgFps(), 70, 40);
    IOManager::getInstance().printMessageAt("Enemy: rock, rain", 50, 20); 
    IOManager::getInstance().printMessageAt("Friend: leaf, umbrella",35, 40); 		
  	IOManager::getInstance().printMessageAt("Press Up Down",50, 60);
  	IOManager::getInstance().printMessageAt("Left Right to move",35, 80);
    IOManager::getInstance().printMessageAt("Space to shoot",30, 100);
    IOManager::getInstance().printMessageAt("Enter to begin",50, 120);
    IOManager::getInstance().printMessageAt("R to restart",50, 140);
    IOManager::getInstance().printMessageAt("F1 to move the hud",50, 160);
  	IOManager::getInstance().printMessageAt("Goal: Ignite the firework", 15 ,180);
  	IOManager::getInstance().printMessageAt("with more than 20 points!", 15 ,200);
  	IOManager::getInstance().printMessageValueAt("BulletsCount: ", chunkCount, 50, 220);
  	IOManager::getInstance().printMessageValueAt("FreeCount: ", freeCount, 50, 240);
  	
  	
  	
}




