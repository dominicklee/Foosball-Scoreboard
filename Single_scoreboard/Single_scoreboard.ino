// Single scoreboard
// Author: Dominick
// Date: 10/13/18

#include <SPI.h>
#include <bitBangedSPI.h>
#include <MAX7219_Dot_Matrix.h>

int scoreA = 0;
int scoreB = 1;
String score = "";
char* cScore = (char*) malloc(sizeof(char)*(score.length() + 1));

MAX7219_Dot_Matrix myDisplay(4, 10);  // 8 chips, and then specify the LOAD pin only

void setup()
{
  Serial.begin(9600);
  myDisplay.begin();
  myDisplay.setIntensity(3);
}  // end of setup

void getScore()
{
  if (scoreA > 9) {
    score = String(scoreA);
  }
  else {
    score = "0" + String(scoreA);
  }
  if (scoreB > 9) {
    score.concat(String(scoreB));
  }
  else {
    score.concat("0" + String(scoreB));
  }
  score.toCharArray(cScore, score.length() + 1);  //turn to cString
}

void showScore()
{
  getScore();
  myDisplay.sendString(cScore);
}

void gameOver()
{
  getScore();
  myDisplay.sendString(cScore);
  Serial.println(score);
  delay(600);
  myDisplay.sendString ("");
  delay(500);
}

void loop ()
{
  if (scoreA == 10 || scoreB == 10) {
    gameOver();
  }
  else {
    scoreA++;
    scoreB++;
    showScore();
    Serial.println(score);
    delay(2000);
  }
}  // end of loop
  
