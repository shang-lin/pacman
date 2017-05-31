CFLAGS = -I/usr/X11R6/include
LFLAGS = -L/usr/X11R6/lib -lglut -lGL -lGLU -lXmu -lXext -lXi -lX11 -lm

#all : General \
#			Network \
#      GameServer

#General :
#	make -C general

#Network :
#	make -C network/

#GameServer : 
#	make -C game_server/

#analyz_c : analyz_c.c
#	c++ -o analyz_c analyz_c.c -ansi -w

all : Final \
	Final
Final :
	make -C final
	mv final/console_server ./
	mv final/console_client ./
	mv final/tester ./
	mv final/servtest ./

clean:
	rm final/*.o
