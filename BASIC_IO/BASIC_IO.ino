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

#include <ArducamSSD1306.h>
#define OLED_RESET  16
ArducamSSD1306 oled(OLED_RESET);

//Specify decode protocol
#define DECODE_NEC
#include <IRremote.hpp>
#define REC_PIN 7

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

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

bool oledOn = false;

void setup() {

  //Setup IR
  IrReceiver.begin(REC_PIN, ENABLE_LED_FEEDBACK);
  
  //Setup LCD
  oled.begin();
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);


  //Setup DHT
  dht.begin();

  //Randomize seed
  randomSeed(analogRead(0));
}

void loop() {
  if(IrReceiver.decode()){
    executeCommand(IrReceiver.decodedIRData.command);
    IrReceiver.resume();
  }
}

void printTitle(String title, char underlineChar = '=', bool clearDisp = true, bool updateDisp = true) {
  if(clearDisp) {
    oled.clearDisplay();
  }
  oled.setCursor(0,0);
  oled.print(title);
  oled.setCursor(0,10);
  String underline = "";
  for (byte i = 0; i < 21; i++) {
    underline.concat(underlineChar);
  }
  oled.print(underline);
  if(updateDisp) {
    oled.display();
  }
}

void reportNoProgram(String buttonName) {
  printTitle(buttonName, '~', true, false);
  oled.setCursor(0, 20);
  oled.print("Button has no program");
  printHelpMessage();
  oled.display();
}

void printHelpMessage() {
  oled.setCursor(0, 40);
  oled.print("Press FUNC/STOP for a");
  oled.setCursor(0, 50);
  oled.print("list of programs.");
}

void gotoTitleScreen() {
  printTitle("Ino OS v0.2", '=', true, false);
  oled.setCursor(0, 20);
  oled.print("Press any button.");
  oled.setCursor(0, 30);
  oled.print(" -OR-");
  printHelpMessage();
  oled.display();
}

void printProgramList() {
  printTitle("Program Guide", '+', true, false);
  oled.setCursor(0, 20);
  oled.print("VOL+ : Dice Roller");
  oled.setCursor(0, 30);
  oled.print("VOL- : Coin Flip");
  oled.setCursor(0, 40);
  oled.print("EQ : Temp & Hum");
  oled.setCursor(0, 50);
  oled.print("ST/REPT : Cool Quote");
  oled.display();
}

void printCoolQuote() {
  const String mandelaQuote[] = {
    "It always seems",
    "impossible until it",
    "is done.",
    "    -- Nelson Mandela"
  };

  const String rooneyQuote[] = {
    "You always pass",
    "failure on the way to",
    "success.",
    "     -- Mickey Rooney"
  };

  const String kitchenQuote[] = {
    "Never invite",
    "pessimism without",
    "inviting optimism.",
    "     -- Jared Kitchen"
  };

  const String quotes [][4] = {
    mandelaQuote,
    rooneyQuote,
    kitchenQuote
  };

  int luckyNum = random(3);
  String chosenQuote [4] = quotes[luckyNum];

  printTitle("Cool Quote", '-', true, false);
  oled.setCursor(0, 20);
  oled.print(chosenQuote[0]);
  oled.setCursor(0,30);
  oled.print(chosenQuote[1]);
  oled.setCursor(0, 40);
  oled.print(chosenQuote[2]);
  oled.setCursor(0, 50);
  oled.print(chosenQuote[3]);
  oled.display();
}

void displayTempAndHum() {
  short temp = 9999;
  byte hum = 0;
  while(true) {
    short nextTemp = dht.readTemperature(true);
    byte nextHum = dht.readHumidity();
    if(nextTemp != temp || nextHum != hum) {
      temp = nextTemp;
      hum = nextHum;
      printTitle("Temp and Humidity", '-', true, false);
      oled.setCursor(0, 20);
      oled.print("Temperature: ");
      oled.print(temp);
      oled.print(" F");
      oled.setCursor(0, 30);
      oled.print("Humidity: ");
      oled.print(hum);
      oled.print("%");
      oled.display();
    }
    delay(1000);
  }
}

void executeCommand(int command) {

  //Below vairables used for reporting a button with no associated program
  bool noProgram = false;
  String buttonName = "";
  if (command == PWR) {
    if(oledOn) {
      oled.clearDisplay();
      oled.display();
    }
    else {
      gotoTitleScreen();
    }
    oledOn = !oledOn;
  }
  if (oledOn) {
    switch(command) {
      case VOL_UP:
        noProgram = true;
        buttonName = "VOL+";
        break;
      case FUNC:
        printProgramList();
        break;
      case REV:
        noProgram = true;
        buttonName = "REVERSE";
        break;
      case PLAY:
        noProgram = true;
        buttonName = "PLAY/PAUSE";
        break;
      case FWD:
        noProgram = true;
        buttonName = "FORWARD";
        break;
      case DWN:
        noProgram = true;
        buttonName = "DOWN";
        break;
      case VOL_DWN:
        noProgram = true;
        buttonName = "VOL-";
        break;
      case UP:
        noProgram = true;
        buttonName = "UP";
        break;
      case ZERO:
        noProgram = true;
        buttonName = "NUMBER 0";
        break;
      case EQ:
        displayTempAndHum();
        break;
      case ST:
        printCoolQuote();
        break;
      case ONE:
        noProgram = true;
        buttonName = "NUMBER 1";
        break;
      case TWO:
        noProgram = true;
        buttonName = "NUMBER 2";
        break;
      case THREE:
        noProgram = true;
        buttonName = "NUMBER 3";
        break;
      case FOUR:
        noProgram = true;
        buttonName = "NUMBER 4";
        break;
      case FIVE:
        noProgram = true;
        buttonName = "NUMBER 5";
        break;
      case SIX:
        noProgram = true;
        buttonName = "NUMBER 6";
        break;
      case SEVEN:
        noProgram = true;
        buttonName = "NUMBER 7";
        break;
      case EIGHT:
        noProgram = true;
        buttonName = "NUMBER 8";
        break;
      case NINE:
        noProgram = true;
        buttonName = "NUMBER 9";
        break;
      // Do nothing if receiver reads an unknown code
    }
    if(noProgram) {
      reportNoProgram(buttonName);
    }
  }
}
