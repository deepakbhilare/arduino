#include<LiquidCrystal.h>

LiquidCrystal m(12, 11, 5, 4, 3, 2);

const int LM_35 = A0;
const int LDR = A1;
const int buzzer = 6;
int input_val_ldr = 0;
int input_val = 0;
int backlight = 13;
//float temp = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  m.begin(16, 2);
  pinMode(backlight, HIGH);
  pinMode(buzzer, OUTPUT);

  //initialize display and calibrating sensor
  m.home();
  m.setCursor(0, 0);
  digitalWrite(backlight, HIGH);
  m.print("Initializing ... ");

  //Beep the buzzer till calibration is not done
  digitalWrite(buzzer, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = 0;

  //initialize display to show temperature
  m.home();
  m.setCursor(0, 1);
  m.print("    ");

  input_val_ldr = analogRead(LDR);
  Serial.print("LDR value is : ");
  Serial.println(input_val_ldr);

  //read temperature for 5 secs and take the mean, this is also used for initial calibration
  for (int i = 0; i < 5; i++) {
    temp += (5.0 * analogRead(LM_35) * 100.0) / 1024;
    delay(1000);
  }

  //Switch off the buzzer once calibration is done
  digitalWrite(buzzer, LOW);

  temp /= 5;

  Serial.print("Temp :");
  Serial.println(temp);

  m.print(temp);
  m.print(" C       ");

  m.setCursor(0, 0);

  if (input_val_ldr < 200) {
    digitalWrite(backlight, HIGH);
    m.print("TEMP:NIGHT:R");
    m.print(input_val_ldr);
  }
  else {
    m.print("TEMP:DAY:R");
    digitalWrite(backlight, LOW);
    m.print(input_val_ldr);
  }

  m.print("      ");
}