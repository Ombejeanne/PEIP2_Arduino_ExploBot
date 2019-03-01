#include <PS2X_lib.h>  //for v1.6
#include<Servo.h>

//manette
#define PS2_DAT        2  //  data brown résistance de 1K soudée  
#define PS2_CMD        3  //  command orange
#define PS2_SEL        4  //  attention yellow
#define PS2_CLK        5  //  clock blue

#define pressures   false
#define rumble      false

PS2X ps2x; 

int error = 0;
byte type = 0;
byte vibrate = 0;

//servomoteur
#define cmdServo 9 //PB1 angles relevés: 0 55 110
Servo servo;
int angle=90; //angle donné en paramètre au servomoteur

//lampe
#define lampe 10
bool light=false;

//moteurs 
#define ENA 6
#define ENB 11
#define IN1 12
#define IN2 13
#define IN3 7
#define IN4 8

int vitesseA; //vitesse des deux moteurs
int vitesseB;

void setup(){

  //moteurs
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  
  //servo
  servo.attach(cmdServo);
  
  //lampe
  pinMode(lampe,OUTPUT);
  digitalWrite(lampe,LOW);
  
  
  //manette
  
  Serial.begin(57600);
  delay(300);  //pour laisser la manette se connecter
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
  if (pressures)
    Serial.println("true ");
  else
    Serial.println("false");
  Serial.print("rumble = ");
  if (rumble)
    Serial.println("true)");
  else
    Serial.println("false");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
  case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
}

void loop() {
  //commandes servo
  servo.write(angle); //on passe l'angle en argument à chaque passage de boucle, on changera la valeur de angle pour faire bouger le servo

  //moteurs
  if(ps2x.Analog(PSS_RY)<=128){ //si on est en marche avant (on regarde le jostick droit sur l'axe Y)

    //A avant
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);

    //B avant
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);

    //Marche avant le joystick va de 128 vers 0
    vitesseA=map(ps2x.Analog(PSS_RY),128,0,0,255);
    vitesseB=map(ps2x.Analog(PSS_RY),128,0,0,255);
  }
  else{ //si on est en marche arrière
    //A arrière
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);

    //B arrière
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);

    //marche arrière le jostick va de 129 vers 255
    vitesseA=map(ps2x.Analog(PSS_RY),129,255,0,255);
    vitesseB=map(ps2x.Analog(PSS_RY),129,255,0,255);
  }

  if(ps2x.Analog(PSS_LX)<=128){ //tourner à gauche càd réduire la vitesse du moteur gauche
    
    vitesseA-=map(ps2x.Analog(PSS_LX),128,0,0,255);
    
    if(vitesseA<0){ //la vitesse doit rester à minimum 0
      vitesseA=0;
    }
  }
  else{ //tourner à droite càd réduire la vitesse du moteur droit
    
    vitesseB-=map(ps2x.Analog(PSS_LX),128,255,0,255);
    
    if(vitesseB<0){ //la vitesse doit rester à minimum 0
      vitesseB=0;
    }
  }
  
  analogWrite(ENA, vitesseA); 
  analogWrite(ENB, vitesseB);

  Serial.print("IN1: ");
  Serial.println(digitalRead(IN1));
  Serial.print("IN2: ");
  Serial.println(digitalRead(IN2));

  Serial.print("IN3: ");
  Serial.println(digitalRead(14));
  Serial.print("IN4: ");
  Serial.println(digitalRead(15));
  
  if(error == 1) //skip loop if no controller found
    return; 
  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed   

    if(ps2x.Button(PSB_PAD_UP)) {      //will be TRUE as long as button is pressed

      angle=90; //on remet le servo à sa position initiale
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){ //augmenter l'angle du servo
      
      angle+=10;
    }
    if(ps2x.Button(PSB_PAD_LEFT)){//baisser l'angle du servo
      
      angle-=10;
    }

    //pour rester avec un angle coimpris entre 0 et 180
    if(angle<0){
      angle=0;
    }
    if(angle>180){
      angle=180;
    }

    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
      
      if(ps2x.Button(PSB_TRIANGLE))
      
        if(light==false){
          digitalWrite(lampe,HIGH);
          light=true;
        }
        else{
          digitalWrite(lampe,LOW);
          light=false;
        }
    }     

    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
    }     
  }
  delay(50);  
}
