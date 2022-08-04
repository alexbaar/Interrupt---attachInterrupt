const byte buzzer = 8;
const byte led = 10;
const byte interruptPin = 2; // rain sensor


//volatile bool buzzerState = LOW;
volatile bool ledState = LOW;


void setup() 
{
  pinMode(buzzer, OUTPUT); 
  pinMode(led, OUTPUT);
  pinMode(interruptPin, INPUT);  

  // step 1 : turn interrupts on the port we use -> D
  PCICR |= 0b00000100;

  // step 2 : select pin D2 (third bit from right) ; rain sensor data pin will be the interruptor
  PCMSK2 |= 0b00000100; 
  
  Serial.begin(9600); // Starts the serial communication
}
void loop() 
{

  
  Serial.print((String)"sensor: " + digitalRead(interruptPin));
  //Serial.print((String)"   //   buzzer: " + digitalRead(buzzer));
  Serial.println((String)"   //   led: " + digitalRead(led));
  delay(1000);
}

ISR (PCINT2_vect)
{
  // interrupt for port D
  // when rain sensor detects rain drops invert the toggles : light off / buzzer on
  //buzzerState = !buzzerState;
  ledState = !ledState;
  digitalWrite(led, ledState);
  //digitalWrite(buzzer, buzzerState);
  
}
