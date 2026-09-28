
const int pingTrigPin = A4; //Trigger connected to PIN
const int pingEchoPin = A5; //Echo connected yo PIN
int led=13; //Buzzer to PIN 4
int buz1=9;


void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buz1, OUTPUT);
  pinMode(pingTrigPin, OUTPUT);
  pinMode(pingEchoPin, INPUT);
  
}

void loop()
{
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  float v = voltage*3;
  // print out the value you read:
  Serial.println(v);
  delay (50);
  if (v <= 5.5) {
    Serial.println ("battery low");
    
    delay (50);
  }
  
  long duration, cm;

  digitalWrite(pingTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingTrigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingTrigPin, LOW);

  duration = pulseIn(pingEchoPin, HIGH);
  cm = microsecondsToCentimeters(duration);

  if(cm<=100 && cm>0) {
  int d= map(cm, 1, 300, 10, 1000);
  digitalWrite(led, HIGH);
  digitalWrite(buz1, HIGH);
  delay(50);
  digitalWrite(led, LOW);
  digitalWrite(buz1, LOW);
  delay(d);
}
  Serial.print(cm);
  Serial.print(cm);
  Serial.println();
  delay(40);
}
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}