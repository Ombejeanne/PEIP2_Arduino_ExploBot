#include <PS2X_lib.h>  //for v1.6
#include<Servo.h>

#define PS2_DAT        2  // PB5 data brown résistance de 1K soudée  
#define PS2_CMD        3  // PB3 command orange
#define PS2_SEL        4  // PB2 attention yellow
#define PS2_CLK        5  // PB4 clock blue

#define cmdServo 9 //PB1 angles relevés: 0 55 110
Servo servo;
int angle=90; //angle donné en paramètre au servomoteur

#define lampe 6
bool light=false;
  
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; 

int error = 0;
byte type = 0;
byte vibrate = 0;

void setup(){

  //servo
  servo.attach(cmdServo);
  //lampe
  pinMode(lampe,OUTPUT);
  digitalWrite(lampe,LOW);
 
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
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
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


  
  if(error == 1) //skip loop if no controller found
    return; 
  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");      

    if(ps2x.Button(PSB_PAD_UP)) {      //will be TRUE as long as button is pressed
      //Serial.print("Up held this hard: ");
      //Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      angle=90; //on remet le servo à sa position initiale
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){ //augmenter l'angle du servo
      //Serial.print("Right held this hard: ");
      //Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      angle+=10;
    }
    if(ps2x.Button(PSB_PAD_LEFT)){//baisser l'angle du servo
      //Serial.print("LEFT held this hard: ");
      //Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      angle-=10;
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
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
      if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if(ps2x.Button(PSB_TRIANGLE))
        //Serial.println("Triangle pressed");
        if(light==false){
          digitalWrite(lampe,HIGH);
          light=true;
        }
        else{
          digitalWrite(lampe,LOW);
          light=false;
        }
    }

    if(ps2x.ButtonPressed(PSB_CIRCLE))               //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
    if(ps2x.ButtonPressed(PSB_CROSS))               //will be TRUE if button was JUST pressed OR released
      Serial.println("X just pressed");
    if(ps2x.ButtonPressed(PSB_SQUARE))              //will be TRUE if button was JUST released
      Serial.println("Square just pressed");     

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
