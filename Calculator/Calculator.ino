
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27 , 16 , 2);

int currentPress;
int firstNumber = 0;
int secondNumber = 0;
bool flag = false;

char operation;
float result;


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'^','0','#','/'}
};
byte rowPins[ROWS] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

float getResult(int n1 , int n2 , char op)
{
  float result;
  switch (op)
  {
    case '+':
      result = n1 + n2;
      break;

    case '-':
      result = n1 - n2;
      break;
    
    case '*':
      result = n1 * n2;
      break;
    
    case '/':
      if(n2 == 0)
      {
        result = NAN;
        break;
      }

      else
      {
      result = (float)n1 / (float)n2;
      break;
      }

      
  }

  return result;
}


void setup(){
  lcd.init();
  lcd.backlight();
}
  
void loop(){

  char customKey = customKeypad.getKey();
  
  if (customKey){

    if (customKey >= '0' && customKey <= '9')
    {
      if(flag == false)
      {
        currentPress = customKey - 48;
        firstNumber = firstNumber * 10 + currentPress;
        lcd.setCursor(0,0);
        lcd.print(firstNumber);
      }

      if (flag == true)
      {
        currentPress = customKey - 48;
        secondNumber = secondNumber * 10 + currentPress;
        lcd.print(currentPress);
      }
    }

    else if (customKey == '+' || customKey == '-' || customKey == '*' || customKey == '/')
    {
    operation = customKey;
    lcd.print(operation);
    flag = true;
    }

    else
    {
      if(customKey == '#')
      {
        result = getResult(firstNumber , secondNumber , operation);
        lcd.setCursor(0,1);
        lcd.print(result);
      }

      else if (customKey == '^')
      {
        flag = false;
        firstNumber = 0;
        operation = 0;
        secondNumber = 0;
        lcd.clear();
      }

    }

  }

}
