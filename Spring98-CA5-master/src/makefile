CC = g++
FLAGS = -std=c++11 -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
COMPILE_FLAGS = $(FLAGS) -c 

OBJECT_FILES = main.o AnimationIndexHandler.o AutomaticMovingObject.o Block.o Brick.o \
Coin.o Collision.o Enemy.o ExactRectangle.o FlagBlock.o Game.o Mario.o Mushroom.o \
Object.o rsdl.o utility.o MapReader.o PipeBlock.o

#main entry
mario.out: $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) $(FLAGS) -o mario.out

#object file entries
main.o: main.cpp  Game.h
	$(CC) $(COMPILE_FLAGS) main.cpp

MapReader.o: MapReader.cpp MapReader.h PipeBlock.h Block.h Game.h
	$(CC) $(COMPILE_FLAGS) MapReader.cpp

AnimationIndexHandler.o: AnimationIndexHandler.cpp AnimationIndexHandler.h  
	$(CC) $(COMPILE_FLAGS) AnimationIndexHandler.cpp

AutomaticMovingObject.o: AutomaticMovingObject.cpp AutomaticMovingObject.h Game.h
	$(CC) $(COMPILE_FLAGS) AutomaticMovingObject.cpp

Block.o: Block.cpp Block.h
	$(CC) $(COMPILE_FLAGS) Block.cpp

Brick.o: Brick.cpp Brick.h AssetsAddresses.h Game.h Coin.h Mushroom.h
	$(CC) $(COMPILE_FLAGS) Brick.cpp

Coin.o: Coin.cpp Coin.h Game.h
	$(CC) $(COMPILE_FLAGS) Coin.cpp

Collision.o: Collision.cpp Collision.h
	$(CC) $(COMPILE_FLAGS) Collision.cpp

Enemy.o: Enemy.cpp Enemy.h AssetsAddresses.h Game.h
	$(CC) $(COMPILE_FLAGS) Enemy.cpp

ExactRectangle.o: ExactRectangle.cpp ExactRectangle.h 
	$(CC) $(COMPILE_FLAGS) ExactRectangle.cpp

FlagBlock.o: FlagBlock.cpp FlagBlock.h Mario.h Game.h
	$(CC) $(COMPILE_FLAGS) FlagBlock.cpp

Game.o: Game.cpp Game.h utility.h MapReader.h
	$(CC) $(COMPILE_FLAGS) Game.cpp

Mario.o: Mario.cpp Mario.h AssetsAddresses.h utility.h Mushroom.h Game.h
	$(CC) $(COMPILE_FLAGS) Mario.cpp

Mushroom.o: Mushroom.cpp Mushroom.h AssetsAddresses.h Game.h
	$(CC) $(COMPILE_FLAGS) Mushroom.cpp

Object.o: Object.cpp Object.h utility.h
	$(CC) $(COMPILE_FLAGS) Object.cpp

rsdl.o: rsdl.cpp rsdl.h 
	$(CC) $(COMPILE_FLAGS) rsdl.cpp

PipeBlock.o: PipeBlock.cpp PipeBlock.h AssetsAddresses.h
	$(CC) $(COMPILE_FLAGS) PipeBlock.cpp

utility.o: utility.cpp utility.h
	$(CC) $(COMPILE_FLAGS) utility.cpp

#header entries
AnimationIndexHandler.h: 

AutomaticMovingObject.h: Object.h

Block.h: Object.h

Brick.h: AnimationIndexHandler.h Object.h

Coin.h: Object.h

Collision.h:

Enemy.h: AutomaticMovingObject.h AnimationIndexHandler.h

ExactRectangle.h: rsdl.h

FlagBlock.h : Object.h

Game.h: rsdl.h AssetsAddresses.h Mario.h Block.h Brick.h Enemy.h FlagBlock.h

Mario.h: Object.h AnimationIndexHandler.h

Mushroom.h: AutomaticMovingObject.h

Object.h: Collision.h ExactRectangle.h

rsdl.h: 

utility.h: rsdl.h ExactRectangle.h

MapReader.h:

PipeBlock.h: Block.h


.PHONY: clean

clean:
	rm *.o