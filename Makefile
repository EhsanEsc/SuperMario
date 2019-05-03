CC = g++
CFLAGS = -std=c++11 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJ = main.o src/Game.o src/Manager.o src/Obstacles.o src/Mario.o src/Texture.o src/Shape.o src/Troopa.o src/Goomba.o \
src/UI_box.o src/Collision.o src/Powerops.o src/Sound.o src/Projectile.o src/rsdl.o

RSDL_SLIST = src/rsdl.hpp
TEXTURE_SLIST = src/rsdl.hpp src/Texture.h
SHAPE_SLIST = src/rsdl.hpp src/Shape.h
PROJECTILE_SLIST = src/rsdl.hpp src/Texture.h src/Shape.h src/Projectile.h
POWEROPS_SLIST = src/rsdl.hpp src/Texture.h src/Shape.h src/Powerops.h
SOUND_SLIST = src/rsdl.hpp src/Sound.h
UIBOX_SLIST = src/rsdl.hpp src/UI_box.h
OBSTACLES_SLIST = src/rsdl.hpp src/Texture.h src/Shape.h src/Powerops.h src/Obstacles.h
MARIO_SLIST = src/rsdl.hpp src/Texture.h src/Shape.h src/Mario.h
TROOPA_SLIST = src/rsdl.hpp src/Texture.h src/Shape.h src/Troopa.h
GOOMBA_SLIST = src/rsdl.hpp src/Texture.h src/Shape.h src/Goomba.h
COLLISION_SLIST = src/rsdl.hpp src/Shape.h src/Collision.h

MANAGER_SLIST = src/rsdl.hpp src/Obstacles.h src/Mario.h src/Texture.h src/Shape.h src/Troopa.h src/Goomba.h \
src/UI_box.h src/Collision.h src/Powerops.h src/Sound.h src/Projectile.h src/Manager.h
GAME_SLIST = $(MANAGER_SLIST) src/Game.h
MAIN_SLIST = $(GAME_SLIST)

a.out: $(OBJ)
	$(CC) $(OBJ) -o a.out $(CFLAGS)
main.o: main.cpp $(MAIN_SLIST)
	$(CC) -c main.cpp -o main.o $(CFLAGS)
src/Game.o: src/Game.cpp $(GAME_SLIST)
	$(CC) -c src/Game.cpp -o src/Game.o $(CFLAGS)
src/Manager.o: src/Manager.cpp $(MANAGER_SLIST)
	$(CC) -c src/Manager.cpp -o src/Manager.o $(CFLAGS)
src/Obstacles.o: src/Obstacles.cpp $(OBSTACLES_SLIST)
	$(CC) -c src/Obstacles.cpp -o src/Obstacles.o $(CFLAGS)
src/Mario.o: src/Mario.cpp $(MARIO_SLIST)
	$(CC) -c src/Mario.cpp -o src/Mario.o $(CFLAGS)
src/Texture.o: src/Texture.cpp $(TEXTURE_SLIST)
	$(CC) -c src/Texture.cpp -o src/Texture.o $(CFLAGS)
src/Shape.o: src/Shape.cpp $(SHAPE_SLIST)
	$(CC) -c src/Shape.cpp -o src/Shape.o $(CFLAGS)
src/Troopa.o: src/Troopa.cpp $(TROOPA_SLIST)
	$(CC) -c src/Troopa.cpp -o src/Troopa.o $(CFLAGS)
src/Goomba.o: src/Goomba.cpp $(GOOMBA_SLIST)
	$(CC) -c src/Goomba.cpp -o src/Goomba.o $(CFLAGS)
src/UI_box.o: src/UI_box.cpp $(UIBOX_SLIST)
	$(CC) -c src/UI_box.cpp -o src/UI_box.o $(CFLAGS)
src/Collision.o: src/Collision.cpp $(COLLISION_SLIST)
	$(CC) -c src/Collision.cpp -o src/Collision.o $(CFLAGS)
src/Powerops.o: src/Powerops.cpp $(POWEROPS_SLIST)
	$(CC) -c src/Powerops.cpp -o src/Powerops.o $(CFLAGS)
src/Sound.o: src/Sound.cpp $(SOUND_SLIST)
	$(CC) -c src/Sound.cpp -o src/Sound.o $(CFLAGS)
src/Projectile.o: src/Projectile.cpp $(PROJECTILE_SLIST)
	$(CC) -c src/Projectile.cpp -o src/Projectile.o $(CFLAGS)
src/rsdl.o: src/rsdl.cpp $(RSDL_SLIST)
	$(CC) -c src/rsdl.cpp -o src/rsdl.o $(CFLAGS)
FORCE: ;
clean:
	rm *.o src/*.o
	rm a.out
