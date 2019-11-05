//#########DEFINING PINS FOR EASE OF USE##############

//<150 recycling
//>150 garbage

#define echo 12 //pins for the ultrasonic
#define trig 13

#define mL1 2 //left motor pins
#define mL2 3
#define mR1 4 //right motor pins
#define mR2 6

#define line A0 //emittier of the line sensor, read in

int flag=0; // 0 for nothing, 1 for recycling, 2 for garbage

void setup() {
  Serial.begin(9600); //allows us to see live data for troubleshooting
  //set up pins for everything
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(mL1, OUTPUT);
  pinMode(mL2, OUTPUT);
  pinMode(mR1, OUTPUT);
  pinMode(mR2, OUTPUT);
  pinMode(line, INPUT);

  //pull up network to remove some interference
  digitalWrite(line, HIGH);
  digitalWrite(echo, HIGH);

  //default motors to off
  off();
}

//#########################################################
void loop() {
  if(flag == 1) { //RECYCLING!!!
    off();
    delay(1000);
    left();
    delay(1000); //tweak to turn 90 degrees right
    off();
    delay(1000);
    forwards();
    delay(1000);
    off();
    delay(1000);
    backwards(); //go back to original position
    delay(1000);
    off();
    delay(1000);
    right();
    delay(1000);
    off();
    flag=0;
    delay(1000); //buffer delay
  }//end flag==1
  
  else if(flag == 2) { //GARBAGE!!!
    off();
    delay(1000);
    right();
    delay(1000); //tweak to turn 90 degrees right
    off();
    delay(1000);
    forwards();
    delay(1000);
    off();
    delay(1000);
    backwards(); //go back to original position
    delay(1000);
    off();
    delay(1000);
    left();
    delay(1000);
    off();
    flag=0;
    delay(1000); //buffer delay
  }//end flag==2

  
  else { //FLAG=0 SO NO OBJECT FOUND!!!
    if(ping()<4) { //object close to us, switch to colour sensing
      forwards(); //go straight towards object
      delay(1000);
      if(lineSense()<=150) { //recycling found
        flag=1; //mark flag as recycling
      }
      else if(lineSense()>200) {
        flag=2; //mark flag as garbage
      }
    }
    
    else {//if(ping()>=6) { //sensing object within a close distance
      forwards();
    }
  }//end flag==0 
}
//#########################################################

void backwards() { //CHANGE NUMBERS TO FIT WHAT WE WANT
  digitalWrite(mL1, HIGH); //left motor
  digitalWrite(mL2, LOW);
  digitalWrite(mR1, HIGH); //right motor
  digitalWrite(mR2, LOW);
}

void forwards() { //CHANGE NUMBERS TO FIT WHAT WE WANT
  digitalWrite(mL1, LOW); //left motor
  digitalWrite(mL2, HIGH);
  digitalWrite(mR1, LOW); //right motor
  digitalWrite(mR2, HIGH);
}

void right() { //CHANGE NUMBERS TO FIT WHAT WE WANT
  digitalWrite(mL1, HIGH); //left motor
  digitalWrite(mL2, LOW);
  digitalWrite(mR1, LOW); //right motor
  digitalWrite(mR2, HIGH);
}

void left() { //CHANGE NUMBERS TO FIT WHAT WE WANT
  digitalWrite(mL1, LOW); //left motor
  digitalWrite(mL2, HIGH);
  digitalWrite(mR1, HIGH); //right motor
  digitalWrite(mR2, LOW);
}

void off() { //CHANGE NUMBERS TO FIT WHAT WE WANT
  digitalWrite(mL1, LOW); //left motor
  digitalWrite(mL2, LOW);
  digitalWrite(mR1, LOW); //right motor
  digitalWrite(mR2, LOW);
}

int ping() { //returns distance in CM
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long dur = pulseIn(echo, HIGH);
  if(dur==0) {
    return 0;
  }
  else {
    int dist = (dur)/29/2;
    return dist;
  }
}

int lineSense() {
  return analogRead(line);
}

