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
byte reset;
// int pos1x, pos1y;
int posx[4] = { 64, random(130, 160), 64, -random(10, 30) };
int posy[4] = { -random(10, 30), 64, random(130, 160), 64 };
int psx[4] = { 148, 135, -5, -5 };
int psy[4] = { -20, 135, 133, -5 };  // diagonals
int pos1x[8] = { 64, 128, 128, 128, 64, 0, 0 };
int pos1y[8] = { 0, 0, 64, 128, 128, 128, 64, 0 };
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
  posx[1] = random(130, 160);
  posx[2] = 64;
  posx[3] = -random(10, 30);

  posy[0] = -random(10, 30);
  posy[1] = 64;
  posy[2] = random(130, 160);
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
  if (reset == 1) {
    pos1x[0] = 64, pos1y[0] = 0;
  } else if (reset == 2) {
    pos1x[1] = 128, pos1y[1] = 0;
  } else if (reset == 3) {
    pos1x[2] = 128, pos1y[2] = 64;
  } else if (reset == 4) {
    pos1x[3] = 128, pos1y[3] = 128;
  } else if (reset == 5) {
    pos1x[4] = 64, pos1y[4] = 128;
  } else if (reset == 6) {
    pos1x[5] = 0, pos1y[5] = 128;
  } else if (reset == 7) {
    pos1x[6] = 0, pos1y[6] = 64;
  } else if (reset == 8) {
    pos1x[7] = 0, pos1y[7] = 0;
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

void positioning() {
  posx[0] = 64;
  posx[1] = random(130, 160);
  posx[2] = 64;
  posx[3] = -random(10, 30);

  posy[0] = -random(10, 30);
  posy[1] = 64;
  posy[2] = random(130, 160);
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
  if (reset == 1) {
    pos1x[0] = 64, pos1y[0] = 0;
  } else if (reset == 2) {
    pos1x[1] = 128, pos1y[1] = 0;
  } else if (reset == 3) {
    pos1x[2] = 128, pos1y[2] = 64;
  } else if (reset == 4) {
    pos1x[3] = 128, pos1y[3] = 128;
  } else if (reset == 5) {
    pos1x[4] = 64, pos1y[4] = 128;
  } else if (reset == 6) {
    pos1x[5] = 0, pos1y[5] = 128;
  } else if (reset == 7) {
    pos1x[6] = 0, pos1y[6] = 64;
  } else if (reset == 8) {
    pos1x[7] = 0, pos1y[7] = 0;
  }
}
// unsigned long eventinterval;
unsigned long prevtime = 0;
void multiple_asteroids(int x, unsigned long t) {
  // for (int i = 0; i <= 55; i++) {
  // unsigned int currentTime = millis();
  if (millis() - prevtime >= t) {
    posx[1] -= x;
    posx[3] += x;
    posy[0] += x;
    posy[2] -= x;
    prevtime = millis();
    tft.fillCircle(posx[1] + x, posy[1], 3, BLACK);
    tft.fillCircle(posx[1], posy[1], 3, YELLOW);
    tft.fillCircle(posx[3] - x, posy[3], 3, BLACK);
    tft.fillCircle(posx[3], posy[3], 3, YELLOW);
    tft.fillCircle(posx[0], posy[0] - x, 3, BLACK);
    tft.fillCircle(posx[0], posy[0], 3, YELLOW);
    tft.fillCircle(posx[2], posy[2] + x, 3, BLACK);
    tft.fillCircle(posx[2], posy[2], 3, YELLOW);
    // flag+=x;

    // destroy(flag,l);
    if (shooter() == 1) {
      tft.fillCircle(posx[0], posy[0], 3, BLACK);  //for destroying asteroids
      posy[0] = -9827;
    } else if (shooter() == 3) {
      tft.fillCircle(posx[1], posy[1], 3, BLACK);
      posx[1] = 3475;

    } else if (shooter() == 5) {
      tft.fillCircle(posx[2], posy[2], 3, BLACK);
      posy[2] = 9827;
    } else if (shooter() == 7) {
      tft.fillCircle(posx[3], posy[3], 3, BLACK);
      posx[3] = -3475;
    }
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
    // }
  }
  point(15);
}
int flag[4];
// int flag=0;
// ammoDisplay(ammo);
void diagonal_asteroids(byte x, unsigned long t) {
  unsigned int currentTime = millis();
  if (currentTime - prevtime >= t) {
    psx[1] -= x;
    psy[1] -= x;
    psx[0] -= x;
    psy[0] += x;
    psx[2] += x;
    psy[2] -= x;
    psx[3] += x;
    psy[3] += x;
    prevtime = currentTime;
    tft.fillCircle(psx[1] + x, psy[1] + x, 3, BLACK);
    tft.fillCircle(psx[1], psy[1], 3, YELLOW);
    tft.fillCircle(psx[3] - x, psy[3] - x, 3, BLACK);
    tft.fillCircle(psx[3], psy[3], 3, YELLOW);
    tft.fillCircle(psx[0] + x, psy[0] - x, 3, BLACK);
    tft.fillCircle(psx[0], psy[0], 3, YELLOW);
    tft.fillCircle(psx[2] - x, psy[2] + x, 3, BLACK);
    tft.fillCircle(psx[2], psy[2], 3, YELLOW);
    if (shooter() == 2) {
      tft.fillCircle(psx[0], psy[0], 3, BLACK);  //for destroying asteroids
      psx[0] = 3475;
      psy[0] = -9827;
      flag[0] = 0;
      ;
    } else if (shooter() == 4) {
      tft.fillCircle(psx[1], psy[1], 3, BLACK);
      psx[1] = 3475;
      psy[1] = 9827;
      flag[1] = 1;
    } else if (shooter() == 6) {
      tft.fillCircle(psx[2], psy[2], 3, BLACK);
      psx[2] = 3475;
      psy[2] = 9827;
      flag[2] = 2;
    } else if (shooter() == 8) {
      tft.fillCircle(psx[3], psy[3], 3, BLACK);
      psx[3] = -3475;
      psy[3] = -9827;
      flag[3] = 3;
    }
    if (flag[0] == 0 && flag[1] == 1 && flag[2] == 2 && flag[3] == 3) {
      positioning();
      multiple_asteroids(2, 500);
    }
    if (psy[0] >= 64 && psx[0] <= 64) {
      GameOver(50, 99);
    } else if (psy[1] <= 64 && psx[1] <= 64) {
      GameOver(50, 99);
    } else if (psy[2] <= 64 && psx[2] >= 64) {
      GameOver(50, 99);
    } else if (psy[3] >= 64 && psx[3] >= 64) {
      GameOver(50, 99);
    }
  }
  point(15);
}
byte asteroids(int x, int t) {
  // unsigned long currentTime = millis();
  if (x == 1) {
    // pos1x = 64, pos1y = 0;
    // while (pos1y >= 54) {
    tft.fillCircle(64, pos1y[0], 3, YELLOW);
    if (millis() - prevtime >= t) {
      pos1y[0] += 2;
      prevtime = millis();
      tft.fillCircle(64, pos1y[0] - 2, 3, BLACK);
      tft.fillCircle(64, pos1y[0], 3, YELLOW);
    }
    if (pos1y[0] >= 54) {
      GameOver(50, 99);
      return 1;
    }
    point(15);
    // }
  }
  if (x == 2) {
    // pos1x = 128, pos1y = 0;
    // while (pos1y <= 64 && pos1x >= 64) {
    tft.fillCircle(pos1x[1], pos1y[1], 3, YELLOW);
    if (millis() - prevtime >= t) {
      pos1y[1] += 1;
      pos1x[1] -= 1;
      prevtime = millis();
      tft.fillCircle(pos1x[1] + 1, pos1y[1] - 1, 3, BLACK);
      tft.fillCircle(pos1x[1], pos1y[1], 3, YELLOW);
      // int l = shooter();
      // destroy(5, l);
    }
    if (pos1y[1] >= 64 && pos1x[1] <= 64) {
      GameOver(50, 99);
      return 2;
    }
    point(15);
    // }
  }
  if (x == 3) {
    // pos1x = 128, pos1y = 64;
    // while (pos1x >= 68) {
    tft.fillCircle(pos1x[2], 64, 3, YELLOW);
    // unsigned long currentTime = millis();
    if (millis() - prevtime >= t) {
      pos1x[2] -= 1;
      prevtime = millis();
      tft.fillCircle(pos1x[2] + 1, 64, 3, BLACK);
      tft.fillCircle(pos1x[2], 64, 3, YELLOW);
      // int l = shooter();
      // destroy(5, l);
    }
    if (pos1x[2] <= 68) {
      GameOver(50, 99);
      return 3;
    }
    point(15);
  }
  // }
  if (x == 4) {
    // pos1x = 128, pos1y = 128;
    // while (pos1y >= 64 && pos1x >= 64) {
    tft.fillCircle(pos1x[3], pos1y[3], 3, YELLOW);
    unsigned long currentTime = millis();
    if (millis() - prevtime >= t) {
      pos1y[3] -= 1;
      pos1x[3] -= 1;
      prevtime = millis();
      tft.fillCircle(pos1x[3] + 1, pos1y[3] + 1, 3, BLACK);
      tft.fillCircle(pos1x[3], pos1y[3], 3, YELLOW);
      // int l = shooter();
      // destroy(5, l);
    }
    if (pos1y[3] <= 64 && pos1x[3] <= 64) {
      GameOver(50, 99);
      return 4;
    }
    point(15);
  }
  if (x == 5) {
    pos1x[4] = 64, pos1y[4] = 128;
    while (pos1y >= 60) {
      tft.fillCircle(64, pos1y[4], 3, YELLOW);
      unsigned long currentTime = millis();
      if (currentTime - prevtime >= t) {
        pos1y[4] -= 1;
        prevtime = currentTime;
        tft.fillCircle(64, pos1y[4] + 1, 3, BLACK);
        tft.fillCircle(64, pos1y[4], 3, YELLOW);
        // int l=shooter();
        // destroy(5,l);
      }
      if (pos1y[4] <= 60) {
        GameOver(50, 99);
        return 5;
      }
      point(15);
    }
  }
  if (x == 6) {
    // pos1x[5] = 0, pos1y[5] = 128;
    // while (pos1y >= 64 && pos1x <= 64) {
    tft.fillCircle(pos1x[5], pos1y[5], 3, YELLOW);
    // unsigned long currentTime = millis();
    if (millis() - prevtime >= t) {
      pos1y[5] -= 1;
      pos1x[5] += 1;
      prevtime = millis();
      tft.fillCircle(pos1x[5] - 1, pos1y[5] + 1, 3, BLACK);
      tft.fillCircle(pos1x[5], pos1y[5], 3, YELLOW);
      // int l = shooter();
      // destroy(5, l);
    }
    if (pos1y[5] <= 64 && pos1x[5] >= 64) {
      GameOver(50, 99);
      return 6;
    }
    point(15);
    // }
  }
  if (x == 7) {
    tft.fillCircle(pos1x[6], 64, 3, YELLOW);
    if (millis() - prevtime >= t) {
      pos1x[6] += 1;
      prevtime = millis();
      tft.fillCircle(pos1x[6] - 1, 64, 3, BLACK);
      tft.fillCircle(pos1x[6], 64, 3, YELLOW);
    }
    if (pos1x[6] >= 60) {
      GameOver(50, 99);
      return 7;
    }
    point(15);
  }
  if (x == 8) { 
    tft.fillCircle(pos1x[7], pos1y[7], 3, YELLOW);
    if (millis() - prevtime >= t) {
      pos1y[7] += 1;
      pos1x[7] += 1;
      prevtime = millis();
      tft.fillCircle(pos1x[7] - 1, pos1y[7] - 1, 3, BLACK);
      tft.fillCircle(pos1x[7], pos1y[7], 3, YELLOW);
    }
    if (pos1y[7] >= 64 && pos1x[7] >= 64) {
      GameOver(50, 99);
      return 8;
    }
    point(15);
  }
}

int ammo = 7;
int shooter() {
  int prevt = 0;
  if (ammo == 0 && digitalRead(B) == 0) {
    ammo = 7;
    ammoDisplay(ammo);
  }
  if (digitalRead(C) == 0 && ammo > 0) {
    switch (dir()) {
      case 1:
        tft.drawLine(64, 64, 64, 0, RED);
        delay(150);
        tft.drawLine(64, 64, 64, 0, BLACK);
        ammo--;
        ammoDisplay(ammo);
        return 1;
      case 2:
        tft.drawLine(64, 64, 128, 0, RED);
        delay(150);
        tft.drawLine(64, 64, 128, 0, BLACK);
        ammo--;
        ammoDisplay(ammo);
        return 2;
      case 3:
        tft.drawLine(64, 64, 128, 64, RED);
        delay(150);
        tft.drawLine(64, 64, 128, 64, BLACK);
        ammo--;
        ammoDisplay(ammo);
        return 3;
        // destroy();
        // break;
      case 4:
        tft.drawLine(64, 64, 128, 128, RED);
        delay(150);
        tft.drawLine(64, 64, 128, 128, BLACK);
        ammo--;
        ammoDisplay(ammo);
        return 4;
        // destroy();
        // break;
      case 5:
        tft.drawLine(64, 64, 64, 128, RED);
        delay(150);
        tft.drawLine(64, 64, 64, 128, BLACK);
        ammo--;
        ammoDisplay(ammo);
        return 5;
        // destroy();
        // break;
      case 6:
        tft.drawLine(64, 64, 0, 128, RED);
        delay(150);
        tft.drawLine(64, 64, 0, 128, BLACK);
        ammo--;
        ammoDisplay(ammo);
        return 6;
        // destroy();
        // break;
      case 7:
        tft.drawLine(64, 64, 0, 64, RED);
        delay(150);
        tft.drawLine(64, 64, 0, 64, BLACK);
        ammo--;
        ammoDisplay(ammo);
        return 7;
        // destroy();
        // break;
      case 8:
        tft.drawLine(64, 64, 0, 0, RED);
        delay(150);
        tft.drawLine(64, 64, 0, 0, BLACK);
        ammo--;
        ammoDisplay(ammo);
        return 8;
        // destroy();
        // break;
      default:
        break;
    }
  }
}

/*void destroy(int k, int m) {
  if (m == 1) {
    pos1x = -3265, pos1y = 9827;
    posx[0] = 3475;
    posy[0] = -9827;
    tft.fillCircle(64, k, 5, BLACK);
    score++;
    scoreDisplay(score);
  } else if (m == 2) {
    pos1x = 3475, pos1y = 9827;
    psx[0] = 3475;
    psy[0] = -9827;
    score++;
    scoreDisplay(score);
  } else if (m == 3) {
    pos1x = -3465, pos1y = 9827;
    posx[1] = 3475;
    posy[1] = 9827;
    tft.fillCircle(k, 64, 5, BLACK);
    score++;
    scoreDisplay(score);
  } else if (m == 4) {
    pos1x = 3475, pos1y = 9827;
    psx[1] = 3475;
    psy[1] = 9827;
    score++;
    scoreDisplay(score);
  } else if (m == 5) {
    pos1x = 3475, pos1y = 9827;
    posx[2] = 3475;
    posy[2] = 9827;
    score++;
    scoreDisplay(score);
  } else if (m == 6) {
    pos1x = 3475, pos1y = 9827;
    psx[2] = 3475;
    psy[2] = 9827;
    score++;
    scoreDisplay(score);
  } else if (m == 7) {
    pos1x = -3475, pos1y = 9827;
    posx[3] = -3475;
    posy[3] = 9827;
    score++;
    scoreDisplay(score);
  } else if (m == 8) {
    pos1x = -3475, pos1y = -9827;
    psx[3] = -3475;
    psy[3] = -9827;
    score++;
    scoreDisplay(score);
  }
}*/
void loop() {
  // point(15);
  // Serial.println(EEPROM.read(address));
  // delay(100);
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
  diagonal_asteroids(2,1000);
  // multiple_asteroids(2, 250);
  // byte gen = random(1, 9);
  // reset = asteroids(1, 100);
  shooter();
}