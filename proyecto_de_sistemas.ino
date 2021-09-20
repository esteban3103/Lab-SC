
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2,4); //configuración de la comunicación bluetooth, pin 2=RX, Pin 4= TX
//declaración de valores a utilizar
int in_motor1_1=13;  //pines usados para habilitar los motores desde el puente H
int in_motor2_1=12;
int in_motor1_2=11;
int in_motor2_2=10;
//----------------------------------
int pwm_motor_1=5; //pines con PWM usados para modificar la velocidad de los motores
int pwm_motor_2=3;
//----------------------------------
int led=9;        //alarmas para cada una de las condiciones
int buzzer=8;
//--------------------------------------------------------
int pinTrig = 7;           //Transmisor del sensor US.
int pinEcho = 6;           //Receptor del sensor
long var_time;            //Variable de tiempo para el sensor
int var_dist;             //Variable de distancia


void setup() {
  bluetooth.begin(9600);     //inicialización del reloj para el bluetooth
  Serial.begin(9600);        
//Configuración de pines 
pinMode(pinTrig, OUTPUT);  
pinMode(pinEcho, INPUT);
pinMode(led, OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode (in_motor1_1,OUTPUT);
pinMode (in_motor2_1,OUTPUT);
pinMode (in_motor1_2,OUTPUT);
pinMode (in_motor2_2,OUTPUT);
pinMode (pwm_motor_1,OUTPUT);
pinMode (pwm_motor_2,OUTPUT);
}

void loop() {
digitalWrite(in_motor1_1,HIGH);     //Configuración de los pines para iniciar el giro de los motores
digitalWrite(in_motor2_1,LOW);
digitalWrite(in_motor1_2,HIGH);
digitalWrite(in_motor2_2,LOW);

digitalWrite(pinTrig, LOW);                //El trig del sensor iniciado en estado bajo.
delayMicroseconds(2);                 //Esperamos 2 microsegundos antes de mandar la primera onda, evitando señales erróneas
digitalWrite(pinTrig, HIGH);//Inicialización del trig
delayMicroseconds(10);
digitalWrite(pinTrig,LOW);
var_time= pulseIn(pinEcho, HIGH);          //Variable que almacena el tiempo de ida y regreso de la onda del sensor.
                                      //Velocidad del Sonido es 349.2 m/s (a 30ºc al nivel del mar)->0.0349cm/microsegundo, Si V=d/t entonces d=(v*(t/2))
var_dist= int (var_time/58.2);      //Variable que almacena la distancia recorrida por la onda. 

Serial.println(var_dist);
bluetooth.print("Distancia (cm): ");
bluetooth.println(var_dist);          //Envío de la variable de distancia por Bluetooth
delay(50);                           //Cada 50 milisegundos mandara una onda ultrasonica para actualizar la dist

if(var_dist<150 && var_dist>100){      //----- Medición del sensor para 1.5 y 1 metro
analogWrite(pwm_motor_1,255);         // el PWM se activa al 100% para ambos motores
analogWrite(pwm_motor_2,255);
analogWrite(led,0);
digitalWrite(buzzer,LOW);
}

if(var_dist<100 && var_dist>50){      //----- Medición de distancia entre 1 metro y 50 centímetros
analogWrite(pwm_motor_1,191);       // El PWM se coloca al 75% en ambos motores
analogWrite(pwm_motor_2,191);
analogWrite(led,(100-var_dist)*255/50);    //Se enciende el led con una intensidad proporcional a la distancia medida
digitalWrite(buzzer,LOW);

}

if(var_dist<50 && var_dist>25){      //----- Medición entre 50 y 25 centímetros
analogWrite(pwm_motor_1,128);        //PWM colocado al 50%
analogWrite(pwm_motor_2,128);
analogWrite(led,0);
digitalWrite(buzzer,HIGH);           //Se enciende la alarma auditiva

}

if(var_dist<25){      //----- Medición menor a 25 cm
analogWrite(pwm_motor_1,0);   //se apagan los motores
analogWrite(pwm_motor_2,0);
analogWrite(led,0);
digitalWrite(buzzer,LOW);

}

}
