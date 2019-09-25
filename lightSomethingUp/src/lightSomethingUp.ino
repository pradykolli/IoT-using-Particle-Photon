
// Example 2 : a Light Detector 14
            // thereallygreatlightmeter.ino
            // Make: Getting Started with the Photon, Simon Monk.
int reading = 0;
double volts = 0.0;
int analogPin = A5;
void setup()
{
  pinMode(analogPin, AN_INPUT);
  Particle.variable("volts", volts);
  Serial.begin(9600);
}
void loop()
{
  reading = analogRead(analogPin);
  volts = reading * 3.3 / 4096.0;
  ariseMinions(String(volts));
}
int ariseMinions(String command)
{
  Serial.println(String(volts));
  return 1;
}