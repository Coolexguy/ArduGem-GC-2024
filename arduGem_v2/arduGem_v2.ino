#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library
#include <SPI.h>
#include <EEPROM.h>

#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8

#define BLACK 0x0000
#define RED 0x001F
#define BLUE 0xF800
#define GREEN 0x07E0
#define YELLOW 0x07FF
#define PURPLE 0xF81F
#define CYAN 0xFFE0
#define WHITE 0xFFFF

#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define X A0
#define Y A1
#define address 0
// #define JB 8
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
float p = 3.1415926;
float root2 = 1.41421356237;
byte ammo = 7;
int asteroid_speed[9] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
int asteroid_speed_reset[9] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
byte asteroid_posn_reset[9][2]{ { 0, 0 }, { 64, 0 }, { 128, 0 }, { 128, 64 }, { 128, 128 }, { 64, 128 }, { 0, 128 }, { 0, 64 }, { 0, 0 } };
byte asteroid_posn[9][2]{ { 0, 0 }, { 64, 0 }, { 128, 0 }, { 128, 64 }, { 128, 128 }, { 64, 128 }, { 0, 128 }, { 0, 64 }, { 0, 0 } };
bool asteroid_presence[9] = { 1, 1, 0, 0, 0, 0, 0, 0, 0 };
byte dir() {
  int x = analogRead(X);
  int y = analogRead(Y);
  if (x > 500 && x < 510 && y > 550) {
    return 1;
  } else if (x > 550 && y > 550) {
    return 2;
  } else if (y > 500 && y < 520 && x > 550) {
    return 3;
  } else if (y < 500 && x > 520) {
    return 4;
  } else if (x > 500 && x < 520 && y < 500) {
    return 5;
  } else if (x < 500 && y < 500) {
    return 6;
  } else if (x < 500 && y > 500 && y < 520) {
    return 7;
  } else if (x < 500 && y > 550) {
    return 8;
  } else {
    return 0;
  }
}
byte point(byte x) {
  if (dir() == 1) {
    tft.drawLine(64, 64 - x, 64, 64, RED);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    return 1;
  } else if (dir() == 2) {
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    return 2;
  } else if (dir() == 3) {
    tft.drawLine(64 + x, 64, 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    return 3;
  } else if (dir() == 4) {
    tft.drawLine(64 + (x / root2), 64 + (x / root2), 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    return 4;
  } else if (dir() == 5) {
    tft.drawLine(64, 64 + x, 64, 64, RED);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    return 5;
  } else if (dir() == 6) {
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    return 6;
  } else if (dir() == 7) {
    tft.drawLine(64 - x, 64, 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    return 7;
  } else if (dir() == 8) {
    tft.drawLine(64 - (x / root2), 64 - (x / root2), 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    return 8;
  } else {
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);  // case2
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);  // case6
    return 0;
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(D, INPUT);
  pinMode(E, INPUT);
  pinMode(F, INPUT);
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  // pinMode(JB, INPUT);
  tft.initR(INITR_BLACKTAB);  // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);

  pinMode(A5, INPUT);
  randomSeed(analogRead(A5));  // random seed

  // EEPROM.update(address,0);/*to reset Highscore*/
  startUp();
  tft.fillScreen(ST7735_BLACK);
  scoreSetup();
  playerSetup();
  ammoSetup();
  scoreDisplay(0);
  ammoDisplay(7);
}
int score = 0;
void scoreSetup() {
  tft.setTextSize(1);
  tft.setTextColor(CYAN);
  tft.setCursor(80, 5);
  tft.print("Score:");
}
void ammoSetup() {
  tft.setTextSize(1);
  tft.setTextColor(CYAN);
  tft.setCursor(86, 123);
  tft.print("Ammo:");
  //  tft.drawLine(112,0,112,128, RED);// for alignment
}
void playerSetup() {
  tft.fillCircle(64, 64, 5, PURPLE);
}
void scoreDisplay(byte k) {
  tft.fillRect(115, 5, 11, 7, BLACK);
  tft.setTextColor(CYAN);
  tft.setCursor(115, 5);
  tft.print(k);
}
void ammoDisplay(byte a) {
  tft.fillRect(115, 123, 5, 9, BLACK);
  tft.setTextColor(CYAN);
  tft.setCursor(115, 123);
  tft.print(a);
}
void startScreenSetup() {
  tft.fillRect(4, 4, 120, 120, RED);
  tft.fillRect(6, 6, 116, 116, BLACK);
  tft.setTextColor(CYAN);
  tft.setCursor(18, 10);
  tft.setTextSize(2);
  tft.print("ASTEROID");

  tft.setTextColor(PURPLE);
  tft.setCursor(24, 30);
  tft.setTextSize(2);
  tft.print("SHOOTER");
}
void startUp() {
  startScreenSetup();

  while (digitalRead(E) && digitalRead(F)) {

    tft.setTextColor(WHITE);
    tft.setCursor(18, 50);
    tft.setTextSize(1);
    tft.print("Press F to start.");

    tft.setTextColor(WHITE);
    tft.setCursor(18, 60);
    tft.print("Press E to-");
    tft.setCursor(60, 70);
    tft.print("-see rules");

    tft.setTextSize(1);
    tft.setCursor(18, 90);
    tft.print("HIGH SCORE:");

    tft.setCursor(90, 85);
    tft.setTextSize(2);
    tft.print(EEPROM.read(address));
  }

  int f = 0;
  while (digitalRead(F)) {
    if (f == 0) {
      tft.fillScreen(ST7735_BLACK);
      tft.setTextColor(WHITE);
      tft.setCursor(4, 4);
      tft.setTextSize(1);
      tft.print("Rules:");
      tft.setCursor(4, 14);
      tft.print("1. Use the joystick to move the pointer.");
      // tft.setCursor(4, 34);
      // tft.print("and shoot the asteroids");
      tft.setCursor(4, 34);
      tft.print("2. Press C to shoot.");
      tft.setCursor(4, 44);
      tft.print("3. Press B to Reload.");
      tft.setCursor(4, 54);
      tft.print("4. Press A to use");
      tft.setCursor(4, 64);
      tft.print("SCATTER.");
      tft.setCursor(4, 74);
      tft.print("5. Press D to use");
      tft.setCursor(4, 84);
      tft.print("SHIELD.");
      tft.setCursor(4, 94);
      tft.print("6. Press F in game");
      tft.setCursor(4, 104);
      tft.print("to pause");
      tft.setCursor(4, 114);
      tft.print("7. Press F to");
      tft.setCursor(4, 124);
      tft.print("Continue to play");

      // tft.setCursor(4, 114);
      // tft.print("10. Press E to start");
      f++;
    }
  }
}
void pause(byte currentScore, byte highScore) {
  tft.fillScreen(ST7735_BLACK);
  tft.fillRect(4, 4, 120, 120, RED);
  tft.fillRect(6, 6, 116, 116, BLACK);

  tft.setTextColor(CYAN);
  tft.setCursor(30, 10);
  tft.setTextSize(2);
  tft.print("PAUSED");

  tft.setTextColor(WHITE);
  tft.setCursor(7, 50);
  tft.setTextSize(1);
  tft.print("Press F to continue");
  tft.setTextSize(1);

  tft.setCursor(8, 70);
  tft.print("CURRENT SCORE:");
  tft.setCursor(92, 65);
  tft.setTextSize(2);
  tft.print(currentScore);

  tft.setTextSize(1);
  tft.setCursor(18, 90);
  tft.print("HIGH SCORE:");
  tft.setCursor(90, 85);
  tft.setTextSize(2);
  tft.print(EEPROM.read(address));

  delay(100);
  while (digitalRead(F)) {
  }
  tft.fillScreen(ST7735_BLACK);

  scoreSetup();
  playerSetup();
  ammoSetup();
  scoreDisplay(score);
  ammoDisplay(ammo);
}
void GameOver(byte currentScore, byte highScore) {

  tft.fillScreen(ST7735_BLACK);
  tft.fillRect(4, 4, 120, 120, RED);
  tft.fillRect(6, 6, 116, 116, BLACK);
  tft.setTextColor(CYAN);
  tft.setCursor(40, 10);
  tft.setTextSize(2);
  tft.print("GAME");

  tft.setTextColor(PURPLE);
  tft.setCursor(40, 30);
  tft.setTextSize(2);
  tft.print("OVER");

  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.setCursor(8, 70);
  tft.print("CURRENT SCORE:");
  tft.setCursor(90, 65);
  tft.setTextSize(2);
  tft.print(currentScore);
  if (currentScore > highScore) {
    EEPROM.update(address, currentScore);
  }
  score = 0;
  ammo = 7;
  tft.setTextSize(1);
  tft.setCursor(18, 90);
  tft.print("HIGH SCORE:");
  tft.setCursor(90, 85);
  tft.setTextSize(2);
  tft.print(EEPROM.read(address));

  tft.setTextSize(1);
  tft.setCursor(10, 110);
  tft.print("Press E to restart");




  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 9; j++) {
      asteroid_posn[j][i] = asteroid_posn_reset[j][i];
    }
  }
  for (int i = 1; i <= 8; i++) {
    // asteroid_presence[i]++;
    asteroid_speed[i] = asteroid_speed_reset[i];
  }
  while (digitalRead(E)) {
  }
  delay(100);
  setup();

  // tft.fillScreen(ST7735_BLACK);

  // scoreSetup();
  // playerSetup();
  // ammoSetup();
  // scoreDisplay(0);
  // ammoDisplay(7);
}

unsigned long pt_asteroids[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte asteroids(int t[9], bool checker[9], byte increment[9]) {

  // tft.fillCircle(64, asteroid_posn[1][1], 3, YELLOW);
  if (checker[1] && millis() - pt_asteroids[1] >= t[1]) {
    asteroid_posn[1][1] += increment[1];
    pt_asteroids[1] = millis();
    tft.fillCircle(64, asteroid_posn[1][1] - increment[1], 3, BLACK);
    tft.fillCircle(64, asteroid_posn[1][1], 3, YELLOW);
  }
  if (asteroid_posn[1][1] >= 55) {
    GameOver(score, EEPROM.read(address));
    return 1;
  }


  // tft.fillCircle(asteroid_posn[2][0], asteroid_posn[2][1], 3, YELLOW);
  if (checker[2] && millis() - pt_asteroids[2] >= t[2]) {
    asteroid_posn[2][1] += increment[2];
    asteroid_posn[2][0] -= increment[2];
    pt_asteroids[2] = millis();
    tft.fillCircle(asteroid_posn[2][0] + increment[2], asteroid_posn[2][1] - increment[2], 3, BLACK);
    tft.fillCircle(asteroid_posn[2][0], asteroid_posn[2][1], 3, YELLOW);
  }
  if (asteroid_posn[2][0] <= 70) {
    GameOver(score, EEPROM.read(address));
    return 2;
  }


  // tft.fillCircle(asteroid_posn[3][0], 64, 3, YELLOW);
  if (checker[3] && millis() - pt_asteroids[3] >= t[3]) {
    asteroid_posn[3][0] -= increment[3];
    pt_asteroids[3] = millis();
    tft.fillCircle(asteroid_posn[3][0] + increment[3], 64, 3, BLACK);
    tft.fillCircle(asteroid_posn[3][0], 64, 3, YELLOW);
  }
  if (asteroid_posn[3][0] <= 73) {
    GameOver(score, EEPROM.read(address));
    return 3;
  }


  // tft.fillCircle(asteroid_posn[4][0], asteroid_posn[4][1], 3, YELLOW);

  if (checker[4] && millis() - pt_asteroids[4] >= t[4]) {
    asteroid_posn[4][1] -= increment[4];
    asteroid_posn[4][0] -= increment[4];
    pt_asteroids[4] = millis();
    tft.fillCircle(asteroid_posn[4][0] + increment[4], asteroid_posn[4][1] + increment[4], 3, BLACK);
    tft.fillCircle(asteroid_posn[4][0], asteroid_posn[4][1], 3, YELLOW);
  }
  if (asteroid_posn[4][1] <= 70) {
    GameOver(score, EEPROM.read(address));
    return 4;
  }


  // tft.fillCircle(64, asteroid_posn[5][1], 3, YELLOW);

  if (checker[5] && millis() - pt_asteroids[5] >= t[5]) {
    asteroid_posn[5][1] -= increment[5];
    pt_asteroids[5] = millis();
    tft.fillCircle(64, asteroid_posn[5][1] + increment[5], 3, BLACK);
    tft.fillCircle(64, asteroid_posn[5][1], 3, YELLOW);
  }
  if (asteroid_posn[5][1] <= 75) {
    GameOver(score, EEPROM.read(address));
    return 5;
  }


  // tft.fillCircle(asteroid_posn[6][0], asteroid_posn[6][1], 3, YELLOW);
  if (checker[6] && millis() - pt_asteroids[6] >= t[6]) {
    asteroid_posn[6][1] -= increment[6];
    asteroid_posn[6][0] += increment[6];
    pt_asteroids[6] = millis();
    tft.fillCircle(asteroid_posn[6][0] - increment[6], asteroid_posn[6][1] + increment[6], 3, BLACK);
    tft.fillCircle(asteroid_posn[6][0], asteroid_posn[6][1], 3, YELLOW);
  }
  if (asteroid_posn[6][1] <= 70) {
    GameOver(score, EEPROM.read(address));
    return 6;
  }


  // tft.fillCircle(asteroid_posn[7][0], 64, 3, YELLOW);
  if (checker[7] && millis() - pt_asteroids[7] >= t[7]) {
    asteroid_posn[7][0] += increment[7];
    pt_asteroids[7] = millis();
    tft.fillCircle(asteroid_posn[7][0] - increment[7], 64, 3, BLACK);
    tft.fillCircle(asteroid_posn[7][0], 64, 3, YELLOW);
  }
  if (asteroid_posn[7][0] >= 54) {
    GameOver(score, EEPROM.read(address));
    return 7;
  }


  // tft.fillCircle(asteroid_posn[8][0], asteroid_posn[8][1], 3, YELLOW);
  if (checker[8] && millis() - pt_asteroids[8] >= t[8]) {
    asteroid_posn[8][1] += increment[8];
    asteroid_posn[8][0] += increment[8];
    pt_asteroids[8] = millis();
    tft.fillCircle(asteroid_posn[8][0] - increment[8], asteroid_posn[8][1] - increment[8], 3, BLACK);
    tft.fillCircle(asteroid_posn[8][0], asteroid_posn[8][1], 3, YELLOW);
  }
  if (asteroid_posn[8][1] >= 57) {
    GameOver(score, EEPROM.read(address));
    return 8;
  }
}


int shooter(int direction) {
  if (ammo == 0 && digitalRead(B) == 0) {
    ammo = 7;
    ammoDisplay(ammo);
    return 0;
  }
  if (digitalRead(C) == 0 && ammo > 0) {

    if (direction == 1) {
      tft.drawLine(64, 64, 64, 0, RED);
      delay(150);
      tft.drawLine(64, 64, 64, 0, BLACK);
      ammo--;
      ammoDisplay(ammo);
      return 1;
    } else if (direction == 2) {
      tft.drawLine(64, 64, 128, 0, RED);
      delay(150);
      tft.drawLine(64, 64, 128, 0, BLACK);
      ammo--;
      ammoDisplay(ammo);
      return 2;
    } else if (direction == 3) {
      tft.drawLine(64, 64, 128, 64, RED);
      delay(150);
      tft.drawLine(64, 64, 128, 64, BLACK);
      ammo--;
      ammoDisplay(ammo);
      return 3;
    } else if (direction == 4) {
      tft.drawLine(64, 64, 128, 128, RED);
      delay(150);
      tft.drawLine(64, 64, 128, 128, BLACK);
      ammo--;
      ammoDisplay(ammo);
      return 4;
    } else if (direction == 5) {
      tft.drawLine(64, 64, 64, 128, RED);
      delay(150);
      tft.drawLine(64, 64, 64, 128, BLACK);
      ammo--;
      ammoDisplay(ammo);
      return 5;
    } else if (direction == 6) {
      tft.drawLine(64, 64, 0, 128, RED);
      delay(150);
      tft.drawLine(64, 64, 0, 128, BLACK);
      ammo--;
      ammoDisplay(ammo);
      return 6;
    } else if (direction == 7) {
      tft.drawLine(64, 64, 0, 64, RED);
      delay(150);
      tft.drawLine(64, 64, 0, 64, BLACK);
      ammo--;
      ammoDisplay(ammo);
      return 7;
    } else if (direction == 8) {
      tft.drawLine(64, 64, 0, 0, RED);
      delay(150);
      tft.drawLine(64, 64, 0, 0, BLACK);
      ammo--;
      ammoDisplay(ammo);
      return 8;
    }
  } else {
    return NULL;
  }
}
bool collision(byte k) {
  if (k == 1 && asteroid_presence[1]) {
    // tft.fillCircle(64, asteroid_posn[1][1], 3, RED);
    tft.fillCircle(64, asteroid_posn[1][1], 3, BLACK);
    asteroid_posn[1][1] = asteroid_posn_reset[1][1];
    asteroid_presence[1] = 0;
    score++;
    return 1;
  } else if (k == 2 && asteroid_presence[2]) {
    tft.fillCircle(asteroid_posn[2][0], asteroid_posn[2][1], 3, BLACK);
    asteroid_posn[2][0] = asteroid_posn_reset[2][0];
    asteroid_posn[2][1] = asteroid_posn_reset[2][1];
    asteroid_presence[2] = 0;
    score++;
    return 1;
  } else if (k == 3 && asteroid_presence[3]) {
    tft.fillCircle(asteroid_posn[3][0], 64, 3, BLACK);
    asteroid_posn[3][0] = asteroid_posn_reset[3][0];
    asteroid_presence[3] = 0;
    score++;
    return 1;
  } else if (k == 4 && asteroid_presence[4]) {
    tft.fillCircle(asteroid_posn[4][0], asteroid_posn[4][1], 3, BLACK);
    asteroid_posn[4][0] = asteroid_posn_reset[4][0];
    asteroid_posn[4][1] = asteroid_posn_reset[4][1];
    asteroid_presence[4] = 0;
    score++;
    return 1;
  } else if (k == 5 && asteroid_presence[5]) {
    tft.fillCircle(64, asteroid_posn[5][1], 3, BLACK);
    asteroid_posn[5][1] = asteroid_posn_reset[5][1];
    asteroid_presence[5] = 0;
    score++;
    return 1;
  } else if (k == 6 && asteroid_presence[6]) {
    tft.fillCircle(asteroid_posn[6][0], asteroid_posn[6][1], 3, BLACK);
    asteroid_posn[6][0] = asteroid_posn_reset[6][0];
    asteroid_posn[6][1] = asteroid_posn_reset[6][1];
    asteroid_presence[6] = 0;
    score++;
    return 1;
  } else if (k == 7 && asteroid_presence[7]) {
    tft.fillCircle(asteroid_posn[7][0], 64, 3, BLACK);
    asteroid_posn[7][0] = asteroid_posn_reset[7][0];
    asteroid_presence[7] = 0;
    score++;
    return 1;
  } else if (k == 8 && asteroid_presence[8]) {
    tft.fillCircle(asteroid_posn[8][0], asteroid_posn[8][1], 3, BLACK);
    asteroid_posn[8][0] = asteroid_posn_reset[8][0];
    asteroid_posn[8][1] = asteroid_posn_reset[8][1];
    asteroid_presence[8] = 0;
    score++;
    return 1;
  } else {
    return 0;
  }
}
unsigned long pt_scatter = 0;
bool scatter(int t) {
  if ((millis() - pt_scatter >= t)) {
    tft.drawCircle(5, 124, 3, BLUE);
    if (!digitalRead(A)) {
      tft.drawLine(64, 64, 64, 0, BLUE);
      tft.drawLine(64, 64, 128, 0, BLUE);
      tft.drawLine(64, 64, 128, 64, BLUE);
      tft.drawLine(64, 64, 128, 128, BLUE);
      tft.drawLine(64, 64, 64, 128, BLUE);
      tft.drawLine(64, 64, 0, 128, BLUE);
      tft.drawLine(64, 64, 0, 64, BLUE);
      tft.drawLine(64, 64, 0, 0, BLUE);
      delay(150);
      tft.drawLine(64, 64, 64, 0, BLACK);
      tft.drawLine(64, 64, 128, 0, BLACK);
      tft.drawLine(64, 64, 128, 64, BLACK);
      tft.drawLine(64, 64, 128, 128, BLACK);
      tft.drawLine(64, 64, 64, 128, BLACK);
      tft.drawLine(64, 64, 0, 128, BLACK);
      tft.drawLine(64, 64, 0, 64, BLACK);
      tft.drawLine(64, 64, 0, 0, BLACK);
      if (asteroid_presence[1]) {
        tft.fillCircle(64, asteroid_posn[1][1], 3, BLACK);
        asteroid_posn[1][1] = asteroid_posn_reset[1][1];
        asteroid_presence[1] = 0;
        score++;
      }
      if (asteroid_presence[2]) {
        tft.fillCircle(asteroid_posn[2][0], asteroid_posn[2][1], 3, BLACK);
        asteroid_posn[2][0] = asteroid_posn_reset[2][0];
        asteroid_posn[2][1] = asteroid_posn_reset[2][1];
        asteroid_presence[2] = 0;
        score++;
      }
      if (asteroid_presence[3]) {
        tft.fillCircle(asteroid_posn[3][0], 64, 3, BLACK);
        asteroid_posn[3][0] = asteroid_posn_reset[3][0];
        asteroid_presence[3] = 0;
        score++;
      }
      if (asteroid_presence[4]) {
        tft.fillCircle(asteroid_posn[4][0], asteroid_posn[4][1], 3, BLACK);
        asteroid_posn[4][0] = asteroid_posn_reset[4][0];
        asteroid_posn[4][1] = asteroid_posn_reset[4][1];
        asteroid_presence[4] = 0;
        score++;
      }
      if (asteroid_presence[5]) {
        tft.fillCircle(64, asteroid_posn[5][1], 3, BLACK);
        asteroid_posn[5][1] = asteroid_posn_reset[5][1];
        asteroid_presence[5] = 0;
        score++;
      }
      if (asteroid_presence[6]) {
        tft.fillCircle(asteroid_posn[6][0], asteroid_posn[6][1], 3, BLACK);
        asteroid_posn[6][0] = asteroid_posn_reset[6][0];
        asteroid_posn[6][1] = asteroid_posn_reset[6][1];
        asteroid_presence[6] = 0;
        score++;
      }
      if (asteroid_presence[7]) {
        tft.fillCircle(asteroid_posn[7][0], 64, 3, BLACK);
        asteroid_posn[7][0] = asteroid_posn_reset[7][0];
        asteroid_presence[7] = 0;
        score++;
      }
      if (asteroid_presence[8]) {
        tft.fillCircle(asteroid_posn[8][0], asteroid_posn[8][1], 3, BLACK);
        asteroid_posn[8][0] = asteroid_posn_reset[8][0];
        asteroid_posn[8][1] = asteroid_posn_reset[8][1];
        asteroid_presence[8] = 0;
        score++;
      }
      pt_scatter = millis();
      return 1;
    } else {
      return 0;
    }
  } else {
    tft.drawCircle(5, 124, 3, BLACK);
    return 0;
  }
}


unsigned long pt_shield = 0;
bool shield(int t) {
  if ((millis() - pt_shield >= t)) {
    tft.drawCircle(5, 115, 3, CYAN);
    if (!digitalRead(D)) {
      tft.drawCircle(64, 64, 7, CYAN);
      delay(150);
      tft.drawCircle(64, 64, 7, BLACK);
      pt_shield = millis();
      return 1;
    }
  } else {
    tft.drawCircle(5, 115, 3, BLACK);
    return 0;
  }
}
void pattern_2() {
  // asteroid_presence[1] = 1;
  // asteroid_presence[3] = 1;
  // asteroid_presence[5] = 1;
  // asteroid_presence[7] = 1;
  // pattern();
  if (asteroid_presence[1] == 0 && asteroid_presence[3] == 0 && asteroid_presence[5] == 0 && asteroid_presence[7] == 0) {
    pattern_3();
  }
}
void pattern_3() {
  asteroid_presence[2] = 1;
  asteroid_presence[4] = 1;
  asteroid_presence[6] = 1;
  asteroid_presence[8] = 1;
  if (asteroid_presence[2] == 0 || asteroid_presence[4] == 0 || asteroid_presence[6] == 0 || asteroid_presence[8] == 0) {
    pattern_3();
  }
}
int sum=1;
bool check[9]={1,1,0,0,0,0,0,0,0};
void pattern_1() {
  if (asteroid_presence[1] == 0 && check[1]==1) {
    asteroid_presence[2] = 1;
    check[1]=0;
    check[2]=1;
  }
  else if (asteroid_presence[2] == 0 && check[2]==1) {
     asteroid_presence[3] = 1;
     check[2]=0;
     check[3]=1;
  }
  else if (asteroid_presence[3] == 0 && check[3]==1) {
    asteroid_presence[4] = 1;
    check[3]=0;
    check[4]=1;
  }
  else if (asteroid_presence[4] == 0 && check[4]==1) {
    asteroid_presence[5] = 1;
    check[4]=0;
    check[5]=1;
  }
  else if (asteroid_presence[5] == 0 && check[5]==1) {
    asteroid_presence[6] = 1;
    check[5]=0;
    check[6]=1;
  }
  else if (asteroid_presence[6] == 0 && check[6]==1) {
    asteroid_presence[7] = 1;
    check[6]=0;
    check[7]=1;
  }
  else if (asteroid_presence[7] == 0 && check[7]==1) {
    asteroid_presence[8] = 1;
    check[7]=0;
    check[8]=1;
  }
  else if (asteroid_presence[8] == 0 check[8]==1) {
    pattern_3();
    check[8]=0;
  }
  for(int i=1;i<=8;i++){
    sum+=check[i];
  }
  if(sum==0){
    pattern_3();
  }
}
byte asteroid_increment[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
void loop() {
  // Serial.println(EEPROM.read(address));
  if (digitalRead(F) == 0) {
    pause(score, EEPROM.read(address));
    delay(100);
  }
  if (digitalRead(E) == 0) {
    GameOver(score, EEPROM.read(address));
    delay(100);
  }
  // Serial.println(shooter(point(15)));
  if (collision(shooter(point(15))) || scatter(20000)) {

    scoreDisplay(score);
  }

  // if (asteroid_presence[1] == 0 && asteroid_speed[1] >= 0) {
  //   asteroid_speed[1] -= 10;
  //   // asteroid_increment[i]++;
  //   asteroid_presence[1]++;
  // }
  // for(int i = 1 ; i <= 8 ;i++){
  //   if(asteroid_presence[i]==0 && asteroid_speed[i]>=0){
  //     asteroid_speed[i]-=100;
  //     // asteroid_increment[i]++;
  //     asteroid_presence[i]++;
  //   }
  // }

  // scatter(1000);
  // shield(1000);
  pattern_1();
  asteroids(asteroid_speed, asteroid_presence, asteroid_increment);
}