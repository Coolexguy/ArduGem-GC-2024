#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
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
byte dir()
{
  int x = analogRead(X);
  int y = analogRead(Y);
  if (x > 500 && x < 510 && y > 550)
  {
    return 1;
  }
  else if (x > 550 && y > 550)
  {
    return 2;
  }
  else if (y > 500 && y < 520 && x > 550)
  {
    return 3;
  }
  else if (y < 500 && x > 520)
  {
    return 4;
  }
  else if (x > 500 && x < 520 && y < 500)
  {
    return 5;
  }
  else if (x < 500 && y < 500)
  {
    return 6;
  }
  else if (x < 500 && y > 500 && y < 520)
  {
    return 7;
  }
  else if (x < 500 && y > 550)
  {
    return 8;
  }
  else
  {
    return 0;
  }
}
void point(byte x)
{
  switch (dir())
  {
  case 1:
    tft.drawLine(64, 64 - x, 64, 64, RED);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    break;
  case 2:
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    break;
  case 3:
    tft.drawLine(64 + x, 64, 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    break;
  case 4:
    tft.drawLine(64 + (x / root2), 64 + (x / root2), 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    break;
  case 5:
    tft.drawLine(64, 64 + x, 64, 64, RED);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    break;
  case 6:
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    break;
  case 7:
    tft.drawLine(64 - x, 64, 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    break;
  case 8:
    tft.drawLine(64 - (x / root2), 64 - (x / root2), 64, 64, RED);
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);
    break;
  default:
    tft.drawLine(64, 0, 64, 128, BLACK);
    tft.drawLine(0, 64, 128, 64, BLACK);
    tft.drawLine(0, 0, 128, 128, BLACK);
    tft.drawLine(0, 128, 128, 0, BLACK);
    tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK); // case2
    tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK); // case6
    break;
  }
}
void setup()
{
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
  tft.initR(INITR_BLACKTAB); // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);

  // scoreSetup();
  // playerSetup();
  // ammoSetup();

  pinMode(A5, INPUT);
  randomSeed(analogRead(A5)); // random seed

  startUp();
  tft.fillScreen(ST7735_BLACK);
  scoreSetup();
  playerSetup();
  ammoSetup();
  scoreDisplay(0);
  ammoDisplay(7);
  // EEPROM.update(address,99);
}
void scoreSetup()
{
  tft.setTextSize(1);
  tft.setTextColor(CYAN);
  tft.setCursor(80, 5);
  tft.print("Score:");
}
void ammoSetup()
{
  tft.setTextSize(1);
  tft.setTextColor(CYAN);
  tft.setCursor(86, 123);
  tft.print("Ammo:");
  //  tft.drawLine(112,0,112,128, RED);// for alignment
}
void playerSetup()
{
  tft.fillCircle(64, 64, 5, PURPLE);
}
void scoreDisplay(byte k)
{
  tft.fillRect(115, 5, 11, 7, BLACK);
  tft.setTextColor(CYAN);
  tft.setCursor(115, 5);
  tft.print(k);
}
void ammoDisplay(byte a)
{
  tft.fillRect(115, 123, 5, 9, BLACK);
  tft.setTextColor(CYAN);
  tft.setCursor(115, 123);
  tft.print(a);
}
void startScreenSetup()
{
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
void startUp(){
  startScreenSetup();

  while (digitalRead(E) && digitalRead(F))
  {

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
  while (digitalRead(F))
  {
    if (f == 0)
    {
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
void pause(byte currentScore, byte highScore)
{
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
  while (digitalRead(F))
  {
  }
  tft.fillScreen(ST7735_BLACK);

  scoreSetup();
  playerSetup();
  ammoSetup();
  scoreDisplay(0);
  ammoDisplay(7);
}
void GameOver(byte currentScore, byte highScore){

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

    delay(100);
  while (digitalRead(E))
  {
  }
  tft.fillScreen(ST7735_BLACK);

  scoreSetup();
  playerSetup();
  ammoSetup();
  scoreDisplay(0);
  ammoDisplay(7);
}

void loop()
{
  point(15);
  // Serial.println(EEPROM.read(address));
  if (digitalRead(F) == 0)
  {
    pause(EEPROM.read(address), EEPROM.read(address));
    // GameOver(EEPROM.read(address), EEPROM.read(address));
    delay(100);
  }
    if (digitalRead(E) == 0)
  {
    // pause(EEPROM.read(address), EEPROM.read(address));
    GameOver(EEPROM.read(address), EEPROM.read(address));
    delay(100);
  }

}