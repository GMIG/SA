//#define TRACE 1
//#define DEBUG 1
#define firstPin A0
#define noOfPins 6
//#define COM9 1
#define COM8 1

#define ONPLACE 1
#define NOT_ONPLACE 0


#ifdef COM9
  int thrs[noOfPins] = {3002, 2500, 2977, 2987, 2995, 2981}; //com9
#endif //COM9
#ifdef COM8
  int thrs[noOfPins] = {2990, 2999, 2980, 2967, 2994, 2500}; //com8
#endif //COM8

int prevState[noOfPins] = {0, 0, 0, 0, 0, 0};

void printBits(long int n);

void setup() {
  Serial.begin(9600);          //  setup serial
  analogReadResolution(12);
  while (!Serial) {}
  delay(3000);
}

void loop() {

  for (int i = firstPin; i < firstPin + noOfPins; i++) {
#ifdef TRACE
    Serial.print(i);
    Serial.print(", ");
    Serial.print(analogRead(i));
    Serial.print(", ");
#endif
    int cindex = i - A0;
    int curstate = prevState[cindex];
    if (analogRead(i) < thrs[cindex]) {
      curstate = ONPLACE;
    }
    if (analogRead(i) > thrs[cindex] + 20) {
      curstate = NOT_ONPLACE;
    }
    if (prevState[cindex] != curstate) {
      char writeChar = 0;
      writeChar = curstate;
      writeChar = writeChar << 3;
      writeChar = writeChar | cindex;
#ifdef DEBUG
      printBits(writeChar);
      Serial.println();
#endif //DEBUG
#ifndef DEBUG || TRACE
      Serial.write(writeChar);
#endif  //DEBUG || TRACE
  }
    prevState[cindex] = curstate ;
  }
#ifdef TRACE
  Serial.println();
#endif
  delay(70);

}

void printBits(long int n) {
  byte numBits = 8;
  char b;
  char c = ' ';
  for (byte i = 0; i < numBits; i++) {
    b = (n & (1 << (numBits - 1 - i))) > 0 ? '1' : '0';
    Serial.print(b);
    if (i < (numBits - 1) && ((numBits - i - 1) % 4 == 0 ))
      Serial.print(c);
  }
}




