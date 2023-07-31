#include <LiquidCrystal_I2C.h>

//Specify decode protocol
#define DECODE_NEC
#include <IRremote.hpp>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int REC_PIN = 7;

void setup() {

  //Setup IR
  IrReceiver.begin(REC_PIN, ENABLE_LED_FEEDBACK);
  
  //Setup LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reciever ready");
}

void loop() {
   if(IrReceiver.decode()){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(IrReceiver.decodedIRData.command, HEX);
      lcd.setCursor(0,1);
      lcd.print(IrReceiver.decodedIRData.command);
      IrReceiver.resume();
   }
}

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
