#include<SoftwareSerial.h>


int read_count=0,tag_count=0;

char data_temp, RFID_data[12];

int LED1=26,LED2=29,LED4=30,LED5=33,LED6=34,LED7=37,LED9=38,LED10=41,number=0;

void setup()
{
Serial1.begin(9600);
Serial.begin(9600);
pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED10,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(LED6,OUTPUT);
  pinMode(LED7,OUTPUT);
  pinMode(LED9,OUTPUT);


}
/*
char s1[12]="000985643000";
char s2[12]="000870128800";
char s3[12]="000869548700";
char s4[12]="000959040800";

char compare[12];


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

*/

void loop()
{

if(Serial1.available()>0)
{
 data_temp=Serial1.read();
RFID_data[read_count]=data_temp;
read_count++;
 }
RFID_data[11]='0';
RFID_data[12]='0';
RFID_data[13]='\0';

Serial.println(RFID_data);
/*
if(strcmp(RFID_data,s1)==0)
{
  off();
 digitalWrite(LED1,HIGH);
 digitalWrite(LED7,HIGH);
  
 // print 1
}
else if(strcmp(RFID_data,s2)==0)
{
   //print 2
   off();
{
digitalWrite(LED1,HIGH);
digitalWrite(LED2,HIGH);
digitalWrite(LED5,HIGH);
digitalWrite(LED10,HIGH);
digitalWrite(LED9,HIGH);
}

}
else if(strcmp(RFID_data,s3)==0)
{
  //Print 3
  off();


{
digitalWrite(LED1,HIGH);
digitalWrite(LED2,HIGH);
digitalWrite(LED5,HIGH);
digitalWrite(LED7,HIGH);
digitalWrite(LED9,HIGH);
}

}

else if(strcmp(RFID_data,s4)==0)
{
  //print 4
  off();

{
  digitalWrite(LED1,HIGH);
  digitalWrite(LED4,HIGH);
  digitalWrite(LED5,HIGH);
  digitalWrite(LED7,HIGH);
}
  
}

else
{
  Serial.println("Nothing Detected");
  //print 0
  digitalWrite(LED1,LOW);
digitalWrite(LED2,LOW);

digitalWrite(LED3,LOW);

digitalWrite(LED4,LOW);
digitalWrite(LED5,LOW);
digitalWrite(LED6,LOW);
digitalWrite(LED8,LOW);
digitalWrite(LED7,LOW);
digitalWrite(LED9,LOW);
digitalWrite(LED10,LOW);
}

}
/*
void RecieveData()
{
if(Serial1.available()>0)
{
data_temp=Serial1.read();
RFID_data[read_count]=data_temp;
read_count++;
}
}


void StoreData()
{

if(read_count==12)
{
disp_control=true;  
for(k=tag_count;k<=tag_count;k++)
{
for(j=0;j<12;j++)
{
data_store[k][j]=RFID_data[j];
}
}
read_count=0;
tag_count++;
}
}

void PrintData()
{
if(disp_control==true)
{
  for(k=0;k<=tag_count;k++)
{
    for(j=0;j<12;j++)
  {
    Serial.write(data_store[k][j]);
  }
  Serial.println();
}
disp_control=false;
}
}
/*
void Substring(String s)
{
  String temp;
  int c=0;
   while (c < 12) 
   {
      temp[c] = s[c-1];
      c++;
   }
   temp[c] = '\0';

}

*/
}

