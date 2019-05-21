# SuperMario - UTAP Spring98

This is a minimal, c++ implementation of the famous and nostalgic game [SuperMario](https://supermariobros.io/), which was chosen as a course project for the Advanced Programming course of the Computer Engineering major of [University of Tehran](https://ut.ac.ir/en), on the 2019 spring semester. 
As a teaching assistant for this course who was in charge of designing this assignment, I felt compelled to write the code that was expected of the students, in order to make sure that the project was neither too big, nor too small. Moreover, it would help bring out all those small ambiguities earlier, that would otherwise be discovered only after the students had started working on the project, and thus help save both the TAs and students significant amounts of time. The repository would also be shown to the students as an example of a "good-enough" design to help guide them towards better designs.

This project is built using the [RSDL](https://github.com/UTAP/RSDL) (Ramtin's Simple DirectMedia Layer) library, which is a library developed to help students use the [SDL](https://www.libsdl.org/) library through a simpler and more object-oriented interface. 

## Getting Started

To play this game, you need to do the typical steps for running any c-based project.
First, clone the repository into a directory which we will call ‍‍‍`<mario-dir>` from now on. Then, change directory to `<mario-dir>/src`.
Then run 
```
make
```
to create the executable. Then run
```
./mario.out <level-file-address>
```
to play the game. The game currently has only one level, and it will default to that one level if the executable is called without any arguments.

## Authors

* **Ahmad Pourihosseini** - *wrote the source code* - [ahmad-PH](https://github.com/ahmad-PH)
* **Farzad Habibi** - *helped with writing the assignment description* - [gsoosk](https://github.com/gsoosk)
* **Amirhossein Habibvand** - *helped with writing the assignment description* - [amirhbv](https://github.com/amirhbv)
* **Bardia Eghbali** - *helped with writing the assignment description* - [sadmanbrad](https://github.com/sadmanbrad)

## Acknowledgments

* All the assets in this project were picked from the two websites: [mariouniverse](http://www.mariouniverse.com/) and [themushroomkingdom](https://themushroomkingdom.net/wav.shtml).
