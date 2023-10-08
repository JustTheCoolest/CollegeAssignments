#include <Arduino.h>

constexpr byte flame_sensor_pin = A0;
constexpr byte led_pin = LED_BUILTIN;
constexpr int baud_rate = 9600;

void setUpFlameSensor(byte flame_sensor_pin){
  pinMode(flame_sensor_pin, INPUT);
}

int readFlameSensor(byte flame_sensor_pin){
  return analogRead(flame_sensor_pin);
}

void setUpLed(byte led_pin){
  pinMode(led_pin, OUTPUT);
}

void calibrate(byte flame_sensor_pin){
    
}

void calibration_driver(byte flame_sensor_pin){
    Serial.println("Calibration awaited.");
    Serial.println("Instructions: At the intended distance from the flame, move the sensor in oscillating motion, passing through the flame and region outside the flame too\n");
    char input;
    do{
        Serial.print("Enter 'y' when ready with sensor and flame: ");
        input = Serial.read();
        input.trim();
        if(input==''){
            continue;
        }
    } while(input != 'y');
    Serial.println("Calibration starts");
    calibrate(flame_sensor_pin);
} 

void setup(){
  setUpFlameSensor(flame_sensor_pin);
  setUpLed(led_pin);
  Serial.begin(baud_rate);
  calibrate(flame_sensor_pin);
}

void loop(){
  int flame_sensor_value = analogRead(flame_sensor_pin);
  Serial.println(flame_sensor_value);
  if(flame_sensor_value > 500){
    digitalWrite(led_pin, HIGH);
  }else{
    digitalWrite(led_pin, LOW);
  }
}
