// ALL DIGITAL PINS ARE OFFSET BY +1 in order to match up with display pinout 1-12

int digits[4] = { 12, 9, 8, 6};
int subdigits[7] = {11, 7, 4, 2, 1, 10, 5};
int dp = 3; 

int integers[10][7] = {
// A  B  C  D  E  F  G
  {1, 1, 1, 1, 1, 1 ,0},
  {0, 1, 1, 0, 0, 0 ,0},
  {1, 1, 0, 1, 1, 0 ,1},
  {1, 1, 1, 1, 0, 0 ,1},
  {0, 0, 0, 0, 0, 0 ,0},
  {0, 0, 0, 0, 0, 0 ,0},
  {1, 0, 1, 1, 1, 1 ,1},
  {0, 0, 0, 0, 0, 0 ,0},
  {1, 1, 1, 1, 1, 1 ,1},
  {0, 0, 0, 0, 0, 0 ,0},
};


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

int write_out_numerals( int input[4], int freq){
  for (int i_digit = 0; i_digit < 4; i_digit++) {
    // PER DIGIT
    off_digits();

    int eight[7] = {1, 1, 1, 1, 1, 1 ,1};


    // write new number
    // get current digits subdigits
    for (int i_subdigit = 0; i_subdigit < 7; i_subdigit++){
      //if ((eight[i_subdigit]) == 1) {
      //if ((integers[input[i_subdigit]][i_subdigit]) == 1) {
      if ((integers[input[i_digit]][i_subdigit]) == 1) {
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
//testing
int one[4][7] = {
{0,0,0,0,0,0,0},
{0,0,0,0,0,0,0},
{0,0,1,0,0,0,0},
{0,0,0,1,0,0,0},
};

int bruh[4] {0,0,3,6};



void loop() {
write_out_numerals(bruh,1000);

}
