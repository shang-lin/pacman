/* Revision History

  4/27
	Removing Sprites
		the graphics were having TERRIBLE FPS on linux machines, they work great on mine,
		but everything points to one problem -> textures.
		It's possible that the lack of 3d acceleration is killing the FPS because of the
		rapid swaping of textures, because the player drawing functions don't really do anything
		oh well, back to the drawing board

*/

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "ghost.h"
#include "player.h"
#include "drawableobject.h"


//TODO
//
//find a place to put the GHOST_SPRITE variable so that it isn't global.
//add an event handler to let the ghost move and add functions to make
//it able to interpret it's next move based on the pacmen's positions
//and the game board.

//add additional sprites for the other ghosts and the eye positions
// the ghosts always look where they're going to turn?  --check on that!


//this is for the sprites that make up the ghost.
//this array should be reduced to 2 or something
//because the ghost moves much too fast right now
//I'll have to wait a while to do so, because we don't know how
//large of a time delay we need to make the game run smoothly.
//extern GLuint GHOST_SPRITE[10];


//draw the ghost
void Ghost::draw(void)
{
	glPushMatrix();


	//move the ghost to the correct spot on the board first.  X and Y should be filled
	//out by messages from the server.
	//can we do this by calling a method from Player?
	Player::draw();



	//move the ghosts on top of the pacmen beacuse that's how the game is
	//this should be taken out because we are turning OFF depth buffering
//	glTranslatef(0.0, 0.0, 0.02);

	//pick the ghost's colour here
	GLubyte red = (color&0xFF0000)>>16;

	GLubyte green = (color&0x00FF00)>>8;

	GLubyte blue= color&0x0000FF;
	
	if(!isEdible())
	{
		glColor3ub(red, green, blue);
	}
	else
	{
		if(numsprite < 10)
		{
			glColor3f(0, 0, .9);
		}
		else
		{
			glColor3f(1, 1, 1);
		}
	}

	//5*getSize()/100 for radius pacman
	GLfloat scaler = getSize()/100;

	//draw the ghost
	glBegin(GL_POLYGON);
		glVertex3f(-5*scaler, 0, 0); //left side start of dome
		glVertex3f(-3.3*scaler, 4*scaler, 0);
		glVertex3f(0, 5*scaler, 0); //top of dome
		glVertex3f(3.3*scaler, 4*scaler, 0);
		glVertex3f(5*scaler, 0, 0); //right side start of dome

		if(numsprite < 10)
		{

			glVertex3f(5*scaler, -5*scaler, 0);
			glVertex3f(3.3*scaler, -4*scaler, 0);
			glVertex3f(1*scaler, -5*scaler, 0);

			glVertex3f(0, -4*scaler, 0); //middle bottom
			
			glVertex3f(-1*scaler, -5*scaler, 0);
			glVertex3f(-3.3*scaler, -4*scaler, 0);
			glVertex3f(-5*scaler, -5*scaler, 0);
		}

		else
		{
			glVertex3f(5*scaler, -4*scaler, 0);
			glVertex3f(3.3*scaler, -5*scaler, 0);
			glVertex3f(1*scaler, -4*scaler, 0);

			glVertex3f(0, -5*scaler, 0); //middle bottom
			
			glVertex3f(-1*scaler, -4*scaler, 0);
			glVertex3f(-3.3*scaler, -5*scaler, 0);
			glVertex3f(-5*scaler, -4*scaler, 0);
		}

	glEnd();


	//turn on alpha blending...
	//this lets us see through the alpha channel previously set up
	//in a texture
//	glEnable(GL_BLEND);
//	glEnable(GL_ALPHA_TEST);

	//the bendfunc is what opengl uses to determine what the end color will be to the user
	//here we have the source alpha (the incoming fragment that is)
	//as the alpha that it has, which will be 0 for black
	//and one minus source alpha as the destination, or one minus the existing color data,
	// for the existing color.
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//accepts the fragment if fragment alpha is >= reference alpha.
	//in this case, reference alpha is .9, which is very large...almost all the black in 
	//the skin texture is at 0 alpha
	//so this gives us a little antialiasing
//	glAlphaFunc(GL_GEQUAL, .6);


	//draw the ghost sprite of the appropriate animation
//	Image::drawResized(GHOST_SPRITE[numsprite], getSize()/100, getSize()/100);


//	glDisable(GL_TEXTURE_2D);
//	glDisable(GL_BLEND);
//	glDisable(GL_ALPHA_TEST);


	numsprite++;
	if(numsprite == 20)
		numsprite = 0;

	glPopMatrix();

	//needs to be put at the end of changes
	glutPostRedisplay();


}

//get the ghost's colour
int Ghost::getColor(void)
{
	return color;
}

void Ghost::setColor(int newcolor)
{
	color = newcolor;
}

void Ghost::setEdible(void)
{
	edible = true;
}

void Ghost::resetEdible(void)
{
	edible = false;
}

// Always returns true. This overrides the virtual function isAGhost() 
// in the Player class. 
bool Ghost::isAGhost( void ) 
{
	return true;
}

// Constructor(s)
Ghost::Ghost(string name, int playerpicid, int newcolor, char* IPaddress)
{
	changeName(name);

	color = newcolor;
	numsprite = 0;
	changeSize(100);
	changeDirection(1);
	setScore(0);
	setFracDist(1);
	SetXYZ(0, 0, 0);
	resetEdible();
}

Ghost::Ghost(void)
{
	color = 0;
	numsprite = 0;
	changeSize(100);
	changeDirection(1);
	setScore(0);
	setFracDist(1);
	SetXYZ(0, 0, 0);
	resetEdible();

}

// Destructor

Ghost::~Ghost ( void ) 
{
	
}

