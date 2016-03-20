
//Spats-Sewani Reference

#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double timeStep=0.0001;
double arx,ary,grx=0,gry=0,rx,ry,xrx,yry;
int gyroScale=131;
int accthres=30;


int Motor1A=9;
int Motor1B=8;
int Motor2A=7;
int Motor2B=6;
double val;
int pwmmotor1=2, pwmmotor2=3, pwmmotor3=13;

int a,b,c;
double angle;
double thresgyro=25;
  



void todo(double angleX,double angleY)
{
  val=map(angleX,-90,90,-255,255);
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
  analogWrite(pwmmotor1,255);
  analogWrite(pwmmotor2,255);
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor1B,HIGH);
  digitalWrite(Motor2A,LOW);
  digitalWrite(Motor2B,HIGH);
  
}

else if(angleX<(-thresgyro))
{
  Serial.println("BackWard");
  
  analogWrite(pwmmotor1,255);
  analogWrite(pwmmotor2,255);
  digitalWrite(Motor1A,HIGH);
  digitalWrite(Motor1B,LOW);
  digitalWrite(Motor2A,HIGH);
  digitalWrite(Motor2B,LOW);
  
}

else if(angleY>thresgyro)
{
  
  analogWrite(pwmmotor1,255);
  analogWrite(pwmmotor2,255);
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor1B,HIGH);
  digitalWrite(Motor2A,HIGH);
  digitalWrite(Motor2B,LOW);
  Serial.println("Left");
}

else if(angleY<(-thresgyro))
{
    Serial.println("Right");
    
  analogWrite(pwmmotor1,255);
  analogWrite(pwmmotor2,255);
  digitalWrite(Motor1A,HIGH);
  digitalWrite(Motor1B,LOW);
  digitalWrite(Motor2A,LOW);
  digitalWrite(Motor2B,HIGH);
}



}




//Functions End


void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(Motor1A,OUTPUT);
  pinMode(Motor1B,OUTPUT);
  pinMode(Motor2A,OUTPUT);
  pinMode(Motor2B,OUTPUT);
  pinMode(pwmmotor1,OUTPUT);
  pinMode(pwmmotor2,OUTPUT);
 
}
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

delay(100);
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

todo(xrx,yry);//Calls the Function To Run The Motor.



  
 
  
}
