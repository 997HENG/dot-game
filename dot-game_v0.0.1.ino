#include<LiquidCrystal.h>

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

////*pin set*////  

////*lcd pattern*////
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);
byte full[8] =
{
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111
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
  0b00000,
  0b00011,
  0b00111,
  0b01111,
  0b01111,
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
  randomSeed(analogRead(0));
  

  /*pattern creating*/
  lcd.createChar(0,full);
  lcd.createChar(1,circle1);
  lcd.createChar(2,circle2);
  lcd.createChar(3,circle3);
  lcd.createChar(4,circle4);
  lcd.createChar(5,circle5);
  lcd.createChar(6,circle6);
  lcd.createChar(7,heart);  


}

void loop() {

  consolePlay();
  
  
}

///////////////////////////////////////////////////////-------------------method------------------//////////////////////////////////////////////////////////////////////////////////

void menu(){                               // displaying menu and waitting for any click

  lcd.setCursor(0,0);
  lcd.print("loading....");
  lcd.blink();
  delay(1000);
  lcd.setCursor(0,1);
  delay(500);
  lcd.noBlink();

  for(int i=0;i<13;i++){                    //loading bar
    lcd.write(byte(0));
    delay( random(300,500) );
  }

  for(int i=0;i<3;i++){
    lcd.write(byte(0));
    delay( random(500,1000) );
  }

  delay(100);
  lcd.clear();                         
  lcd.setCursor(0,0);
  lcd.blink();
  String ready="Ready ?";

  for(int i=0;i<ready.length();i++){
    lcd.print(ready.charAt(i));
    delay(400);
  }               
                            
  waiting();

  if(timeOut){

    timeOut = false;
    showPussy();
    return;
  }

  lcd.noBlink();
  delay(1000);
  lcd.clear();                                //waiting for game start

  return;

}


void stage(){                               

}

//////////////////////////////////////////////////////lcd display pattern

void showCircle(int init){                              //displaying circle from init column

  lcd.setCursor(init,0);
  lcd.write(byte(1));
  lcd.write((byte)2);
  lcd.write((byte)3);
  lcd.setCursor(init,1);
  lcd.write((byte)4);
  lcd.write((byte)5);
  lcd.write((byte)6);

  return;
}

void displayQuestion(){                                                   //lcd display question

  return;
}

void displayHeart(){                                                         //lcd display remaining heart
  lp = lp-1;                                                                // 3 condition 2,1,0 

  if(lp==0){
    Serial.println("gg!");
    lp=3;
    isLose=true;
    return;
  }

  Serial.print("heart:");
  Serial.println(lp);
  
  return;
}

void showPussy(){                                                       //lcd display pussy

  return;
}

void losing(){                                                       //lcd display losing scene
  
  Serial.println("GAME OVER!!");
  return;
}

void ending(){                                                     //lcd display ending scene

  return;
}

///////////////////////////////////////logical method

void setQuestion(int stage_question[],int size){                //making stage_question
  
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
  displayQuestion();

  return;
}

void answering(int stage_answer[],int size){                //answering question

  int starTime = millis();
  int duration;
  int n=0;
  Serial.println("answering");
  while(n<size){

    duration = millis() - starTime;
    delay(250);
    
    if(digitalRead(buttom1)){

      stage_answer[n] = 0;
      Serial.print("stage_answer[");
      Serial.print(n);
      Serial.print("]:");
      Serial.println(stage_answer[n]);
      n++;
      continue;
    }

    else if(digitalRead(buttom2)){
      
      stage_answer[n] = 1;
      Serial.print("stage_answer[");
      Serial.print(n);
      Serial.print("]:");
      Serial.println(stage_answer[n]);
      n++;
      continue;
    }

    else if(digitalRead(buttom3)){
      
      stage_answer[n] = 2;
      Serial.print("stage_answer[");
      Serial.print(n);
      Serial.print("]:");
      Serial.println(stage_answer[n]);
      n++;
      continue;
    }
    if(duration>30000){                          ///30 seconds to answer
      lp -= 1;
      displayHeart();
      return;
    }
  }
  
  
  return;
}

void checking(int stage_question[],int stage_answer[],int size){            //checking result

  for(int i=0;i<size;i++){

    if(stage_question[i]!=stage_answer[i]){
      displayHeart();

      if( isLose){
        losing();
        return;
      }

      Serial.println("wrong answer");
      setQuestion(stage_question,size);
      answering(stage_answer,size);
      checking(stage_question,stage_answer,size);
      return;
    }
    
  }
  Serial.println("right answer");
  return;
}

///////////////////////////////other method

void consolePlay(){

  Serial.println();
  delay(2000);

  for(int j=1;j<=3;j++){
    for(int i=0;i<j*5;i++){
      Serial.print("stage:");
      Serial.print(j);
      Serial.print("-");
      Serial.println(i+1);
      Serial.println("---------------");
      setQuestion(stage_question,j*5);
      answering(stage_answer,j*5);
      checking(stage_question,stage_answer,j*5);
      Serial.println();
      if(isLose){
        return;
      }
      delay(5000);
    }
  }
  

}

void waiting(){
 
 int starTime = millis();
 timeOut = false;
 int duration;

 while(duration<30000){             //waiting for 30 second
 
   duration = millis() - starTime;
   Serial.println(duration);

   if(digitalRead(buttom1)||digitalRead(buttom2)||digitalRead(buttom3)){
      Serial.println("click");
      return;
   }
 }
 timeOut = true;                           
 return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////test

void randomTest(){

  int n=100;
  int cnt1=0;
  int cnt2=0;
  int cnt3=0;
  int arry[3];

  while(n-->0){
    arry[random(0,3)]+=1;
    Serial.print("arry[0]:");
    Serial.println(arry[0]);
    Serial.print("arry[1]:");
    Serial.println(arry[1]);
    Serial.print("arry[2]:");
    Serial.println(arry[2]);
    Serial.print(100-n);
    Serial.println(" times");
    Serial.println();
    delay(500);
 } 

 return;
}

void aryTest(int ary[],int length){

  for(int i=0;i<length;i++){
    ary[i]=random(0,50);
  }
  for(int i=0;i<length;i++){
    Serial.println(ary[i]);
    delay(1000);
  }

  delay(3000);

  return;
}

void buttomTest(){

  if(digitalRead(buttom1))
    Serial.println("buttom1");
  if(digitalRead(buttom2))
    Serial.println("buttom2");
  if(digitalRead(buttom3))
    Serial.println("buttom3");
  
  return;
}