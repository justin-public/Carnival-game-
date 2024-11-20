#include <Adafruit_NeoPixel.h>
#include <Thread.h>
#include <ThreadController.h>

#ifdef __AVR__
 #include <avr/power.h> 
#endif

ThreadController controll = ThreadController();
Thread* myThread = new Thread();
Thread hisThread = Thread();

#define SO_PIN 12
#define ST_PIN 11
#define SCK_PIN 13
#define CS_PIN 10  // change ?? 14

#if 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#endif

#define NUM_LED 24

int IR_LED[] = {22,23,24,25,26,27,28,29,30};
int IR_LED_CNT = 8;

#if 1
Adafruit_NeoPixel pixels1(NUM_LED, PIN2, NEO_GRB + NEO_KHZ800);   // score 2 
Adafruit_NeoPixel pixels2(NUM_LED, PIN3, NEO_GRB + NEO_KHZ800);   // score 2 
Adafruit_NeoPixel pixels3(NUM_LED, PIN4, NEO_GRB + NEO_KHZ800);   // score 1
Adafruit_NeoPixel pixels4(NUM_LED, PIN5, NEO_GRB + NEO_KHZ800);   // score 3
Adafruit_NeoPixel pixels5(NUM_LED, PIN6, NEO_GRB + NEO_KHZ800);   // score 2 
Adafruit_NeoPixel pixels6(NUM_LED, PIN7, NEO_GRB + NEO_KHZ800);   // score 1
Adafruit_NeoPixel pixels7(NUM_LED, PIN8, NEO_GRB + NEO_KHZ800);   // score 1 
Adafruit_NeoPixel pixels8(NUM_LED, PIN9, NEO_GRB + NEO_KHZ800);   // score 2
Adafruit_NeoPixel pixels9(NUM_LED, PIN10, NEO_GRB + NEO_KHZ800);  // score 2 
#endif

#define Buffer   16

char Sensor_rcv1[Buffer];
char Sensor_rcv1_S[Buffer];

char Sensor_rcv2[Buffer];
char Sensor_rcv2_S[Buffer];

char Sensor_rcv3[Buffer]; 
char Sensor_rcv3_S[Buffer];
char Sensor_rcv3_SS[Buffer];

char Sensor_rcv4[Buffer];
char Sensor_rcv4_S[Buffer];
char Sensor_rcv4_SS[Buffer];

char Sensor_rcv5[Buffer];
char Sensor_rcv5_S[Buffer];

char Sensor_rcv6[Buffer];
char Sensor_rcv6_S[Buffer];

char Sensor_rcv7[Buffer];

char Sensor_rcv8[Buffer];

char Sensor_rcv9[Buffer];

/**/
const int buttonPin = 11;

int buttonState = 0;         
int cnt = 0;

int state_m = 1;

int buttonState1 = 0;         
int cnt_1 = 0;

/**/
int reset_pin = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  
  digitalWrite(reset_pin, HIGH);
  delay(200);
  pinMode(reset_pin, OUTPUT);
  
  for(int Irpin = 0; Irpin<IR_LED_CNT; Irpin++){
       pinMode(IR_LED[Irpin],INPUT);
  }
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  #if 1
  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
  pixels5.begin();
  pixels6.begin();
  pixels7.begin();
  pixels8.begin();
  pixels9.begin();
  #endif
  #if 0
  hole1_led(0,150,150);       // 1단계  
  hole2_led(0,150,150);
  hole3_led(0,150,150);
  hole4_led(0,150,150);
  hole5_led(0,150,150);
  hole6_led(0,150,150);
  hole7_led(150,0,150);
  hole8_led(150,0,150);
  hole9_led(0,150,150);
  #endif
  #if 1
  hole1_led(0,0,0);   
  hole2_led(0,0,0);
  hole3_led(0,0,0);
  hole4_led(0,0,0);
  hole5_led(0,0,0);
  hole6_led(0,0,0);
  hole7_led(0,0,0);
  hole8_led(0,0,0);
  hole9_led(0,0,0);
  #endif
  myThread->onRun(hole_sensor);
  myThread->setInterval(1);

  //hisThread.onRun(hole_led);
  //hisThread.setInterval(2);
  
  controll.add(myThread);
  //controll.add(&hisThread);
}


int step_s0 = 1;      // Sensor 0  , Score 2
int step_s1 = 1;      // Sensor 1  , Score 2

int step_s2 = 1;      // Sensor 3  , Score 3
int step_s3 = 1;      // Sensor 4  , Score 3

int step_s4 = 1;
int step_s5 = 1;

int step_s6 = 1;
int step_s7 = 1;

int step_s8 = 1;
int step_s9 = 1;

int cnt1,cnt2,cnt3,cnt4,cnt5,cnt6,cnt7,cnt8,cnt9;

#if 1
void hole_sensor()
{
   /*Sensor1*/
   if(step_s0 == 1)
   {
      if(digitalRead(IR_LED[0]) == LOW){
        hole1_led(150,150,0);
        cnt1++;
        delay(200);
      }
      if(cnt1 == 1)
      {
        sprintf(Sensor_rcv1,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv1);
        hole1_led(150,0,150);
        delay(200);
        cnt1 = 0;
        step_s0 = 2;
      }
   }
   if(step_s0 == 2)
   {
      if(digitalRead(IR_LED[0]) == LOW)
      {
        hole1_led(150,150,0);
        cnt1++;
        delay(200);
      }
      if(cnt1 == 1)
      {
        sprintf(Sensor_rcv1_S,"player;1;score;2",sizeof(Buffer));
        Serial.print(Sensor_rcv1_S);
        hole1_led(150,0,150);
        delay(300);
        cnt1 = 0;
      }
   }
   /**********/
   /*Sensor2*/
   if(step_s1 == 1)
   {
      if(digitalRead(IR_LED[1]) == LOW){
        hole2_led(150,150,0);
        cnt2++;
        delay(200);
      }
      if(cnt2 == 1)
      {
        sprintf(Sensor_rcv2,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv2);
        hole2_led(150,0,150);
        delay(200);
        cnt2 = 0;
        step_s1 = 2;
      }
   }
   if(step_s1 == 2)
   {
      if(digitalRead(IR_LED[1]) == LOW)
      {
        hole2_led(150,150,0);
        cnt2++;
        delay(200);
      }
      if(cnt2 == 1)
      {
        sprintf(Sensor_rcv2_S,"player;1;score;2",sizeof(Buffer));
        Serial.print(Sensor_rcv2_S);
        hole2_led(150,0,150);
        delay(300);
        cnt2 = 0;
      }
   }
   /**********/
   /*Sensor3*/
   if(step_s2 == 1)
   {
      if(digitalRead(IR_LED[3]) == LOW){
        hole4_led(150,150,0);
        cnt3++;
        delay(200);
      }
      if(cnt3 == 1)
      {
        sprintf(Sensor_rcv3,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv3);
        hole4_led(150,0,150);       //Red
        delay(200);
        cnt3 = 0;
        step_s2 = 2;
      }
   }
   if(step_s2 == 2)
   {
      if(digitalRead(IR_LED[3]) == LOW)
      {
        hole4_led(150,150,0);
        cnt3++;
        delay(200);
      }
      if(cnt3 == 1)
      {
        sprintf(Sensor_rcv3_S,"player;1;score;2",sizeof(Buffer));
        Serial.print(Sensor_rcv3_S);
        hole4_led(0,150,0);         //Red
        delay(300);
        cnt3 = 0;
        step_s2 = 3;
      }
   }
   if(step_s2 == 3)
   {
     if(digitalRead(IR_LED[3]) == LOW)
      {
        hole4_led(150,150,0);
        cnt3++;
        delay(200);
      }
      if(cnt3 == 1)
      {
        sprintf(Sensor_rcv3_SS,"player;1;score;3",sizeof(Buffer));
        Serial.print(Sensor_rcv3_SS);
        hole4_led(0,150,0);         //Red
        delay(300);
        cnt3 = 0;
      }
   }
   /**********/
   /*Sensor4*/
   if(step_s3 == 1)
   {
      if(digitalRead(IR_LED[4]) == LOW){
        hole5_led(150,150,0);
        cnt4++;
        delay(200);
      }
      if(cnt4 == 1)
      {
        sprintf(Sensor_rcv4,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv4);
        hole5_led(150,0,150);
        delay(200);
        cnt4 = 0;
        step_s3 = 2;
      }
   }
   if(step_s3 == 2)
   {
      if(digitalRead(IR_LED[4]) == LOW)
      {
        hole5_led(150,150,0);
        cnt4++;
        delay(200);
      }
      if(cnt4 == 1)
      {
        sprintf(Sensor_rcv4_S,"player;1;score;2",sizeof(Buffer));
        Serial.print(Sensor_rcv4_S);
        hole5_led(0,150,0);
        delay(300);
        cnt4 = 0;
        step_s3 = 3;
      }
   }
   if(step_s3 == 3)
   {
      if(digitalRead(IR_LED[4]) == LOW)
      {
        hole5_led(150,150,0);
        cnt4++;
        delay(200);
      }
      if(cnt4 == 1)
      {
        sprintf(Sensor_rcv4_SS,"player;1;score;3",sizeof(Buffer));
        Serial.print(Sensor_rcv4_SS);
        hole5_led(0,150,0);
        delay(300);
        cnt4 = 0;
      }
   }
   /**********/

   /*Sensor6*/
   if(step_s4 == 1)
   {
      if(digitalRead(IR_LED[6]) == LOW){
        hole7_led(150,150,0);
        cnt5++;
        delay(200);
      }
      if(cnt5 == 1)
      {
        sprintf(Sensor_rcv5,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv5);
        hole7_led(0,150,150);
        delay(200);
        cnt5 = 0;
        step_s4 = 2;
      }
   }
   if(step_s4 == 2)
   {
      if(digitalRead(IR_LED[6]) == LOW)
      {
        hole7_led(150,150,0);
        cnt5++;
        delay(200);
      }
      if(cnt5 == 1)
      {
        sprintf(Sensor_rcv5_S,"player;1;score;2",sizeof(Buffer));
        Serial.print(Sensor_rcv5_S);
        hole7_led(0,150,150);
        delay(300);
        cnt5 = 0;
      }
   }
   /**********/

   /*Sensor8*/
   if(step_s5 == 1) 
   {
      if(digitalRead(IR_LED[8]) == LOW){
        hole9_led(150,150,0);
        cnt6++;
        delay(200);
      }
      if(cnt6 == 1)
      {
        sprintf(Sensor_rcv6,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv6);
        hole9_led(150,0,150);
        delay(200);
        cnt6 = 0;
        step_s5 = 2;
      }
   }
   if(step_s5 == 2)
   {
      if(digitalRead(IR_LED[8]) == LOW)
      {
        hole9_led(150,150,0);
        cnt6++;
        delay(200);
      }
      if(cnt6 == 1)
      {
        sprintf(Sensor_rcv6_S,"player;1;score;2",sizeof(Buffer));
        Serial.print(Sensor_rcv6_S);
        hole9_led(150,0,150);
        delay(300);
        cnt6 = 0;
      }
   }
   /**********/

   /*Sensor9*/
   if(step_s6 == 1) 
   {
      if(digitalRead(IR_LED[2]) == LOW){
        hole3_led(150,150,0);
        cnt7++;
        delay(200);
      }
      if(cnt7 == 1)
      {
        sprintf(Sensor_rcv7,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv7);
        hole3_led(0,150,150);
        delay(200);
        cnt7 = 0;
      }
   }
   /**********/

   /*Sensor10*/
   if(step_s6 == 1) 
   {
      if(digitalRead(IR_LED[2]) == LOW){
        hole3_led(150,150,0);
        cnt7++;
        delay(200);
      }
      if(cnt7 == 1)
      {
        sprintf(Sensor_rcv7,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv7);
        hole3_led(0,150,150);
        delay(200);
        cnt7 = 0;
      }
   }
   /**********/

   /*Sensor10*/
   if(step_s7 == 1) 
   {
      if(digitalRead(IR_LED[5]) == LOW){
        hole6_led(150,150,0);
        cnt8++;
        delay(200);
      }
      if(cnt8 == 1)
      {
        sprintf(Sensor_rcv8,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv8);
        hole6_led(0,150,150);
        delay(200);
        cnt8 = 0;
      }
   }
   /**********/

   /*Sensor11*/       
   if(step_s8 == 1) 
   {
      if(digitalRead(IR_LED[5]) == LOW){
        hole6_led(150,150,0);
        cnt8++;
        delay(200);
      }
      if(cnt8 == 1)
      {
        sprintf(Sensor_rcv8,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv8);
        hole6_led(0,150,150);
        delay(200);
        cnt8 = 0;
      }
   }
   /**********/

   /*Sensor12*/       
   if(step_s9 == 1) 
   {
      if(digitalRead(IR_LED[7]) == LOW){
        hole8_led(150,150,0);
        cnt9++;
        delay(200);
      }
      if(cnt9 == 1)
      {
        sprintf(Sensor_rcv9,"player;1;score;1",sizeof(Buffer));
        Serial.print(Sensor_rcv9);
        hole8_led(150,0,150);
        delay(200);
        cnt9 = 0;
      }
   }
   /**********/
}
#endif

#if 0
void hole_led(int hole_vis,int logic)
{
  if(hole_vis == 1)
  {
      hole1_led(0,139,139);         
      delay(200);
      if(logic == 1) hole1_led(150,150,150);
      if(logic == 0) hole1_led(0,0,0);
      delay(200);
      hole1_led(0,139,139);
      delay(200);
      if(logic == 1) hole1_led(150,150,150);
      if(logic == 0) hole1_led(0,0,0); 
  }
  if(hole_vis == 2)
  {
      hole2_led(0,139,139);         
      delay(200);
      if(logic == 1) hole2_led(150,150,150);
      if(logic == 0) hole2_led(0,0,0);
      delay(200);
      hole2_led(0,139,139);
      delay(200);
      if(logic == 1) hole2_led(150,150,150);
      if(logic == 0) hole2_led(0,0,0);
  }
  if(hole_vis == 3)
  {
      hole3_led(150,0,150);         
      delay(200);
      if(logic == 1) hole3_led(150,150,150);
      if(logic == 0) hole3_led(0,0,0);
      delay(200);
      hole3_led(150,0,150);
      delay(200);
      if(logic == 1) hole3_led(150,150,150);
      if(logic == 0) hole3_led(0,0,0);
  }
  if(hole_vis == 4)
  {
      hole4_led(0,10,255);         
      delay(200);
      if(logic == 1) hole4_led(150,150,150);
      if(logic == 0) hole4_led(0,0,0);
      delay(200);
      hole4_led(0,10,255);
      delay(200);
      if(logic == 1) hole4_led(150,150,150);
      if(logic == 0) hole4_led(0,0,0);
  }
  if(hole_vis == 5)
  {
      hole5_led(0,139,139);         
      delay(200);
      if(logic == 1) hole5_led(150,150,150);
      if(logic == 0) hole5_led(0,0,0);
      delay(200);
      hole5_led(0,139,139);
      delay(200);
      if(logic == 1) hole5_led(150,150,150);
      if(logic == 0) hole5_led(0,0,0);
  }
  if(hole_vis == 6)
  {
      hole6_led(150,0,150);         
      delay(200);
      if(logic == 1) hole6_led(150,150,150);
      if(logic == 0) hole6_led(0,0,0);
      delay(200);
      hole6_led(150,0,150);
      delay(200);
      if(logic == 1) hole6_led(150,150,150);
      if(logic == 0) hole6_led(0,0,0);
  }
  if(hole_vis == 7)
  {
      hole7_led(0,139,139);         
      delay(200);
      if(logic == 1) hole7_led(150,150,150);
      if(logic == 0) hole7_led(0,0,0);
      delay(200);
      hole7_led(0,139,139);
      delay(200);
      if(logic == 1) hole7_led(150,150,150);
      if(logic == 0) hole7_led(0,0,0);
  }
  if(hole_vis == 8)
  {
      hole8_led(0,150,150);         
      delay(200);
      if(logic == 1) hole8_led(150,150,150);
      if(logic == 0) hole8_led(0,0,0);
      delay(200);
      hole8_led(0,150,150);
      delay(200);
      if(logic == 1) hole8_led(150,150,150);
      if(logic == 0) hole8_led(0,0,0);
  }
  if(hole_vis == 9)
  {
      hole9_led(0,139,139);         
      delay(200);
      if(logic == 1) hole9_led(150,150,150);
      if(logic == 0) hole9_led(0,0,0);
      delay(200);
      hole9_led(0,139,139);
      delay(200);
      if(logic == 1) hole9_led(150,150,150);
      if(logic == 0) hole9_led(0,0,0);
   }
}
#endif

void hole1_led(int r, int g , int b)
{
  for(int i=0; i<NUM_LED; i++)
  {
      pixels1.setPixelColor(i, pixels1.Color(r, g, b));    // violet     0 , 255, 51 
  }
  pixels1.show();
}

void hole2_led(int r, int g , int b)
{
  for(int i=0; i<NUM_LED; i++)
  {
      pixels2.setPixelColor(i, pixels2.Color(r, g, b));    // violet 
  }
  pixels2.show();
}

void hole3_led(int r, int g , int b)
{
  for(int i=0; i<NUM_LED; i++)
  {
      pixels3.setPixelColor(i, pixels3.Color(r, g, b));    // violet 
  }
  pixels3.show();
}

void hole4_led(int r, int g , int b)
{
  for(int i=0; i<NUM_LED; i++)
  {
      pixels4.setPixelColor(i, pixels4.Color(r, g, b));    // violet 
  }
  pixels4.show();
}

void hole5_led(int r, int g , int b)
{
  for(int i=0; i<NUM_LED; i++)
  {
      pixels5.setPixelColor(i, pixels5.Color(r, g, b));    // violet 
  }
  pixels5.show();
}

void hole6_led(int r, int g , int b)
{
  for(int i=0; i<NUM_LED; i++)
  {
      pixels6.setPixelColor(i, pixels6.Color(r, g, b));    // violet 
  }
  pixels6.show();
}

void hole7_led(int r, int g , int b)
{
  for(int i=0; i<NUM_LED; i++)
  {
      pixels7.setPixelColor(i, pixels7.Color(r, g, b));    // violet 
  }
  pixels7.show();
}

void hole8_led(int r, int g , int b)
{
  for(int i=0; i<NUM_LED; i++)
  {
      pixels8.setPixelColor(i, pixels8.Color(r, g, b));    // violet 
  }
  pixels8.show();
}

void hole9_led(int r, int g , int b)
{
  for(int i=0; i<NUM_LED; i++)
  {
      pixels9.setPixelColor(i, pixels9.Color(r, g, b));    // violet 
  }
  pixels9.show();
}


void loop() {
  // put your main code here, to run repeatedly:
  if(state_m == 1)
  {
    cnt_1 = 0;
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW)
    {
      cnt++;
      delay(500);
    }
    if(cnt == 1)
    {
      hole1_led(0,150,150);       // 1단계  
      hole2_led(0,150,150);
      hole3_led(0,150,150);
      hole4_led(0,150,150);
      hole5_led(0,150,150);
      hole6_led(0,150,150);
      hole7_led(150,0,150);
      hole8_led(150,0,150);
      hole9_led(0,150,150);
      cnt = 0;
      state_m = 2;
   }
  }
  if(state_m == 2)
  {
    buttonState1 = digitalRead(buttonPin);
    if(buttonState1 == LOW)
    {
      cnt_1++;
      delay(500);
    }
    if(cnt_1 == 1)
    {
      state_m = 1;
      digitalWrite(reset_pin, LOW);
    }
    controll.run();
  }
}
