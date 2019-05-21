g++ *.cpp -std=c++11 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -g
if [ $? == 0 ]
then
	./a.out $1
fi