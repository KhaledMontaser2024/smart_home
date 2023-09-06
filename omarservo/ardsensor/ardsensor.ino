#define trig 11 
#define echo 3
float distance = 0 ;//will be sent to arduino 2 
float duration =0 ;
bool state ;
void changestate (){
  state = 1;}//random func to handle the interrupt
float sensor(){
  digitalWrite(trig,LOW);
  delay(3);
  digitalWrite(trig,HIGH);
  delay(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
 return distance = duration / 57 ;//57 = 1/(speed of air in specific conditions(cm\ms)/2)
}
void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  attachInterrupt(digitalPinToInterrupt(echo), changestate  , FALLING);

}

void loop() {
  sensor();

}
