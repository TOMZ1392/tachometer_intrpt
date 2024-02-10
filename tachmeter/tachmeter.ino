#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 6, 5, 4, 3);

volatile uint8_t intrpt = 0, intrptOld = 0, diff = 0;
uint32_t rpm = 0;
unsigned long timeOld = 0, timeDiff = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  attachInterrupt(0, intrptCtr, RISING);

}
uint8_t samples = 0;
void loop() {

  intrpt = 0;
  timeOld = millis();
  timeDiff = 0;
  while (timeDiff < 100)
  {
    timeDiff = millis() - timeOld;
  }

  rpm += 150 * intrpt ;
  samples++;
  Serial.println(intrpt);
  if (samples == 11)
  {
    rpm /= samples;
    samples = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed: ");
    lcd.print(rpm);
    lcd.setCursor(12, 0);
    lcd.print("rpm");
    rpm = 0;
    //delay(100);
  }
}

void intrptCtr()
{
  intrpt++;
}
