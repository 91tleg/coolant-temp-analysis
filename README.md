The main purpose of the program is to compare values from a lookup table (which contains predefined temperature-resistance 
values for the thermistor) with the calculated values using the Steinhart-Hart equation (which models the relationship
between the temperature and resistance of the thermistor).

The Steinhart-Hart equation is a third-order polynomial equation that describes the relationship between the temperature and 
resistance of an NTC (Negative Temperature Coefficient) thermistor. The equation is:

	1/t = A + B * log(r) + C * log(r)^3

where:
T is the temperature in Kelvin (K).
R is the resistance of the thermistor at that temperature (in ohms).
A, B, C are constants specific to the thermistor, typically provided by the manufacturer(Calculated in our case).

To read the temperature from a thermistor, a voltage divider circuit is used. This circuit consists of two components:
Thermistor: A resistor in the voltage divider, whose resistance changes with temperature.
Fixed Resistor: A second resistor that stays constant (Resistance value of the sensor at room temp 25°C)

              ____         ____
    5V o-----|____|---+---|____|---o GND
              2.5K    |   sensor
                      | 
PIN A0 o--------------+

How the voltage divider works: The Arduino reads the voltage across the thermistor, and the corresponding resistance is then calculated.
As the thermistor's resistance changes with temperature, the voltage across it will also change, which is read by the Arduino's analog input.
Using this voltage, the resistance of the thermistor is calculated (using the known values for the fixed resistor and supply voltage).
Once the resistance is determined, we are able to calculate the temperature.

