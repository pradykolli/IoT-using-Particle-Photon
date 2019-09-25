double voltage;
void setup() {
    Particle.variable("volts",voltage);
}

void loop() {
    voltage = random();
    delay(1000);
}