// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>


#define PI 3.143
const int G_SENS=131;          //a division factor that directly gives omega calculated
const float dt=0.0001;//derivative time interval

float y_old_theta=0,y_theta=0;       
float y_sum_theta=0;float y_diff;

float x_old_theta=0,x_theta=0;       
float x_sum_theta=0;float x_diff;



const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
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
  
  
   AcX = constrain(AcX,-15500,15500);
   AcY = constrain(AcY,-15500,15500);
   AcZ = constrain(AcZ,-15500,15500);
  
  AcX = map(AcX,-15500,15500,-10,10);
  AcY = map(AcY,-15500,15500,-10,10);
  AcZ = map(AcZ,-15500,15500,-10,10);
  
  
   float ACCY=asin((double)AcX/(double)10)*180/PI; 
  float ACCX=asin((double)AcY/(double)10)*180/PI; 
   
  
 // Serial.println("   "); Serial.print(ACCY);Serial.print("           "); Serial.println(ACCX); Serial.println("   ");
  
  
   int GYRY=(float)GyY/G_SENS;          //GYRY is the omega about y axis          
  //G_SENS is factor that directly gives the omega from raw data of gyroscope in IMU          
  
  y_theta=0.85*(y_old_theta+GYRY*dt)+0.15*(ACCY);//complimentary filter                                                         
  y_old_theta=y_theta;
  
  
   int GYRX=(float)GyX/G_SENS;          //GYRY is the omega about y axis          
  //G_SENS is factor that directly gives the omega from raw data of gyroscope in IMU          
  
  x_theta=0.85*(x_old_theta+GYRX*dt)+0.15*(ACCX);//complimentary filter                                                         
  x_old_theta=x_theta;
  
  
  
   Serial.println("   "); Serial.print(y_theta);Serial.print("           "); Serial.println(x_theta); Serial.println("   ");
  
  
  
  
  /*
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  */
  
  
  delay(100);
  
}
