

volatile byte r, t ,b = 0;

const int touchLed = 9;
const int buttonLed = 11;
const int rainLed = 12;

const uint16_t t1_load = 0;
const uint16_t t1_comp = 31250;




void setup() 
{
  // led
  pinMode(rainLed, OUTPUT); 
  pinMode(touchLed, OUTPUT);  
  pinMode(buttonLed, OUTPUT); 

  // step 1 : turn interrupts on the port we use -> D
  PCICR |= 0b00000111;

  // step 2 : select pin D2 (third bit from right) ; rain sensor data pin and motion are both interruptors now
  PCMSK2 |= 0b00101100; 
  
  Serial.begin(9600); // Starts the serial communication
cli();//stop interrupts

// RAIN sensor
//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 250;// = (16*10^6) / (2000*64) - 1 (must be <256)        ; that value is chosen just to show fast led reaction
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

// TOUCH button
//set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 55624;// = (16*10^6) / (1*1024) - 1 (must be <65536)    ; that value is chosen just to show slow led reaction
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

 sei();
}
void loop() 
{
  //digitalWrite(12,r); // rain
  //digitalWrite(9,t); // touch 
  digitalWrite(11,b); // button
}

ISR (PCINT2_vect)
{
  r = PIND & B00000100; // rain
  t = PIND & B00001000; // touch
  b = PIND & B00100000; // button
}

ISR(TIMER0_COMPA_vect)
{
  if (t){
    digitalWrite(touchLed,HIGH);
    t = 0;
    
  }
  else{
    //digitalWrite(touchLed,LOW);
  }
}


ISR(TIMER1_COMPA_vect)
{
  if (r){
    digitalWrite(rainLed,HIGH);
    r=0;
    digitalWrite(touchLed,LOW);
    
  }
  else{
    digitalWrite(rainLed,LOW);
    
  }
}
