#define BASE_STEP_PIN 2
#define BASE_DIR_PIN 3
#define BOOM_STEP_PIN 4
#define BOOM_DIR_PIN 5
#define SPOOL_STEP_PIN 6
#define SPOOL_DIR_PIN 7

#define BASE_ENA_PIN 8
#define BOOM_ENA_PIN 9
#define SPOOL_ENA_PIN 10

#define JOYSTICK_FORWARD 30
#define JOYSTICK_BACKWARD 31
#define JOYSTICK_LEFT 32
#define JOYSTICK_RIGHT 33
#define BUTTON_FORWARD 40
#define BUTTON_BACKWARD 41

bool BASE_ON = false;
bool BOOM_ON = false;
bool SPOOL_ON = false;

bool BASE_DIR = false;
bool BOOM_DIR = false;
bool SPOOL_DIR = false;

bool motorRunning = false;
//long stepDelay  = 250; //higher stepdelay = slower

long stepDelay = 10000;

//750 was the old one
//Base Stepper:
// 1 0 0 1 0 0
// 1 2 3 4 5 6

//Boom Stepper:
// 0 1 1 1 1 0
// 1 2 3 4 5 6

//Spool Stepper:
// 1 0 1 1 1 0
// 1 2 3 4 5 6


void setup() {
  pinMode(BASE_STEP_PIN, OUTPUT);
  pinMode(BASE_DIR_PIN, OUTPUT);
  pinMode(BOOM_STEP_PIN, OUTPUT);
  pinMode(BOOM_DIR_PIN, OUTPUT);
  pinMode(SPOOL_STEP_PIN, OUTPUT);
  pinMode(SPOOL_DIR_PIN, OUTPUT);


  pinMode(BASE_ENA_PIN, OUTPUT);
  pinMode(BOOM_ENA_PIN, OUTPUT);
  pinMode(SPOOL_ENA_PIN, OUTPUT);

  digitalWrite(BASE_ENA_PIN, HIGH);
  digitalWrite(BOOM_ENA_PIN, HIGH);
  digitalWrite(SPOOL_ENA_PIN, HIGH);

  pinMode(JOYSTICK_FORWARD, INPUT_PULLUP);
  pinMode(JOYSTICK_BACKWARD, INPUT_PULLUP);
  pinMode(JOYSTICK_LEFT, INPUT_PULLUP);
  pinMode(JOYSTICK_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_FORWARD, INPUT_PULLUP);
  pinMode(BUTTON_BACKWARD, INPUT_PULLUP);

  Serial.begin(9600);
  //Serial.println("JESCO");
  //Serial.println("Joystick: Base and Boom, Button Spool");
}


void loop() {
  BASE_ON = false;
  BOOM_ON = false;
  SPOOL_ON = false;
  
  BASE_DIR = false;
  BOOM_DIR = false;
  SPOOL_DIR = false;
  motorRunning = false;

  //long stepDelay  = 250;

  if (!digitalRead(JOYSTICK_LEFT)) {
    motorRunning = true;
    BASE_ON = true;
    BASE_DIR = true;
    //Serial.println("LEFT");
    long stepDelay  = 10000;
  }

  if (!digitalRead(JOYSTICK_RIGHT)) {
    motorRunning = true;
    BASE_ON = true;
    BASE_DIR = false;
    //Serial.println("right");
    long stepDelay  = 10000;
  }

  if (!digitalRead(JOYSTICK_FORWARD)) {
    motorRunning = true;
    BOOM_ON = true;
    BOOM_DIR = false;
    //Serial.println("FORWARD");
  }

  if (!digitalRead(JOYSTICK_BACKWARD)) {
    motorRunning = true;
    BOOM_ON = true;
    BOOM_DIR = true;
    //Serial.println("BACKWARD");
  }

  if (!digitalRead(BUTTON_FORWARD)) {
    motorRunning = true;
    SPOOL_ON = true;
    SPOOL_DIR = true;
    //Serial.println("Button Forward");
  }

  if (!digitalRead(BUTTON_BACKWARD)) {
    motorRunning = true;
    SPOOL_ON = true;
    SPOOL_DIR = false;
    //Serial.println("Button Backward");
  }

  if (motorRunning) {  
    digitalWrite(BASE_DIR_PIN, BASE_DIR);
    digitalWrite(BOOM_DIR_PIN, BOOM_DIR);
    digitalWrite(SPOOL_DIR_PIN, SPOOL_DIR);

    if (BASE_ON)  {digitalWrite(BASE_STEP_PIN, HIGH);}


    if (BOOM_ON)  {
      
      digitalWrite(BOOM_STEP_PIN, HIGH);
      //Serial.println("Boom is on");

      }

      
    if (SPOOL_ON) {
      
      digitalWrite(SPOOL_STEP_PIN, HIGH);
      //Serial.println("Spool is on");

      }

    delayMicroseconds(stepDelay);

    digitalWrite(BASE_STEP_PIN, LOW);
    digitalWrite(BOOM_STEP_PIN, LOW);
    digitalWrite(SPOOL_STEP_PIN, LOW);

    delayMicroseconds(stepDelay);
  }
}
