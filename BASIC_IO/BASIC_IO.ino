//MAPPING FOR ELEGOO NEC REMOTE 
//BUTTON - HEX, INT
//power - 45, 69
//vol+ - 46, 70
//func/stop - 47, 71 
//reverse - 44, 68
//play/pause - 40, 64 
//forward - 43, 67
//down - 7, 7
//vol- - 15, 21
//up - 9, 9
//0 - 16, 22
//eq - 19, 25
//st/rept - D, 13
//1 - C, 12
//2 - 18, 24
//3 - 5E, 94
//4 - 8, 8
//5 - 1C, 28
//6 - 5A, 90
//7 - 42, 66
//8 - 52, 82
//9 - 4A, 74

#include <LiquidCrystal_I2C.h>

//Specify decode protocol
#define DECODE_NEC
#include <IRremote.hpp>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte REC_PIN = 7;

//Button constants
const byte PWR = 69;
const byte VOL_UP = 70;
const byte FUNC = 71;
const byte REV = 68;
const byte PLAY = 64;
const byte FWD = 67;
const byte DWN = 7;
const byte VOL_DWN = 21;
const byte UP = 9;
const byte ZERO = 22;
const byte EQ = 25;
const byte ST = 13;
const byte ONE = 12;
const byte TWO = 24;
const byte THREE = 94;
const byte FOUR = 8;
const byte FIVE = 28;
const byte SIX = 90;
const byte SEVEN = 66;
const byte EIGHT = 82;
const byte NINE = 74; 

const String noPrgmMsg = "Btn Lacks A Prgm";

const byte NUMBERS[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

void setup() {

  //Setup IR
  IrReceiver.begin(REC_PIN, ENABLE_LED_FEEDBACK);
  
  //Setup LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  executeCommand(PWR);

  randomSeed(analogRead(0));
}

void loop() {
   if(IrReceiver.decode()){
      executeCommand(IrReceiver.decodedIRData.command);
      IrReceiver.resume();
   }
}

//void gamble() {
//  byte luckyNum = random(1, 11);
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Pick Num 1-10");
//  bool validNumGiven = false;
//  while(!validNumGiven) {
//    if(IrReceiver.decode()){
//      for (byte i = 0; i < 10; i++) {
//        if(IrReceiver.decodedIRData.command == NUMBERS[i]){
//          
//        }
//      }
//    }
//  }
//}

void coinFlip() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Flipping...");
  byte result = random(2);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(result);
  lcd.setCursor(0,1);
  if(result == 0) {
    lcd.print("HEADS");
  }
  if (result == 1) {
    lcd.print("TAILS");
  }
}
void executeCommand(int command) {
  switch(command) {
    //PLAY/PAUSE
    case PWR:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Ino OS v0.1");
      lcd.setCursor(0,1);
      lcd.print("Push Any Button");
      break;
    case VOL_UP:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("VOL+");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case FUNC:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("FUNC/STOP");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case REV:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("REVERSE");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case PLAY:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PLAY/PAUSE");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case FWD:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("FORWARD");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case DWN:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DOWN");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case VOL_DWN:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("VOL-");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case UP:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("UP");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case ZERO:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("0");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case EQ:
      coinFlip();
      break;
    case ST:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ST/REPT");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case ONE:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("1");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case TWO:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("2");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case THREE:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("3");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case FOUR:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("4");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case FIVE:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("5");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case SIX:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("6");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case SEVEN:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("7");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case EIGHT:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("8");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    case NINE:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("9");
      lcd.setCursor(0,1);
      lcd.print(noPrgmMsg);
      break;
    // Do nothing if revciver reads an unknown input
  }
}
