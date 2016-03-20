/*Author-Sudarshan Sharma
Purpose-Full KTJ WAREHOUSE EVENT Code
*/


#include<Wire.h>


int read_count=0,tag_count=0;

char data_temp, RFID_data[13];

int LED1=26,LED2=29,LED4=30,LED5=33,LED6=34,LED7=37,LED9=38,LED10=41,number=0;

char s1[13]="000985643000";
char s2[13]="000870128800";
char s3[13]="000869548700";
char s4[13]="000959040800";



const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double timeStep=0.0001;
double arx,ary,grx=0,gry=0,rx,ry,xrx,yry;
int gyroScale=131;
int accthres=50;



int Motor1A=8;
int Motor1B=9;
int Motor2A=7;
int Motor2B=6;
int Motor3A=11, Motor3B=12;
double val;
int pwmmotor1=2, pwmmotor2=3, pwmmotor3=4;
int pin1=A1;
int pin2=A3;
int pin3=A5;

double a,b,c;
double angle;
double thresgyro=25;
  
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





//Function To Tell Motors What To Do
void todo(double angleX,double angleY)
{
 // val=map(angleX,-90,90,-255,255);
if(abs(angleX)<thresgyro&&abs(angleY)<thresgyro)
{
  Serial.println("Stop");
  analogWrite(pwmmotor1,255);
  analogWrite(pwmmotor2,255);
  digitalWrite(Motor1A,HIGH);
  digitalWrite(Motor1B,HIGH);
  digitalWrite(Motor2A,HIGH);
  digitalWrite(Motor2B,HIGH);
  
}
else if(angleX>thresgyro)
{
  Serial.println("Forward");
  analogWrite(pwmmotor1,200);
  analogWrite(pwmmotor2,200);
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor1B,HIGH);
  digitalWrite(Motor2A,LOW);
  digitalWrite(Motor2B,HIGH);
  
}

else if(angleX<(-thresgyro))
{
  Serial.println("BackWard");
  
  analogWrite(pwmmotor1,200);
  analogWrite(pwmmotor2,200);
  digitalWrite(Motor1A,HIGH);
  digitalWrite(Motor1B,LOW);
  digitalWrite(Motor2A,HIGH);
  digitalWrite(Motor2B,LOW);
  
}

else if(angleY>thresgyro)
{
  
  analogWrite(pwmmotor1,200);
  analogWrite(pwmmotor2,200);
  digitalWrite(Motor1A,HIGH);
  digitalWrite(Motor1B,LOW);
  digitalWrite(Motor2A,LOW);
  digitalWrite(Motor2B,HIGH);
  Serial.println("Left");
}

else if(angleY<(-thresgyro))
{
    Serial.println("Right");
    
  analogWrite(pwmmotor1,200);
  analogWrite(pwmmotor2,200);
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor1B,HIGH);
  digitalWrite(Motor2A,HIGH);
  digitalWrite(Motor2B,LOW);
}


}

void fork(double accangle)
{
  if(abs(accangle)<accthres)
{
 // Serial.println("Stop");
  analogWrite(pwmmotor3,255);
  digitalWrite(Motor3A,HIGH);

  digitalWrite(Motor3B,HIGH);
}

else if(accangle>accthres)
{
 // Serial.println("Up");
   analogWrite(pwmmotor3,240);
  digitalWrite(Motor3A,LOW);

  digitalWrite(Motor3B,HIGH);
}
else if(accangle<(-accthres))
{
  //Serial.println("Down");
   analogWrite(pwmmotor3,240);
  digitalWrite(Motor3A,HIGH);
  digitalWrite(Motor3B,LOW);
}

}



//SetUp Begin

void setup(){
  

  
Serial1.begin(9600);

pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED10,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(LED6,OUTPUT);
  pinMode(LED7,OUTPUT);
  pinMode(LED9,OUTPUT);




  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  pinMode(Motor1A,OUTPUT);
  pinMode(Motor1B,OUTPUT);
  pinMode(Motor2A,OUTPUT);
  pinMode(Motor2B,OUTPUT);
  pinMode(pwmmotor1,OUTPUT);
  pinMode(pwmmotor2,OUTPUT);
 
pinMode(pin1,INPUT);
pinMode(pin2,INPUT);
pinMode(pin3,INPUT);
//pinMode(13,OUTPUT);
 pinMode(Motor3A,OUTPUT);
  pinMode(Motor3B,OUTPUT);
  pinMode(pwmmotor3,OUTPUT);

}
//Loop Starts.

void loop(){
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

delay(10);
 arx = (180/3.141592) * asin(AcX/sqrt(pow(AcY,2)+pow(AcZ,2)+pow(AcX,2))); 
ary = (180/3.141592) * asin(AcY/sqrt(pow(AcZ,2)+pow(AcY,2)+pow(AcX,2))); 

GyX=GyX/gyroScale;
GyY=GyY/gyroScale;


 grx = grx + (timeStep * GyX);
 gry = gry + (timeStep * GyY);
   
  rx = (0.15 * arx) + (0.85 * grx);
ry = (0.15 * ary) + (0.85 * gry);

xrx=map(rx,-13.5,13.5,-90,90);
yry=map(ry,-13.5,13.5,-90,90);
  
a=analogRead(pin1);
delay(15);
b=analogRead(pin2);
delay(15);
c=analogRead(pin3);
delay(15);


angle=map(b,315,356,-90,90);
//Serial.println(angle);
todo(xrx,yry);
fork(angle);


if(Serial1.available()>0)
{
 data_temp=Serial1.read();
RFID_data[read_count]=data_temp;
read_count++;
 }
 
RFID_data[10]='0';
RFID_data[11]='0';
RFID_data[12]='\0';

if(read_count==12)
{

if(strcmp(RFID_data,s1)==0)
{
  
 
digitalWrite(LED1,HIGH);
digitalWrite(LED2,HIGH);
digitalWrite(LED5,HIGH);
digitalWrite(LED10,HIGH);
digitalWrite(LED9,HIGH);
digitalWrite(LED4,LOW);

  digitalWrite(LED7,LOW);

digitalWrite(LED6,LOW);

 // print 2A
}
else if(strcmp(RFID_data,s2)==0)
{
   //print 3A
   
   

 digitalWrite(LED1,HIGH);
digitalWrite(LED2,HIGH);
digitalWrite(LED5,HIGH);
digitalWrite(LED7,HIGH);
digitalWrite(LED9,HIGH);
digitalWrite(LED4,LOW);
digitalWrite(LED6,LOW);
digitalWrite(LED10,LOW);

}
else if(strcmp(RFID_data,s3)==0)
{
  //Print 1A
  
digitalWrite(LED1,HIGH);
  digitalWrite(LED7,HIGH);
  digitalWrite(LED4,LOW);
digitalWrite(LED6,LOW);
digitalWrite(LED10,LOW);
digitalWrite(LED2,LOW);
digitalWrite(LED5,LOW);
digitalWrite(LED9,LOW);


}

else if(strcmp(RFID_data,s4)==0)
{
  //print 4A

  digitalWrite(LED1,HIGH);
  digitalWrite(LED4,HIGH);
  digitalWrite(LED5,HIGH);
  digitalWrite(LED7,HIGH);
digitalWrite(LED2,LOW);
digitalWrite(LED6,LOW);
digitalWrite(LED10,LOW);

digitalWrite(LED9,LOW);


  
}

else
{
 
  Serial.println("Nothing Detected");
  //print 0
  digitalWrite(LED1,HIGH);
digitalWrite(LED2,HIGH);



digitalWrite(LED4,HIGH);
digitalWrite(LED6,HIGH);

digitalWrite(LED7,HIGH);
digitalWrite(LED9,HIGH);
digitalWrite(LED10,HIGH);
}
read_count=0;
}


}



