const byte buzzer = 8;
const byte led = 10;
const byte interruptPin = 2; // rain sensor

volatile byte state = LOW; 
volatile byte state2 = HIGH;


void setup() 
{
  pinMode(buzzer, OUTPUT); 
  pinMode(led, OUTPUT);
  pinMode(interruptPin, INPUT);  

  // here, if the pin value of rain sensor changes (0 / 1) then execute the action function below
  attachInterrupt(digitalPinToInterrupt(interruptPin), action, CHANGE); 
  Serial.begin(9600); // Starts the serial communication
}
void loop() 
{
  digitalWrite(led, state2);
  digitalWrite(buzzer, state);
  
  Serial.print((String)"sensor: " + digitalRead(interruptPin));
  Serial.print((String)"   //   buzzer: " + digitalRead(buzzer));
  Serial.println((String)"   //   led: " + digitalRead(led));
  delay(1000);
}

void action()
{
  // when rain sensor detects rain drops 
  state = !state;  // buzzer go off
  state2 = !state2;  // led light stop blinking 
}
