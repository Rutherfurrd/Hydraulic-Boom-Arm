const int numReadings = 7;
double posReadings[numReadings];
double velReadings[numReadings];
double accReadings[numReadings];
int readIndex = 0;
double posTotal = 0;
double velTotal = 0;
double accTotal = 0;
double lastMil = 0;
double curVel = 0;
double curAcc = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i<numReadings;i++){
    posReadings[i] = 0;
    velReadings[i] = 0;
    accReadings[i] = 0;

  }
}

void loop() {
  posTotal = posTotal - posReadings[readIndex];
  velTotal = velTotal - velReadings[readIndex];
  double input = analogRead(A0);
  posReadings[readIndex] = input/1012 * 215.57;
  
  if (readIndex > numReadings-2){
    velReadings[readIndex] = (posReadings[readIndex]-posReadings[9]);
    accReadings[readIndex] = (velReadings[readIndex]-velReadings[9])/(1*0.032);
  } else {
    velReadings[readIndex] = (posReadings[readIndex]-posReadings[readIndex-1]);
    accReadings[readIndex] = (velReadings[readIndex]-velReadings[readIndex-1])/(1*0.032);
  }
  lastMil = millis();
  posTotal = posTotal + posReadings[readIndex];
  velTotal = velTotal + velReadings[readIndex];
  curVel = velReadings[readIndex];
  curAcc = accReadings[readIndex];
  readIndex=readIndex + 1;
  if (readIndex >= numReadings){
    readIndex = 0;
  }
  double avgPos = posTotal / numReadings;
 
  double avgVel = velTotal / numReadings;
  
  Serial.print(0);
  Serial.print(" ");
  Serial.print(220);
  Serial.print(" ");
  Serial.print(avgPos);
  Serial.print(" ");
  
  Serial.print(avgVel);

  Serial.print(" ");

  Serial.print(millis());
  Serial.print(" ");

  
  Serial.println(curAcc);

  delay(1);



}
