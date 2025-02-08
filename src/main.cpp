#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/io.h>
#include <util/delay.h>
#include "def.h"
#include "steinhart.h"
#include "table.h"

//LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

LiquidCrystal_I2C lcd(0x27,20,4);

constexpr uint8_t NUM_SAMPLES = 5;

extern int16_t coolant_temp_farenheit;

void setup()
{
  
  lcd.init();
	lcd.backlight();
	lcd.setCursor(3,0);
	lcd.print("set up...");
  _delay_ms(3000);
	lcd.clear();
  Serial.begin(9600);
}

void loop()
{
  float voltage = 0.0;
  float average_reading_adc = 0.0;
  
  for (uint8_t i = 0; i < NUM_SAMPLES; ++i)
  {
    average_reading_adc += analogRead(SENSOR_PIN);
  }
  average_reading_adc /= NUM_SAMPLES;

  voltage = (average_reading_adc * 5.0) / 1023.0;

  uint8_t average_reading_byte_size = adc_to_byte(voltage);

  read_coolant_table(average_reading_byte_size);
  lcd.setCursor(0, 0);
  lcd.print("Look up:  ");
  lcd.print(coolant_temp_lut);

  read_coolant_steinhart(average_reading_adc);
  lcd.setCursor(0, 1);
  lcd.print("Calcltd:  ");
  lcd.print(coolant_temp_farenheit);

  _delay_ms(1000);

}