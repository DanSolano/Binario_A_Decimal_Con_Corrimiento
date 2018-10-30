// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int pushButt0 = 0;
int pushButt1 = 0;
int pushButtReset = 0;

int num = 0;
String inverseNumber = "";
String onScreen = "";
String stackControl = "";

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Binary Number");
  lcd.setCursor(0, 1);
  lcd.print("Decimal Number");
  pinMode(9, INPUT);//boton  es entrada --0
  pinMode(8, INPUT);//boton  es entrada --1
  pinMode(10, INPUT);


}

void loop() {
  pushButt0 = digitalRead(9);
  pushButt1 = digitalRead(8);
  pushButtReset = digitalRead(10);

  //When the pushButton of the 0 hass pressed
  if (pushButt0 == HIGH) {
    int num = 0; //pressed value
    //Function to calculate the decimal number
    calculate(num);
  }//When the pushButton of the 0 hass pressed
  else if (pushButt1 == HIGH) {
    int num = 1; //pressed value
    //Function to calculate the decimal number
    calculate(num);
  }  else if (pushButtReset == HIGH) {
    reset();
  }

}

void calculate(int num) {
  delay(250);
  lcd.begin(16, 2);
  /**
    The binary number is inverted to calculate the value
    from the least significant "bit"
  */
  inverseNumber = num + inverseNumber;
  /**
    The binary number in the order
    entered through the pushButton
  **/
  onScreen = onScreen + num;
  lcd.print(onScreen);
  int stringSize = inverseNumber.length() + 1;
  char char_array[stringSize];
  char array[stringSize];
  inverseNumber.toCharArray(char_array, stringSize);


  lcd.setCursor(0, 1);
  int decimal = 0;

  //Go through the "array" to calculate the decimal number
  for (int i = 0; i < stringSize ; i = i + 1) {
    num = (int)char_array[i];
    if (num == 49) {
      //Sum 0.5 because the "pow" function calculates float values
      decimal += 0.5 + pow(2, i);
    } else {
      decimal += 0;
    }
  }
  //validate if the decimal result is greater than 32767 ((2^15)-1)
  if (decimal < 0) {
    lcd.print("Stack Overflow");
    reset();
  } else {
    lcd.print(decimal);
  }
}


void reset() {
  inverseNumber = "";
  onScreen = "";
  delay(1000);
  lcd.begin(16, 2);
  lcd.print("Reset values");
  delay(1000);
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("Binary Number");
  lcd.setCursor(0, 1);
  lcd.print("Decimal Number");
}
