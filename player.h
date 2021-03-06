//**********************************************************
// File: player.h
// Desc: The class for the player and all of the operations
//          on the player. This is the class that is used
//          for actually playing the game
//**********************************************************

#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "block.h"
#include "sound.h"
#include <QPixmap>

class Player : public Entity {
    bool jumpKeyPressed;		  //Whether or not the up/w key is pressed
	bool jumping;				  //Whether or not the player is jumping or falling
    bool left, right;			  //Whether or not the left or right key is pressed
    int hSpeed;					  //The player's velocity
    int vSpeed;					  //The player's vertical speed
    int jumpHeight, maxVSpeed;    //Maximum jump height and vertical speed
    int jumpDistance;			  //The current distance the player has jumped
	int jumpSpeed;				  //The speed of a jump
    int dir;					  //The direction the player is currently facing
    bool dead;
    bool cheat;
    bool touched;
    bool vibrate;
    bool invincible;
    bool bullet;
    int times;
    int reload;

    QPixmap pLeft;                //The image for facing left
    QPixmap pRight;               //The image for facing right

public:
    //Creates the player at a certain position
    //<initLevel> The level that the entity is inside
    //<initX> The starting x position of the exit
    //<initY> The starting y position of the exit
    Player(Level* initLevel, int initX, int initY);

    //Destructor for player
    ~Player() { }

    //Updates the player - all of the code for movement and such
    void update();

    //save the status of the player entity
    void savePosition(QTextStream &out);

    //Clears the input flags of the user, such as
    //left, right, and jumpKeyPressed
    void clearFlags();

    //Setters
    void setRight(bool newRight) { right = newRight; }
    void setLeft(bool newLeft) { left = newLeft; }
    void setJumping(bool newJumping) { jumpKeyPressed = newJumping; }
	void setDir(int newDir) { dir = newDir; }
    void setDead(bool isDead) { dead = isDead; Sound::instance().dead();}
    void setCheatJumpHeight();
    void setVib(bool v){vibrate = v; times = 0;}
    void setBullet(bool b){bullet = b; if(b)reload = 20;}

	//Getters
	int getDir() { return dir; }
    bool getVib(){return vibrate;}
    bool hasBullet(){return bullet;}
    bool isDead() { return dead; }
    bool isInvincible() { return invincible; }
};

#endif // PLAYER_H
