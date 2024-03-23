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
// int posx[4] = { 64, 150, 64, -20 };
// int posy[4] = { -5, 64, 168, 64 };  // horizintal + vertical asteroids
int posx[4] = { 64, random(130,160), 64, -random(10,30) };
int posy[4] = { -random(10,30), 64, random(130,160), 64 };

int psx[4] = { 148, 135, -15, -5 };
int psy[4] = { -20, 135, 133, -5 };  // diagonals
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
int point(byte x) {
  switch (dir()) {
    case 1:
      tft.drawLine(64, 64 - x, 64, 64, RED);
      tft.drawLine(0, 64, 128, 64, BLACK);
      tft.drawLine(0, 0, 128, 128, BLACK);
      tft.drawLine(0, 128, 128, 0, BLACK);
      tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
      tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
      return 1;
      break;
    case 2:
      tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, RED);
      tft.drawLine(64, 0, 64, 128, BLACK);
      tft.drawLine(0, 64, 128, 64, BLACK);
      tft.drawLine(0, 0, 128, 128, BLACK);
      tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
      return 2;
      break;
    case 3:
      tft.drawLine(64 + x, 64, 64, 64, RED);
      tft.drawLine(64, 0, 64, 128, BLACK);
      tft.drawLine(0, 0, 128, 128, BLACK);
      tft.drawLine(0, 128, 128, 0, BLACK);
      tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
      tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
      return 3;
      break;
    case 4:
      tft.drawLine(64 + (x / root2), 64 + (x / root2), 64, 64, RED);
      tft.drawLine(64, 0, 64, 128, BLACK);
      tft.drawLine(0, 64, 128, 64, BLACK);
      tft.drawLine(0, 128, 128, 0, BLACK);
      tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
      tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
      return 4;
      break;
    case 5:
      tft.drawLine(64, 64 + x, 64, 64, RED);
      tft.drawLine(0, 64, 128, 64, BLACK);
      tft.drawLine(0, 0, 128, 128, BLACK);
      tft.drawLine(0, 128, 128, 0, BLACK);
      tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
      tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
      return 5;
      break;
    case 6:
      tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, RED);
      tft.drawLine(64, 0, 64, 128, BLACK);
      tft.drawLine(0, 64, 128, 64, BLACK);
      tft.drawLine(0, 0, 128, 128, BLACK);
      tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
      return 6;
      break;
    case 7:
      tft.drawLine(64 - x, 64, 64, 64, RED);
      tft.drawLine(64, 0, 64, 128, BLACK);
      tft.drawLine(0, 0, 128, 128, BLACK);
      tft.drawLine(0, 128, 128, 0, BLACK);
      tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
      tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
      return 7;
      break;
    case 8:
      tft.drawLine(64 - (x / root2), 64 - (x / root2), 64, 64, RED);
      tft.drawLine(64, 0, 64, 128, BLACK);
      tft.drawLine(0, 64, 128, 64, BLACK);
      tft.drawLine(0, 128, 128, 0, BLACK);
      tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
      tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
      return 8;
      break;
    default:
      tft.drawLine(64, 0, 64, 128, BLACK);
      tft.drawLine(0, 64, 128, 64, BLACK);
      tft.drawLine(0, 0, 128, 128, BLACK);
      tft.drawLine(0, 128, 128, 0, BLACK);
      tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);  // case2
      tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);  // case6
      return 0;
      break;
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

  // scoreSetup();
  // playerSetup();
  // ammoSetup();

  pinMode(A5, INPUT);
  randomSeed(analogRead(A5));  // random seed

  startUp();
  tft.fillScreen(ST7735_BLACK);
  scoreSetup();
  playerSetup();
  ammoSetup();
  scoreDisplay(0);
  ammoDisplay(7);

  // EEPROM.update(address,99);
}

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
      tft.print("4. Press A to get");
      tft.setCursor(4, 64);
      tft.print("powerups.");
      tft.setCursor(4, 74);
      tft.print("5. Press D to use");
      tft.setCursor(4, 84);
      tft.print("powerups.");
      tft.setCursor(4, 94);
      tft.print("6. Press F to");
      tft.setCursor(4, 104);
      tft.print("Continue to play");
      tft.setCursor(4, 114);
      tft.print("7. Press F in game");
      tft.setCursor(4, 124);
      tft.print("to pause");

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
  tft.setCursor(90, 65);
  tft.setTextSize(2);
  tft.print(currentScore);

  tft.setTextSize(1);
  tft.setCursor(18, 90);
  tft.print("HIGH SCORE:");
  tft.setCursor(90, 85);
  tft.setTextSize(2);
  tft.print(highScore);

  delay(100);
  while (digitalRead(F)) {
  }
  tft.fillScreen(ST7735_BLACK);

  scoreSetup();
  playerSetup();
  ammoSetup();
  scoreDisplay(0);
  ammoDisplay(7);
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

  tft.setTextSize(1);
  tft.setCursor(18, 90);
  tft.print("HIGH SCORE:");
  tft.setCursor(90, 85);
  tft.setTextSize(2);
  tft.print(highScore);

  tft.setTextSize(1);
  tft.setCursor(10, 110);
  tft.print("Press E to restart");
  posx[0] = 64;
  posx[1] = random(130,160);
  posx[2] = 64;
  posx[3] = -random(10,30);

  posy[0] = -random(10,30);
  posy[1] = 64;
  posy[2] = random(130,160);
  posy[3] = 64;  //resetting values for vertical&horizontal
// int posx[4] = { 64, random(130,160), 64, -random(10,30) };
// int posy[4] = { -random(10,30), 64, random(130,160), 64 };

  psx[0] = 148;
  psx[1] = 135;
  psx[2] = -15;
  psx[3] = -5;

  psy[0] = -20;
  psy[1] = 135;
  psy[2] = 133;
  psy[3] = -5;  //resetting values for diagonals

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


// unsigned long eventinterval;
unsigned long prevtime = 0;
void multiple_asteroids(int x, unsigned long t) {
  for (int i = 0; i <= 55; i++) {
    unsigned int currentTime = millis();
    if (currentTime - prevtime >= t) {

      posx[1] -= x;
      posx[3] += x;
      posy[0] += x;
      posy[2] -= x;
      prevtime = currentTime;
      tft.fillCircle(posx[1] + 2, posy[1], 3, BLACK);
      tft.fillCircle(posx[1], posy[1], 3, YELLOW);
      tft.fillCircle(posx[3] - 2, posy[3], 3, BLACK);
      tft.fillCircle(posx[3], posy[3], 3, YELLOW);
      tft.fillCircle(posx[0], posy[0] - 2, 3, BLACK);
      tft.fillCircle(posx[0], posy[0], 3, YELLOW);
      tft.fillCircle(posx[2], posy[2] + 2, 3, BLACK);
      tft.fillCircle(posx[2], posy[2], 3, YELLOW);
      if (posx[1] <= 70) {
        GameOver(50, 99);
      }
      if (posx[3] >= 64) {
        GameOver(50, 99);
      }
      if (posy[0] >= 55) {
        GameOver(50, 99);
      }
      if (posy[2] <= 64) {
        GameOver(50, 99);
      }
    }
  }
  point(15);
}

// ammoDisplay(ammo);
void diagonal_asteroids(byte x, unsigned long t) {
  unsigned int currentTime = millis();
  if (currentTime - prevtime >= t) {
    psx[1] -= 2;
    psy[1] -= 2;
    psx[0] -= 2;
    psy[0] += 2;
    psx[2] -= 2;
    psy[2] -= 2;
    psx[3] += 2;
    psy[3] -= 2;
    psx[4] += 2;
    psx[4] += 2;
    prevtime = currentTime;
    tft.fillCircle(psx[1] + 2, psy[1] + 2, 3, BLACK);
    tft.fillCircle(psx[1], psy[1], 3, YELLOW);
    tft.fillCircle(psx[3] - 2, psy[3] + 2, 3, BLACK);
    tft.fillCircle(psx[3], psy[3], 3, YELLOW);
    tft.fillCircle(psx[0] + 2, psy[0] - 2, 3, BLACK);
    tft.fillCircle(psx[0], psy[0], 3, YELLOW);
    tft.fillCircle(psx[2] + 2, psy[2] + 2, 3, BLACK);
    tft.fillCircle(psx[2], psy[2], 3, YELLOW);
    // if (posx[1] <= 64) {
    //   GameOver(50, 99);
    // }
    // if (posx[3] >= 64) {
    //   GameOver(50, 99);
    // }
    // if (posy[0] >= 64) {
    //   GameOver(50, 99);
    // }
    // if (posy[2] <= 64) {
    //   GameOver(50, 99);
    // }
  }
  point(15);
}
int ammo = 7;
void shooter() {
  int prevt = 0;
  int shoot = point(15);
  unsigned int currentTime = millis();
  if (ammo == 0 && digitalRead(B) == 0) {
    if (currentTime - prevt >= 1000) {
      ammo = 7;
      ammoDisplay(ammo);
      currentTime = prevt;
    }
  }
  if (digitalRead(C) == 0 && ammo > 0) {
    switch (shoot) {
      case 1:
        tft.drawLine(64, 64, 64, 0, RED);
        delay(150);
        tft.drawLine(64, 64, 64, 0, BLACK);
        ammo--;
        ammoDisplay(ammo);
        // return 1;
        break;
      case 2:
        tft.drawLine(64, 64, 128, 0, RED);
        delay(150);
        tft.drawLine(64, 64, 128, 0, BLACK);
        ammo--;
        ammoDisplay(ammo);
        // return 2;
        break;
      case 3:
        tft.drawLine(64, 64, 128, 64, RED);
        delay(150);
        tft.drawLine(64, 64, 128, 64, BLACK);
        ammo--;
        ammoDisplay(ammo);
        // return 3;
        break;
      case 4:
        tft.drawLine(64, 64, 128, 128, RED);
        delay(150);
        tft.drawLine(64, 64, 128, 128, BLACK);
        ammo--;
        ammoDisplay(ammo);
        // return 4;
        break;
      case 5:
        tft.drawLine(64, 64, 64, 128, RED);
        delay(150);
        tft.drawLine(64, 64, 64, 128, BLACK);
        ammo--;
        ammoDisplay(ammo);
        // return 5;
        break;
      case 6:
        tft.drawLine(64, 64, 0, 128, RED);
        delay(150);
        tft.drawLine(64, 64, 0, 128, BLACK);
        ammo--;
        ammoDisplay(ammo);
        break;
      case 7:
        tft.drawLine(64, 64, 0, 64, RED);
        delay(150);
        tft.drawLine(64, 64, 0, 64, BLACK);
        ammo--;
        ammoDisplay(ammo);
        // return 7;
        break;
      case 8:
        tft.drawLine(64, 64, 0, 0, RED);
        delay(150);
        tft.drawLine(64, 64, 0, 0, BLACK);
        ammo--;
        ammoDisplay(ammo);
        // return 8;
        break;
      default:
        break;
    }
  }
}
void destroy() {
}
void loop() {
  // point(15);
  // Serial.println(EEPROM.read(address));
  if (digitalRead(F) == 0) {
    pause(EEPROM.read(address), EEPROM.read(address));
    // GameOver(EEPROM.read(address), EEPROM.read(address));
    delay(100);
  }
  if (digitalRead(E) == 0) {
    // pause(EEPROM.read(address), EEPROM.read(address));
    GameOver(EEPROM.read(address), EEPROM.read(address));

    delay(100);
  }
  // diagonal_asteroids();
  multiple_asteroids(2, 1000);
  shooter();
}