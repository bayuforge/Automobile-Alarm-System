//HC-SR04 DOCS: https://projecthub.arduino.cc/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-7cabe1

//Declare pin variables for buzzer, red light, yellow light, green light
const int buzzer_pin = 10;
const int RL = 13, YL = 12, GL = 11;
const int echo_pin = 3, trig_pin = 5;

//Declare float variable to store input data
float distance, duration;
float soundspeed = .0343;


void setup()
{
  pinMode(buzzer_pin, OUTPUT);
  
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  Serial.begin(9600);
  
  pinMode(RL, OUTPUT);
  pinMode(YL, OUTPUT);
  pinMode(GL, OUTPUT);

  //Set all light to LOW first
  digitalWrite(RL, LOW);
  digitalWrite(YL, LOW);
  digitalWrite(GL, LOW);
}

void loop()
{
  //first we need to set the trig pin to LOW for 2 ms, then
  //set it high for 10 ms which sends out 8 cycle conic burst
  //from the transmitter.
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  
  //Calculate duration and distance
  //For the distance, we use distance = time x speed
  //In this case, the speed is sound of speed in cm
  //Then divide by 2 because it is going to travel back
  duration = pulseIn(echo_pin, HIGH);
  distance = (duration * soundspeed)/2;
   
  //print the result  
  Serial.print("Distance: ");  
  Serial.println(distance);  
  delay(100);

  if(distance > 175){
  	digitalWrite(YL, LOW);
    digitalWrite(RL, LOW);
    
    digitalWrite(GL, HIGH);
    delay(1000);
    digitalWrite(GL, LOW);
    delay(1000);
   
    tone(buzzer_pin, 2000);
  	delay(1000);
  	noTone(buzzer_pin);
  	delay(100);
  }
  
  else if (distance > 100 && distance < 175){
  	digitalWrite(RL, LOW);
    digitalWrite(GL, LOW);
    
    digitalWrite(YL, HIGH);
    delay(1000);
    digitalWrite(YL, LOW);
    delay(1000);
   
    tone(buzzer_pin, 1000);
  	delay(1000);
  	noTone(buzzer_pin);
  	delay(100);
  }
  
  else{
    digitalWrite(GL, LOW);
    digitalWrite(YL, LOW);
    
    digitalWrite(RL, HIGH);
    delay(500);
    digitalWrite(RL, LOW);
    delay(500);
    
    tone(buzzer_pin, 400);
  	delay(1000);
  	noTone(buzzer_pin);
  }
}
