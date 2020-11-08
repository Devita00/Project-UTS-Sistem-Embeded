const int FLAME_SENSOR_PIN = 2;
int mtrPin = 3;
int FLAME_SENSOR_state=0;
int FLAME_SENSOR_serial_data_R2;
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(mtrPin, OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("FLAME DETECTION");
  lcd.setCursor(0,1);
  lcd.print("ROOM 2");
  delay(1000);
}
void loop()
{
  FLAME_SENSOR_state = digitalRead(FLAME_SENSOR_PIN);
  if(FLAME_SENSOR_state== HIGH)
  {
    lcd.clear();
    FLAME_SENSOR_serial_data_R2=30;
    Serial.write(FLAME_SENSOR_serial_data_R2);
  }
  else
  {
    lcd.clear();
    FLAME_SENSOR_serial_data_R2=40;
    Serial.write(FLAME_SENSOR_serial_data_R2);
  }
  
  if(FLAME_SENSOR_serial_data_R2 == 30)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FLAME DETECTED");
    lcd.setCursor(0,1);
    lcd.print("ROOM 2");
    delay(50);
    digitalWrite(mtrPin, HIGH);
  }
  else
  {
    if (FLAME_SENSOR_serial_data_R2 == 40)
    {
      int FLAME_SENSOR_serial_data_R1= Serial.read();
      if(FLAME_SENSOR_serial_data_R1 == 10)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("FLAME DETECTED");
        lcd.setCursor(0,1);
        lcd.print("ROOM 1");
        delay(50);
      }
      else 
      {
        if(FLAME_SENSOR_serial_data_R1 == 20)
        {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("NO FLAME");
          delay(50);
        } 
      }
    }
    digitalWrite(mtrPin, LOW);
  }
}
