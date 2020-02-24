#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"


SoftwareSerial mySoftwareSerial(A3, A2); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


//***  01 拆装弹文件夹 ***/
int BoomDefFolder = 1;
// 01 拆弹成功
int BoomHasBeenDefuse = 1;
// 02 装弹成功
int BoomHasBeenPlaned = 2;

//***  02 GoGoGo文件夹 ***/
int GoGoGoFolder = 2;

//***  03 欢呼 & 零碎文件夹 ***/
int CheerFolder = 3;

//***  04 胜利结果文件夹 ***/
int ResultFoler = 4;
// 01 反恐精英胜利
int CounterTerroristWin = 1;
// 02 匪徒胜利
int TerroristWin = 2;


void setupMusic()
{
  delay(1000); 
  mySoftwareSerial.begin(9600);
//  pinMode(13, OUTPUT);
//  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
//  delay(10n00); 
//  myDFPlayer.playFolder(1, 2);
//  playSoundRandom(CheerFolder);
//  delay(1000); 
  playSoundRandom(GoGoGoFolder);
  delay(1000); 
//playSound(BoomDefFolder, BoomHasBeenPlaned);
}

void playSound(int folderID, int soundID)
{
  Serial.print(F("playSound, folderID:"));
  Serial.print(folderID);
  Serial.print(F(", soundID:"));
  Serial.println(soundID);
  
  myDFPlayer.playFolder(folderID, soundID);//play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
}

void playSoundRandom(int folderID)
{
  Serial.print(F("playSoundRandom, folderID:"));
  Serial.println(folderID);
  
  int fileCount = myDFPlayer.readFileCountsInFolder(folderID);//read fill counts in folder SD:/03
  int randomID = random(1, fileCount);
  
  playSound(folderID, randomID);
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
