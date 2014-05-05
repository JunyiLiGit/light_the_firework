#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "twRotateMultisprite.h"
#include "twMultisprite.h"


Manager::~Manager() { 


	for (unsigned int i = 0; i < worlds.size(); ++i) {
		delete worlds[i];}


	for(unsigned int i=0; i< sprites.size(); ++i){

		delete sprites[i];
	}

	for(unsigned int i=0; i< shootingRains.size(); ++i){

		delete shootingRains[i];
	}      


	delete player;


}

Manager::Manager() :
	env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
	io( IOManager::getInstance() ),
	clock( Clock::getInstance() ),
	screen( io.getScreen() ),
	worlds(),
	viewport( Viewport::getInstance() ),
	hud(),
	bar(),
	sprites(),
	shootingRains(),
	player(new Player("fire")),

	makeVideo( false ),
	frameCount( 0 ),
	currentSprite(0),
	username(  Gamedata::getInstance().getXmlStr("username") ),
	title( Gamedata::getInstance().getXmlStr("screenTitle") ),
	frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
	hudFlag(true),
	die(false),
	win(false),
	pastmountain(false),
	stopRight(false),
	stopLeft(false),
	sound()
{


	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw string("Unable to initialize SDL: ");
	}
	SDL_WM_SetCaption(title.c_str(), NULL);
	atexit(SDL_Quit);

	worlds.reserve(3);
	worlds.push_back(new World("sky", Gamedata::getInstance().getXmlInt("sky/Factor")));  
	worlds.push_back(new World("mountains", Gamedata::getInstance().getXmlInt("mountains/Factor")));


	int i;
	int rocksNumber = Gamedata::getInstance().getXmlInt("rocks/Count");
	float lrocksposX = Gamedata::getInstance().getXmlInt("rocks/Loc/leftX");
	float lrocksspeedX = Gamedata::getInstance().getXmlInt("rocks/leftSpeedX");

	float rrocksposX = Gamedata::getInstance().getXmlInt("rocks/Loc/rightX");
	float rrocksspeedX = Gamedata::getInstance().getXmlInt("rocks/rightSpeedX");

	float rocksspeedY = Gamedata::getInstance().getXmlInt("rocks/SpeedY");
	float rocksposY = Gamedata::getInstance().getXmlInt("rocks/Loc/Y");
	for(i = 0; i < rocksNumber; i++)
	{   
		lrocksposX = lrocksposX+150,
				   rrocksposX = rrocksposX+150,
				   sprites.push_back(new MultiSprite("rocks",
							   Vector2f(
								   lrocksposX,
								   rocksposY
								   ),
							   Vector2f(
								   lrocksspeedX,
								   rocksspeedY
								   )
							   ));
		sprites.push_back(new MultiSprite("rocks",
					Vector2f(
						rrocksposX,
						rocksposY
						),
					Vector2f(
						rrocksspeedX,
						rocksspeedY
						)
					));


	}

	



	SpriteStruct *fireworks = new SpriteStruct("fireworks");
    sprites.push_back(fireworks);

   int leafNumber = Gamedata::getInstance().getXmlInt("leaf/Count");

	for(i = 0; i < leafNumber; i++)
	{
		SpriteStruct *leaf = new SpriteStruct("leaf",
				Vector2f(
					Gamedata::getInstance().getRandInRange(20,300),
					Gamedata::getInstance().getRandInRange(20,300)
					),
				Vector2f(
					Gamedata::getInstance().getRandInRange(30,500),
					Gamedata::getInstance().getRandInRange(30,500)
					), player);
		sprites.push_back(leaf);

	}


	sprites.push_back(new MultiSprite("umbrella",
				Vector2f(Gamedata::getInstance().getXmlInt("umbrella/Loc/X"), 
					Gamedata::getInstance().getXmlInt("umbrella/Loc/Y")), 
				Vector2f(Gamedata::getInstance().getXmlInt("umbrella/SpeedX"), 
					Gamedata::getInstance().getXmlInt("umbrella/SpeedY"))

				));


	sprites.push_back( new Sprite("volcano") );
	sprites.push_back( new Sprite("pond") );
	sprites.push_back( new Sprite("mountain") );



	int rainNumber = Gamedata::getInstance().getXmlInt("rain/Count");
	float rainposX = Gamedata::getInstance().getXmlInt("rain/Loc/X");
	float rainposY = Gamedata::getInstance().getXmlInt("rain/Loc/Y");
	float rainspeedX = Gamedata::getInstance().getXmlInt("rain/SpeedX");
	float rainspeedY = Gamedata::getInstance().getXmlInt("rain/SpeedY");
	for(i = 0; i < rainNumber; i++)
	{   
		rainposX = rainposX+100,
				 shootingRains.push_back(new ShootingSprite("rain",
							 Vector2f(
								 rainposX,
								 rainposY
								 ),
							 Vector2f(
								 rainspeedX,
								 rainspeedY
								 )
							 ));



	}


	viewport.setObjectToTrack(player);
	std::sort(sprites.begin(), sprites.end(),DepthGreater());
}


bool Manager::checkNumber(const std::string& number) const {
	if (number.size() > 1) return false;
	if (number[0] >= '0' && number[0] < '6') return true;
	return false;
}


const string Manager::checkForCollisions() {

	std::vector<Drawable*>::const_iterator sprite = sprites.begin();
	while ( sprite != sprites.end() ) {
		if ( (*sprite)->getName() == string("leaf") || ((*sprite)->getName() == string("fireworks") && player->getScore() > 10 ) ){
			if(static_cast<SpriteStruct*>(*sprite)->hit(player)) {
				if((*sprite)->getName() == string("leaf")){	
					sound[0];  player->scoreAdd();}
				return (*sprite)->getName();
			}
		}



		if(player->newcollideWith(*sprite)){



			if((*sprite)->getName()=="pond")
			{ sound[1];  player->setScore(0);   die=true; win=false;


			}

			if((*sprite)->getName()=="rocks" && static_cast<MultiSprite*>(*sprite)->getScale()==1)

			{ sound[2]; player->scoreMin();  }

			


			if((*sprite)->getName()=="fireworks" &&  player->getScore() > 20 )
			{ sound[3];   win=true; }

			if((*sprite)->getName()=="mountain" && !pastmountain)
			{ 



				stopLeft=false; stopRight=true;



			} 

			if((*sprite)->getName()=="mountain" && player->X() < Gamedata::getInstance().getXmlInt("mountain/Loc/X"))
			{ 



				stopLeft=false; stopRight=false;



			} 


			if((*sprite)->getName()=="umbrella" && !pastmountain)
			{      
				stopRight=false; 

				sound[4];

				//	player->scoreAdd();

				(*sprite)->X(player->X()-50);   
				(*sprite)->Y(player->Y()-60) ;
				(*sprite)->velocityX(player->velocityX());
				(*sprite)->velocityY(player->velocityY());




			}	





		}

		if(player->collideWith(*sprite)){

			if ( (*sprite)->getName() == "rocks"){


				sound[5];
				player->scoreAdd();
				static_cast<MultiSprite*>(*sprite)->setScale(0.5);

			}   



		}


		++sprite;
	}
	std::vector<ShootingSprite*>::const_iterator shootingSprite = shootingRains.begin();
	while(shootingSprite != shootingRains.end()){

		if((*shootingSprite)->collideWith(player) && (*shootingSprite)->getScale() ==1 ){


			player-> scoreMin();
			sound[6];

			// std::cout<<"drop"<<std::endl;

			return (*shootingSprite)->getName();

		}


		if(player->collideWith(*shootingSprite)){

			sound[7];  player-> scoreAdd();  (*shootingSprite)->setScale(0.5);

		}

		++shootingSprite;

	}

	return string("oops");


}





void Manager::draw() const {


	for (unsigned i = 0; i < worlds.size(); ++i) {
		worlds[i]->draw();
	}


	for(std::vector<ShootingSprite*>::const_iterator iter = shootingRains.begin(); iter!= shootingRains.end(); ++iter){
		(*iter)->draw();}

	for(std::vector<Drawable*>::const_iterator iter = sprites.begin(); iter!= sprites.end(); ++iter){
		(*iter)->draw();}

	if(!die){
		player->draw();}


	if(hudFlag){

		hud.draw();
	}



	viewport.draw();

	if(die) {IOManager::getInstance().printMessageAt( "YOU DIED...", 250,160,"deadfont");}

	if(win) {IOManager::getInstance().printMessageAt( "YOU WIN!!!", 250,120,"deadfont");}

	SDL_Flip(screen);

}




void Manager::update() {
	++clock;
	Uint32 ticks = clock.getElapsedTicks();

	for (unsigned int i = 0; i < worlds.size(); ++i) {
		worlds[i]->update();
	}

	for(std::vector<Drawable*>::const_iterator iter = sprites.begin(); iter!= sprites.end(); ++iter){
		(*iter)->update(ticks);}


	for(std::vector<ShootingSprite*>::const_iterator iter = shootingRains.begin(); iter!= shootingRains.end(); ++iter){
		(*iter)->update(ticks);}

	for(std::vector<ShootingSprite*>::const_iterator iter = shootingRains.begin(); iter!= shootingRains.end(); ++iter){
		(*iter)->shoot();
	}

	//bar.update(ticks);

	if(player->X() > Gamedata::getInstance().getXmlInt("mountain/Loc/X")+Gamedata::getInstance().getXmlInt("mountain/Width")-50)

	{ pastmountain = true;}
	else pastmountain = false;
	
	if(player->getScore() < 0) {die = true; win=false;} 



	if(!die){
		player->update(ticks);
		checkForCollisions();
		}

	if ( makeVideo && frameCount < frameMax ) {
		makeFrame();
	}



	viewport.update(); // always update viewport last
	hud.setChunkCount(player->getBullets()->bulletCount());
	hud.setFreeCount(player-> getBullets()->freeCount());
}


void Manager::makeFrame() {
	std::stringstream strm;
	strm << "video/" << username<< '.' 
		<< std::setfill('0') << std::setw(4) 
		<< frameCount++ << ".bmp";
	std::string filename( strm.str() );
	std::cout << "Making frame: " << filename << std::endl;
	SDL_SaveBMP(screen, filename.c_str());
}

void Manager::init(){
		
        win=die=false;	
		player->reset();
		stopRight=false;
        stopLeft=false;
			
	std::vector<Drawable*>::const_iterator sprite = sprites.begin();
	while ( sprite != sprites.end() ){
				
		 if((*sprite)->getName() == string("leaf"))
		{
			static_cast<SpriteStruct*>(*sprite)->reset();
			}
			
		 if((*sprite)->getName() == string("fireworks"))
		{
			static_cast<SpriteStruct*>(*sprite)->reset();
			}
		 if((*sprite)->getName() == string("umbrella"))
		{
			static_cast<MultiSprite*>(*sprite)->reset();
			}
			
			
			
		if((*sprite)->getName() == string("rocks"))
		
		{ static_cast<MultiSprite*>(*sprite)->setScale(1); }
			
		++sprite;
			
	}	
	
	
	for(std::vector<ShootingSprite*>::const_iterator iter = shootingRains.begin(); iter!= shootingRains.end(); ++iter){
		(*iter)->setScale(1);}
				
 }
	



void Manager::play() {
	SDL_Event event;

	bool done = false;
	bool keyCatch = false;
	while ( not done ) {


		SDL_PollEvent(&event);
		Uint8 *keystate = SDL_GetKeyState(NULL);
		if (event.type ==  SDL_QUIT) { done = true; break; }
		if(event.type == SDL_KEYUP) { 
			keyCatch = false; 
		}
		if(event.type == SDL_KEYDOWN) {


			if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
				done = true;
				break;
			}

			//collision strategy
			player->setCollisionStrategy(2);

			if (keystate[SDLK_1]) {
				player->setCollisionStrategy(0);
				// std::cout << "1 " << std::endl;  
			}
			if (keystate[SDLK_2]) {
				player->setCollisionStrategy(1);
				//std::cout << "2" << std::endl;  
			}


			if (keystate[SDLK_s] && !keyCatch) {
				keyCatch = true;
				clock.toggleSloMo();
			}
			if (keystate[SDLK_p] && !keyCatch) {
				keyCatch = true;
				if ( clock.isPaused() ) clock.unpause();
				else clock.pause();
			}

			if (keystate[SDLK_F1] && !keyCatch){
				keyCatch = true;
				hudFlag = !hudFlag;
			}

			if (keystate[SDLK_RETURN] && !keyCatch){
				keyCatch = true;
				player->start();
				die=false;

			}

			if (keystate[SDLK_SPACE] && !keyCatch){
				keyCatch = true; 

				player->playershoot();


			}





			if (keystate[SDLK_F4] && !makeVideo) {
				std::cout << "Making video frames" << std::endl;
				makeVideo = true;
			}

			if (keystate[SDLK_RIGHT] && stopRight==false) {

				player->moveForward();
				player->setDirection(string("right"));
			}
			if (keystate[SDLK_LEFT] ) {

				player->moveBack();
				player->setDirection(string("left"));

			}

			if (keystate[SDLK_UP] && !keyCatch) {


				keyCatch = true;

				player->moveUp();
				player->setDirection(string("up"));

			}
			if (keystate[SDLK_DOWN]) {
				player->moveDown();
			}
			
			if (keystate[SDLK_r] && !keyCatch){
				init();
				}
				


		}

		draw();
		update();
	}

}






