
const int stbPin = 7;
const int clkPin = 9;
const int dioPin = 8;
int button=4;
int tump=0;
int temp=0;
int push=0;
void sendCommand(uint8_t value) { 
   digitalWrite(stbPin, LOW);
   shiftOut(dioPin, clkPin, LSBFIRST, value);
   digitalWrite(stbPin, HIGH);
}  

void setup() {
   pinMode(stbPin, OUTPUT);
   pinMode(clkPin, OUTPUT);
   pinMode(dioPin, OUTPUT);
   sendCommand(0x8f);
   pinMode(button,INPUT);
   Serial.begin(9600);
}

void loop() {
  push=digitalRead(button);
   if (push==HIGH){
    temp = temp + 1;
    delay(2000);
   }
   tump = temp/2;
   if(tump > 4){
    tump=0;
   }
  Serial.println(push);
  Serial.println(temp);
  delay(500);
  number();
}

bool number() {
   uint8_t digits[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };   
   sendCommand(0x40);
   digitalWrite(stbPin, LOW);
   shiftOut(dioPin, clkPin, LSBFIRST, 0xc0);
   shiftOut(dioPin, clkPin, LSBFIRST, digits[tump/1000%10]);
   shiftOut(dioPin, clkPin, LSBFIRST, 0x00);            
   shiftOut(dioPin, clkPin, LSBFIRST, digits[tump/100%10]);
   shiftOut(dioPin, clkPin, LSBFIRST, 0x00);
   shiftOut(dioPin, clkPin, LSBFIRST, digits[tump/10%10]);
   shiftOut(dioPin, clkPin, LSBFIRST, 0x00);
   shiftOut(dioPin, clkPin, LSBFIRST, digits[tump%10]);
   shiftOut(dioPin, clkPin, LSBFIRST, 0x00);
   digitalWrite(stbPin, HIGH);
   return 0; 
 }
