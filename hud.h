#ifndef __HUD_H__
#define __HUD_H__
// Class for creating a hud
#include <iostream>
#include <string>
#include "vector2f.h"
#include "aaline.h" 
#include "frame.h"
#include "ioManager.h"

class Hud {
public:
	Hud();
	Hud(const Hud& hud);
	virtual ~Hud() {} 
	virtual void draw() const;
	void setChunkCount(const int count) { chunkCount = count; }
	void setFreeCount(const int count) { freeCount = count; }
	//void update(Uint32 t);
		
private:
	void displayText() const;
	Vector2f start;
	int totalLength;
	int thick;
	int chunkCount;
	int freeCount;
	//Health bar;
	Hud& operator=(const Hud& rhs);
};
#endif // __HUD_H__
