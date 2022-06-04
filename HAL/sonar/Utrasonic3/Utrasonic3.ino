
#include "Wire.h"

#define TRIG 11    //connecting trigger pin to pin 11 at arduino
#define ECHO 12    //connecting echo pin to pin 12 at arduino

int distance;      //global variable to store readings

void setup()
{  
Serial.begin(9600);
Wire.begin(12);                 //join I2C bus with address 12 for third ultrasonic
Wire.onReceive(I2C_action);    //running ultrasonic when receiving value from ST
Wire.onRequest(Send_Readings); //sending readings to STM
}

void Send_Readings()
{
  char values[2];                      //array to save readings byte by byte  
  values[0] = (distance & 0xFF00)>>8;  //first byte of read value
  values[1] = (distance & 0xFF);       //second byte of read value
  Wire.write(values);                  //sending readings over I2C 
}

void I2C_action(void)
{  
  int x = Wire.read();        // receive byte as an integer
  Serial.println(x);          // print the integer

  switch(x)
  {
    case 81:                 //in case of TAKE_RANGE_CMD
      startUltrasonic();     
    break;   
  }
}

void startUltrasonic()
{
  pinMode(TRIG, OUTPUT) ;   //setting trigger pin as output pin to send start signal [pulse for 10usec]
  pinMode(ECHO ,INPUT) ;    //settinh echo pin as input to receive delay in time 

  /*sending start signa;*/ 
digitalWrite(TRIG,LOW);    //starting from low state
delayMicroseconds(5);      //making sure it is low
digitalWrite(TRIG,HIGH);   //converting from low to high
delayMicroseconds(10);     //delay for 10 usec while it is high
digitalWrite(TRIG,LOW);    //converting from high to low & end of trigger signal

//echo will not rise to high unless it sends 8 pulses

t = pulseIn(ECHO,HIGH) ;   //getting time during ECHO is high [time of transmission and receive]
distance = t/57 ;          //calculations of distance in centimeters
}


void loop() {
  // put your main code here, to run repeatedly:

}
