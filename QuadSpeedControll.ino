// Dani Quad motor control

// pin definitions
const int Throttle = 14;  // Throttle
const int RPWM=5;
const int LPWM=6;
const int L_EN=7;
const int R_EN=8;
const int dirPin = 2; // Direction Switch

// serial debug enabele
boolean debug = true;


boolean dirValue = 0;    //0 forward 1 reverse
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setPWMfrequency(int freq){
   TCCR0B = TCCR0B & 0b11111000 | freq ;
  }

void setup() {
  setPWMfrequency(0x02);// timer 0 , 3.92KHz
  
  pinMode(dirPin, INPUT_PULLUP); 
  for(int i=5;i<9;i++){
   pinMode(i,OUTPUT);
  }
   for(int i=5;i<9;i++){
   digitalWrite(i,LOW);
  }
  Serial.begin(9600);
}

void loop() {

  sensorValue = analogRead(Throttle);
  dirValue = digitalRead(dirPin);
  //dirValue = 0;
  
  outputValue = map(sensorValue, 270, 725, 45, 255);
  if (outputValue > 255) outputValue = 255;
  if (outputValue < 50) outputValue = 0;

  if (dirValue == 1) {
    digitalWrite(R_EN,HIGH);
    digitalWrite(L_EN,HIGH);
    analogWrite(RPWM, outputValue);
    analogWrite(LPWM, 0);
  }

  if (dirValue == 0) {
    digitalWrite(R_EN,HIGH);
    digitalWrite(L_EN,HIGH);
    analogWrite(RPWM, 0);
    analogWrite(LPWM, outputValue);
  }

  // print the results to the Serial Monitor:
  if (debug == true) {
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print("  dir = ");
    Serial.print(dirValue);
    Serial.print("  output = ");
    Serial.print(outputValue);
    Serial.print("  ");
    Serial.println(outputValue);
  }
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(10);
}
