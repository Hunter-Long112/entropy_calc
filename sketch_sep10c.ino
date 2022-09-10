/* TURN PROGRAM */

  #define RIGHT 100
  #define LEFT  101
  #define FORWARD 200
  #define BACKWARD 201
  #define STOP 125

  #include <PRIZM.h>
  #include <Wire.h>  // include PRIZM library
  PRIZM prizm;            // instantiate a PRIZM object “prizm” so we can use its functions
  int distanceInFront;
  int distanceBehind;
  int middle;
  int count = 0;

void inPlaceTurn(int degree, int direction);
void driveUntilStop(int stopDistance, int direction);

void setup() {

  prizm.PrizmBegin();           // initialize PRIZM
  prizm.setMotorInvert(1,1);    // invert the direction of DC Motor 1 to harmonize direction
  Serial.begin(9600);     // configure the serial monitor for 9600 baud rate
                              
}

void loop() {

  distanceInFront = prizm.readSonicSensorCM(3);
  inPlaceTurn(180, RIGHT);
  brake();
  distanceBehind = prizm.readSonicSensorCM(3);

  middle = (distanceInFront + distanceBehind) / 2;

  if(distanceInFront > distanceBehind){
    //move backwards until distance read in is equal to middle
    driveUntilStop(middle, BACKWARD);
  }
  else if(distanceInFront < distanceBehind){
    //move forward until distance read in is equal to middle
    driveUntilStop(middle, FORWARD);
  }

  delay(500);
  
  inPlaceTurn(90, RIGHT);
  brake();

  distanceInFront = prizm.readSonicSensorCM(3);
  inPlaceTurn(180, RIGHT);
  brake();
  distanceBehind = prizm.readSonicSensorCM(3);

  middle = (distanceInFront + distanceBehind) / 2;

  if(distanceInFront > distanceBehind){
    //move backwards until distance read in is equal to middle
    driveUntilStop(middle, BACKWARD);
  }
  if(distanceInFront < distanceBehind){
    //move forward until distance read in is equal to middle
    driveUntilStop(middle, FORWARD);
  }

  count++;
  if (count > 3)
    prizm.PrizmBegin();

}

void inPlaceTurn(int degree, int direction){
  
  int time = map(degree, 0, 360, 0, 3200);
  
  // turn right
  if(direction == RIGHT){
    prizm.setMotorPowers(30, -30);
    delay(time);
    prizm.setMotorPowers(125, 125);
  }
  
  // turn left
  if(direction == LEFT){
    prizm.setMotorPowers(-30, 30);
    delay(time);
    prizm.setMotorPowers(125, 125);
  }
  
}

void driveUntilStop(int stopDistance, int direction){
  
  if(direction == FORWARD){
    while(prizm.readSonicSensorCM(3) > stopDistance){
      prizm.setMotorPowers(30, 30);
    }
    prizm.setMotorPowers(125, 125);
    return;
  }

  if(direction == BACKWARD){
    while(prizm.readSonicSensorCM(3) < (stopDistance - 30)){
      prizm.setMotorPowers(-30, -30);
    }
    prizm.setMotorPowers(125, 125);
  }
  
  return;
}

void brake() { 
prizm.setMotorPowers(STOP, STOP);
delay(500);
}



