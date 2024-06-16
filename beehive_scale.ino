#include <HX711.h>

#define DOUT 13
#define CLK 12

HX711 scale;
float calibration_factor = -40000;

void setup()
{
    Serial.begin(115200);
    Serial.println("HX711 calibration sketch");
    Serial.println("Remove all weight from scale");
    Serial.println("After readings begin, place known weight on scale");
    Serial.println("Press + or a to increase calibration factor");
    Serial.println("Press - or z to decrease calibration factor");

    scale.begin(DOUT, CLK);
    scale.set_scale();
    scale.tare();

    // Get a baseline reading.
    // This can be used to remove the need to tare the scale.
    // Useful in permanent scale projects.
    long zero_factor = scale.read_average();
    Serial.print("Zero factor: ");
    Serial.println(zero_factor);
}

void loop()
{
    // The weight is divided by `calibration_factor`.
    scale.set_scale(calibration_factor);

    Serial.print("Reading: ");
    Serial.print(scale.get_units(), 1);
    // Change this to kg and re-adjust the calibration factor,
    // if you follow SI units like a sane person.
    Serial.print(" kg,");
    Serial.print(" calibration_factor: ");
    Serial.print(calibration_factor);
    Serial.println();

    if (Serial.available())
    {
        char temp = Serial.read();
        if (temp == '+' || temp == 'a')
            calibration_factor += 10;
        else if (temp == '-' || temp == 'z')
            calibration_factor -= 10;
    }
}
