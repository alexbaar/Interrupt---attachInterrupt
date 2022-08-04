const byte buzzer = 8;
const byte ledRain = 10;
const byte ledMotion = 9;
const byte interruptPinRain = 2; // rain sensor
const byte interruptPinMotion = 3;


//volatile bool buzzerState = LOW;
volatile bool ledStateRain = LOW;
volatile bool ledStateMotion = LOW;

void setup() 
{
  pinMode(buzzer, OUTPUT); 
  pinMode(ledRain, OUTPUT);
  pinMode(interruptPinRain, INPUT);  
  pinMode(interruptPinMotion, INPUT);  

  // step 1 : turn interrupts on the port we use -> D
  PCICR |= 0b00000100;

  // step 2 : select pin D2 (third bit from right) ; rain sensor data pin and motion are both interruptors now
  PCMSK2 |= 0b00001100; 
  
  Serial.begin(9600); // Starts the serial communication
}
void loop() 
{


  Serial.print((String)"Rain: " + digitalRead(interruptPinRain));
  Serial.println((String)" // Rain led: " + digitalRead(ledRain));
  Serial.print((String)"Motion: " + digitalRead(interruptPinMotion));
  Serial.println((String)" // Motion led: " + digitalRead(ledMotion));
  delay(1000);
}

ISR (PCINT2_vect)
{
  // interrupt for port D
  // check which port caused interruption:

  // D2 ? Rain Led?
  if(digitalRead(interruptPinRain) == HIGH)
  {
    // Pin D2 triggered the ISR when detecting rain and sending data value "1" to pin D2
    ledStateRain = !ledStateRain;
    // reflect that state in green led
    digitalWrite(ledRain, ledStateRain);
  }
  
  // D3 ? Motion Led?
  if(digitalRead(interruptPinMotion) == HIGH)
  {
    // Pin D3 triggered the ISR when detecting motion and sending data value "1" to pin D3
    ledStateMotion = !ledStateMotion;
    // reflect that state in green led
    digitalWrite(ledMotion, ledStateMotion);
  }
  
}
