//This code reads data from the SDP8xx series DP sensors
//All the operating modes are listed in the setup section



// This code is provided to you by ege621
#include <Wire.h> 
byte myData[10];  //array to hold data coming from sensor

void setup() 
{
  Wire.begin();
  Serial.begin(9600);

// ---------CONTINOUS READING COMMANDS----------//

//Mass Flow, Average till read
//  Wire.beginTransmission(0x25);
//  Wire.write(0x36);
//  Wire.write(0x03);   
//  Wire.endTransmission();

   //Mass Flow, None, update rate 0.5ms
//  Wire.beginTransmission(0x25);
//  Wire.write(0x36);
//  Wire.write(0x08);   
//  Wire.endTransmission();
//
// //Differential Pressure, Average till read
//  Wire.beginTransmission(0x25);
//  Wire.write(0x36);
//  Wire.write(0x15);   
//  Wire.endTransmission();

// //Differential Pressure, None, Update rate 0.5ms
  Wire.beginTransmission(0x25);
  Wire.write(0x36);
  Wire.write(0x1E);   
  Wire.endTransmission();

//-----------------------------------------------//

//------TRIGGERED READING COMMANDS---------//

 //Mass Flow, w/o clock stretching
//  Wire.beginTransmission(0x25);
//  Wire.write(0x36);
//  Wire.write(0x24);   
//  Wire.endTransmission();

 //Mass flow, w/ clock stretching
//  Wire.beginTransmission(0x25);
//  Wire.write(0x37);
//  Wire.write(0x26);   
//  Wire.endTransmission();

//Differential pressure w/o clock stretching
//  Wire.beginTransmission(0x25);
//  Wire.write(0x36);
//  Wire.write(0x2F);   
//  Wire.endTransmission();

 //Differential pressure w/ clock stretching
//  Wire.beginTransmission(0x25);
//  Wire.write(0x37);
//  Wire.write(0x2D);   
//  Wire.endTransmission();


  //------RESET COMMAND----//
//  Wire.beginTransmission(0x25);
//  Wire.write(0x00);
//  Wire.write(0x06);  
//  Wire.endTransmission();

   //Enter sleep mode
//  Wire.beginTransmission(0x25);
//  Wire.write(0x36);
//  Wire.write(0x77);   //see data sheets
//  Wire.endTransmission();
  //Any command other than go to sleep will wake the sensor up. 

delay(500);
}

void loop() 
{
  delay(10);
  Wire.requestFrom(0x25, 9);
  delay(8);
  for(int i=0; i<9; i++)
  {
    myData[i] = Wire.read();
  delay(3);
  }
  delay(1);
  
  int16_t Pressure_raw = myData[0]<<8|myData[1]; // Raw Pressure Data 
  //myData[2] = CRC of Pressure data
 
  int16_t Temperature_raw = myData[3]<<8|myData[4];// Raw Temperature data 
  //myData[5]= CRC of Temperature data
  double Temperature = Temperature_raw/float(200);
  
  float SF_pressure = myData[6]<<8|myData[7];  //Scale factor for differential pressure
  //myData[8] = CRC of scale factor data
  float Pressure = Pressure_raw/float(SF_pressure); 
   
  //----measurement stop command--
//  Wire.beginTransmission(0x25);
//  Wire.write(0x3F);
//  Wire.write(0xF9);   //see data sheets
//  Wire.endTransmission();

//Serial.print("Differential Pressure= ");
Serial.print(Pressure); //Print pressure reading in terminal (Pa)
Serial.print(" ");

//Serial.print("Temperature= ");
Serial.println(Temperature);
//Serial.print("C\n");
//Serial.print("\n");
  
  //----------------------
  delay(50);   //test interval
}
