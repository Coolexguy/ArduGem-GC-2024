#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library
#include <SPI.h>


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
// #define JB 8
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
float p = 3.1415926;
float root2 = 1.41421356237;
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
void point(byte x) {
  switch (dir()) {
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
      tft.drawLine(64 + (x / root2), 64 - (x / root2), 64, 64, BLACK);  //case2
      tft.drawLine(64 - (x / root2), 64 + (x / root2), 64, 64, BLACK);  //case6
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
  randomSeed(analogRead(A5));//random seed

  // startUp();
  tft.fillScreen(ST7735_BLACK);
  scoreSetup();
  playerSetup();
  ammoSetup();
  scoreDisplay(0);
  ammoDisplay(7);
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
void startUp() {
    tft.fillRect(4, 4,120,120, RED);
    tft.fillRect(6, 6,116,116, BLACK);
    tft.setTextColor(CYAN);
    tft.setCursor(18, 10);
    tft.setTextSize(2);
    tft.print("ASTEROID");

    tft.setTextColor(PURPLE);
    tft.setCursor(24, 30);
    tft.setTextSize(2);
    tft.print("SHOOTER");


while(digitalRead(E)){
  tft.setTextColor(WHITE);
  tft.setCursor(18, 50);
  tft.setTextSize(1);
  tft.print("Press E to start");

  tft.setTextColor(WHITE);
  tft.setCursor(4, 60);
  tft.setTextSize(1);
  tft.print("Press F to see rules");
  if(digitalRead(F)==0){
    delay(1000);
    while(digitalRead(F)){
      int f = 0;
      if(f==0){
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(WHITE);
  tft.setCursor(4, 4);
  tft.setTextSize(1);
  tft.print("Rules:");
  tft.setCursor(4, 14);
  tft.print("1. Use the joystick to move the");
  tft.setCursor(4, 24);
  tft.print("player and shoot the asteroids");
  tft.setCursor(4, 34);
  tft.print("2. Press E to shoot");
  tft.setCursor(4, 44);
  tft.print("3. Press F to pause");
  tft.setCursor(4, 54);
  tft.print("4. Press E to resume");
  tft.setCursor(4, 64);
  tft.print("5. Press F to restart");
  tft.setCursor(4, 74);
  tft.print("6. Press E to exit");
  tft.setCursor(4, 84);
  tft.print("7. Press F to see rules");
  tft.setCursor(4, 94);
  tft.print("8. Press E to start");
  tft.setCursor(4, 104);
  tft.print("9. Press F to see rules");
  tft.setCursor(4, 114);
  tft.print("10. Press E to start");
  f++;
    }

  }

}
}

//     int f = 0;
//   while(digitalRead(F)){
//     if(f==0){

//   tft.fillScreen(ST7735_BLACK);
//   tft.setTextColor(WHITE);
//   tft.setCursor(4, 4);
//   tft.setTextSize(1);
//   tft.print("Rules:");
//   tft.setCursor(4, 14);
//   tft.print("1. Use the joystick to move the");
//   tft.setCursor(4, 24);
//   tft.print("player and shoot the asteroids");
//   tft.setCursor(4, 34);
//   tft.print("2. Press E to shoot");
//   tft.setCursor(4, 44);
//   tft.print("3. Press F to pause");
//   tft.setCursor(4, 54);
//   tft.print("4. Press E to resume");
//   tft.setCursor(4, 64);
//   tft.print("5. Press F to restart");
//   tft.setCursor(4, 74);
//   tft.print("6. Press E to exit");
//   tft.setCursor(4, 84);
//   tft.print("7. Press F to see rules");
//   tft.setCursor(4, 94);
//   tft.print("8. Press E to start");
//   tft.setCursor(4, 104);
//   tft.print("9. Press F to see rules");
//   tft.setCursor(4, 114);
//   tft.print("10. Press E to start");
//   f++;
//     }
// }
}
 

void loop() {
// point(15); 



}
