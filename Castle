#include <SPI.h>
#include <EEPROM.h>
#include <Gamebuino.h>
Gamebuino gb;

// image declaration
//extern const byte PROGMEM logo[];
extern const byte PROGMEM select[];
extern const byte PROGMEM point[];
extern const byte PROGMEM Rifle[];
extern const byte PROGMEM Shotgun[];
extern const byte PROGMEM SniperRifle[];
extern const byte PROGMEM shot[];
extern const byte PROGMEM fence[][18];
extern const byte PROGMEM monster[][20];
extern const byte PROGMEM king[][40];
extern const byte PROGMEM king_skil[][40];
extern const byte PROGMEM castle[];
extern const byte PROGMEM HP_bar[];
extern const byte PROGMEM rifle_img[];
extern const byte PROGMEM shotgun_img[];
extern const byte PROGMEM sniper_img[];
extern const byte PROGMEM motion_slow[];
extern const byte PROGMEM motion_stun[][38];
extern const byte PROGMEM shop[];

extern const byte font5x7[];
extern const byte font3x5[];

// system info
int world_y;
int camera_y;
byte shake_x, shake_y;
boolean shake_state;
byte shake_timeLeft;
byte shake_magnitude;
boolean readyGo;
byte ready_Cnt;
byte screen;

boolean weapon_select;
byte main_sub;
byte weapon_point;
boolean weapon_change;

int LevelUp_x;
byte Level;
boolean leveling;

boolean Shop_State;
byte scroll;

byte slowmotion_time[5] = {0};
byte stunmotion_time[5] = {0};

#define RANKMAX 5 //number of high scores to save
#define NAME_LENGTH 10
int Highscores[RANKMAX];
char name[RANKMAX][NAME_LENGTH+1];

// Me info
int player_x, player_y;
byte weapon=0;              // weapon select after
byte mainweapon, subweapon;
int Me_HP;
byte slowUP;
byte stunUP;
int kill;
int coin;
byte reloading_delay;     // reload speed
boolean reloading;     // true = shot, false = not attck, weaponchange
typedef struct gun{
  byte power;                 // damage
  byte shot_delay_time;       // rifle = 0 , shotgun = 21 , sniper = 35
  byte Ammo;
  byte Ammo_MAX;              // Upgrade
  boolean shot_state;         // true = shot, false = reload
  boolean shot_delay;         // true = shot, false = delay , rifle = reload delay
  boolean reload_show;
} Gun;

Gun Guns[3];

// Monster info
byte mon_Ramdom_MAX;
byte mon_HPup;
byte mon_SpeedUp;
byte mon_max;                // max = 5
byte mon_make;               // map random make
byte default_Speed;
boolean Boss;
boolean Bossing;
boolean BossDie;
byte Boss_message;
byte monster_drop;
boolean droping;
int King_default_HP;
int Monster_default_HP;
typedef struct monster{
  int mon_x;
  int mon_y;
  int mon_HP;               // base 10
  byte mon_Speed;            // base 3, 1 =slow, 0 = stun
  byte monMovement;          // speed save value
  byte mon_SpeedMAX;         // (Speed++ > SpeedMAX) mon_y--
  byte slow_time;
  byte stun_time;
  boolean monMove;           // true = left, false = right
  boolean monState;          // true = life, false = die
  boolean slow_state;        // shotgun special ability
  boolean stun_state;        // sniper special ability
} Monster;

Monster Mon[5] = { {0},{0},{0} };

void setup(){
  gb.begin();                
  gb.battery.show = false;
  gb.titleScreen(F("Castle Defence!"));
  load_Highscore();
  initGame();
}

void loop(){
  if(gb.update()){
    
    while(weapon_select){
      if(gb.update()){
        gb.display.drawBitmap(15, 0, select);
        if(weapon_point == 0) gb.display.drawBitmap(18, 27, point);
        else if(weapon_point == 1) gb.display.drawBitmap(36, 27, point);
        else if(weapon_point == 2) gb.display.drawBitmap(57, 27, point);
        
        if(main_sub == 1) if(mainweapon == 0) gb.display.drawBitmap(76, 37, rifle_img); else if(mainweapon == 1) gb.display.drawBitmap(76, 37, shotgun_img); else if(mainweapon == 2) gb.display.drawBitmap(76, 37, sniper_img);
        if(main_sub == 2) {
          if(mainweapon == 0) gb.display.drawBitmap(76, 37, rifle_img); else if(mainweapon == 1) gb.display.drawBitmap(76, 37, shotgun_img); else if(mainweapon == 2) gb.display.drawBitmap(76, 37, sniper_img);
          if(subweapon == 0) gb.display.drawBitmap(76, 31, rifle_img); else if(subweapon == 1) gb.display.drawBitmap(76, 31, shotgun_img); else if(subweapon == 2) gb.display.drawBitmap(76, 31, sniper_img);
        }
        if(gb.buttons.pressed(BTN_UP)){
          display_highScore();
        }
        if(gb.buttons.repeat(BTN_LEFT,5)){
          if(weapon_point != 0) { gb.sound.playTick(); weapon_point--; }
        }
        if(gb.buttons.repeat(BTN_RIGHT,5)){
          if(weapon_point != 2) { gb.sound.playTick(); weapon_point++; }
        }
        if(gb.buttons.pressed(BTN_A)){ 
          if(!main_sub) { gb.sound.playOK(); mainweapon = weapon_point; main_sub++;}
          else if(main_sub == 1 && (mainweapon != weapon_point)){ gb.sound.playOK(); subweapon = weapon_point; main_sub++; }
          else if(main_sub == 2){ gb.sound.playOK(); weapon_select = false; weapon = mainweapon; break; } 
        }
        if(gb.buttons.pressed(BTN_B)){
          if(main_sub != 0) { gb.sound.playCancel(); main_sub--; }
        }
        if(gb.buttons.pressed(BTN_C)) {gb.titleScreen(F("Castle Defence!")); initGame();}
      }
    }
    
    while(!readyGo){
      if(gb.update()){
        displayBackgrond();
        displayHP();
        display_Ammo();
        gb.display.cursorX = 26;
        gb.display.cursorY = 11;
        if((!(ready_Cnt % 10 == 0)) && ready_Cnt <= 49) gb.display.println("Ready..?");
        else if(ready_Cnt >= 50) { gb.display.setFont(font5x7); gb.display.cursorX = 26 + random(0,2); gb.display.cursorY = 11 + random(0,2); gb.display.println(" GO!! "); gb.display.setFont(font3x5); }
        if(ready_Cnt >= 80) { readyGo = true; ready_Cnt = 0; break; }
        ready_Cnt++;
      }
    }
    
    if(shake_state) shakeScreen();
    else if(!Shop_State) displayBackgrond();
    if(!Shop_State) displayMonster();
    displayHP();
    display_shot_bar();
    display_Ammo();
    Level_Up();
    monsterDrop();
    display_Shop();
    if(Boss) all_kill();

    if(kill == (Level * 15)){ 
      leveling = true; 
      Level++;
      if(Level%5 == 0) Bossing = true;
      if(Level%3 == 0){
        mon_SpeedUp ++; 
        default_Speed++; 
        if(!mon_Ramdom_MAX <= 40) mon_Ramdom_MAX -= 10;
      }
      if(Level%2 == 0){
        mon_HPup += 2; 
        King_default_HP = mon_HPup*30;
        Monster_default_HP = mon_HPup+10;
      }
    }
    
    // display me
    switch(weapon){
      case 0 : gb.display.drawBitmap(player_x,    player_y,    Rifle);break;
      case 1 : gb.display.drawBitmap(player_x,    player_y,    Shotgun);break;
      case 2 : gb.display.drawBitmap(player_x-16, player_y-16, SniperRifle);break;
    }
    // move
    if(gb.buttons.repeat(BTN_UP,1)){
      if(player_y > -4){
        if(weapon == 0) player_y --;
        player_y --;
      } else {
        player_y = -4;
        if(world_y > LCDHEIGHT){
          if(weapon == 0) {world_y -= 2; camera_y += 2;} 
          else {world_y--; camera_y++;}
        }else {camera_y = 0; world_y = 48;}
      }
    }
    if(gb.buttons.repeat(BTN_DOWN,1)){
      if(player_y < LCDHEIGHT-5){
        if(weapon == 0) player_y ++;
        player_y ++;
      } else {
        player_y = LCDHEIGHT-5;
        if(world_y < (LCDHEIGHT*2)){
          if(weapon == 0){world_y += 2; camera_y -=2;}
          else {world_y++; camera_y--;}
        }else {camera_y = -48; world_y = 96;}
      }
    }
    if(gb.buttons.repeat(BTN_LEFT,1)){
      if(player_x > 5){
        if(weapon == 0) player_x --;
        player_x --;
      } else player_x = 5;
    }
    if(gb.buttons.repeat(BTN_RIGHT,1)){
      if(player_x < LCDWIDTH-14){
        if(weapon == 0) player_x ++;
        player_x ++;
      } else player_x = LCDWIDTH-14;
    }
    // attack
    if(!Shop_State){
      if(weapon == 0){
        if(gb.buttons.repeat(BTN_A,4)){ 
          Guns[0].shot_delay = false;      // rifle.shot_delay = reload delay
          Attack(); 
        }else if(gb.buttons.released(BTN_A)) Guns[0].shot_delay = true;
      }else if(gb.buttons.pressed(BTN_A)) Attack();
    }
    // reload
    if(gb.buttons.pressed(BTN_B)){
      if(!Shop_State){
        switch(weapon){
          case 0 : if(Guns[weapon].Ammo <= ((Guns[weapon].Ammo_MAX/2) + 10) && Guns[weapon].shot_delay){
                     reloading = false;
                     Guns[weapon].shot_state = false;
                   }break;
          case 1 : if(Guns[weapon].Ammo <= ((Guns[weapon].Ammo_MAX/2) + 5) && Guns[weapon].shot_delay){
                     reloading = false;
                     Guns[weapon].shot_state = false;
                   }break;
          case 2 : if(Guns[weapon].Ammo <= ((Guns[weapon].Ammo_MAX/2) + 2) && Guns[weapon].shot_delay){
                     reloading = false;
                     Guns[weapon].shot_state = false;
                   }break;
        }
      }
    }
    // weapon change
    if(gb.buttons.pressed(BTN_C)){
      if(!Shop_State){
        if(reloading){
          gb.sound.playTick();
          if(!weapon_change) { weapon = subweapon; weapon_change = true; }
          else{ weapon = mainweapon; weapon_change = false; }
        }
      }
    }
  }
}

// ==================== function list ==================== //

/////////////// initialize Game ////////////////////
void initGame(){
  gb.battery.show = false;
  
  // Map info or system info
  world_y = LCDHEIGHT;       // LCDHEIGHT*2 = 96
  camera_y = 0;
  shake_x = 0;
  shake_y = 0;
  shake_state = false;
  
  LevelUp_x = LCDWIDTH;
  Level = 1;
  leveling = false;
  
  Shop_State = false;
  scroll = LCDHEIGHT;
  
  weapon_select = 1;
  main_sub = 0;
  weapon_point = 0;
  weapon_change = false;
  readyGo = false;
  ready_Cnt = 0;
  screen = 0;
  
  // Me info
  player_x = LCDWIDTH / 2; 
  player_y = LCDHEIGHT / 2;
  Me_HP = 7;
  slowUP = 0;
  stunUP = 0;
  kill = 0;
  coin = 0;
  reloading_delay = 0;
  reloading = true;
  
  Guns[0].power = 2; Guns[1].power = 7; Guns[2].power = 12;
  Guns[0].shot_delay_time = 0; Guns[1].shot_delay_time = 21; Guns[2].shot_delay_time = 35;
  Guns[0].Ammo = 20; Guns[1].Ammo = 10; Guns[2].Ammo = 4;
  for(byte i=0; i<=2; i++) Guns[i].Ammo_MAX = 0;
  for(byte i=0; i<=2; i++) Guns[i].shot_state = true;
  for(byte i=0; i<=2; i++) Guns[i].shot_delay = true;
  for(byte i=0; i<=2; i++) Guns[i].reload_show = true;
  
  // Monster info
  mon_Ramdom_MAX = 200;
  mon_HPup = 0;
  mon_SpeedUp = 0;
  mon_max = 0;
  default_Speed = 3;
  Boss = false;
  Bossing = false;
  BossDie = false;
  Boss_message = 0;
  monster_drop = 0;
  droping = false;
  King_default_HP = mon_HPup*30;
  Monster_default_HP = mon_HPup+10;
  
  for(byte i=0; i<=4; i++) Mon[i].monMovement = 0;
  for(byte i=0; i<=4; i++) Mon[i].slow_time = 0;
  for(byte i=0; i<=4; i++) Mon[i].stun_time = 0;
  for(byte i=0; i<=4; i++) Mon[i].monMove = 0;
  for(byte i=0; i<=4; i++) Mon[i].monState = 0;
  for(byte i=0; i<=4; i++) Mon[i].slow_state = 0;
  for(byte i=0; i<=4; i++) Mon[i].stun_state = 0;
}
/////////////// shake Screen ////////////////////
void shakeScreen(){
  if(shake_state){
    if(shake_timeLeft > 0){
      shake_timeLeft--;
      shake_x += random(-shake_magnitude,shake_magnitude+1);
      shake_y += random(-shake_magnitude,shake_magnitude+1);
      displayBackgrond();
    }else {
      shake_x = 0;
      shake_y = 0;
      displayBackgrond();
      shake_state = false;
    } 
  }
}
/////////////// display Background ////////////////////
void displayBackgrond(){
  gb.display.drawFastVLine(8 + shake_x, 0 + shake_y, 47);
  gb.display.drawFastVLine(75 + shake_x, 0 + shake_y, 47);
  
  gb.display.drawBitmap(8 + shake_x, 0 + camera_y + shake_y, castle);
 
  gb.display.drawBitmap(8 + shake_x, 16 + camera_y + shake_y, fence[0]);
  gb.display.drawBitmap(8 + shake_x, 32 + camera_y + shake_y, fence[1]);
  //gb.display.drawBitmap(8 + shake_x, 48 + camera_y + shake_y, fence[1]);
  //gb.display.drawBitmap(8 + shake_x, 64 + camera_y + shake_y, fence[1]);
  //gb.display.drawBitmap(8 + shake_x, 80 + camera_y + shake_y, fence[1]);
  gb.display.drawBitmap(69 + shake_x, 16 + camera_y + shake_y, fence[0]);
  gb.display.drawBitmap(69 + shake_x, 32 + camera_y + shake_y, fence[1]);
  gb.display.drawBitmap(69 + shake_x, 48 + camera_y + shake_y, fence[1]);
  //gb.display.drawBitmap(69 + shake_x, 64 + camera_y + shake_y, fence[1]);
  //gb.display.drawBitmap(69 + shake_x, 80 + camera_y + shake_y, fence[1]);
  
}
/////////////// display HB bar, display Level, display coin ////////////////////
void displayHP(){
  char HPshake_x = 0, HPshake_y = 0;
  if(Me_HP <= 2){
    HPshake_x += random(-1,+1);
    HPshake_y += random(-1,+1); 
  }
  gb.display.drawBitmap(79 + HPshake_x, 1 + HPshake_y, HP_bar);
  switch(Me_HP){
    case 7 : gb.display.fillRect(80, 2, 2, 23); break;
    case 6 : gb.display.fillRect(80, 6, 2, 19); break;
    case 5 : gb.display.fillRect(80, 10, 2, 15); break;
    case 4 : gb.display.fillRect(80, 14, 2, 11); break;
    case 3 : gb.display.fillRect(80 + HPshake_x, 18 + HPshake_y, 2, 7); break;
    case 2 : gb.display.fillRect(80 + HPshake_x, 22 + HPshake_y, 2, 3); break;
    case 0 : GameOver(); break;
  }
  // display Level
  gb.display.println("Lv");
  gb.display.println(Level);
  // display Coin
  gb.display.println("");
  gb.display.println("$");
  gb.display.print(coin);
}
/////////////// display shot delay bar ////////////////////
void display_shot_bar(){
  if(!Guns[weapon].shot_delay && weapon >= 1){
    if(Guns[weapon].shot_delay_time >= 28){
      gb.display.fillRect(0, 43, Guns[weapon].shot_delay_time-28, 1);
      gb.display.fillRect(0, 44, 7, 4);
    }else if(Guns[weapon].shot_delay_time >= 21){
      gb.display.fillRect(0, 44, Guns[weapon].shot_delay_time-21, 1);
      gb.display.fillRect(0, 45, 7, 3);
    }else if(Guns[weapon].shot_delay_time >= 14){
      gb.display.fillRect(0, 45, Guns[weapon].shot_delay_time-14, 1);
      gb.display.fillRect(0, 46, 7, 2);
    }else if(Guns[weapon].shot_delay_time >= 7){
      gb.display.fillRect(0, 46, Guns[weapon].shot_delay_time-7, 1); 
      gb.display.fillRect(0, 47, 7, 1);
    }else gb.display.fillRect(0, 47, Guns[weapon].shot_delay_time, 1);
    if(Guns[weapon].shot_delay_time-- <= 0){
      if(weapon == 1) Guns[weapon].shot_delay_time = 21; else if(weapon ==2)Guns[weapon].shot_delay_time = 35; 
      Guns[weapon].shot_delay = true;
    }
  } 
}
/////////////// display Ammo, weapon state, reloading ////////////////////
void display_Ammo(){
  // display Ammo, weapon state
  if(weapon == 0) gb.display.drawBitmap(76, 37, rifle_img);
  else if(weapon == 1) gb.display.drawBitmap(76, 38, shotgun_img);
  else if(weapon == 2) gb.display.drawBitmap(76, 36, sniper_img);
  
  gb.display.cursorX = 77;
  gb.display.cursorY = 43;
  switch(weapon){
    case 0 : if(Guns[0].Ammo <= ((Guns[0].Ammo_MAX/2) + 10)){
             if(Guns[0].reload_show){ gb.display.print(Guns[0].Ammo); Guns[0].reload_show=false; }
             else Guns[0].reload_show=true;
             }else gb.display.print(Guns[0].Ammo);
             break; 
    case 1 : if(Guns[1].Ammo <= ((Guns[1].Ammo_MAX/2) + 5)){
             if(Guns[1].reload_show){ gb.display.print(Guns[1].Ammo); Guns[1].reload_show=false; }
             else Guns[1].reload_show=true;
             }else gb.display.print(Guns[1].Ammo);
             break; 
    case 2 : if(Guns[2].Ammo <= ((Guns[2].Ammo_MAX/2) + 2)){
             if(Guns[2].reload_show){ gb.display.print(Guns[2].Ammo); Guns[2].reload_show=false; }
             else Guns[2].reload_show=true;
             }else gb.display.print(Guns[2].Ammo);
             break;
  }
  
  // reloading
    if(reloading == false){
      gb.display.cursorX = (LCDWIDTH / 4)-2;
      gb.display.cursorY = (LCDHEIGHT / 3)+2;
      gb.display.setFont(font5x7);
      gb.display.print("Reload \35");
      gb.display.setFont(font3x5);
      
      if(weapon == 0){
        if(reloading_delay++ >= 1){
          gb.sound.playOK();
          if(Guns[weapon].Ammo++ < Guns[weapon].Ammo_MAX+19) reloading_delay = 0;
          else {reloading = true; Guns[weapon].shot_state = true; }
        }
      }
      if(weapon == 1){
        if(reloading_delay++ >= 3){
          gb.sound.playOK();
          if(Guns[weapon].Ammo++ < Guns[weapon].Ammo_MAX+9) reloading_delay = 0;
          else {reloading = true; Guns[weapon].shot_state = true; }
        }
      }
      if(weapon == 2){
        if(reloading_delay++ >= 6){
          gb.sound.playOK();
          if(Guns[weapon].Ammo++ < Guns[weapon].Ammo_MAX+3) reloading_delay = 0;
          else {reloading = true; Guns[weapon].shot_state = true; }
        }
      }
    }
}
/////////////// display Level UP! ////////////////////
void Level_Up(){
  if(leveling){
    gb.display.cursorX = LevelUp_x-=2;
    gb.display.cursorY = 0;
    gb.display.setFont(font5x7);
    gb.display.print("LEVEL UP!");
    gb.display.setFont(font3x5);
    if(LevelUp_x == -50) {leveling = false; LevelUp_x = LCDWIDTH;}
  }
  
  if(Bossing){
    gb.display.cursorX = 22+random(0,2);
    gb.display.cursorY = 10+random(0,2);
    if( Boss_message++ <= 70 ){
      gb.display.setFont(font5x7); 
      gb.display.print("DANGER\01"); 
      gb.display.setFont(font3x5);
    }
    if(mon_max == 0 && Boss_message >= 70){ Boss = true; Boss_message = 0; Bossing = false; }
  }
}
/////////////// display Game Over ////////////////////
void GameOver(){ // save score EEPROM, display score lanking
  while(true){
    if(gb.update()){
      displayBackgrond();
      if(camera_y) camera_y++;
      else if(camera_y <= 0){
        camera_y = 0;
        gb.display.cursorX = 16;
        gb.display.cursorY = 20;
        gb.display.setFont(font5x7);
        gb.display.println("GAME OVER");
        gb.display.setFont(font3x5);
        gb.display.println("");
        gb.display.cursorX = 0;
        gb.display.setFont(font5x7);
        gb.display.println("please button\26");
        gb.display.setFont(font3x5);
        gb.display.cursorX = 11;
        gb.display.print(" Your Socre :");
        gb.display.println(coin);
        gb.display.cursorX = 12+random(0,2);
        gb.display.cursorY = 0+random(0,2);
        if(coin > Highscores[RANKMAX-1]){
          gb.display.println("NEW HIGHT SCORE");
          if(gb.buttons.pressed(BTN_B)){
            gb.display.setFont(font5x7); save_Highscore(); gb.display.setFont(font3x5); break;
          }
        }else if(gb.buttons.pressed(BTN_B)){ display_highScore(); break; }
      }
    }
  }
  gb.titleScreen(F("Castle Defence!"));
  initGame();
}

void save_Highscore(){
  gb.getDefaultName(name[RANKMAX-1]);
  gb.keyboard(name[RANKMAX-1], NAME_LENGTH+1);
  Highscores[RANKMAX-1] = coin;
  for(byte i=RANKMAX-1; i>0; i--){ //bubble sorting FTW
    if(Highscores[i-1] < Highscores[i]){
      char tempName[NAME_LENGTH];
      strcpy(tempName, name[i-1]);
      strcpy(name[i-1], name[i]);
      strcpy(name[i], tempName);
      unsigned int tempScore;
      tempScore = Highscores[i-1];
      Highscores[i-1] = Highscores[i];
      Highscores[i] = tempScore;
    }
    else{
      break;
    }
  }
  for(byte thisScore = 0; thisScore < RANKMAX; thisScore++){
    for(byte i=0; i<NAME_LENGTH; i++){
      EEPROM.write(i + thisScore*(NAME_LENGTH+2), name[thisScore][i]);
    }
    EEPROM.write(NAME_LENGTH + thisScore*(NAME_LENGTH+2), Highscores[thisScore] & 0x00FF); //LSB
    EEPROM.write(NAME_LENGTH+1 + thisScore*(NAME_LENGTH+2), (Highscores[thisScore] >> 8) & 0x00FF); //MSB
  }
  display_highScore();
}

void display_highScore(){
  while(true){
    if(gb.update()){
      gb.display.cursorX = 3+random(0,2);
      gb.display.cursorY = 0+random(0,2);
      gb.display.setFont(font5x7);
      gb.display.println(F("HIGH SCORES"));
      gb.display.textWrap = false;
      gb.display.cursorX = 0;
      gb.display.cursorY = gb.display.fontHeight;
      for(byte thisScore=0; thisScore<RANKMAX; thisScore++){
        if(Highscores[thisScore]==0)
          gb.display.print('-');
        else
          gb.display.print(name[thisScore]);
        gb.display.cursorX = LCDWIDTH-3*gb.display.fontWidth;
        gb.display.cursorY = gb.display.fontHeight+gb.display.fontHeight*thisScore;
        gb.display.println(Highscores[thisScore]);
      }
      if(gb.buttons.pressed(BTN_A) || gb.buttons.pressed(BTN_B) || gb.buttons.pressed(BTN_C)){
        gb.sound.playOK();
        gb.display.setFont(font3x5);
        break;
      }
    }
  }
}

void load_Highscore(){
  for(byte thisScore = 0; thisScore < RANKMAX; thisScore++){
    for(byte i=0; i<NAME_LENGTH; i++){
      name[thisScore][i] = EEPROM.read(i + thisScore*(NAME_LENGTH+2));
    }
    Highscores[thisScore] = EEPROM.read(NAME_LENGTH + thisScore*(NAME_LENGTH+2)) & 0x00FF; //LSB
    Highscores[thisScore] += (EEPROM.read(NAME_LENGTH+1 + thisScore*(NAME_LENGTH+2)) << 8) & 0xFF00; //MSB
    Highscores[thisScore] = (Highscores[thisScore]==0xFFFF) ? 0 : Highscores[thisScore];
  }
}  
