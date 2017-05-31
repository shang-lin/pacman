CFLAGS = -g -I/usr/X11R6/include
#LFLAGS = -g -L/usr/ug/lib -L/usr/X11R6/lib -lglut -lGL -lGLU -lXmu -lXext -lXi -lX11 -lm -lvorbis -lvorbisfile -logg -lao -lpthread -ldl
LFLAGS = -g -L/opt/X11/lib -lglut -lGL -lGLU -lXmu -lXext -lXi -lX11 -lm -lpthread -ldl

COMP=g++

OBJFILES= opengl.o \
					bitmap.o \
					image.o \
					text.o \
					playerlist.o \
					player.o \
					pacman.o \
					ghost.o \
					pacskin.o \
					chatwnd.o \
					sidebar.o \
					buttonwidget.o \
					labelwidget.o \
					event.o \
					textinputwidget.o \
					scrollingwidget.o \
					radiowidget.o \
					sliderwidget.o \
					menuwidget.o \
					menusystem.o \
					servermenusystem.o \
					clientmenusystem.o \
					menupane.o \
					drawableobject.o \
          network.o \
          NetworkException.o \
          TCP.o \
          TCPServer.o \
          UDP.o \
          UDPacket.o \
					RUDP.o \
					ComTracker.o \
					FileException.o \
					Space.o \
					Level.o \
					Exception.o \
					BaseItem.o \
					Pellet.o \
					PowerPellet.o \
					AIRules.o \
					AIGhost.o \
					BaseItem.o \
					GameBoard.o \
					GameClient.o \
					GameMechanicsRules.o \
					GameRules.o \
					GameServer.o \
					ServerGameboard.o

#all : servtest tester console_server console_client $(OBJFILES)
all : servtest tester console_server $(OBJFILES)


# Applications using the object files

pacman_client : console_client \
					client_test.o \
				 cliopengl.o \
				 bitmap.o \
				 image.o \
				 text.o \
					buttonwidget.o \
					labelwidget.o \
					textinputwidget.o \
					baseitem.o \
					scrollingwidget.o \
					radiowidget.o \
					sliderwidget.o \
					event.o \
					menupane.o \
					menuwidget.o \
					playerlist.o \
					servermenusystem.o \
					clientmenusystem.o \
					menusystem.o \
					player.o \
					pacman.o \
          network.o \
          NetworkException.o \
          TCP.o \
          TCPServer.o \
          UDP.o \
          UDPacket.o \
					RUDP.o \
					genlevel.o \
					ComTracker.o \
					FileException.o \
					Space.o \
					Level.o \
					Exception.o \
					ghost.o \
					pacskin.o \
					chatwnd.o \
					sidebar.o \
				 drawableobject.o
	$(COMP) $(LFLAGS) \
		client_test.o \
		cliopengl.o \
		bitmap.o \
		image.o \
		text.o \
		event.o \
		buttonwidget.o \
		labelwidget.o \
		baseitem.o \
		textinputwidget.o \
		scrollingwidget.o \
		radiowidget.o \
		sliderwidget.o \
		menuwidget.o \
		menusystem.o \
		menupane.o \
		playerlist.o \
		servermenusystem.o \
		clientmenusystem.o \
		player.o \
		network.o \
		NetworkException.o \
		TCP.o \
		TCPServer.o \
		UDP.o \
		UDPacket.o \
		RUDP.o \
		ComTracker.o \
		FileException.o \
		Space.o \
		Level.o \
		genlevel.o \
		Exception.o \
		pacman.o \
		ghost.o \
		pacskin.o \
		chatwnd.o \
		sidebar.o \
		drawableobject.o \
		-o pacman_client

console_server : ConsoleServer.o \
								 Exception.o \
								 network.o \
								 NetworkException.o \
								 TCP.o \
								 TCPServer.o \
								 UDP.o \
								 UDPacket.o \
								 RUDP.o \
								 ComTracker.o \
								 playerlist.o \
								 player.o \
								 pacman.o \
								 ghost.o \
								 pacskin.o \
								 sidebar.o \
								 chatwnd.o \
								 image.o \
								 text.o \
								 opengl.o \
								 bitmap.o \
								 drawableobject.o \
								 BaseItem.o \
								 Level.o \
								 Space.o \
								 BFS.o \
								 genlevel.o \
								 FileException.o
	$(COMP) $(LFLAGS) ConsoleServer.o \
		Exception.o \
		network.o \
		NetworkException.o \
		TCP.o \
		TCPServer.o \
		UDP.o \
		UDPacket.o \
		RUDP.o \
		ComTracker.o \
		playerlist.o \
		player.o \
		pacman.o \
		ghost.o \
		pacskin.o \
		sidebar.o \
		chatwnd.o \
		image.o \
		text.o \
		opengl.o \
		bitmap.o \
		drawableobject.o \
		BaseItem.o \
		Level.o \
		Space.o \
		BFS.o \
		genlevel.o \
		FileException.o \
		-o console_server

console_client : ConsoleClient.o \
								 Exception.o \
								 network.o \
								 NetworkException.o \
								 TCP.o \
								 TCPServer.o \
								 UDP.o \
								 UDPacket.o \
								 RUDP.o \
								 ComTracker.o \
									buttonwidget.o \
									labelwidget.o \
									event.o \
									textinputwidget.o \
									scrollingwidget.o \
									radiowidget.o \
									sliderwidget.o \
									menuwidget.o \
									menusystem.o \
									servermenusystem.o \
									clientmenusystem.o \
									menupane.o \
								 playerlist.o \
								 player.o \
								 pacman.o \
								 ghost.o \
								 pacskin.o \
								 sidebar.o \
								 chatwnd.o \
								 image.o \
								 text.o \
								 opengl.o \
								 bitmap.o \
								 drawableobject.o \
								 Level.o \
								 Space.o \
								 BFS.o \
								 BaseItem.o \
								 genlevel.o \
								 FileException.o
	$(COMP) $(LFLAGS) ConsoleClient.o \
		Exception.o \
		network.o \
		NetworkException.o \
		TCP.o \
		TCPServer.o \
		UDP.o \
		UDPacket.o \
		RUDP.o \
		ComTracker.o \
		playerlist.o \
		player.o \
		pacman.o \
		buttonwidget.o \
		labelwidget.o \
		event.o \
		textinputwidget.o \
		scrollingwidget.o \
		radiowidget.o \
		sliderwidget.o \
		menuwidget.o \
		menusystem.o \
		servermenusystem.o \
		clientmenusystem.o \
		menupane.o \
		ghost.o \
		pacskin.o \
		sidebar.o \
		chatwnd.o \
		image.o \
		text.o \
		opengl.o \
		bitmap.o \
		drawableobject.o \
		Level.o \
		Space.o \
		BFS.o \
		BaseItem.o \
		genlevel.o \
		FileException.o \
		-o console_client

tester : test.o \
								 Exception.o \
								 network.o \
								 NetworkException.o \
								 TCP.o \
								 TCPServer.o \
								 UDP.o \
								 UDPacket.o \
								 RUDP.o \
								 ComTracker.o \
								 playerlist.o \
								 player.o \
								 pacman.o \
								 ghost.o \
								 pacskin.o \
								 sidebar.o \
								 chatwnd.o \
								 image.o \
								 text.o \
								 opengl.o \
								 bitmap.o \
								 drawableobject.o \
								 Level.o \
								 Space.o \
								 BFS.o \
								 BaseItem.o \
								 genlevel.o \
								 FileException.o
	$(COMP) $(LFLAGS) test.o \
		Exception.o \
		network.o \
		NetworkException.o \
		TCP.o \
		TCPServer.o \
		UDP.o \
		UDPacket.o \
		RUDP.o \
		ComTracker.o \
		playerlist.o \
		player.o \
		pacman.o \
		ghost.o \
		pacskin.o \
		sidebar.o \
		chatwnd.o \
		image.o \
		text.o \
		opengl.o \
		bitmap.o \
		drawableobject.o \
		Level.o \
		BFS.o \
		Space.o \
		BaseItem.o \
		genlevel.o \
		FileException.o \
		-o tester

servtest : servertest.o \
								 Exception.o \
								 network.o \
								 NetworkException.o \
								 TCP.o \
								 TCPServer.o \
								 UDP.o \
								 UDPacket.o \
								 RUDP.o \
								 ComTracker.o \
								 playerlist.o \
								 player.o \
								 pacman.o \
								 ghost.o \
								 pacskin.o \
								 sidebar.o \
								 chatwnd.o \
								 image.o \
								 text.o \
								 opengl.o \
								 bitmap.o \
								 drawableobject.o \
								 Level.o \
								 Space.o \
								 BFS.o \
								 AIGhost.o \
								 AIRules.o \
								 BaseItem.o \
								 GameBoard.o \
								 GameClient.o \
								 GameMechanicsRules.o \
								 GameRules.o \
								 GameServer.o \
								 ServerGameboard.o \
								 genlevel.o \
								 FileException.o
	$(COMP) $(LFLAGS) servertest.o \
		Exception.o \
		network.o \
		NetworkException.o \
		AIGhost.o \
		AIRules.o \
		BaseItem.o \
		GameBoard.o \
		GameClient.o \
		GameMechanicsRules.o \
		GameRules.o \
		GameServer.o \
		ServerGameboard.o \
		TCP.o \
		TCPServer.o \
		UDP.o \
		UDPacket.o \
		RUDP.o \
		ComTracker.o \
		playerlist.o \
		player.o \
		pacman.o \
		ghost.o \
		pacskin.o \
		sidebar.o \
		chatwnd.o \
		image.o \
		text.o \
		opengl.o \
		bitmap.o \
		drawableobject.o \
		Level.o \
		BFS.o \
		Space.o \
		genlevel.o \
		FileException.o \
		-o servtest


# Building the object files
menusystem.o : MenuSystem.cc
	$(COMP) $(CFLAGS) -c MenuSystem.cc -o menusystem.o
 
clientmenusystem.o : ClientMenuSystem.cc
	$(COMP) $(CFLAGS) -c ClientMenuSystem.cc -o clientmenusystem.o
 
servermenusystem.o : ServerMenuSystem.cc
	$(COMP) $(CFLAGS) -c ServerMenuSystem.cc -o servermenusystem.o
 
buttonwidget.o : ButtonWidget.cc
	$(COMP) $(CFLAGS) -c ButtonWidget.cc -o buttonwidget.o
 
labelwidget.o: LabelWidget.cc
	$(COMP) $(CFLAGS) -c LabelWidget.cc -o labelwidget.o
 
textinputwidget.o: TextInputWidget.cc
	$(COMP) $(CFLAGS) -c TextInputWidget.cc -o textinputwidget.o
 
menuwidget.o: MenuWidget.cc
	$(COMP) $(CFLAGS) -c MenuWidget.cc -o menuwidget.o
 
scrollingwidget.o: ScrollingMenuWidget.cc
	$(COMP) $(CFLAGS) -c ScrollingMenuWidget.cc -o scrollingwidget.o
 
radiowidget.o: RadioWidget.cc
	$(COMP) $(CFLAGS) -c RadioWidget.cc -o radiowidget.o
 
sliderwidget.o: SliderWidget.cc
	$(COMP) $(CFLAGS) -c SliderWidget.cc -o sliderwidget.o
 
menupane.o: MenuPane.cc
	$(COMP) $(CFLAGS) -c MenuPane.cc -o menupane.o
 
event.o : Event.h Event.cc
	$(COMP) $(CFLAGS) -c Event.cc -o event.o

servertest.o : servertest.cc
	$(COMP) $(CFLAGS) -c servertest.cc -o servertest.o

test.o : test.cpp
	$(COMP) $(CFLAGS) -c test.cpp -o test.o

ConsoleClient.o : ConsoleClient.cc
	$(COMP) $(CFLAGS) -c ConsoleClient.cc -o ConsoleClient.o

ConsoleServer.o : ConsoleServer.cc
	$(COMP) $(CFLAGS) -c ConsoleServer.cc -o ConsoleServer.o

cliopengl.o : client_opengl.h client_opengl.cpp
	$(COMP) $(CFLAGS) -c client_opengl.cpp -o cliopengl.o

opengl.o : opengl.h opengl.cpp
	$(COMP) $(CFLAGS) -c opengl.cpp -o opengl.o

bitmap.o : bitmap.h bitmap.c
	$(COMP) $(CFLAGS) -c bitmap.c -o bitmap.o

image.o : image.h image.cpp
	$(COMP) $(CFLAGS) -c image.cpp -o image.o

text.o : text.h text.cpp
	$(COMP) $(CFLAGS) -c text.cpp -o text.o

playerlist.o : playerlist.h playerlist.cpp
	$(COMP) $(CFLAGS) -c playerlist.cpp -o playerlist.o

player.o : player.h player.cpp
	$(COMP) $(CFLAGS) -c player.cpp -o player.o

pacman.o : pacman.h pacman.cpp
	$(COMP) $(CFLAGS) -c pacman.cpp -o pacman.o

ghost.o : ghost.h ghost.cpp
	$(COMP) $(CFLAGS) -c ghost.cpp -o ghost.o

pacskin.o : pacskin.h pacskin.cpp
	$(COMP) $(CFLAGS) -c pacskin.cpp -o pacskin.o

chatwnd.o : chatwnd.h chatwnd.cpp
	$(COMP) $(CFLAGS) -c chatwnd.cpp -o chatwnd.o

sidebar.o : sidebar.h sidebar.cpp
	$(COMP) $(CFLAGS) -c sidebar.cpp -o sidebar.o

drawableobject.o : drawableobject.h drawableobject.cpp
	$(COMP) $(CFLAGS) -c drawableobject.cpp -o drawableobject.o

network.o : network.h network.cc
	$(COMP) $(CFLAGS) -c network.cc -o network.o

NetworkException.o : NetworkException.h NetworkException.cc
	$(COMP) $(CFLAGS) -c NetworkException.cc -o NetworkException.o

TCP.o : TCP.h TCP.cc NetworkException.h
	$(COMP) $(CFLAGS) -c TCP.cc -o TCP.o

baseitem.o : BaseItem.cc
	$(COMP) $(CFLAGS) -c BaseItem.cc -o baseitem.o
 
TCPServer.o : TCPServer.h TCPServer.cc NetworkException.h
	$(COMP) $(CFLAGS) -c TCPServer.cc -o TCPServer.o

UDPacket.o : UDPacket.h UDPacket.cc NetworkException.h
	$(COMP) $(CFLAGS) -c UDPacket.cc -o UDPacket.o

UDP.o : UDP.h UDP.cc NetworkException.h UDPacket.o
	$(COMP) $(CFLAGS) -c UDP.cc -o UDP.o

RUDP.o : RUDP.h RUDP.cc ComTracker.o
	$(COMP) $(CFLAGS) -c RUDP.cc -o RUDP.o

ComTracker.o : ComTracker.h ComTracker.cc UDP.o
	$(COMP) $(CFLAGS) -c ComTracker.cc -o ComTracker.o 

FileException.o : FileException.h FileException.cc
	$(COMP) $(CFLAGS) -c FileException.cc -o FileException.o

Space.o : Space.h Space.cc
	$(COMP) $(CFLAGS) -c Space.cc -o Space.o

Level.o : Level.h Level.cc
	$(COMP) $(CFLAGS) -c Level.cc -o Level.o

BFS.o : BFS.h BFS.cc
	$(COMP) $(CFLAGS) -c BFS.cc -o BFS.o

genlevel.o : genlevel.h genlevel.cpp
	$(COMP) $(CFLAGS) -c genlevel.cpp -o genlevel.o

Exception.o : Exception.h Exception.cc
	$(COMP) $(CFLAGS) -c Exception.cc -o Exception.o

BaseItem.o : BaseItem.h BaseItem.cc
	$(COMP) $(CFLAGS) -c BaseItem.cc -o BaseItem.o

Pellet.o : Pellet.h Pellet.cc
	$(COMP) $(CFLAGS) -c Pellet.cc

PowerPellet.o : PowerPellet.h PowerPellet.cc
	$(COMP) $(CFLAGS) -c PowerPellet.cc

AIGhost.o : AIGhost.h AIGhost.cc
	$(COMP) $(CPFLAGS) -c AIGhost.cc -o AIGhost.o
					
AIRules.o : AIRules.h AIRules.cc
	$(COMP) $(CFLAGS) -c AIRules.cc -o AIRules.o

GameBoard.o : GameBoard.h GameBoard.cc
	$(COMP) $(CFLAGS) -c GameBoard.cc -o GameBoard.o

GameClient.o : GameClient.h GameClient.cc
	$(COMP) $(CFLAGS) -c GameClient.cc -o GameClient.o

GameMechanicsRules.o : GameMechanicsRules.h GameMechanicsRules.cc
	$(COMP) $(CFLAGS) -c GameMechanicsRules.cc -o GameMechanicsRules.o

GameRules.o : GameRules.h GameRules.cc
	$(COMP) $(CFLAGS) -c GameRules.cc -o GameRules.o

GameServer.o : GameServer.h GameServer.cc
	$(COMP) $(CFLAGS) -c GameServer.cc -o GameServer.o

ServerGameboard.o : ServerGameboard.h ServerGameboard.cc
	$(COMP) $(CFLAGS) -c ServerGameboard.cc -o ServerGameboard.o

#Ogg.o : Ogg.h Ogg.cc
#	$(COMP) $(CFLAGS) -c Ogg.cc -o Ogg.o

#OggPlayer.o : OggPlayer.h OggPlayer.cc
#	$(COMP) $(CFLAGS) -c OggPlayer.cc -o OggPlayer.o

clean:
	rm *.o

