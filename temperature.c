#include<LiquidCrystal.h>

LiquidCrystal m(12,11,5,4,3,2);

const int LM_35 = A0;
const int LDR = A1;
int input_val_ldr = 0;
int input_val = 0;
int backlight = 13;
float temp = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  m.begin(16, 2);
  pinMode(backlight, HIGH);  
}

void loop() {
  // put your main code here, to run repeatedly:
  input_val_ldr = analogRead(LDR);
  Serial.print("LDR value is : ");
  Serial.println(input_val_ldr);
  delay(1000);
  
  input_val = analogRead(LM_35);
  temp = (5.0 * input_val *100.0) / 1024;
  Serial.print("Temp :");
  Serial.println(temp);

  m.home();
  m.setCursor(0, 1);
  m.print("    ");

  m.print(temp);
  m.print(" C   ");

  m.setCursor(0, 0);
  
  if(input_val_ldr < 100){

    digitalWrite(backlight, HIGH);
    m.print("TEMP:NIGHT:R");
    m.print(input_val_ldr);
  }
  else{
      m.print("TEMP:DAY:R");
      m.print(input_val_ldr);    
  }

  m.print("      ");
    
  delay(1000);

  if(input_val_ldr < 100)
    digitalWrite(backlight, HIGH);
}
