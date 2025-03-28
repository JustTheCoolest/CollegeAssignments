/*
Notes:
Use data types like uint and uchar to save memory
*/

constexpr unsigned char NUM_CARS = 4;
constexpr byte SENSORS[] = {A0, A1, A2, A3};
constexpr byte INDICATORS[] = {D0, D1, D2, D3};

void setup(){
    for(int i=0; i<NUM_CARS; ++i){
        pinMode(INDICATORS[i], OUTPUT);
        digitalWrite(INDICATORS[i], LOW);
    }
}

void loop(){
    for(int i = 0; i < NUM_CARS; ++i){
        if(digitalRead(SENSORS[i])){
            digitalWrite(INDICATORS[i], LOW);
        }
        else{
            digitalWrite(INDICATORS[i], HIGH);
        }
    }
}