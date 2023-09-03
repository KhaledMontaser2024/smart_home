#define H1 7
#define H2 8
#define EN 6
int light = 0;
int flag = 0;

void motorclose()
{
  analogWrite(EN, 100);
  digitalWrite(H2, HIGH);
  digitalWrite(H1, LOW);
  delay(1000);
}

void motoropen()
{
  analogWrite(EN, 100);
  digitalWrite(H1, HIGH);
  digitalWrite(H2, LOW);
  delay(1000);
}

void motorstop()
{
  analogWrite(EN, 0);
  digitalWrite(H1, LOW);
  digitalWrite(H2, LOW);
}

void setup()
{
  Serial.begin(9600); 
  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(EN, OUTPUT);
}

void loop()
{
  if (Serial.available() >= sizeof(light)) {
   
    Serial.readBytes((char*)&light, sizeof(light));

    
    Serial.print("Received light value: ");
    Serial.println(light);

    if (light > 50 && flag == 0)
    {
      motoropen();
      delay(1000);
      motorstop();
      flag = 1;
    }
    else if (light < 50 && flag == 1)
    {
      motorclose();
      delay(1000);
      motorstop();
      flag = 0;
    }
  }

}