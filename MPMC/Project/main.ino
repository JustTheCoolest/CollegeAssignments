#include <Arduino.h>

constexpr unsigned int baud_rate = 9600;
constexpr unsigned int rounds_calibration = 500;
constexpr unsigned int delay_calibration = 0;
constexpr unsigned float ratio_calibration = 0.3;

constexpr byte flame_sensor_pin = A0;
constexpr byte led_pin = LED_BUILTIN;
int threshold;

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
    int min = __INT_MAX__, max = -1;
    for(int i=0; i<rounds_calibration; i++){
        int flame_sensor_value = readFlameSensor(flame_sensor_pin);
        if(flame_sensor_value > max){
            max = flame_sensor_value;
        }
        if(flame_sensor_value < min){
            min = flame_sensor_value;
        }
        delay(delay_calibration);
    }
    int threshold = ratio_calibration * (max - min) + min;
    return threshold;
}

 int ui_calibration(byte flame_sensor_pin){
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
    int threshold = calibrate(flame_sensor_pin);
    Serial.println("Calibration ends with threshold: " + String(threshold));
    return threshold;
} 

bool digitalisedData(int sensor_value, int threshold, bool greater_is_higher = true){
    int sign = greater_is_higher ? 1 : -1;
    return sensor_value * sign > threshold * sign;
}

void printIfChanged(int sensor_value, string messages[]){
    static int prev_sensor_value = sensor_value;
    

}

void setup(){
  setUpFlameSensor(flame_sensor_pin);
  setUpLed(led_pin);
  Serial.begin(baud_rate);
  threshold = ui_calibration(flame_sensor_pin);
}

void loop(){
  static bool flag;
  int flame_sensor_value = analogRead(flame_sensor_pin);
  flame_sensor_value = digitalisedData(flame_sensor_value, threshold, false);
  digitalWrite(led_pin, flame_sensor_value);
}
