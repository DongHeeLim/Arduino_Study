
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello,!");
  lcd.setCursor(2,1);
  lcd.print("Ywro!");
   lcd.setCursor(0,2);
  lcd.print("Ardu");
   lcd.setCursor(1,1);
  lcd.print("Power By Ec-yuan!");
}


void loop()
{
}
