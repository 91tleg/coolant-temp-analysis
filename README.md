This program compares the coolant temperature values from VGR3's B10 scan tool with the temperature calculated from the Steinhart-Hart equation.

The Steinhart-Hart equation is a third-order polynomial equation that describes the relationship between the temperature and 
resistance of an NTC (Negative Temperature Coefficient) thermistor. 
The equation:

	1/t = A + B * log(r) + C * log(r)^3

where:
T is the temperature in Kelvin (K).\
R is the resistance of the thermistor at that temperature (in ohms).\
A, B, C are constants specific to the thermistor, calculated using specs provided on the factory service manual.\

In this setup, we are using a simple voltage divider circuit to measure the temperature using a thermistor (resistance changes with temperature). The basic idea is that the thermistor’s resistance changes with temperature, and by measuring the voltage across it, we can figure out its resistance and ultimately calculate the temperature.

### Schematic of the Voltage Divider Circuit
2.5k Resistor: Resistance value of the sensor at room temp 25°C\
Sensor: We are using the Subaru OEM coolant temp sensor part number 22630AA041\
PIN: Analog pin\
```text
              ____         ____
    5V o-----|____|---+---|____|---o GND
              2.5K    |   Sensor
                      | 
   PIN o--------------+
