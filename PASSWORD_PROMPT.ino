#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4; //Four rows
const byte COLS = 4; //Four columns

//RS, E, D4, D5, D6, D7
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);


//Define the symbols on the keymaps
char hexakeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };

byte rowPins[ROWS] = {9, 8, 7, 6}; //Connect to the row pinouts of the keypad
byte rowCols[COLS] = {5, 4, 3, 2}; //Connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexakeys), rowPins, rowCols, ROWS, COLS);

const String password = "5405";
String enteredPin = "";

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  showEnterPasswordScreen();
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey){
    Serial.println(customKey);

    if(customKey == '*'){
      //Use '*' as a clear/reset key
      enteredPin = "";
      showEnterPasswordScreen();
    }
    else if (customKey == '#'){
      //Use '#' as an explicit submit key
      checkPassword;
    }
    else if (isDigit(customKey)){
      if (enteredPin.length() < 4){
        enteredPin += customKey;
        updatePinDisplay();
      }
      if (enteredPin.length() == 4){
        delay(200);
        checkPassword();
      }
    }
  }
}


void showEnterPasswordScreen(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter password: ");
  lcd.setCursor(0, 1);
}

void updatePinDisplay(){
  lcd.setCursor(0, 1);
  for (unsigned int i = 0; i < enteredPin.length(); i++){
    lcd.print('*');
  }
}


void checkPassword(){
  lcd.clear();
  lcd.setCursor(0, 0);

  if (enteredPin == password){
    lcd.print("Correct");
  } else {
    lcd.print("Incorrect");
  }
  delay(2000);
  enteredPin = "";
  showEnterPasswordScreen();
}

