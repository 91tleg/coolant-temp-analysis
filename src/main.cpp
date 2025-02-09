#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/io.h>
#include <util/delay.h>
#include "def.h"
#include "steinhart.h"
#include "table.h"
/*
 * 20° C (68° F)	2-3K ohms
 * 50° C (122° F)	700-1000 ohms
 * 80° C (176° F)	300-400 ohms
 */

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup()
{
  DDRB = 0xff;
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("66230AA041");
  _delay_ms(1500);
  lcd.clear();
  Serial.begin(9600);
}

void loop()
{
  PORTB |= (1 << 5);
  _delay_ms(100);
  PORTB &= ~(1 << 5);

  float avg_reading_adc = 0.0;
  float voltage = 0.0;
  float resistance = 0.0;
  uint16_t temp_lookup_value = 0;
  uint16_t temp_steinhart_value = 0;

  for (uint8_t i = 0; i < NUM_SAMPLES; ++i)
  {
    avg_reading_adc += analogRead(SENSOR_PIN);
  }
  avg_reading_adc /= NUM_SAMPLES;

  voltage = claculate_voltage(avg_reading_adc);
  resistance = get_resistance(avg_reading_adc);
  _delay_ms(100);
  int index =  adc_to_arr_index(voltage);
  temp_lookup_value = get_lookup_temp(index);
  temp_steinhart_value = get_steinhart_temp(resistance);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TB:");
  lcd.print(temp_lookup_value);
  lcd.print("F");

  lcd.setCursor(9, 0);
  lcd.print("SH:");
  lcd.print(temp_steinhart_value);
  lcd.print("F");

  lcd.setCursor(0, 1);
  lcd.print(resistance);
  lcd.print("ohms");
  _delay_ms(1000);
}
