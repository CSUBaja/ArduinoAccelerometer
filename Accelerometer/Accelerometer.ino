 

#include <Wire.h> 

#include <SPI.h> 

#include <Adafruit_LIS3DH.h> 

#include <Adafruit_Sensor.h> 

#include <SD.h> //Load SD library 

 
 

int chipSelect = 4; //chip select pin for the MicroSD Card Adapter 

File file; // file object that is used to read and write data 

 
 
 

// Used for software SPI 

#define LIS3DH_CLK 13 

#define LIS3DH_MISO 12 

#define LIS3DH_MOSI 11 

// Used for hardware & software SPI 

#define LIS3DH_CS 10 

 
 

// software SPI 

//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK); 

// hardware SPI 

//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS); 

// I2C 

Adafruit_LIS3DH lis = Adafruit_LIS3DH(); 

 
 

void setup(void) { 

  Serial.begin(9600); 

  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens 

 
 

  Serial.println("LIS3DH test!"); 

 
 

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address 

    Serial.println("Couldnt start"); 

    while (1) yield(); 

  } 

  Serial.println("LIS3DH found!"); 

 
 

   lis.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G! 

 
 

  Serial.print("Range = "); Serial.print(2 << lis.getRange()); 

  Serial.println("G"); 

 
 

  // lis.setDataRate(LIS3DH_DATARATE_50_HZ); 

  Serial.print("Data rate set to: "); 

  switch (lis.getDataRate()) { 

    case LIS3DH_DATARATE_1_HZ: Serial.println("1 Hz"); break; 

    case LIS3DH_DATARATE_10_HZ: Serial.println("10 Hz"); break; 

    case LIS3DH_DATARATE_25_HZ: Serial.println("25 Hz"); break; 

    case LIS3DH_DATARATE_50_HZ: Serial.println("50 Hz"); break; 

    case LIS3DH_DATARATE_100_HZ: Serial.println("100 Hz"); break; 

    case LIS3DH_DATARATE_200_HZ: Serial.println("200 Hz"); break; 

    case LIS3DH_DATARATE_400_HZ: Serial.println("400 Hz"); break; 

 
 

    case LIS3DH_DATARATE_POWERDOWN: Serial.println("Powered Down"); break; 

    case LIS3DH_DATARATE_LOWPOWER_5KHZ: Serial.println("5 Khz Low Power"); break; 

    case LIS3DH_DATARATE_LOWPOWER_1K6HZ: Serial.println("16 Khz Low Power"); break; 

  } 

     

  pinMode(chipSelect, OUTPUT); // chip select pin must be set to OUTPUT mode 

  if (!SD.begin(chipSelect)) { // Initialize SD card 

    Serial.println("Could not initialize SD card."); // if return value is false, something went wrong. 

  } 

   

  if (SD.exists("Data.txt")) { // if "file.txt" exists, fill will be deleted 

    Serial.println("File exists."); 

     

     

  } 

} 

 
 
 

void loop() { 

  lis.read();      // get X Y and Z data at once 

  file = SD.open("Data.txt", FILE_WRITE); 

  

  /* Or....get a new sensor event, normalized */ 

  sensors_event_t event; 

  lis.getEvent(&event); 

  if (file){ 

  file.print(millis()); 

  file.print("\t\tX: "); file.print(event.acceleration.x); 

  file.print(" \tY: "); file.print(event.acceleration.y); 

  file.print(" \tZ: "); file.print(event.acceleration.z); 

  file.println(" m/s^2 "); 

  Serial.println("added"); 

  file.close(); 

  } 

 
 

  /* Display the results (acceleration is measured in m/s^2) */ 

  Serial.print(millis()); 

  Serial.print("\t\tX: "); Serial.print(event.acceleration.x); 

  Serial.print(" \tY: "); Serial.print(event.acceleration.y); 

  Serial.print(" \tZ: "); Serial.print(event.acceleration.z); 

  Serial.println(" m/s^2 "); 

 
 

  Serial.println(); 

 
 

  delay(10); 

} 

 
 

 