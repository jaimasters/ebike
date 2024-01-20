// ALL DIGITAL PINS ARE OFFSET BY +1 in order to match up with display pinout 1-12


float output = 0;
#define wheel_rad 0.311 //m

#define pi 3.14159265359

int digits[4] = { 12, 9, 8, 6};
int subdigits[7] = {11, 7, 4, 2, 1, 10, 5};
int dp = 3; 

volatile long int last_tach = 0; 
volatile float velocity = 0; 



int integers[11][8] = {
// A  B  C  D  E  F  G,  Pixels
  {1, 1, 1, 1, 1, 1 ,0,  6},
  {0, 1, 1, 0, 0, 0 ,0,  2},
  {1, 1, 0, 1, 1, 0 ,1,  5},
  {1, 1, 1, 1, 0, 0 ,1,  5},
  {0, 1, 1, 0, 0, 1 ,1,  4},
  {1, 0, 1, 1, 0, 1 ,1,  5},
  {1, 0, 1, 1, 1, 1 ,1,  6},
  {1, 1, 1, 0, 0, 0 ,0,  3},
  {1, 1, 1, 1, 1, 1 ,1,  7},
  {1, 1, 1, 1, 0, 1 ,1,  6},
  {0, 0, 0, 0, 0, 0, 1,  1}
};

float tachometer() {
  if (analogRead(1) > 10) {return;}
  if (millis() - last_tach < 200) {return;}
  int deltaT = millis() - last_tach;
  last_tach = millis();
  float ang_vel = wheel_rad/(float(deltaT)/1000.0);
  float velocity = ang_vel*pi*2.0;
  float kmph = velocity * 3.6;
  Serial.println("updated: " + String(kmph));
  return(kmph);
} 


void setup() {
  Serial.begin(115200);
  for (int i = 1;i < 13;i++){
    pinMode(i+1, OUTPUT);
    digitalWrite(i+1, LOW);
  }
}

void off_digits() {
    //rst digits 
    for (int i_digit = 0; i_digit < 4; i_digit++) {
    digitalWrite(digits[i_digit]+1,HIGH);
  }


}

int write_out_binary(int input[4][7], int decimal[4], int freq) {
  for (int i_digit = 0; i_digit < 4; i_digit++) {
    // PER DIGIT
    off_digits();
    // write new number
    // get current digits subdigits
    for (int i_subdigit = 0; i_subdigit < 8; i_subdigit++){
      if ((input[i_digit][i_subdigit]) == 1) {
        digitalWrite(subdigits[i_subdigit]+1,HIGH);
      } else {
        digitalWrite(subdigits[i_subdigit]+1,LOW);
      } 
      
    }
    // open digit 
    digitalWrite(digits[i_digit]+1,LOW);
    // sleep for frequency
    delay(1000/freq);
  }
  off_digits();
}

int write_out_numerals( int input[4], int freq, int i_dp){
  int domain[5] = {0,1,2,3};
  for (int i_digit = 0; i_digit < 4; i_digit++) {
    // PER DIGIT
    off_digits();
    // write new number
    // get current digits subdigits
    for (int i_subdigit = 0; i_subdigit < 7; i_subdigit++){

      if ((integers[input[i_digit]][i_subdigit]) == 1) {
        digitalWrite(subdigits[i_subdigit]+1,HIGH);
      } else {
        digitalWrite(subdigits[i_subdigit]+1,LOW);
      } 
    }
    //Add dp if needed
    if(i_digit == i_dp){ digitalWrite(dp+1, HIGH);} else { digitalWrite(dp+1, LOW);}
    // open digit 
    digitalWrite(digits[i_digit]+1,LOW);
    // sleep for frequency, scaled by how many segments used for uniform brightness
    delay(1000*pow(integers[input[i_digit]][7],0.5)/(freq)); //number of segments extends time, load balancing brightness 
  }
  off_digits();
}

void write_out_float(float input, int freq) {
  String str_input = String(input,5);

  int decimal_place = str_input.indexOf("."); 
  str_input.remove(decimal_place,1);

  int num_output[4];
  for(int i = 0; i<4; i++){
    String singleDigit = String(str_input[i]);
    num_output[i] = singleDigit.toInt();
  }
  write_out_numerals(num_output,freq,decimal_place-1);
}



void loop() {
velocity = tachometer();
if (millis()%1000 < 10) {
//if (true) {
output = velocity;
Serial.print("speed: " + String(output,4));
Serial.println(" volt: " + String(analogRead(1)));
}
write_out_float(output,2000);

}
