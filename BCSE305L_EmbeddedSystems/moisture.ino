/*
Notes:
Use data types like uint and uchar to save memory
*/

constexpr int THRESHOLD = 512;

constexpr unsigned char NUM_PLANTS = 4;
constexpr byte SENSORS[] = {A0, A1, A2, A3};
constexpr byte PUMPS[] = {D0, D1, D2, D3};

void setup(){
    for(int i=0; i<NUM_PLANTS; ++i){
        pinMode(PUMPS[i], OUTPUT);
        digitalWrite(PUMPS[i], LOW);
    }
}

void loop(){
    for(int i = 0; i < NUM_PLANTS; ++i){
        if(analogRead(SENSORS[i]) >= THRESHOLD){
            digitalWrite(PUMPS[i], LOW);
        }
        else{
            digitalWrite(PUMPS[i], HIGH);
        }
    }
}