#Asteroid Shooter :- Arduino version
We developed it for  ArduGem for GC'24(IIT Bhubaneswar's inter-branch competition).

#Description:-
This game is based on the concept of Arcade style survival games. 
It is a game of pace , accuracy and reflexes.
Asteroids will be spwaning randomly from 8 different directions in the game and the player shall aim and shoot down the asteroids.

#Dependecies:-
SPI.h
Adafruit_GFX.h
Adafruit_ST7735.h
EEPROM.h

#Control Scheme:-
The game starts with a startup screen having it's name and other context of the game.
The player shall press 'F' to start the game.
Pressing 'E' will take you to the rules page.
Asteroids will be spwaning randomly from 8 different directions in the game and the player shall aim and shoot down the asteroids.
Use the joystick shield to start aiming at the spwaning asteroids.
Press 'B' to shoot down the asteroid.
Only ONE asteroid can be shot down at a time.
The player has 7 lasers(bullets) to shoot down the asteroids, there is a pointer to cross check his aim.
When the player runs out of ammo, he/she can press the button 'B' on the joystick to reload.
20 seconds into the game, the player can see a blue little circle on the left corner.
Press 'A' to use a special powerup(scatter) which destroys all the asteroids present on the screen.
Player can use scatter every 20 seconds in the game.
