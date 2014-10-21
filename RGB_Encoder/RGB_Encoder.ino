
//Inputs
int pinA = 2;
int pinB = 3;
int encoderSwitchPin = 4;
int whiteSwitch = 5;
int blackSwitch = 6;
int greenSwitch = 7;
int yellowSwitch = 8;
int redSwitch = 9;

//LEDs
int blueLed = 10;
int greenLed = 11;
int redLed = 12;

//Pin to allow keyboard and mouse actions.
int allowPin = 13;

//Misc Variables
int lastEncoded = 0;
long encoderValue = 0;
long lastencoderValue = 0;
int lastMSB = 0;
int lastLSB = 0;

void setup()
{
  Serial.begin (9600);

  //Setup input pins
  pinMode(pinA, INPUT); 
  pinMode(pinB, INPUT);
  pinMode(encoderSwitchPin, INPUT); 
  pinMode(whiteSwitch, INPUT);
  pinMode(blackSwitch, INPUT);
  pinMode(greenSwitch, INPUT);
  pinMode(yellowSwitch, INPUT);
  pinMode(redSwitch, INPUT);

  //Setup LED pins
  pinMode(blueLed, OUTPUT); 
  pinMode(greenLed, OUTPUT); 
  pinMode(redLed, OUTPUT); 
  
  //Setup allow pin.
  pinMode(allowPin, INPUT); 

  digitalWrite(pinA, HIGH); //turn pullup resistor on
  digitalWrite(pinB, HIGH); //turn pullup resistor on

  //digitalWrite(encoderSwitchPin, HIGH); //turn pullup resistor on  

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
}

void loop()
{
  if(Allowed())
  {
    if(buttonPressed())
    {
      ledOff(blueLed);ledOn(greenLed);ledOff(redLed);
      delay(50);    
    }
  }
  Serial.print(encoderValue);
  Serial.print("\t");
  Serial.println(digitalRead(encoderSwitchPin));
  
  ledOn(redLed);ledOn(blueLed);ledOn(greenLed);
}

void updateEncoder(){
  int MSB = digitalRead(pinA); //MSB = most significant bit
  int LSB = digitalRead(pinB); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
  {
    encoderValue ++;
    ledOn(blueLed);ledOff(greenLed);ledOff(redLed);
    delay(100);
  }
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
  {
    encoderValue --;
    ledOn(blueLed);ledOff(greenLed);ledOff(redLed);
    delay(100);
  }
  lastEncoded = encoded; //store this value for next time
}

boolean Allowed()
{
  if(digitalRead(allowPin)==0)
  {
    return true;   
  }
  return false;
}

void ledOff(int led){
  digitalWrite(led, HIGH);
}

void ledOn(int led){
  digitalWrite(led, LOW);
}

boolean buttonPressed()
{
  if(digitalRead(encoderSwitchPin)==1)
  {
    return true;
  }
  else if (digitalRead(whiteSwitch)==1)
  {
    return true;
  }
  /*
  if else (digitalRead(blackSwitch)==1)
  {
    return true;
  }
  if else (digitalRead(greenSwitch)==1)
  {
    return true;
  }
  if else (digitalRead(yellowSwitch)==1)
  {
    return true;
  }
  if else (digitalRead(redSwitch)==1)
  {
    return true;
  }
  */
  return false;
}
