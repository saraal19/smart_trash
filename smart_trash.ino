#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

// stepper Motor
const int stepsPerRevolution = 2038;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); 
// Ultra
long t;

void setup() {
  Serial.begin(9600);
  pinMode(13,INPUT); //echo
  pinMode(12,OUTPUT); //trig 
  lcd.init();  // Initialize I2C LCD module
  lcd.backlight();
  lcd.setCursor(0, 0);               // Go to column 0, row 1
  lcd.print("Hi, it's meca");
  delay(500);
  myStepper.setSpeed(10);
}

void loop() {
  lcd.clear();  // Initialize I2C LCD module
  lcd.setCursor(0, 0);               // Go to column 0, row 1
  lcd.print("Happy day!");
  lcd.setCursor(0, 1);               // Go to column 0, row 2
  lcd.print("poubelle vide");
  //ultra son
  digitalWrite(12,HIGH);
  delayMicroseconds(10);
  digitalWrite(12,LOW);
  t = pulseIn(13,HIGH);
  float v = 340; //m/s
  float d = (v*t/10000)/2;
  Serial.print(d);
  Serial.println("cm");

  if (d<10){
    lcd.clear();  // Initialize I2C LCD module
    lcd.setCursor(0, 0);               // Go to column 0, row 1
    lcd.print("La poubelle va ");
    lcd.setCursor(0, 1);               // Go to column 0, row 2
    lcd.print("ouvrire");
    // Rotate CW slowly at 10 RPM
    myStepper.step(600);
    lcd.clear();
    lcd.setCursor(0, 0);               // Go to column 0, row 1
    lcd.print("La poubelle va ");
    lcd.setCursor(0, 1);               // Go to column 0, row 2
    lcd.print("ferme");
    // Rotate CCW quickly at 10 RPM
    //monter
    myStepper.step(-600);
  }else{
    lcd.clear();  // Initialize I2C LCD module
    lcd.setCursor(0, 0);               // Go to column 0, row 1
    lcd.print("Happy day!");
    lcd.setCursor(0, 1);               // Go to column 0, row 2
    lcd.print("poubelle vide");
  }
}
