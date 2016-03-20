/*the following code is to print the RFID value of the card.
we have used the Arduino Mega and put the RFID reader Tx pin in Rx1 */
#include <SoftwareSerial.h>

int LED1=26,LED2=29,LED4=30,LED5=33,LED6=34,LED7=37,LED9=38,LED10=41,number=0;

// The following is the card no. for 3 cards. You will be provided these numbers.
String c1="29003359BBF8";
String c2="29003358A0E2";
String c3="2900336893E1";

String s1="33009256887F";
String s2="33009665AE6E";
String s3="1A008DCFFAA2";
String s4="1A007345361A";
String s5="1A0072BDF124";
String s6="220084AEBFB7";
String s7="3300969DCBF3";
String s8="220084C5680B";
String s9="3300965A4AB5";
String s10="3300927964BC";
String s11="33009773FF28";
String s12="330096CEEB80";

String p1="0001166707";
String p2="340011E323E5";
void setup()
{
   Serial.begin(9600);
   Serial1.begin(9600);
    pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED10,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(LED6,OUTPUT);
  pinMode(LED7,OUTPUT);
  pinMode(LED9,OUTPUT);

}

void off()
{
  digitalWrite(LED1,LOW);
digitalWrite(LED2,LOW);
digitalWrite(LED5,LOW);
digitalWrite(LED4,LOW);
digitalWrite(LED6,LOW);
digitalWrite(LED7,LOW);
digitalWrite(LED9,LOW);
digitalWrite(LED10,LOW);
}

String a="";
String s="";


void loop()
{
  if(Serial1.available())
  {
  a=a+(char)Serial1.read();
  s=a;
  }
  

//0001166707
  Serial.println(s);
  if(s.equalsIgnoreCase(p1))
  {
    off();
     digitalWrite(LED1,HIGH);
     digitalWrite(LED7,HIGH);
     //Compare and prints 1.
    Serial.println(s+" p1");
  }
  else if(s.equalsIgnoreCase(p2))
  {
    off();

digitalWrite(LED1,HIGH);
digitalWrite(LED2,HIGH);
digitalWrite(LED5,HIGH);
digitalWrite(LED10,HIGH);
digitalWrite(LED9,HIGH);
}
/*
    Serial.println(s+" p2");
  }
  else if(s.equalsIgnoreCase(c3))
    Serial.println(s+" p3");
    */
    
}
