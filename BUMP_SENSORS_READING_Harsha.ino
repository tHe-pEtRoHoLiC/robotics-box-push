# define LS_EMIT_PIN      11    // Documentation says 11.
//# define LS_LEFT_PIN      A11   // Complete for DN1 pin
//# define LS_MIDLEFT_PIN   A0   // Complete for DN2 pin
//# define LS_MIDDLE_PIN    A2   // Complete for DN3 pin
//# define LS_MIDRIGHT_PIN  A3   // Complete for DN4 pin
//# define LS_RIGHT_PIN     A4   // Complete for DN5 pin
# define BUMP_LEFT_PIN    4
# define BUMP_RIGHT_PIN   5



// Store our pin numbers into an array, which means
// we can conveniently select one later.
// ls(line sensor)_pin
//int ls_pins[5] = {LS_LEFT_PIN,
//                  LS_MIDLEFT_PIN,
//                  LS_MIDDLE_PIN,
//                  LS_MIDRIGHT_PIN,
//                  LS_RIGHT_PIN };


//# define MAX_SAMPLES 5
//float results[ MAX_SAMPLES ]; // An array of MAX_SAMPLES length


//Bump sensors array declaration
int BS_pins[2]={BUMP_LEFT_PIN,
                BUMP_RIGHT_PIN,
                };

# define Max_Bump_Sensors 2
float bump_results[Max_Bump_Sensors];


void setup() 
  {

   //sensor read pin
//   pinMode(BUMP_LEFT_PIN, INPUT);
//   pinMode(BUMP_RIGHT_PIN, INPUT);
  
   // Set some initial pin modes and states
   pinMode( LS_EMIT_PIN, OUTPUT ); 
   digitalWrite(LS_EMIT_PIN, HIGH);
  
   // Start Serial, wait to connect, print a debug message.
   Serial.begin(9600);
   delay(500);
   Serial.println("***RESET***");

  } // End of setup()


void loop() {

  // Collect MAX_SAMPLES readings.
  for( int i = 0 ; i < Max_Bump_Sensors; i++) 
   {

           // This calls our new function, which you need
           // to complete below.  As a result, this should read DN1
           // and save the reading into results[i].
    bump_results[i] = readBumpSensor( i );  
    delay(200);
   }

      Serial.println("Results: ");
      for( int i = 0; i < Max_Bump_Sensors; i++ ) 
      {
        Serial.println( bump_results[i] );
      }
      delay(1000);
  

} // End of loop()



// A function to read a line sensor.
// Specify which sensor to read with number.
// Number should be a value between 0 and 4
float readBumpSensor( int number ) 
  {
   
    pinMode( LS_EMIT_PIN, OUTPUT );
    digitalWrite( LS_EMIT_PIN, HIGH );

    //retrieve pin values from array
    pinMode( BS_pins[ number ], OUTPUT );
    digitalWrite( BS_pins[ number ], HIGH );
    delayMicroseconds( 10 );

    pinMode( BS_pins[number], INPUT);
    
    unsigned long start_time = micros();

    while( digitalRead( BS_pins[number] ) == HIGH ) 
    {
        // Do nothing here (waiting).
    }
    
    pinMode( LS_EMIT_PIN, INPUT );
    
    unsigned long end_time = micros();

    unsigned long elapsed_time = end_time - start_time;

    // Give the result back to wherever this
    // function was called from.
    return (float)elapsed_time;
}
