#define LDR A0
int light;

void setup()
{
  Serial.begin(9600); // Set the baud rate to match the receiving Arduino
}

void loop()
{
  light = analogRead(LDR);
  Serial.write((byte*)&light, sizeof(light)); // Send the light value as binary data

  delay(1000);
}