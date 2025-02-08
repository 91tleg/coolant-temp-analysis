#include <Arduino.h>
#include <stdint.h>
#include <LiquidCrystal_I2C.h>
#include "def.h"
#include "steinhart.h"
#include "table.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

constexpr uint8_t NUM_SAMPLES = 5;

void setup()
{
  pinMode(SENSOR_PIN, INPUT);
  lcd.init(I2C_SDA, I2C_SCL);
	lcd.backlight();
	lcd.setCursor(3,0);
	lcd.print("Hello, world!");
	lcd.setCursor(2,1);
  Serial.begin(9600);
}

void loop()
{
  float average_reading_adc = 0.0;
  for (uint8_t i = 0; i < NUM_SAMPLES; ++i)
  {
    average_reading_adc += analogRead(SENSOR_PIN);
    delay(1000);
  }
  average_reading_adc /= NUM_SAMPLES;

  uint8_t average_reading_byte_size = adc_to_byte(average_reading_adc);

  read_coolant_table(average_reading_byte_size);
  lcd.setCursor(0, 0);
  lcd.print(coolant_temp_lut);

  read_coolant_steinhart(average_reading_adc);
  lcd.setCursor(0, 1);
  lcd.print(coolant_temp_steinhart);

  delay(1000);
}
