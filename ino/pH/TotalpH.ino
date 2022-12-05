float analogPin = A0;
int val = 0;
int buffer_arr[10];
float pH, avgval, ans, upH;
int ph7=515;
int acidMotorPin = A1;
int alkaliMotorPin = A2;
int blinkPin = 13; // pin that turns on the LED
int watertime = 5; // how long to water in seconds
int waittime = 60;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(acidMotorPin, OUTPUT); // set A0 to an output so we can use it to turn on the transistor
  pinMode(alkaliMotorPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<10;i++)
 {
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=2;i<8;i++){
 avgval+=buffer_arr[i];
val=avgval/6;
 }
 pH=7-(val-515)/11;
  Serial.println(pH);
  if (pH<upH-0.2){
     digitalWrite(alkaliMotorPin, HIGH); // turn on the motor
     digitalWrite(acidMotorPin, LOW);
  }
  else if (pH>upH+0.2){
     digitalWrite(acidMotorPin, HIGH); // turn on the motor
     digitalWrite(alkaliMotorPin, LOW);
  }
  else{
    digitalWrite(alkaliMotorPin, LOW);
    digitalWrite(acidMotorPin, LOW);
  }
  avgval=0;
  delay(1000);
}