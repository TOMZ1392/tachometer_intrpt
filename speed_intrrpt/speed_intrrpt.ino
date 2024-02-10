  #include <LiquidCrystal.h>
  LiquidCrystal lcd(8, 9, 6, 5, 4, 3);
   volatile byte half_revolutions,k;
   volatile byte half_revolutions_old=0;
const byte interruptPin =0;
 unsigned int rpm;

 unsigned long timeold;

 void setup()
 {
  lcd.begin(16, 2);
   attachInterrupt(0, rpm_fun, CHANGE);

   half_revolutions = 0;
   rpm = 0;
   timeold = 0;
 }

 void loop()
 {
   half_revolutions_old=half_revolutions;
   if (half_revolutions >= 4) { 
     //Update RPM every 20 counts, increase this for better RPM resolution,
     //decrease for faster update
     half_revolutions_old=half_revolutions;
     rpm = 30*1000/(millis() - timeold)*half_revolutions;
     timeold = millis();
     half_revolutions = 0;
      lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("speed");
  lcd.setCursor(0, 1);
  lcd.print(rpm);
   }
   k=half_revolutions-half_revolutions_old;
   if (k <= 100 && rpm >=0)
   {
     rpm--;
    
     lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("speed");
  lcd.setCursor(0, 1);
  lcd.print(rpm);
  delay(400);
   }
 }

 void rpm_fun()
 {
   half_revolutions++;
   //Each rotation, this interrupt function is run twice
 }
