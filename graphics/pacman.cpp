/* Revision History

	4/27
	Removing Sprites
		the graphics were having TERRIBLE FPS on linux machines, they work great on mine,
		but everything points to one problem -> textures.
		It's possible that the lack of 3d acceleration is killing the FPS because of the
		rapid swaping of textures, because the player drawing functions don't really do anything
		oh well, back to the drawing board

	4/29
	Moved Skin
		Moved the PacSkin data memeber skin into the parent class of ghost and pacman
		I figured that it would be easier to leave it in pacman, but I forgot to 
		consider the consequences of changing the gender of a player from pacman
		to ghost

  	5/16
	Removed Alpha Testing
		I removed alpha testing today because it wasn't needed.  
		Honestly, I can't remember why I put it in there, I thought it was needed, but it wasn't.
		Blending is enough to lay the pacskin ontop of pacman with transparency.  The alpha function
		just did a crappy job of it so you couldn't even see it.

*/

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "pacman.h"
#include "player.h"
#include "drawableobject.h"

//TODO
//
//find a place to put the PACMAN_SPRITE variable so that it isn't global.
//add an event handler to let the pacman move on it's own between server
//messages

//add additional sprites for Ms Pacman
//she has lips!

//pacman needs a death animation too.  Poor pacman

//this is for the sprites that make up the pacman.
//extern GLuint PACMAN_SPRITE[10];

//draw the pacman and skin
void Pacman::draw(void)
{
	glPushMatrix();


	//move the pacman to the correct spot on the board first.  X and Y should be filled
	//out by messages from the server.
	//can we do this by calling a method from Player?
	Player::draw();




	//rotate the system so that the pacman is facing the right way, James said that
	//West was 1, north 2, east 3 and south 4, up is 5 and down is 6, but they don't
	//matter right here.
	//5 or 6 should never affect the graphics because they cause the pacman to jump
	//to a different level....that's a potential problem

	//we can't use a for loop for it because then pacman goes upsidedown....so here's
	//another set of if's even though I know they're frowned upon :/
	if(getDirection() == 2)
		glRotatef(-90, 0, 0, 1);

	if(getDirection() == 3)
		glScalef(-1, 1, 1);

	if(getDirection() == 4)
		glRotatef(90, 0, 0, 1);


	//move up slightly to get off of the gameboard itself
	//not using a depth buffer anymore
//	glTranslatef(0.0, 0.0, 0.001);


	//now we need to translate the system to the right coords to draw the pacman.
	//this is done by using the coords of the space that the pacman is moving too
	//this space is given by Player::Space * location

	//Space * location is the space that pacman is moving into.  

	//Once Pacman has crossed the midpoint in a space, 
	//location is set to the space that he's moving into

	//so, we need to draw pacman fracdist away from the center of the location Space
	//and pointed in the opposite direction.
	
	//the distance between two Space's is considered to be 1 reguarding fracdist.  

	//get the coords of location.
	//now, BECAUSE we already rotated the system so that the pacman THINKS he's going
	//left reguardless of where he's actually going, we can just translate the system
	//to the right a fractional distance
	
	//subtract (1-fracdist)*the distance between two Space midpoints (6 I think)

	//so translate(-(1-fracdist)*6, 0, 0)
//	glTranslatef(-(1-getFracDist())*6, 0, 0);


	//we might need to scratch all the fracdist stuff....and just use x and y




	//draw the pacman disk here
	GLUquadricObj *quadratic;				// Storage For Our Quadratic Objects
	quadratic=gluNewQuadric();			// Create A Pointer To The Quadric Object 

	GLfloat offset;
	if(numsprite == 0)
		offset = 0;
	else
		offset = numsprite*6;
	
	//turn him yellow
	glColor3f(1, 1, 0);

	//the pacman faces to the right, which is direction 1
	gluPartialDisk(quadratic, 0, 5*getSize()/100, 16, 2, -90+offset, 360-2*offset);

	gluDeleteQuadric(quadratic);

	//turn on alpha blending...
	//this lets us see through the alpha channel previously set up
	//in a texture
	glEnable(GL_BLEND);
//	glEnable(GL_ALPHA_TEST);
	//the bendfunc is what opengl uses to determine what the end color will be to the user
	//here we have the source alpha (the incoming fragment that is)
	//as the alpha that it has, which will be 0 for black
	//and one minus source alpha as the destination, or one minus the existing color data,
	// for the existing color.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//accepts the fragment if fragment alpha is >= reference alpha.
	//in this case, reference alpha is X...almost all the black in 
	//the skin texture is at 0 alpha
	//so this gives us a little antialiasing
//	glAlphaFunc(GL_GEQUAL, .01);


	//draw the pacman sprite of the appropriate animation
	//Image::drawResized(PACMAN_SPRITE[numsprite], getSize()/100, getSize()/100);


	//move the coord system out a little before drawing the skin, this lets us use
	//alpha blending without hassling with the depth buffer
	//it's possible to do both, but what's the point if it's a 2d view
	//this might cause a problem when we switch to orthographic projection
	//and the skin has to be resized....
	//no it won't because the .1 can be .0000001 and still work where the alpha blending
	//is concerned.
	//yea you're right
//	glTranslatef(0.0, 0.0, 0.1);



	if(!isSkinNull())
	{
		GetSkin()->drawResized(getSize()/100, getSize()/100);
	}

//	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
//	glDisable(GL_ALPHA_TEST);


	//if we've reached the last sprite, start reversing them
	if(numsprite == 9)
		opening=false;
	//if this is the closed pacman, go the other way
	if(numsprite == 0)
		opening=true;

	//increment or decrement the pacman sprite to chomp his mouth
	if(opening)
		numsprite+=1;
	else
		numsprite-=1;

	glPopMatrix();
	//needs to be put at the end of changes
	glutPostRedisplay();

}

// Always returns false. This overrides the virtual function 
// isAGhost() in the Player class. 
bool Pacman::isAGhost( void ) {
	return false;
}


// Constructor(s)

Pacman::Pacman(string name, int playerpicid, PacSkin * tex, char* IPaddress)
{
	this->changeName(name);

	SetSkin(tex);
	numsprite = 0;
	opening = true;
	changeSize(100);
	changeDirection(1);
	setScore(0);
	setFracDist(1);
	SetXYZ(0, 0, 0);
}

Pacman::Pacman(void)
{

//	not neccessary to add the pacman yellow underlayed itself, an init function will handle it
//	this->setGraphicsHashID(Image::addImage("pacman.bmp"));
	numsprite = 0;
	opening = true;
	changeSize(100);
	changeDirection(1);
	setScore(0);
	setFracDist(1);
	SetXYZ(0, 0, 0);
}

// Destructor

Pacman::~Pacman ( void ) {
	
}

