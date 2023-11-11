#define EMIT_PIN 11
#define BR 5 //bump BumpSensor right
#define BL 4 //bump BumpSensor left

// Store our pin numbers into an array, which means
// we can conveniently select one later.
// ls(line BumpSensor)_pin
int bump_pins[2] = {BR, BL};



#define LS_PIN_COUNT 5
#define MAX_SAMPLE 4
#define THRESHOLD 1500


class BumpSensor {

  public:
    int bump_pins[2] = {BR, BL};
    unsigned long end_times[2];
    int bump_sensor_reading[2];
    BumpSensor() {

    }

    void initialise() {
      pinMode(EMIT_PIN, INPUT);
      digitalWrite( EMIT_PIN, LOW );
      emitOFF();
    }
    void emitON() {
      pinMode(EMIT_PIN, OUTPUT);
      digitalWrite(EMIT_PIN, LOW);
    }
    void emitOFF() {
      pinMode(EMIT_PIN, INPUT);
    }


    float readBumpSensor() {
      int pin;
      int count = 2;
      bool done = false;
      emitON();

      for (int i = 0; i < 2; i++) {
        pinMode(bump_pins[i], OUTPUT);
        digitalWrite(bump_pins[i], HIGH);
      }

      delayMicroseconds(10);

      for (int i = 0; i < 2; i++) {
        end_times[i] = 0; //initialise end_times
      }

      for (int i = 0; i < 2; i++) {
        pinMode(bump_pins[i], INPUT);
      }
      unsigned long start_time = micros();

      while (done == false) {
        for (int i = 0; i < 2; i++) {

          if (end_times[i] == 0) {
            if (digitalRead(bump_pins[i]) == LOW) {
              end_times[i] = micros();
              count = count - 1;
            }
          }
          if (count == 0) {
            done = true;
          }
        }
        unsigned long elapsed_time;
        for (int i = 0; i < 2; i++) {
          elapsed_time = end_times[i] - start_time;
          bump_sensor_reading[i] = (float)elapsed_time;
        }
      }
      emitOFF();

    }
    /*
      float weighted_measure() {
      float LS, MS, RS, total;

      LS = bump_sensor_reading[1];
      MS = bump_sensor_reading[2];
      RS = bump_sensor_reading[3];

      total = LS + MS + RS;
      LS /= total;
      MS /= total;
      RS /= total;

      wleft = LS + (MS * 0.5);
      wright = RS + (MS * 0.5);

      errorline = wleft - wright;

      float Kp = 1;
      controlSignal = errorline * Kp;

      float maxTurn = 50;

      maxTurn *= controlSignal;
      Serial.print("maxTurn");
      Serial.print(maxTurn);
      Serial.println("");
      return maxTurn;
      }
    */

};
