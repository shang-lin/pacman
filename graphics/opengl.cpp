/* Revision History

	4/06
	Sleep function
		changed the Sleep(33) functions
		it doesn't compile under linux 
		substituted
			struct timespec to_wait;
			to_wait.tv_sec = 0;
			to_wait.tv_nsec = 33000000; //33 million nanoseconds = 33 milliseconds
			nanosleep(&to_wait,NULL);
		instead of using glTimeDelay, or whatever the OpenGL one is

	4/14
	Chat Window
		added chat window stuff to this main loop.
		Everything, especially player list, still needs to be included
		in the GameBoard class.  Hopefully that won't be too bad.

	Zoom Level
		added the zoom level using CTRL-A and CTRL-Z
		I can't believe that is supported by OpenGL, I certainly didn't find it
		in any of the stupid OpenGL books that I have :/  it's done using a call
		to glutGetModifiers

	4/15 - 
	Platform Independence
		added some define statements that should take care of the Sleep function
		problem across windows and linux, did the same thing for some includes
		for time and sys/time.h

	4/17 -
	Includes
		changed some include files, they didn't work in linux.

	4/27
	Removing Sprites
		the graphics were having TERRIBLE FPS on linux machines, they work great on mine,
		but everything points to one problem -> textures.
		It's possible that the lack of 3d acceleration is killing the FPS because of the
		rapid swaping of textures, because the player drawing functions don't really do anything
		oh well, back to the drawing board

	4/27
	Removing Smoothing
		3 little lines were killing the performance on linux machines in UGCS, they're gone now

	New Graphics
		Got rid of sprites because textures just kill performance on non-hardware
		accelerated machines.  I put in some generic polygons for drawing the ghost
		they're not very good right now, I'll be working on that later though becase
		right now they get the job done.

	5/4
	Removing Depth Testing
		Another time killer is gone, depth testing!!  I had removed depth testing from all of the
		drawing methods, but I hadn't turned it off :/  that's gone now, glTranslatef was changed
		to glScalef and the gluPerspective was changed to a more presentable glOrtho call.
		It seems to be going much much faster now.

  	5/13
	Added Level Drawing
		Added the code for the drawing of a level.  It's too bloated, and there's a lot of
		repetition, but it works, and I didn't want to concentrate on condensing it right now
		especially because in it's current form, it's optimized.  I will be integrating the
		code into the level class when it's ready.


		6/3
		Added a #define _MENU_TEST_MODE_ that calls methods on and sends data
		to the menusystem * ms instead of the playerlist. 
*/
#include <iostream>
#include <string>

#ifndef WIN32
#include <sys/time.h>
#endif

#include "image.h"
#include "text.h"
#include "opengl.h"
#include "playerlist.h"
#include "chatwnd.h"
#include "sidebar.h"


// turns on menu-test compilation mode
//#define _MENU_TEST_MODE_

#ifdef _MENU_TEST_MODE_
	#include "MenuSystem.h"
#endif

//playerlist is global now, but it should be GameBoard
//or Gameclient when this thing is done.
//I just need something to draw right now to test the player objects
extern PlayerList playerlist;


#ifdef _MENU_TEST_MODE_
	extern MenuSystem * ms;
#endif

//temp level stuff

#ifdef WIN32
bool level[17][7] =
{
	{0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 0},
	{0, 0, 1, 0, 0, 1, 0},
	{0, 0, 1, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0}
};
int length = 7;
int height = 17;
void DrawLevel();
#endif

//this is global now, it should be moved with playerlist into the GameBoard object...
ChatWnd chatwnd;
SideBar sidebar(&playerlist);
extern int myID;

//this is global now, it should be moved with playerlist into the GameBoard object...
GLfloat zoomlevel = .5;

//TODO

//add the sidebar and chat window code elsewhere.  They need the orthogonal matrix
//make sure you remember that!

//make the window full sized in the setup and resize function
//add the code to prevent everything from being scaled by a rectangular window!!

//add a remove texture function

//take out GL_PROJECTIONS?

//eliminate all depth fucntions

//add semaphores to limit accessing of the playerlist...?


//the main rendering function for opengl.
//this function should be kept as sparse as possible, because ALL
//the drawing should be done in the individual draw methods of all the nouns
//or objects on screen
void RenderScene()
{
	//sleep to synchronize the clients and server...this should
	//take much more than the processing time of the rendering
	//
	// NOTE: this function seems to only work in windows. i'm 
	// commenting it out to test the graphics code.
	
#ifdef WIN32
	Sleep(33);
#endif

#ifndef WIN32

	struct timespec to_wait;
	to_wait.tv_sec = 0;
	to_wait.tv_nsec = 33000000; //33 million nanoseconds = 33 milliseconds
	nanosleep(&to_wait,NULL);

#endif

	//clear the system
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);


	//activate the model view matrix, change this to the ortho matrix to render
	//the sidebar and chat window
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//save the base state
	glPushMatrix();


//	move the entire system to the place where this player's character is
//	the upper left space is at 0, 0.  I think, and the system goes
//	down and right from there in increments detailed in the draw level function
//	use that to determine where they go based on what space they're in, and their
//	fractional distance...
//	This section actually needs to be fairly substantial because the system
//	should appear to move around pacman, and not pacman moving around inside the system

	//move over to give the sidebar room
	//no need to do this...
//	glTranslatef(-10, 0, 0);


//	glTranslatef(0, 0, zoomlevel);//move out to get a better view
	glScalef(zoomlevel, zoomlevel, 1);
	glColor4f(1, 1, 1, 1);



#ifdef WIN32
	//this should be changed to GameClient, or GameBoard.draw().
	//this is just a place holder
	DrawLevel();
#endif

#ifndef _MENU_TEST_MODE_
	playerlist.draw();
//	chatwnd.addMessage("hello");
	chatwnd.draw();
	sidebar.draw();
#endif
#ifdef _MENU_TEST_MODE_
	ms->draw();
#endif

//	int key = Image::addImage("pacskin2.bmp");
//	Image::drawResized(key, 2.5, 1);
//	Image::drawPortion(key, .2, .2, .5, .2);

	glColor3f(1, 1, 1);
	//this works, it should be moved elsewhere...try to have no drawing actually done on this page
//	Text::print("some text for you.");

	glPopMatrix();

	glutSwapBuffers();

	//just screwing around here to test fracdist
//	playerlist.getPlayer(myID)->setFracDist(playerlist.getPlayer(myID)->getFracDist()+.05);
}

//OpenGL setup function, I don't think the SMOOTH Enables actually do anything
//but who am I to argue
void SetupRC()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//glEnable(GL_DEPTH_TEST);

	//these were killing the performance on UGCS
	//glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);

}

//handles the window function
//remember to make it full size in the final version
void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//a very interesting function, much easier than doing aspect ratios by hand
//	gluPerspective(50.0, (GLfloat)w/(GLfloat)h, 1.0, 800.0);

	//took perspective out because this is faster...

	if(w<=h)
		glOrtho(-50.0, 50.0, -50.0*h/w, 50.0*h/w, -1.0, 1.0);
	else
		glOrtho(-50.0*w/h, 50.0*w/h, -50.0, 50.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



#ifdef WIN32
//temp draw level
//put this into the draw function in the level class
//pacman's size is 10
void DrawLevel(void)
{
	//before the level draws itself, it has to move to the space that pacman is in
	//this player's pacman should always be in the center of the screen.



	//set the cool blue for the walls
	glColor3f(0, 0, 1);

	//with GL_LINES, lines are given in sets of pairs
	glBegin(GL_LINES);


	//DO THE TOP LINES
	for(int j=0; j<height; j++)
	{
		for(int i=0; i<length; i++)
		{
			//dot placeholders
//			glVertex2f(i*6, -j*6);
//			glVertex2f(i*6+1, -j*6);

			if(level[j][i] && ( j == 0 || j == height - 1 || i == 0 || i == length - 1 ) )
			{
				//needs special processing, it's a wrap around tunnel
			}
			else if(level[j][i] && !level[j-1][i]) //if there isn't one above it
			{
				if(!level[j][i-1]) //there's no neighbor to the left
				{
					//draw 1 and 2
					glVertex2f(i*6-6, -j*6+6);
					glVertex2f(i*6, -j*6+6);
				}
				else if(!level[j-1][i-1]) //the left neighbor has no neighbor above it
				{
					//draw 2
					glVertex2f(i*6-3, -j*6+6);
					glVertex2f(i*6, -j*6+6);
				}

				if(!level[j][i+1]) //there's no neighbor to the right
				{
					//draw 3 and 4
					glVertex2f(i*6, -j*6+6);
					glVertex2f(i*6+6, -j*6+6);
				}
				else if(!level[j-1][i+1]) //the right neighbor has no neighbor above it
				{
					//draw 3
					glVertex2f(i*6, -j*6+6);
					glVertex2f(i*6+3, -j*6+6);
				}
			}
		}
	}


	//do the right side
	for(j=0; j<height; j++)
	{
		for(int i=0; i<length; i++)
		{
			if(level[j][i] && ( j == 0 || j == height - 1 || i == 0 || i == length - 1 ) )
			{
				//needs special processing, it's a wrap around tunnel
			}
			else if(level[j][i] && !level[j][i+1]) //if there isn't a space to the right of it
			{
				if(!level[j-1][i]) //there's no neighbor above it, draw a wall on the right
				{
					//draw 1 and 2
					glVertex2f(i*6+6, -j*6+6);
					glVertex2f(i*6+6, -j*6);
				}
				else if(!level[j-1][i+1]) //the above neighbor has no neighbor to it's right
				{
					//draw 2
					glVertex2f(i*6+6, -j*6+3);
					glVertex2f(i*6+6, -j*6);
				}

				if(!level[j+1][i]) //there's no neighbor below it
				{
					//draw 3 and 4
					glVertex2f(i*6+6, -j*6);
					glVertex2f(i*6+6, -j*6-6);
				}
				else if(!level[j+1][i+1]) //the below neighbor has no neighbor to it's right
				{
					//draw 3
					glVertex2f(i*6+6, -j*6);
					glVertex2f(i*6+6, -j*6-3);
				}
			}
		}
	}

	//do the left side
	for(j=0; j<height; j++)
	{
		for(int i=0; i<length; i++)
		{
			if(level[j][i] && ( j == 0 || j == height - 1 || i == 0 || i == length - 1 ) )
			{
				//needs special processing, it's a wrap around tunnel
			}
			else if(level[j][i] && !level[j][i-1]) //if there isn't a space to the left of it
			{
				if(!level[j-1][i]) //there's no neighbor above it, draw a wall on the left
				{
					//draw 1 and 2
					glVertex2f(i*6-6, -j*6+6);
					glVertex2f(i*6-6, -j*6);
				}
				else if(!level[j-1][i-1]) //the above neighbor has no neighbor to it's left
				{
					//draw 2
					glVertex2f(i*6-6, -j*6+3);
					glVertex2f(i*6-6, -j*6);
				}

				if(!level[j+1][i]) //there's no neighbor below it
				{
					//draw 3 and 4
					glVertex2f(i*6-6, -j*6);
					glVertex2f(i*6-6, -j*6-6);
				}
				else if(!level[j+1][i-1]) //the below neighbor has no neighbor to it's left
				{
					//draw 3
					glVertex2f(i*6-6, -j*6);
					glVertex2f(i*6-6, -j*6-3);
				}
			}
		}
	}


	//do the bottom side
	for(j=0; j<height; j++)
	{
		for(int i=0; i<length; i++)
		{
			if(level[j][i] && ( j == 0 || j == height - 1 || i == 0 || i == length - 1 ) )
			{
				//needs special processing, it's a wrap around tunnel
			}
			else if(level[j][i] && !level[j+1][i]) //if there isn't one below it
			{
				if(!level[j][i-1]) //there's no neighbor to the left
				{
					//draw 1 and 2
					glVertex2f(i*6-6, -j*6-6);
					glVertex2f(i*6, -j*6-6);
				}
				else if(!level[j+1][i-1]) //the left neighbor has no neighbor below it
				{
					//draw 2
					glVertex2f(i*6-3, -j*6-6);
					glVertex2f(i*6, -j*6-6);
				}

				if(!level[j][i+1]) //there's no neighbor to the right
				{
					//draw 3 and 4
					glVertex2f(i*6, -j*6-6);
					glVertex2f(i*6+6, -j*6-6);
				}
				else if(!level[j+1][i+1]) //the right neighbor has no neighbor below it
				{
					//draw 3
					glVertex2f(i*6, -j*6-6);
					glVertex2f(i*6+3, -j*6-6);
				}
			}
		}
	}

	glEnd();

}
#endif


//this is a pretty lame key catching process as described by one of the groups
//in the last presentations, but it make be perfect for what we're doing, because
//the length of time that you hold the key down doesn't matter in pacman
//this works using keyboard messages, which are generated once, and then are generated
//continuously after a certain time has elapsed.
//if a different key is pressed, one new message is sent immediately.
//this may be a problem however if it doesn't account for multiple keys at a time
//but I don't know how to get the SHORT AsyncKeyState() in linux....
void SpecialKeyEvent(int key, int x, int y)
{
#ifdef _MENU_TEST_MODE_
	ms->specialKey (key, x, y);
#else
	switch(key)
	{
	case GLUT_KEY_DOWN:
		playerlist.getPlayer(myID)->changeDirection(4);
		theGame->requestMove(4);
		break;
	case GLUT_KEY_RIGHT:
		playerlist.getPlayer(myID)->changeDirection(3);
		theGame->requestMove(3);
		break;
	case GLUT_KEY_UP:
		playerlist.getPlayer(myID)->changeDirection(2);
		theGame->requestMove(2);
		break;
	case GLUT_KEY_LEFT:
		playerlist.getPlayer(myID)->changeDirection(1);
		theGame->requestMove(1);
		break;
	case GLUT_KEY_PAGE_UP:
		playerlist.getPlayer(myID)->changeDirection(5);
		theGame->requestMove(5);
		break;
	case GLUT_KEY_PAGE_DOWN:
		playerlist.getPlayer(myID)->changeDirection(6);
		theGame->requestMove(6);
		break;

	default:
		break;
	}
#endif
	//very important to PostRedisplay after a change in the graphics that's outside the main thread.
	glutPostRedisplay();
}

//this is a pretty lame key catching process as described by one of the groups
//in the last presentations, but it make be perfect for what we're doing, because
//the length of time that you hold the key down doesn't matter in pacman
//this works using keyboard messages, which are generated once, and then are generated
//continuously after a certain time has elapsed.
//if a different key is pressed, one new message is sent immediately.
//this may be a problem however if it doesn't account for multiple keys at a time
//but I don't know how to get the SHORT AsyncKeyState() in linux....
//key even is only used for chat too.....and zooming and music....
void KeyEvent(unsigned char key, int x, int y)
{
#ifdef _MENU_TEST_MODE_
	ms->regularKey (key, x, y);
#else
	string message;

	switch(key)
	{
	//the backspace key gumshoe
	case 0x08:  
		chatwnd.deleteChar();
		break;
	//the enter key
	case 0x0d:
		message = chatwnd.getString();
		//send message using the network here
		break;

	//all key inputs should go to the chat window...
	default:
		//this will have to be changed to support GameBoard
		chatwnd.addChar(key);
	}

	//this function is really pretty sweet....it's glut's little way
	//of catching ctrl, shift and alt, it took my forever to find!!!
	//******important note:
	//for some reason, a is 1 when it's attached to ctrl, and 97 when 
	//ctrl is not held down....I have no idea why!
	if(glutGetModifiers() == GLUT_ACTIVE_CTRL && key == 1)
	{
		//time to zoom out
		zoomlevel*=.95;
	}
	if(glutGetModifiers() == GLUT_ACTIVE_CTRL && key == 26)
	{
		//time to zoom in
		if(zoomlevel<.5)
		{
			zoomlevel*=1.05;
		}
	}
#endif

	glutPostRedisplay();
}

//use this function to set up OpenGL
void OpenGL::InitializeOpenGL()
{
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#ifndef __APPLE__
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(700, 700);
#endif
#ifdef __APPLE__
	glutInit(NULL, 0);										
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
#endif	
	glutCreateWindow("MIP");

	SetupRC();

	//this needs to be changed to use the glTimeDelayFunc() declaration.
	//I think it takes 2 parameters.  a void * for the function to call
	//and an int for the amount of time to wait before calling it
	//it'll work cross platform
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);

	//declaration of keyboard handlers..
	//may need to be changed, see above explanations
	glutKeyboardFunc(KeyEvent);
	glutSpecialFunc(SpecialKeyEvent);
}

void OpenGL::StartMainLoop()
{
	//this needs to be changed to use the glTimeDelayFunc() declaration.
	//I think it takes 2 parameters.  a void * for the function to call
	//and an int for the amount of time to wait before calling it
	//it'll work cross platform
	glutMainLoop();
}


//function of the OpenGL class that adds the texture into memory using the
//glBindTexture function.
//this method has an opposite removeBitmap method, but it is not implemented yet
GLuint OpenGL::AddBitmap(BITMAPINFO *TexInfo, GLubyte *TexBits, bool blackclear)
{
	//this will hold the texture ID
	//we want to make one texture at a time
	GLuint newtexture[1];
	newtexture[0] = 42;
	glGenTextures(1, &newtexture[0]); //generate the texture's ID

	//if this is the first one, we need to allocate some space for it
	if(numtextures == 0)
	{
		texture_objects=(GLuint*)malloc(sizeof(GLuint));
		texture_objects[0]=newtexture[0];
	}

	//BindTexture is an OpenGL API function, and it's very confusing :/
	//too much so to go into detail here.
    glBindTexture(GL_TEXTURE_2D, newtexture[0]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//if the black is clear then the channel has an alpha layer
	//if we add support for pictures with alpha channels already then this variable should
	//be changed to alphaexists or something like that because this is misleading
	if(blackclear)
	{
		glTexImage2D (GL_TEXTURE_2D, 0, 4, TexInfo->bmiHeader.biWidth, TexInfo->bmiHeader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, TexBits);
	}
	//if the black isn't cleared, then the bmp has no alpha channel
	//again, this variable needs to be changed if we support images that inheirently
	//have an alpha channel
	else
	{
		glTexImage2D (GL_TEXTURE_2D, 0, 3, TexInfo->bmiHeader.biWidth, TexInfo->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	}

	return newtexture[0];
}

/*
//initialise the ghost and pacman sprites for animation
//we will probably also need a Ms Pacman sprite because of her lips :/
//this must only be called AFTER OpenGL has initialized.
//OpenGL is initialized in the constructor
bool InitializeSprites(void)
{
	for(int i=0; i<10; i++)
	{
		char * filename;
		filename=(char*)malloc(sizeof(char)*256);

		sprintf(filename, "pacman%i.bmp", i);

		PACMAN_SPRITE[i] = Image::addImage(filename, true);

		free(filename);
	}

	GHOST_SPRITE[0] = Image::addImage("ghost0.bmp", true);
	GHOST_SPRITE[1] = Image::addImage("ghost1.bmp", true);

	return 1;
}
*/

//simple constructor.
OpenGL::OpenGL(void)
{
	InitializeOpenGL();
	//can't use sprites so liberally anymore
//	InitializeSprites();
}
