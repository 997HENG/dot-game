#include <LiquidCrystal.h>


///*pin set*/// ----------analog pin 0 forbidden

//lcd
const int rs = 2,
          en = 3,
          d4 = 7,
          d5 = 8,
          d6 = 9,
          d7 = 10;

//buttom
const int buttom1 = 11,
          buttom2 = 12,
          buttom3 = 13;
//buzzer
const int buzzer = 4;

////*pin set*////  

////*lcd pattern*////
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);
byte bar[8] =
{
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};
byte heart[8] =
{
  0b00000, 
  0b00000, 
  0b01010, 
  0b11111, 
  0b11111, 
  0b01110, 
  0b00100, 
  0b00000
};
byte circle1[8] =
{
  0b00000,
  0b00000,
  0b00011,
  0b00111,
  0b01111,
  0b01111,
  0b11111,
  0b11111
};
byte circle2[8] =
{
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte circle3[8] =
{
  0b00000,
  0b00000,
  0b11000,
  0b11100,
  0b11110,
  0b11110,
  0b11111,
  0b11111
};
byte circle4[8] =
{
  0b11111,
  0b11111,
  0b01111,
  0b01111,
  0b00111,
  0b00011,
  0b00000,
  0b00000
};
byte circle5[8] =
{
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000
};
byte circle6[8] =
{
  0b11111,
  0b11111,
  0b11110,
  0b11110,
  0b11100,
  0b11000,
  0b00000,
  0b00000
};

byte full[8] =
{
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
/*lcd pattern*/

/////*bool var*/////
bool isReady = false;
bool isLose = false;
bool isWrong = false;
bool timeOut = false;
//////*bool var*/////



///////*question & answer temp*////////
int stage_question[15];                    /////ary={{*5},{*10},{*15}};
int stage_answer[15];
int ary[5];                                
////////*question & answer temp*///////

int lp = 3;

void setup() {

  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(buttom1,INPUT);
  pinMode(buttom2,INPUT);
  pinMode(buttom3,INPUT);
  pinMode(buzzer,OUTPUT);
  randomSeed(analogRead(0));
  

  /*pattern creating*/
  lcd.createChar(0,bar);
  lcd.createChar(1,circle1);
  lcd.createChar(2,circle2);
  lcd.createChar(3,circle3);
  lcd.createChar(4,circle4);
  lcd.createChar(5,circle5);
  lcd.createChar(6,circle6);
  lcd.createChar(7,heart);  
  lcd.createChar(8,full);
  
 



}
void loop(){

  starting();
  if(isReady){
    loading();
  }
 


  
  lcd.clear();
  delay(5000);

}

///////////////////////////////////////////////////////-------------------method------------------//////////////////////////////////////////////////////////////////////////////////
void starting(){

  lcd.clear();
  lp=3;
  isReady = false;
  isLose = false;
  isWrong = false;
  timeOut = false;
  delay(500);
  displayCircle(2);
  displayCircle(7);
  displayCircle(12);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   DOT-GAME!!");
  delay(500);
  lcd.setCursor(0,1);
  lcd.blink();
  delay(200);
  String click = "click any bottom";
  for(int i=0;i<click.length();i++){
    lcd.print(click.charAt(i));
    delay(100);
  }
  lcd.noBlink();
  waiting();
  lcd.clear();
  if(timeOut){
    timeOut = false;
    isReady = false;
    lcd.clear();
    lcd.noBlink();
    return;
  }
  
  String instruction1 ="CLICK THE BOTTOMS" ;
  String instruction2 ="IN THE RIGHT ORDER OF APPEARING OF DOTS";
  lcd.setCursor(0,0);
  lcd.blink();
  for(int i=0;i<instruction1.length();i++){    
    lcd.print(instruction1.charAt(i)); 
    if(i==15)
      lcd.scrollDisplayLeft();
    delay(200);
  }
   
   delay(300);
   lcd.clear();
   lcd.noBlink();
   delay(700);
   lcd.setCursor(0,1);
   lcd.blink();
  for(int i=0;i<instruction2.length();i++){
    lcd.print(instruction2.charAt(i));
    if(i>14)
      lcd.scrollDisplayLeft();
    delay(200);
  }
  delay(1000);
  lcd.clear();
  lcd.noBlink();
  delay(800);
  lcd.setCursor(0,1);
  delay(300);
  lcd.print("got it?");
  lcd.blink();
  tone(buzzer,300,100);
  waiting();
  if(timeOut){
    timeOut = false;
    isReady = false;
    lcd.clear();
    lcd.noBlink();
    return;
  }
  lcd.noBlink();
  
  lcd.clear();
  isReady = true;
  return;
  

}

void loading(){                               // displaying menu and waitting for any click

  isReady = false;
  lcd.setCursor(0,0);
  lcd.blink();
  String load = "loading....";
  for(int i=0;i<load.length();i++){
    lcd.print(load.charAt(i));
    delay(200);
  }
  delay(1000);
  lcd.noBlink();
  lcd.setCursor(0,1);
  delay(500);


  for(int i=0;i<13;i++){                    //loading bar
    lcd.write((byte)8);
    delay( random(300,500) );
  }

  for(int i=0;i<3;i++){
    lcd.write((byte)8);
    delay( random(800,2000) );
  }

  delay(100);
  lcd.clear();                         
  lcd.setCursor(0,0);
  lcd.blink();
  String ready="Ready ?";


  for(int i=0;i<ready.length();i++){
    lcd.print(ready.charAt(i));
    delay(500);
  }
            
  tone(buzzer,300,100);                       
  waiting();
  lcd.noBlink();

  if(timeOut){

    timeOut = false;
    isReady = false;
    lcd.clear();
    lcd.noBlink();
    return;
  }


  delay(1000);
  lcd.clear();                                //waiting for game start
  stage();
  ending();

  return;

}


void stage(){     
   
  delay(1000);
  String hint = "YOU ONLY HAVE THREE CHANCES";
  lcd.setCursor(0, 0);
  lcd.blink();
  for(int i=0;i<hint.length();i++){
    lcd.print(hint.charAt(i));
    if(i>14)
      lcd.scrollDisplayLeft();
    delay(200);
  }
  delay(300);
  lcd.noBlink();
  lcd.clear();
  displayHeart();
  delay(500);
  lcd.clear(); 
  consolePlay();                        
  return;
}

//////////////////////////////////////////////////////lcd display pattern

void displayCircle(int init){                              //displaying circle from init column... 2 for left , 7 for middle , 11 for right

  lcd.setCursor(init,0);                                
  lcd.write(byte(1));
  lcd.write((byte)2);
  lcd.write((byte)3);
  lcd.setCursor(init,1);
  lcd.write((byte)4);
  lcd.write((byte)5);
  lcd.write((byte)6);

   if(init == 2 && isReady){
    tone(buzzer,500,100);
    delay(300);
    lcd.clear();
  }
  else if(init == 7 && isReady){
    tone(buzzer,900,100);
    delay(300);
    lcd.clear();
  }
  else if(init == 12 && isReady){
    tone(buzzer,1200,100);
    delay(300);
    lcd.clear();
  }

  return;
}

void displayHeart(){                                                         //lcd display remaining heart
   lcd.clear();

   if(lp==1){
     Serial.println("gg!");
     isLose=true;
     lp = 3;
     return;
   }

   if(isWrong){
     lp -= 1;
     isWrong = false;
    }
   Serial.print("heart:");
   Serial.println(lp);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("HEARTS:");

   for(int i=0;i<lp;i++){
     lcd.print(" ");
     lcd.write((byte)7);
     delay(500);
   }
   lcd.blink(); 

   tone(buzzer,100,100);
   delay(1000);
   lcd.noBlink();
   
   
   
   lcd.clear();
   delay(500);
  return;
}

void displayQuestion(int stage_question[],int size,int difficulty){                      //lcd display question

  for(int i=0;i<size;i++){
    if(stage_question[i] == 0)
      displayCircle(2);
    else if (stage_question[i] == 1)
      displayCircle(7);
    else if (stage_question[i] == 2)
      displayCircle(12);
    lcd.clear();
    delay(difficulty);
  }

  return;

}

//////////////////////////////////scene

void losing(){                                                       //lcd display losing scene
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.blink();
  String lose = "GAME OVER!!!";
  for(int i =0;i<lose.length();i++){
    lcd.print(lose.charAt(i));
    delay(200);
  }
  tone(buzzer,300,100);
  waiting();
  lcd.noBlink();
  lcd.clear();
  return;
}

void wining(){
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.blink();
  String lose = "YOU WON!!!";
  for(int i =0;i<lose.length();i++){
    lcd.print(lose.charAt(i));
    delay(200);
  }
  tone(buzzer,300,100);
  waiting();
  lcd.noBlink();
  lcd.clear();
  return;
}

void ending(){                                                     //lcd display ending scene
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.blink();
  String lose = "end";
  for(int i =0;i<lose.length();i++){
    lcd.print(lose.charAt(i));
    delay(200);
  }
  tone(buzzer,300,100);
  waiting();
  lcd.noBlink();
  lcd.clear();

  return;
}
///////////////////////////////////////logical method

void setQuestion(int stage_question[],int size,int difficulty){                //making stage_question

  
  Serial.println("settingQuestion");

  for(int i=0;i<size;i++){                                      // 0 for b1, 1 for b2, 2 for b3.
    stage_question[i] = random(0,3);
  }
   
   for(int i=0;i<size;i++){     
    Serial.print("stage_question[");
    Serial.print(i);
    Serial.print("]");      
    Serial.println(stage_question[i]);
  }
  displayQuestion(stage_question,size,difficulty);

  return;
}

void answering(int stage_answer[],int size){                //answering question

  int starTime = millis();
  int duration=0;
  int n=0;
  Serial.println("answering");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.blink();
  tone(buzzer,1000,200);
  delay(800);
  lcd.noBlink();
  lcd.clear();
  while(n<size){

    duration = millis() - starTime;
    delay(50);
    
    if(digitalRead(buttom1)){

      stage_answer[n] = 0;
      Serial.print("stage_answer[");
      Serial.print(n);
      Serial.print("]:");
      Serial.println(stage_answer[n]);
      displayCircle(2);
      n++;
      continue;
    }

    else if(digitalRead(buttom2)){
      
      stage_answer[n] = 1;
      Serial.print("stage_answer[");
      Serial.print(n);
      Serial.print("]:");
      Serial.println(stage_answer[n]);
      displayCircle(7);
      n++;
      continue;
    }

    else if(digitalRead(buttom3)){
      
      stage_answer[n] = 2;
      Serial.print("stage_answer[");
      Serial.print(n);
      Serial.print("]:");
      Serial.println(stage_answer[n]);
      displayCircle(12);
      n++;
      continue;
    }
    if(duration>30000){                          ///30 seconds to answer
      timeOut = true;
      return;
    }
   
  }
  
  
  return;
}

void checking(int stage_question[],int stage_answer[],int size,int difficulty){            //checking result

  for(int i=0;i<size;i++){

      if(stage_question[i]!=stage_answer[i]||timeOut){
  
        isWrong = true ;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.blink();
        String wrong = "WRONG!!";
        for(int i =0;i<wrong.length();i++){
          lcd.print(wrong.charAt(i));
          delay(200);
        }
        tone(buzzer,300,100);
        delay(500);
        lcd.noBlink();
        lcd.clear();
        

        displayHeart();
        Serial.println("wrong answer");
        if( isLose){
          losing();        
          return;
        }
        setQuestion(stage_question,size,difficulty);
        answering(stage_answer,size);
        checking(stage_question,stage_answer,size,difficulty);
      
        return;
      }
    
  }
  Serial.println("right answer");
  lcd.clear();
        lcd.setCursor(0, 0);
        lcd.blink();
        String right = "RIGHT!!";
        for(int i =0;i<right.length();i++){
          lcd.print(right.charAt(i));
          delay(200);
        }
        tone(buzzer,300,100);
        delay(500);
        lcd.noBlink();
        lcd.clear();
  return;
}

///////////////////////////////other method

void consolePlay(){

  Serial.println();
  lp=3;
  isReady = true ;
  isLose = false ;
  isWrong = false;
  timeOut = false;

  for(int j=1;j<=3;j++){
    for(int i=0;i<3;i++){
      Serial.print("stage:");
      Serial.print(j);
      Serial.print("-");
      Serial.println(i+1);
      Serial.println("---------------");
      lcd.setCursor(0, 0);
      lcd.print("stage ");
      lcd.print(j);
      lcd.print("-");
      lcd.print(i+1);
      delay(1000);
      lcd.clear();
      delay(1000);
      setQuestion(stage_question,3+2*j,1500-(i+1)*300);
      answering(stage_answer,3+2*j);
      checking(stage_question,stage_answer,3+2*j,1500-(i+1)*300);
      Serial.println();
      if(isLose){
        return;
      }
      delay(1000);
    }
  }
  if(!isLose){
    wining();
  }
  
  return;

}

void waiting() {
 
 int starTime = millis();
 timeOut = false;
 int duration = 0;
 Serial.println("on waiting");


 while(duration<30000){             //waiting for 30 second
 
   duration = millis() - starTime;
   


   if(digitalRead(buttom1)||digitalRead(buttom2)||digitalRead(buttom3)){
      Serial.println("click");
      tone(buzzer,500,50);
      return;
   }
 }
 timeOut = true;                           
 return;
}
