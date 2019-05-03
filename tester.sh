# g++ example.cpp src/rsdl.cpp -std=c++11 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
g++ main.cpp src/Game.cpp src/Manager.cpp src/Obstacles.cpp src/Mario.cpp src/Texture.cpp src/Shape.cpp src/Troopa.cpp src/Goomba.cpp src/UI_box.cpp src/Collision.cpp src/Powerops.cpp src/Sound.cpp src/Projectile.cpp src/rsdl.cpp -std=c++11 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o a.out
./a.out "assets/maps/1/1.txt"
read -p "Press..."
