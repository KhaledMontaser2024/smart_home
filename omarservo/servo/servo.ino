#include <Servo.h>
#include <EEPROM.h>
#define pin1 9 
#define pin2 10 
#define switchpin 11 
Servo home_door ;
Servo room_door ;
float distance = 0 ;//would be recived from arduino 1

int ent_pass ;//would be recieved from pass node

void roomdoor(float distance){
  if (distance <= 100 )
    {room_door.write(100);
    }
    else 
    {
    room_door.write(0);
    }

    } 
void homedoor(){ 
  
    if (ent_pass == EEPROM[0])//check if the recieved pass is correct
    {home_door.write(100);
     delay(3000);
    home_door.write(0);
    }

  }


void setup() {
  Serial.begin(9600);
  home_door.attach(pin1) ; 
  room_door.attach(pin2) ; 
  pinMode(switchpin,INPUT);
  
  EEPROM.update(0,123) ;

}

void loop() {
homedoor(); 
roomdoor(distance);

}
