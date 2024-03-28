# Asteroid Shooter :- Arduino version
We developed it for  ArduGem for GC'24(IIT Bhubaneswar's inter-branch competition).

# Description:-
+ This game is based on the concept of Arcade style survival games.
+ It is a game of pace,accuracy and reflexes.
+ Asteroids will be spawning randomly from 8 different directions in the game and the player shall aim and shoot the asteroids to destroy them.

# Dependecies:-
+ <SPI.h>
+ <Adafruit_GFX.h>
+ <Adafruit_ST7735.h>
+ <EEPROM.h>

# Control Scheme:-
+ The game starts with a startup screen having it's name and highscore of the game. 
+ Press 'F' to start the game.
+ Pressing 'E' will take you to the rules page.
+ Asteroids will be spawning randomly from 8 different directions in the game and the player shall aim and shoot the asteroids to destroy them.
+ Use the joystick to start aiming at the spwaning asteroids.
+ Press 'B' to shoot the asteroid.
+ Only ONE asteroid can be shot down at a time.
+ The player has s to shoot down the asteroids, there is a pointer to cross check his aim.
+ When the player runs out of ammo, press the button 'B' on the joystick shield to reload.
+ Every 20 seconds the player can see a blue little circle on the left corner,which indicates a special powerup(scatter).![WhatsApp Image 2024-03-28 at 18 45 41_9ac40f2a](https://github.com/Coolexguy/ArduGem-GC-2024/assets/164471213/b7f124eb-9f84-4dfe-99d7-363cd5b28971)

+ Press 'A' to use scatter which destroys all the asteroids present on the screen.
