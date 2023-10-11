#include <Arduino.h>

constexpr unsigned int baud_rate = 9600;
constexpr unsigned int rounds_calibration = 500;
constexpr unsigned int delay_calibration = 10;
constexpr float ratio_calibration = 0.3;

constexpr byte flame_sensor_pin = A0;
constexpr byte led_pin = LED_BUILTIN;
int threshold;

void setUpFlameSensor(byte flame_sensor_pin){
  pinMode(flame_sensor_pin, INPUT);
}

int readFlameSensor(byte flame_sensor_pin){
  int value  = analogRead(flame_sensor_pin);
  // Serial.print(value);
  // Serial.print(" ");
  return value;
}

void setUpLed(byte led_pin){
  pinMode(led_pin, OUTPUT);
}

int calibrate(byte flame_sensor_pin){
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
        do{
            input = Serial.read();
        } while(input == -1);
    } while(input != 'y');
    Serial.println("\nCalibration starts");
    int threshold = calibrate(flame_sensor_pin);
    Serial.println("Calibration ends with threshold: " + String(threshold));
    return threshold;
} 

bool digitalisedData(int sensor_value, int threshold, bool greater_is_higher = true){
    int sign = greater_is_higher ? 1 : -1;
    return sensor_value * sign > threshold * sign;
}

void printIfChanged(int sensor_value, String messages[2]){
  static int prev_sensor_value = sensor_value;
  static bool flag;
  if(prev_sensor_value == sensor_value){
    return;
  }
  Serial.println(messages[flag]);
  prev_sensor_value = sensor_value;
  flag = !flag;
}

void setup(){
  setUpFlameSensor(flame_sensor_pin);
  setUpLed(led_pin);
  Serial.begin(baud_rate);
  threshold = ui_calibration(flame_sensor_pin);
}

void loop(){
  static bool flag;
  int flame_sensor_value = readFlameSensor(flame_sensor_pin);
  flame_sensor_value = digitalisedData(flame_sensor_value, threshold, false);
  String messages[] = {"Flame detected", "Flame not detected"};
  printIfChanged(flame_sensor_value, messages);
  digitalWrite(led_pin, flame_sensor_value);
}
