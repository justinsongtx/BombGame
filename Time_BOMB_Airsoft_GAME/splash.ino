
//爆炸，匪徒胜利
void explodeSplash(){

  //led，lcd归位
  digitalWrite(REDLED, LOW);  
  digitalWrite(GREENLED, LOW); 
  digitalWrite(YELLOWLED, LOW); 
  cls();

  //等100毫秒
  delay(100);
  endGame = false;

  //展示匪徒胜利，按任意键继续
  lcd.setCursor(1,0);
  lcd.print("TERRORISTS WIN");
  lcd.setCursor(4,1);
  lcd.print("Push Any Button To Continue");

  //匪徒赢了，亮红灯，播音乐
  digitalWrite(REDLED, HIGH);  
  for(int i = 200; i>0; i--)// this is the ultra hi definition explosion sound xD
  {
    tone(tonepin,i);
    delay(20);
  }

  //按键之后，停音乐关红灯
  keypad.waitForKey();
  noTone(tonepin);
  digitalWrite(REDLED, LOW); 

  //重新开始
  cls();
  if (relayEnable)
  {
    //禁用重新开始，直接回到主菜单
    menuPrincipal();
  }
  else
  {
    //开启重新开始，重新玩
    lcd.print("Play Again?");
    lcd.setCursor(0,1);
    lcd.print("A : Yes B : No");
    while(1)
    {
      var = keypad.waitForKey();
      if(var == 'a' ){
        tone(tonepin,2400,30);
        //We have two options, search & destroy and sabotaje play again options so!
        if(sdStatus){
          startGameCount();
          search();
        }
        if(saStatus){
          saStatus=true;
          startGameCount();
          start=true; //to set iTime to actual millis() :D
          sabotage();
        }
      }  
      if(var == 'b' ){
        tone(tonepin,2400,30);
        menuPrincipal();
  
        break;
      }  
    } 
  }
  
}

//游戏时间到未爆炸也未拆弹成功，和局
void failSplash()
{
  //led，lcd，种种归位
  digitalWrite(REDLED, LOW);  
  digitalWrite(GREENLED, LOW); 
  digitalWrite(YELLOWLED, LOW); 
  endGame = false;
  cls();

  //展示超时，按任意键继续
  lcd.setCursor(1,0);
  lcd.print(" TIME OUT");
  lcd.setCursor(4,1);
  lcd.print("Push Any Button To Continue");

  //超时，亮黄灯，播音乐
  digitalWrite(YELLOWLED, HIGH);
  for(int i = 200; i>0; i--)// this is the ultra hi definition explosion sound xD
  {
    tone(tonepin,i);
    delay(20);
  }
  
  //按键之后，停音乐关黄灯
  keypad.waitForKey();
  noTone(tonepin);
  digitalWrite(YELLOWLED, LOW); 

  //重新开始
  cls();
  if (relayEnable)
  {
    menuPrincipal();
  }
  else
  {
    lcd.print("Play Again?");
    lcd.setCursor(0,1);
    lcd.print("A : Yes B : No");
    while(1)
    {
      var = keypad.waitForKey();
      if(var == 'a' ){
        tone(tonepin,2400,30);
        //We have two options, search & destroy and sabotaje play again options so!
        if(sdStatus){
          startGameCount();
          search();
        }
        if(saStatus){
          saStatus=true;
          startGameCount();
          start=true; //to set iTime to actual millis() :D
          sabotage();
        }
      }  
      if(var == 'b' ){
        tone(tonepin,2400,30);
        menuPrincipal();
  
        break;
      }  
    }
  }
}
void disarmedSplash()
{
  //led，lcd，种种归位
  endGame = false;
  digitalWrite(REDLED, LOW); 
  digitalWrite(GREENLED, LOW);
  digitalWrite(YELLOWLED, LOW); 
  
  if(sdStatus || saStatus)
  {
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("GOODS WIN");
    lcd.setCursor(3,1);
    lcd.print("Push Any Button To Continue");
    digitalWrite(GREENLED, HIGH);  
    keypad.waitForKey();
    digitalWrite(GREENLED, LOW); 
  }
 
  //重新开始
  cls();
  if (relayEnable)
  {
    //禁用重新开始，直接回到主菜单
    menuPrincipal();
  }
  else
  {
    //开启重新开始，重新玩
    lcd.print("Play Again?");
    lcd.setCursor(0,1);
    lcd.print("A : Yes B : No");
    digitalWrite(REDLED, LOW);  
    digitalWrite(GREENLED, LOW); 
    while(1)
    {
      var = keypad.waitForKey();
      if(var == 'a' ){
        tone(tonepin,2400,30);
        //We have two options, search & destroy and sabotaje play again options so!
        if(sdStatus){
          startGameCount();
          search();
        }
        if(saStatus){
          saStatus=true;
          startGameCount();
          start=true; //to set iTime to actual millis() :D
          sabotage();
        }
      }  
      if(var == 'b' ){
        tone(tonepin,2400,30);
        menuPrincipal();
        break;
      }  
    } 
  }
  
}
