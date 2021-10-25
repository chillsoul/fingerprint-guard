#include <Adafruit_Fingerprint.h>
#include <Servo.h>
// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
// #define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial
SoftwareSerial mySerial(D2, D3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
    finger.LEDcontrol(0x04,0,0,0);
    //finger.setPassword(839);
  }
  
  /**else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }**/
  
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  pinMode(D6,INPUT);
  pinMode(D5,OUTPUT);
  digitalWrite(D5,LOW);

}
void servoControl(int pul){
  for(int i=0;i<=5;i++){
    digitalWrite(D5,HIGH);
    delayMicroseconds(pul);
    digitalWrite(D5,LOW);
    delayMicroseconds(20000-pul);
  }
}
//use
void openDoor(){
  servoControl(500);
  delay(1500);
  servoControl(2500);
  delay(1500);
}
void loop()                     // run over and over again
{
  if(digitalRead(D6)==HIGH){
    //蓝色
    finger.LEDcontrol(0x03,0,0x04,0);
    getFingerprintIDez();
    delay(500);
    //关闭
    finger.LEDcontrol(0x04,0,0,0);
  }
  delay(100);            //don't ned to run this at full speed.
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  {
    finger.LEDcontrol(0x02,0,0x01,0);
  return -1;
  }
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  {
    finger.LEDcontrol(0x02,0,0x01,0);
  return -1;
  }
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  {
    finger.LEDcontrol(0x02,0,0x01,0);
  return -1;
  }
  finger.LEDcontrol(0x02,0,0x02,0);
  // found a match!
  openDoor();
  
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
