#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

SdFat sd;
SFEMP3Shield MP3player;

//초음파 센서의 핀번호를 설정한다.
int echoPin = 4;
int trigPin = 5;
float duration, distance;

void setup() {
  Serial.begin(9600);
  // trig를 출력모드로 설정, echo를 입력모드로 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  sd.begin(SD_SEL, SPI_HALF_SPEED);
  MP3player.begin();
  
  Serial.println("Make fun!!");
}

void loop() {
  dist();
  if (distance < 30) {
    MP3player.playTrack(random(6));   
    Serial.println("Let's Play the Music!!!");
  } else {
    MP3player.stopTrack();
    Serial.println("Stop the Music!!");
  }
  delay(500);
}

void dist() {
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration = pulseIn(echoPin, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance = ((float)(340 * duration) / 10000) / 2;  
  
  Serial.print(distance);
  Serial.print("cm, ");
}
