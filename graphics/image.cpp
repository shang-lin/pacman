/* Revision History

	5/4
	MODULATE and REPLACE
		we don't need to vary the color of the textures anymore, so I changed all the
		GL_MODULATE's to GL_REPLACE.  We needed to change texture colors because
		pacman's color is variable, now that can be done with a simple glColor call.
*/

#include <iostream>
#include <string>
#include "image.h"

//the global OpenGL object
//it's likely that this will stay global, because everything needs access to it
//it runs in it's own thread too, so we don't want the graphics thread dependent 
//on any of the Model data.
extern OpenGL opengl;

//TODO
//this class needs better error handling
//I'm waiting on the file exception class and exception class to do this

//add support for other images, like jpg, or tga?
//this is in our specs, but is kind of a low priority.
//everything can be put into bmp and I'd rather see the game work than
//look for jpg or tga loading code

// Description:
//
// This static object allows you to draw the OpenGL texture with 
// key ImageID onto the screen as a sprite. 
//this class looks significantly different from out OOA/OOD specs because
// a lot of it's functions were redundant, ie, the draw scaled and draw resized 
// functions are the same commands in OpenGL.  I have additionally added a 
// function that allows the display of partial textures, because textures must
// be 2^n in width and height in order to be displayed.  And the end display
//will not always be a square

//LoadRGBA is a function that gives a bitmap an alpha channel
//OpenGL would not work in a 2D environment using textures without this function
//it turns all black pixels into transparent pixels when blending is enabled
GLubyte * LoadRGBA(const char *filename, BITMAPINFO **info)
{
    GLubyte    *bgr; //BGR bitmap data 
    GLubyte    *rgba; //RGBA bitmap data 
    int        x, y; //Looping vars 
    int        length; //Length of scanline 
    GLubyte    *bgr_ptr; //Pointer into BGR data 
    GLubyte    *rgba_ptr; //Pointer into RGBA data

	//call the load function from the existing bitmap loader code
    bgr    = LoadDIBitmap(filename, info);

	//we meed to adjust the size of the buffer to account for the extra channel
    rgba   = (unsigned char*)malloc((*info)->bmiHeader.biWidth * (*info)->bmiHeader.biHeight * 4);
    length = ((*info)->bmiHeader.biWidth * 3 + 3) & ~3;

	//loop through the pixels and determine the alpha transparency of the pixel by the colour itself
    for (y = 0; y < (*info)->bmiHeader.biHeight; y ++)
	{
        bgr_ptr  = bgr + y * length;
        rgba_ptr = rgba + y * (*info)->bmiHeader.biWidth * 4;

        for (x = 0; x < (*info)->bmiHeader.biWidth; x ++, bgr_ptr += 3, rgba_ptr += 4)
        {
            rgba_ptr[0] = bgr_ptr[2];
            rgba_ptr[1] = bgr_ptr[1];
            rgba_ptr[2] = bgr_ptr[0];

			//here we are using a color value of less than 20 as the transparent channels
			//and they will have a varying alpha channel, which we can account
			//for while blending
			if(bgr_ptr[0] + bgr_ptr[1] + bgr_ptr[2] < 20)
				rgba_ptr[3] = bgr_ptr[0] + bgr_ptr[1] + bgr_ptr[2];
			else
				//if the bitmap has a color value greater than 20, we give it full
				//opacity.  Note that with UINTs, 255 is the highest
				rgba_ptr[3] = 255;

		}
    }
    free(bgr);
    return (rgba);
}

// adds an image to the OpenGL image hash and returns it's Texture ID. 
int Image::addImage(string filename, bool blackclear)
{
	int key;

	if(filename.rfind(".bmp")) //we are dealing with a bitmap, so load it.
	{
		//if this needs to be a texture that has invisible parts, do so
		//we will use this for player textures and item textures
		if(blackclear)  //turn the alpha channel of the pic to 0 for black
		{
			BITMAPINFO *TexInfo;
			GLubyte * TexBits;
			TexBits = LoadRGBA(filename.c_str(), &TexInfo);

//			cerr << "TexInfo is " << TexInfo << "\n";
//			cerr << "TexBits is " << TexBits << "\n";
			key = opengl.AddBitmap(TexInfo, TexBits, blackclear);
			free(TexBits);
			free(TexInfo);
		}

		//if black is opaque, load it the regular way
		//use this for pictures of the players themselves, and the game board
		else
		{
			BITMAPINFO *TexInfo;
			GLubyte * TexBits;
		    TexBits = LoadDIBitmap(filename.data(), &TexInfo);

//			cerr << "TexInfo is " << TexInfo << "\n";
//			cerr << "TexBits is " << TexBits << "\n";
			key = opengl.AddBitmap(TexInfo, TexBits);
			free(TexBits);
			free(TexInfo);
		}
	}
	return key;
}

// Calls the standard draw function with coordinates ( 0, 0 ).
//move the coordinate system before calling this method with glTranslatef(x, y, z);
void Image::draw(int ImageID, GLfloat width, GLfloat height)
{
	//just call the drawPortion with 0's all around
	//saves some code here, and there's only one place to change
	//it if we need to change the draw function or add a new parameter
	Image::drawPortion(ImageID, 0, 0, 0, 0, width, height); 

}

// Draws the image at ( 0, 0 ), with its width and 
// height scaled to the given values. 
// pass in the width and height values as 1 is normal
void Image::drawResized(int ImageID, GLfloat widthscaler, GLfloat heightscaler,
						GLfloat width, GLfloat height)
{
	glPushMatrix();
	glScalef(widthscaler, heightscaler, 0);
	Image::draw(ImageID, width, height);
	glPopMatrix();
}

// Draws a portion of the image at ( 0, 0 ), with its width and 
// height equal to the values given. 
// the indent values are 0.0 - 1.0 and represent the amount you want to indent the texture
// from the left side, right side, top and bottom
//if the drawing code needs to be changed.  This function will do it
void Image::drawPortion (int ImageID, GLfloat leftindent, GLfloat rightindent, 
						 GLfloat topindent, GLfloat bottomindent, GLfloat width, GLfloat height)
{
	//if texturing is turned on currently, we should mess with it by turning it off
	bool turnofftex=false;

	//if texturing is turned on
	if(!glIsEnabled(GL_TEXTURE_2D)) 
	{
		turnofftex=true;
	    glEnable(GL_TEXTURE_2D); //enable texture mapping
	}

	//bind the passed in texture to the current system
    glBindTexture(GL_TEXTURE_2D, ImageID);

	//set the texture mode.  This only needs to be done in the beginning,
	//but something might reset it, so we might as well do it everytime
	//unless speed starts to become an issue
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//set up sprite width and height
	GLfloat spritew, spriteh;
	spritew = width/2;
	spriteh = height/2;

	//draw the sprite
    glBegin (GL_QUADS);
        glTexCoord2f (leftindent ,bottomindent); //lower left 
        glVertex3f (-spritew, -spriteh, 0);
        glTexCoord2f ((1.0f-rightindent), bottomindent); //lower right
        glVertex3f (spritew, -spriteh, -0);
        glTexCoord2f ((1.0f-rightindent), (1.0f-topindent)); //upper right 
        glVertex3f (spritew, spriteh, 0);
        glTexCoord2f (leftindent, (1.0f-topindent)); //upper left
        glVertex3f (-spritew, spriteh, -0);
    glEnd ();

	if(turnofftex)
	{
		glDisable(GL_TEXTURE_2D);
	}
}


