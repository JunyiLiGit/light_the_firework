#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "shootingSprite.h"
#include "collisionStrategy.h"
class Player : public ShootingSprite {
public:
Player(const std::string&);
virtual ~Player();

//Player& operator=(const Player&);
void draw() const;
void update(Uint32 ticks);
//const Drawable* getSprite(){return twoway;}
void moveForward() { forward = true; }
void moveBack() { back = true; }
void moveUp() { up = true; }
void moveDown() { down = true; }
void start();
void stop();

bool newcollideWith(const Drawable* d) const {
    
    return strategy->execute(*this, *d);
  }
  
void setCollisionStrategy(int index) {
    strategy = strategies[index];
  }

int scoreAdd() { return score=score+3; } 
int scoreMin() {return --score; }

int getScore() const {return score;}
void setScore(const int s) {score = s;}

void reset();

private:

//TWMultiSprite *twoway;
const std::vector<Frame *> frames;
int worldWidth;
int worldHeight;
int frameWidth;
int frameHeight;
int count;
bool forward, back, up, down, flagStop,flag, physics;
int score;
std::vector<CollisionStrategy*> strategies;
CollisionStrategy * strategy;
Player(const Player&);
Player& operator=(const Player&);

};
#endif
