#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2) ;


int pinTrig = 3;           //Transmisor del sensor US.
int pinEcho = 4;           //Receptor del sensor

int led_Green=5;          //Led indicador de tanque lleno (verde)
int led_Red=6;         //Led indicador de tanque vació (rojo) 
int buzzer=A0;          //Puerto que activa el Buzzer
long var_time;            //Variable de tiempo para el sensor
int var_dist;             //Variable de distancia

void setup() {
Serial.begin(9600);
lcd.backlight();
lcd.init();
pinMode(pinTrig, OUTPUT);
pinMode(pinEcho, INPUT);

pinMode(led_Green, OUTPUT);
pinMode(led_Red, OUTPUT);
pinMode(buzzer,OUTPUT);

}


void loop() {

digitalWrite(pinTrig, 0);                //El trig del sensor iniciado en estado bajo.
delayMicroseconds(2);                 //Esperamos 5 microsegundos antes de mandar la primera onda, evitando señales erróneas
digitalWrite(pinTrig, HIGH);//Inicialización del trig
delayMicroseconds(10);
digitalWrite(pinTrig,LOW);
var_time= pulseIn(pinEcho, HIGH);          //Variable que almacena el tiempo de ida y regreso de la onda del sensor.
                                      //Velocidad del Sonido es 349.2 m/s (a 30ºc al nivel del mar)->0.0349cm/microsegundo, Si V=d/t entonces d=(v*(t/2))
var_dist= int (0.034*(var_time/2));      //Variable que almacena la distancia recorrida por la onda. 

delay(100);                           //Cada 600 milisegundos mandara una onda ultrasonica para actualizar la dist
lcd.clear(); 
lcd.setCursor(0,0);
lcd.print("Medida:");  
Serial.println(var_dist);

if((var_dist<100)&&(var_dist>=0)){

lcd.print(var_dist); 

}
else{
lcd.print("xxx");
}
lcd.print("cm");


if((var_dist<100)&&(var_dist>=51)){      //----- 
lcd.setCursor(0,1);
lcd.print("Dist segura"); 
digitalWrite(led_Green, HIGH);
digitalWrite(led_Red, LOW); 
digitalWrite(buzzer, LOW);

}


if((var_dist<50)&&(var_dist>=26)){      //----- 
lcd.setCursor(0,1);
lcd.print("PRECAUCION"); 
digitalWrite(led_Green, LOW);
digitalWrite(led_Red, HIGH); 
digitalWrite(buzzer, LOW);

}

if((var_dist<25)&&(var_dist>=5)){      //----- 
lcd.setCursor(0,1);
lcd.print("ALERTA"); 
digitalWrite(led_Green, LOW);
digitalWrite(led_Red, LOW); 
digitalWrite(buzzer, HIGH);

}

}
