README for Project 8: Simple Demo Scene
By: Justin & Ryan

To Run:

1) Install required libraries:
- sudo apt-get install freeglut3-dev mesa-common-dev libglu1-mesa-dev libglew-dev libglfw3-dev libsoil-dev libglm-dev
- sudo apt-get install libfreetype-dev libfreetype6 libfreetype6-dev

2) Compile:
- g++ main.cpp -o pong -lGL -lglut -lGLU

3) Run:
- ./pong

4) Command Hotkeys:
(Also available in the Documentation)

	Left Paddle:
|Command	|Hotkey	|
|-------------------|
|move up	|W		|
|move down	|S		|


	Right Paddle:
|Command	|Hotkey	|
|-------------------|
|move up	|U		|
|move down	|J		|

The game stops when a player reaches 5 points and you can restart it with 'R'