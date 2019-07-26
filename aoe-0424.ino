#include <RGBmatrixPanel.h>

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

int dirRight = 11;
int dirLeft = 12;
int lt_banzi = 0;
int x_sudu = 1;
int y_sudu = 1;
int x_xiaoqiu = 2;
int y_xiaoqiu = 13;
int width = 4;
int height = 2;
int x_start = 2;
int y_start = 2;
int difficulty_level = 150;
int row_brickMat = 3;
const byte col_brickMat = 7;
const byte row_brickMat_default = 20;
boolean addLayer = true;
boolean goRight = true;
boolean goUp = false;
boolean gameOn = true;
boolean gameWin = false;
boolean welcomePage = true;
boolean addLayerMode = true;
const int anniu = 2;          
int buttonState = 1000;  
int shikuang = 6;
int youshikuang = 6;
boolean levDecided = false;


RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
unsigned long initTime;

int brickMat[row_brickMat_default][col_brickMat];

void setup() {
  pinMode(dirLeft, INPUT);
  pinMode(dirRight, INPUT);
  pinMode(anniu, INPUT);

  Serial.begin(9600);
  matrix.begin();
  resetMatrix();

}

void loop() {
  while(welcomePage){
    huanying();
  }
  initTime = millis();
  while (!levDecided){
    changeDiffLev();
  }
  while (gameOn){
    play();
  }
  jieshu();
}

void play(){

  matrix.drawLine(lt_banzi, 15, lt_banzi+4, 15, matrix.Color333(7, 0, 0));//red
  
  for (int i = 0; i < col_brickMat; i++){
    for (int j = 0; j < row_brickMat; j++){
        if (brickMat[j][i] != 0){
          int x_brick = x_start + i * width;
          int y_brick = y_start + j * height ;
          if (brickMat[j][i] == 1){
            matrix.drawRect(x_brick, y_brick, width, height, matrix.Color333(0, 1, 2));//sky blue
          } else if (brickMat[j][i] == 2){
            matrix.drawRect(x_brick, y_brick, width, height, matrix.Color333(2, 2, 0));//yellow
          } else if (brickMat[j][i] == 3){
            matrix.drawRect(x_brick, y_brick, width, height, matrix.Color333(1, 0, 2));//pink
          }
          
        }
    }
  }

  matrix.drawPixel(x_xiaoqiu, y_xiaoqiu, matrix.Color333(7, 7, 7));//white

  delay(difficulty_level);

    if(digitalRead(dirRight) == LOW){
    //Serial.println("Direction:RIGHT");
    if (lt_banzi < 27){
      lt_banzi +=2;
    }
  }
  else if(digitalRead(dirLeft) == LOW){
    //Serial.println("Direction:LEFT");
    if (lt_banzi > 0){
      lt_banzi -=2;
    }
  }

  if (y_xiaoqiu == 14 || y_xiaoqiu == 15){
    if (x_xiaoqiu <= lt_banzi + 5 && x_xiaoqiu >= lt_banzi - 1){
      goUp = false;
      if (x_xiaoqiu == 31 || x_xiaoqiu == 0){
        goRight = !goRight;
      }
    } else {
      gameOn = false;
    }
  }
  else if (x_xiaoqiu == 31 || x_xiaoqiu == 0){
    int randomNumTimeTravel = random(1,11);
    if (!goUp && randomNumTimeTravel == 7){
      x_xiaoqiu = 31 - x_xiaoqiu;
    } else {
      goRight = !goRight;
    }
    if (y_xiaoqiu == 0){
      goUp = !goUp;
    } else {
      if (!goUp){
        int randomNum = random(0,9);
        if (randomNum % 2== 0){
          goUp = !goUp;
        }
      }
    }
    
  }
  else if (y_xiaoqiu == 0){
    goUp = !goUp;
  }
  
  else {
    reflect();
  }

  if (goRight && goUp){
    x_xiaoqiu += x_sudu;
    y_xiaoqiu += y_sudu;
  } else if (goRight && !goUp){
    x_xiaoqiu += x_sudu;
    y_xiaoqiu -= y_sudu;
  } else if (!goRight && goUp){
    x_xiaoqiu -= x_sudu;
    y_xiaoqiu += y_sudu;
  } else if (!goRight && !goUp){
    x_xiaoqiu -= x_sudu;
    y_xiaoqiu -= y_sudu;
  }
//  changeBrickState();

  gameWin = true;
  for (int i = 0; i < row_brickMat; i++){
    for (int j = 0; j < col_brickMat; j++){
      if (brickMat[i][j] < 0){
        brickMat[i][j] = 0;
      }
      if (brickMat[i][j] != 0){
        gameWin = false;
      }
    }
  }

  if (gameWin){
    gameOn = false;
  }

  if (addLayerMode && addLayer){
    unsigned long curTime = millis();
    if ((curTime - initTime) >= 40000 && (curTime - initTime) % 40000 > 0 && (curTime - initTime) % 40000 < 500 && addLayer){
      //Serial.println(curTime - initTime);
      addNewLayer();
      addLayer = false;
      printArray();
    } else if ((curTime - initTime) >= 40000 && (curTime - initTime) % 40000 >= 50){
      addLayer = true;
    }
  }
  

  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

void addNewLayer(){
  
  for (int i = row_brickMat++; i > 0; i--){
    for (int j = 0; j < col_brickMat; j++){
      brickMat[i][j] = brickMat[i-1][j];
    }
  }

  for (int i = 0; i < col_brickMat; i++){
    brickMat[0][i] = random(1,4);
  }

  if (y_start + row_brickMat * height > 14){
    for (int i = row_brickMat - 1; i >= (14 - y_start) / height; i--){
      for (int j = 0; j < col_brickMat; j++){
        if (brickMat[i][j] != 0){
          gameOn = false;
          break;
        }
      }
    }
  }
}

void reflect(){

  if (!goUp && goRight){
    if (x_xiaoqiu >= x_start - 1 && x_xiaoqiu <= x_start + col_brickMat * width - 1){
      int col_ball = (x_xiaoqiu - x_start + 1) / width;
      if (col_ball == 7){
        col_ball--;
      }
      for (int i = 0; i < row_brickMat; i++){
        int brick_bottom = y_start + 1 + i * height;
        int brick_left = x_start + col_ball * width;
        if (brickMat[i][col_ball] > 0){

          if ((y_xiaoqiu == brick_bottom + 1 && x_xiaoqiu != brick_left - 1)|| (y_xiaoqiu == brick_bottom && x_xiaoqiu == brick_left)){
            brickMat[i][col_ball] -- ;
            printArray();
            goUp = !goUp;
          } else if (x_xiaoqiu == brick_left - 1 && (y_xiaoqiu == brick_bottom || y_xiaoqiu == brick_bottom - 1)){
            brickMat[i][col_ball] -- ;
            printArray();
            goRight = !goRight;
          } else if (y_xiaoqiu <= brick_bottom && y_xiaoqiu >= brick_bottom - height + 1 && x_xiaoqiu >= brick_left && x_xiaoqiu <= brick_left + width - 1){
            brickMat[i][col_ball] -- ;
            printArray();
            goRight = !goRight;
          }
          
        }
      }
    }
  }
  else if (!goUp && !goRight){
    if (x_xiaoqiu >= x_start + 1 && x_xiaoqiu <= x_start + col_brickMat * width + 1){
      int col_ball = (x_xiaoqiu - x_start - 1) / width;
      for (int i = 0; i < row_brickMat; i++){
        int brick_bottom = y_start + 1 + i * height;
        int brick_right = (x_start + width - 1) + col_ball * width;
        if (brickMat[i][col_ball] > 0){

          if ((y_xiaoqiu == brick_bottom + 1 && x_xiaoqiu != brick_right + 1) || (y_xiaoqiu == brick_bottom && x_xiaoqiu == brick_right)){
            brickMat[i][col_ball] -- ;
            goUp = !goUp;
          } else if (x_xiaoqiu == brick_right + 1 && (y_xiaoqiu == brick_bottom || y_xiaoqiu == brick_bottom - 1)){
            brickMat[i][col_ball] -- ;
            goRight = !goRight;
          } else if (y_xiaoqiu <= brick_bottom && y_xiaoqiu >= brick_bottom - height + 1 && x_xiaoqiu <= brick_right && x_xiaoqiu >= brick_right - width + 1){
            brickMat[i][col_ball] -- ;
            goRight = !goRight;
          }
        }
      }
    }
  }
  else if (goUp && goRight) {
    if (x_xiaoqiu >= x_start - 1 && x_xiaoqiu <= x_start + col_brickMat * width - 1){
      int col_ball = (x_xiaoqiu - x_start + 1) / width;
      for (int i = 0; i < row_brickMat; i++){
        int brick_top = y_start + i * height;
        int brick_left = x_start + col_ball * width;

        if (brickMat[i][col_ball] > 0){

          if ((y_xiaoqiu == brick_top - 1 && x_xiaoqiu != brick_left - 1) || (y_xiaoqiu == brick_top && x_xiaoqiu == brick_left)){
            brickMat[i][col_ball] -- ;
            goUp = !goUp;
          } else if (x_xiaoqiu == brick_left - 1 && (y_xiaoqiu == brick_top || y_xiaoqiu == brick_top + 1)){
            brickMat[i][col_ball] -- ;
            goRight = !goRight;
          } else if (y_xiaoqiu >= brick_top && y_xiaoqiu <= brick_top + height - 1 && x_xiaoqiu >= brick_left && x_xiaoqiu <= brick_left + width - 1){
            brickMat[i][col_ball] -- ;
            goRight = !goRight;
          }
          
        }
        
      }
    }
  }
  else if (goUp && !goRight){
    if (x_xiaoqiu >= x_start + 1 && x_xiaoqiu <= x_start + col_brickMat * width + 1){
      int col_ball = (x_xiaoqiu - x_start - 1) / width;
      for (int i = 0; i < row_brickMat; i++){
        int brick_top = y_start + i * height;
        int brick_right = x_start + width - 1 + col_ball * width;

        if (brickMat[i][col_ball] > 0){

          if ((y_xiaoqiu == brick_top - 1 && x_xiaoqiu != brick_right + 1) || (y_xiaoqiu == brick_top && x_xiaoqiu == brick_right)){
            brickMat[i][col_ball] -- ;
            goUp = !goUp;
          } else if (x_xiaoqiu == brick_right + 1 && (y_xiaoqiu == brick_top || y_xiaoqiu == brick_top + 1)){
            brickMat[i][col_ball] -- ;
            goRight = !goRight;
          } else if (y_xiaoqiu >= brick_top && y_xiaoqiu <= brick_top + height - 1 && x_xiaoqiu <= brick_right && x_xiaoqiu >= brick_right - width + 1){
            brickMat[i][col_ball] -- ;
            goRight = !goRight;
          }
          
        }
        
      }
    }
  }
}
void jieshu(){
  int x_sudu = 0;
  int y_sudu = 0;

  if (gameWin){
    matrix.setCursor(0,0);
    matrix.setTextColor(matrix.Color333(2,0,0));
    matrix.print('C');
    matrix.setTextColor(matrix.Color333(2,1,0));
    matrix.print('O');
    matrix.setTextColor(matrix.Color333(2,2,0));
    matrix.print('N');
    matrix.setTextColor(matrix.Color333(1,2,0));
    matrix.print('G');
    matrix.setTextColor(matrix.Color333(0,2,0));
    matrix.print('R');
  
    matrix.setCursor(1, 9);  // next line
    matrix.setTextColor(matrix.Color333(0,2,2));
    matrix.print('A');
    matrix.setTextColor(matrix.Color333(0,1,2));
    matrix.print('T');
    matrix.setTextColor(matrix.Color333(0,0,7));
    matrix.print('S');
    matrix.setTextColor(matrix.Color333(1,0,2));
    matrix.print('!');
    matrix.setTextColor(matrix.Color333(2,0,1));
    matrix.print(' ');
    gameOn=false;
    delay(2000);
    
  } else {
    matrix.setCursor(0,0);
    matrix.setTextColor(matrix.Color333(2,0,0));
    matrix.print('G');
    matrix.setTextColor(matrix.Color333(2,1,0));
    matrix.print('A');
    matrix.setTextColor(matrix.Color333(2,2,0));
    matrix.print('M');
    matrix.setTextColor(matrix.Color333(1,2,0));
    matrix.print('E');
    matrix.setTextColor(matrix.Color333(0,2,0));
    matrix.print(' ');
  
    matrix.setCursor(1, 9);  // next line
    matrix.setTextColor(matrix.Color333(0,2,2));
    matrix.print('O');
    matrix.setTextColor(matrix.Color333(0,1,2));
    matrix.print('V');
    matrix.setTextColor(matrix.Color333(0,0,7));
    matrix.print('E');
    matrix.setTextColor(matrix.Color333(1,0,2));
    matrix.print('R');
    matrix.setTextColor(matrix.Color333(2,0,1));
    matrix.print('!');
    gameOn=false;
    delay(2000);
  }
  Serial.print("welcomePage:");
  Serial.println(welcomePage);
  Serial.print("gameOn:");
  Serial.println(gameOn);  
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  while(!gameOn && !welcomePage){
    matrix.setCursor(0, 0);  // next line
    matrix.setTextColor(matrix.Color333(0,2,2));
    matrix.print('A');
    matrix.setTextColor(matrix.Color333(0,1,2));
    matrix.print('G');
    matrix.setTextColor(matrix.Color333(0,0,7));
    matrix.print('A');
    matrix.setTextColor(matrix.Color333(1,0,2));
    matrix.print('I');
    matrix.setTextColor(matrix.Color333(2,0,1));
    matrix.print('N');

    matrix.setCursor(7, 9);  // next line
    matrix.setTextColor(matrix.Color333(2,0,1));
    matrix.print('Y');
    matrix.setTextColor(matrix.Color333(2,0,1));
    matrix.print('/');
    matrix.setTextColor(matrix.Color333(2,0,1));
    matrix.print('N');

    matrix.drawRect(shikuang, 8, 7, 8, matrix.Color333(7, 7, 0));
    //matrix.drawRect(18, 8, 7, 8, matrix.Color333(7, 7, 0));

    if(digitalRead(dirRight) == LOW){
      //Serial.println("Direction:RIGHT");
      if (shikuang < 18){
        shikuang +=3 ;
      }
    }
    else if(digitalRead(dirLeft) == LOW){
    //Serial.println("Direction:LEFT");
      if (shikuang > 6){
        shikuang -= 3;
      }
    }
    buttonState = analogRead(A3);
    if (buttonState < 100) {
      if (shikuang == 6){ //Y
        gameOn=true;
        welcomePage=false;
        buttonState=1000;
        restartGame();
        //shikuang = 6;
      } else if (shikuang == 18){ //N
        welcomePage=true;
        gameOn=false;
        shikuang = 6;
        buttonState=1000;
        restartGame();
      }   
    }   
    delay(100);
    matrix.fillScreen(matrix.Color333(0, 0, 0)); 
  }
}

void resetMatrix(){
  for (int i = 0; i < row_brickMat; i++){
    for (int j = 0; j < col_brickMat; j++){
      brickMat[i][j] = random(1, 4);
    }
  }
}

void restartGame(){
  row_brickMat = 3;
  resetMatrix();
  x_xiaoqiu = 2;
  y_xiaoqiu = 13;
  lt_banzi = 0;
  gameWin = false;
  gameOn = true;
  addLayer = true;
  levDecided = false;
}

void printArray(){
  for (int i = 0; i < row_brickMat; i++){
    for (int j = 0; j < col_brickMat; j++){
      Serial.print(brickMat[i][j]);
      Serial.print(", ");
    } 
    Serial.println("");
  }
  Serial.println("-----------------------------");
}


void huanying(){
//w
  matrix.drawLine(0,3,0,6,matrix.Color333(3,3,3));
  matrix.drawLine(2,5,2,6,matrix.Color333(3,3,3));
  matrix.drawLine(4,3,4,6,matrix.Color333(3,3,3));
  matrix.drawPixel(1, 7, matrix.Color333(3,3,3));
  matrix.drawPixel(3, 7, matrix.Color333(3,3,3));
//e
  matrix.drawLine(6,3,8,3,matrix.Color333(3,3,3));
  matrix.drawLine(6,4,6,7,matrix.Color333(3,3,3));
  matrix.drawPixel(7, 5, matrix.Color333(3,3,3));
  matrix.drawLine(7,7,8,7,matrix.Color333(3,3,3));
//l
  matrix.drawLine(10,3,10,7,matrix.Color333(3,3,3));
  matrix.drawLine(10,3,10,7,matrix.Color333(3,3,3));
  matrix.drawLine(11,7,12,7,matrix.Color333(3,3,3));
//c
  matrix.drawLine(14,3,16,3,matrix.Color333(3,3,3));
  matrix.drawLine(14,4,14,7,matrix.Color333(3,3,3));
  matrix.drawLine(15,7,16,7,matrix.Color333(3,3,3));
//o
  matrix.drawLine(18,3,20,3,matrix.Color333(3,3,3));
  matrix.drawLine(18,4,18,7,matrix.Color333(3,3,3));
  matrix.drawLine(20,4,20,7,matrix.Color333(3,3,3));
  matrix.drawPixel(19, 7, matrix.Color333(3,3,3));
//m
  matrix.drawLine(22,3,22,7,matrix.Color333(3,3,3));
  matrix.drawLine(26,3,26,7,matrix.Color333(3,3,3));
  matrix.drawPixel(23, 4, matrix.Color333(3,3,3));
  matrix.drawPixel(24, 5, matrix.Color333(3,3,3));
  matrix.drawPixel(25, 4, matrix.Color333(3,3,3));
//e
  matrix.drawLine(28,3,30,3,matrix.Color333(3,3,3));
  matrix.drawLine(28,4,28,7,matrix.Color333(3,3,3));
  matrix.drawPixel(29, 5, matrix.Color333(3,3,3));
  matrix.drawLine(29,7,30,7,matrix.Color333(3,3,3));

//to
  matrix.drawLine(12,9,14,9,matrix.Color333(5,5,5));
  matrix.drawLine(13,10,13,13,matrix.Color333(5,5,5));
  matrix.drawLine(16,9,18,9,matrix.Color333(5,5,5));
  matrix.drawLine(16,10,16,13,matrix.Color333(5,5,5));
  matrix.drawLine(18,10,18,13,matrix.Color333(5,5,5));
  matrix.drawPixel(17, 13, matrix.Color333(5,5,5));


  matrix.drawLine(24,9,24,10,matrix.Color333(1,1,0));
  matrix.drawLine(26,9,26,10,matrix.Color333(1,1,0));
  matrix.drawLine(24,14,26,14,matrix.Color333(1,1,0));
  matrix.drawPixel(22, 12, matrix.Color333(1,1,0));  
  matrix.drawPixel(23, 13, matrix.Color333(1,1,0));
  matrix.drawPixel(27, 13, matrix.Color333(1,1,0));  
  matrix.drawPixel(28, 12, matrix.Color333(1,1,0));


  matrix.drawLine(3,9,4,9,matrix.Color333(1,0,0));
  matrix.drawLine(6,9,7,9,matrix.Color333(1,0,0));
  matrix.drawLine(2,10,8,10,matrix.Color333(1,0,0));
  matrix.drawLine(2,11,8,11,matrix.Color333(1,0,0));
  matrix.drawLine(3,12,7,12,matrix.Color333(1,0,0));
  matrix.drawLine(4,13,6,13,matrix.Color333(1,0,0));
  matrix.drawPixel(5, 14, matrix.Color333(1,0,0));

  delay(1900);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(100);
  
  matrix.setCursor(0,0);
  matrix.setTextColor(matrix.Color333(2,0,0));
  matrix.print('B');
  matrix.setTextColor(matrix.Color333(2,1,0));
  matrix.print('R');
  matrix.setTextColor(matrix.Color333(2,2,0));
  matrix.print('E');
  matrix.setTextColor(matrix.Color333(1,2,0));
  matrix.print('A');
  matrix.setTextColor(matrix.Color333(0,2,0));
  matrix.print('K');

  matrix.setCursor(7,9);
  matrix.setTextColor(matrix.Color333(2,2,0));
  matrix.print('O');
  matrix.setTextColor(matrix.Color333(1,2,0));
  matrix.print('U');
  matrix.setTextColor(matrix.Color333(0,2,0));
  matrix.print('T');
  matrix.setTextColor(matrix.Color333(0,2,0));
  matrix.print('!');


  for (int i = 0; i < 3000; i++){
    buttonState = analogRead(A3);
    if(buttonState<100){
      welcomePage = false;
      buttonState=1000;
      break;
      //matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    delay(1);
  }
  
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}


void changeDiffLev(){
// change difficulty level
  delay(300);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  while(!levDecided){ 
    matrix.setCursor(0, 0);  // next line
    matrix.setTextColor(matrix.Color333(0,2,2));
    matrix.print('M');
    matrix.setTextColor(matrix.Color333(0,1,2));
    matrix.print('O');
    matrix.setTextColor(matrix.Color333(0,0,7));
    matrix.print('D');
    matrix.setTextColor(matrix.Color333(1,0,2));
    matrix.print('E');
    matrix.setTextColor(matrix.Color333(2,0,1));
    matrix.print('?');

    matrix.setCursor(7, 9);  // next line
    matrix.setTextColor(matrix.Color333(2,0,1));
    matrix.print('E');// write easy
    matrix.setTextColor(matrix.Color333(2,0,1));
    matrix.print('M');
    matrix.setTextColor(matrix.Color333(2,0,1));
    matrix.print('H');// write hard

    matrix.drawRect(youshikuang, 8, 7, 8, matrix.Color333(5, 5, 5));
    //matrix.drawRect(18, 8, 7, 8, matrix.Color333(7, 7, 0));

    if(digitalRead(dirRight) == LOW){
      //Serial.println("Direction:RIGHT");
      if (youshikuang < 18){
        youshikuang +=3 ;
      }
    }
    else if(digitalRead(dirLeft) == LOW){
    //Serial.println("Direction:LEFT");
      if (youshikuang > 6){
        youshikuang -= 3;
      }
    }
    
    buttonState = analogRead(A3);
    if (buttonState < 100) {
      if (youshikuang == 6){ // Easy
        addLayerMode = false;
        levDecided = true;
        buttonState = 1000;
      } else if (youshikuang == 18){ //Hard
        addLayerMode = true;
        levDecided = true;
        buttonState = 1000;
        youshikuang = 6;
      }   
    }   
    delay(100);
    matrix.fillScreen(matrix.Color333(0, 0, 0)); 
  }
}
