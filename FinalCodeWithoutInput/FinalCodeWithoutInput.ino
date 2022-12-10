//pH variab;es
float pHSensor = A0, val=0, buffer_arr[10], pH, avgval, ans, upH, ph7=443.5,acidMotorPin = 5, alkaliMotorPin = 6, blinkPin = 13 ;

//Temperature variables
#define RT0 10000 // Ω
#define B 3977 // K
//--------------------------------------
#define VCC 5 //Supply voltage
#define R 10000 //R=10KΩ
float temp, RT, VR, ln, TX, T0, VRT;
int tempPin=A1,tempMin=26,tempMax=34, heater=2;

//Stirring variables
int PWM=3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(acidMotorPin, OUTPUT); // set A0 to an output so we can use it to turn on the transistor
  pinMode(alkaliMotorPin, OUTPUT);

  pinMode(heater, OUTPUT);
  pinMode(tempPin, INPUT);
  T0=25+273.15;

  pinMode(PWM,OUTPUT);
}

float heatingSys(){

  VRT = analogRead(A0); //Acquisition analog value of VRT
  VRT = (5.00 / 1023.00) * VRT; //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R); //Resistance of RT

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

  TX = TX - 273.15; //Conversion to Celsius

  Serial.print("Temperature:");
  Serial.print("\t");
  Serial.print(TX);
  Serial.print("C\t\t");
  Serial.print(TX + 273.15); //Conversion to Kelvin
  Serial.print("K\t\t");
  Serial.print((TX * 1.8) + 32); 
  Serial.print("F");
  delay(1000);

  if(TX <= tempMin) {

  digitalWrite(heater, HIGH);

  }

  if(TX >= tempMax) 

  {
  analogWrite(heater, LOW); 

  }


}

float pHSys(){
  upH=7;
  for(int i=0;i<10;i++)
 {
 buffer_arr[i]=analogRead(pHSensor);
 delay(30);
 }
 for(int i=2;i<8;i++){
 avgval+=buffer_arr[i];
  val=avgval/6;
 }
 pH=7-(val-ph7)/12;
  Serial.println("pH Value: ");
  Serial.println(pH);
  if (pH<upH-2){
     analogWrite(alkaliMotorPin, 255); // turn on the motor
     analogWrite(acidMotorPin, 0);
  }
  else if (pH<upH-1 && pH>upH-2){
     analogWrite(alkaliMotorPin, 175); // turn on the motor
     analogWrite(acidMotorPin, 0);
  }
  else if (pH<upH-0.2&& pH>upH-1){
     analogWrite(alkaliMotorPin, 140); // turn on the motor
     analogWrite(acidMotorPin, 0);
  }
  else if (pH>upH+2){
     analogWrite(acidMotorPin, 255); // turn on the motor
     analogWrite(alkaliMotorPin, 0);
  }
  else if (pH>upH+1 && pH<upH+2){
     analogWrite(acidMotorPin, 175); // turn on the motor
     analogWrite(alkaliMotorPin, 0);
  }
  else if (pH>upH+0.2 && pH<upH+1){
     analogWrite(acidMotorPin, 140); // turn on the motor
     analogWrite(alkaliMotorPin, 0);
  }
  else{
    analogWrite(alkaliMotorPin, LOW);
    analogWrite(acidMotorPin, LOW);
  }
  avgval=0;
}
float stirSys(){
  int input = 1500; //change this to input from UI
  int mappwm = map(PWM,0,1500,40,255);
  analogWrite(PWM,mappwm);
}
void loop() {
  pHSys();
 heatingSys();
 stirSys();
 delay(1000);

  //Temperature
  
}
