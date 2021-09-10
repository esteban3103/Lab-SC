
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2) ;

int int_in =2;
int led_out=3;
int value_estate=0;
int in_pot =0;
int intensity;
int cont_push=0;
int push_add=5;
int push_sub=6;
int porciento;
int value_push_add;
int value_push_sub;
 void setup() {
  Serial.begin(9600);
  lcd.backlight();
  lcd.init();
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print("Estado: ");
   
  pinMode (int_in,INPUT);  
  pinMode (led_out, OUTPUT);
  pinMode (push_add,INPUT);
  pinMode (push_sub,INPUT);
}

void loop() {


value_estate=digitalRead(int_in);

//Primera condición
  if (value_estate==HIGH){
    lcd.setCursor(8,0);
    lcd.print("Pos 1");

    intensity=analogRead(in_pot);

    if(intensity>=0 && intensity<=300){
    lcd.setCursor(4,1);
    lcd.print("DC=25%");
      analogWrite(led_out,64); //1024/4 *25% 
      }
 
    if(intensity>300 && intensity<=700){
    lcd.setCursor(4,1);
    lcd.print("DC=50%");
      analogWrite(led_out,128); //1024/4*50%
    }
    
    if(intensity>700 && intensity<=1024){
    lcd.setCursor(4,1);
    lcd.print("DC=75%");
      analogWrite(led_out,192); //1024/4*75%
    }
  }

//Segunda Condición 
  else {
    lcd.setCursor(8,0);
    lcd.print("Pos 2");
value_push_add=digitalRead(push_add);
   if(value_push_add==HIGH){
    if(cont_push<3){
      delay(200);
      cont_push=cont_push+1;
      porciento=25*cont_push;
      lcd.setCursor(4,1);
      lcd.print("DC= ");
      lcd.print(porciento);
      lcd.setCursor(11,1);
      lcd.print("%");
      analogWrite(led_out,1024/400*porciento);
    }}

value_push_sub=digitalRead(push_sub);
   if(value_push_sub==HIGH){
    if(cont_push>1){
      delay(200);
      cont_push=cont_push-1;
      porciento=25*cont_push;
      lcd.setCursor(4,1);
      lcd.print("DC= ");
      lcd.print(porciento);
      lcd.setCursor(11,1);
      lcd.print("%");
      analogWrite(led_out,1024/400*porciento);
    }}


  }

}
