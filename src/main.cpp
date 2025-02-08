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
  DDRB = 0xff;
  lcd.init();
	lcd.backlight();
	lcd.setCursor(3,0);
	lcd.print("set up...");
  _delay_ms(1000);
  Serial.begin(9600);
}

void loop()
{
  PORTB |= (1 << 5);
  _delay_ms(1000);
  PORTB &= ~(1 << 5);
  lcd.clear();
  static float voltage = 0.0;
  static float average_reading_adc = 0.0;
  static float resistance = 0.0;
  for (uint8_t i = 0; i < NUM_SAMPLES; ++i)
  {
    average_reading_adc += analogRead(SENSOR_PIN);
  }
  average_reading_adc /= NUM_SAMPLES;

  voltage = (average_reading_adc * 5.0) / 1023.0;
  uint8_t average_reading_byte_size = adc_to_byte(voltage);

  lookup_coolant_temp(average_reading_byte_size);
  lcd.setCursor(0, 0);
  lcd.print("LUT:");
  lcd.print(coolant_temp_lookup_value);
  calculate_steinhart_temp(average_reading_adc);
  lcd.setCursor(9, 0);
  lcd.print("CLC:");
  lcd.print(coolant_temp_farenheit);

  resistance = (RESISTOR_VALUE * average_reading_adc) / (1023.0 - average_reading_adc);
  lcd.setCursor(0,1);
  lcd.print(resistance);
  lcd.print("ohms");
  _delay_ms(1000);

}