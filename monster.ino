/////////////// display Monster ////////////////////
void displayMonster(){
  byte mon_num;
  if(Boss){
     if(Mon[2].monState == 0 && !Bossing && !BossDie){
       mon_num = 2;
       Mon_setting(mon_num);
    }
  }else if(mon_max <= 5 && !Boss && !Bossing){  // make monster
    mon_make = random(1,mon_Ramdom_MAX);
    if(mon_make == mon_Ramdom_MAX/2-20){
      mon_num = 0;
      Mon_setting(mon_num);
    }else if(mon_make == mon_Ramdom_MAX/2-10){
      mon_num = 1;
      Mon_setting(mon_num);
    }else if(mon_make == mon_Ramdom_MAX/2){
      mon_num = 2;
      Mon_setting(mon_num);
    }else if(mon_make == mon_Ramdom_MAX/2+10){
      mon_num = 3;
      Mon_setting(mon_num);
    }else if(mon_make == mon_Ramdom_MAX/2+20){
      mon_num = 4;
      Mon_setting(mon_num);
    }
  }
  // display monster, set monster speed
  if(Mon[0].monState){ monster_draw(0); }
  if(Mon[1].monState){ monster_draw(1); }
  if(Mon[2].monState){
    if(Boss && !Bossing){
      if(Mon[2].mon_y == 72 || Mon[2].mon_y == 47){
        gb.display.drawBitmap( Mon[2].mon_x, Mon[2].mon_y + camera_y, king_skil[Mon[2].monMove]); 
        if(!Mon[2].stun_state){
          if(monster_drop++ == 70) {monster_drop = 0; Mon[2].mon_y--;}
          else if(monster_drop == 30) droping = true;
        }  
        if(Mon[2].monMove) Mon[2].monMove = false; 
        else Mon[2].monMove = true; 
      }else {
      gb.display.drawBitmap( Mon[2].mon_x, Mon[2].mon_y + camera_y, king[Mon[2].monMove]);
      if((Mon[2].monMovement += Mon[2].mon_Speed) > Mon[2].mon_SpeedMAX){
         Mon[2].mon_y--;
         Mon[2].monMovement = 0;
        if(Mon[2].monMove) Mon[2].monMove = false; 
        else Mon[2].monMove = true; 
      }
    }
  }else monster_draw(2); 
  }
  if(Mon[3].monState){ monster_draw(3); }
  if(Mon[4].monState){ monster_draw(4); }
  
  // monster attack
  if(Mon[0].mon_y == 15){
      monster_die(0);
      Me_HP--;
      monster_shake();
  }
  if(Mon[1].mon_y == 15){
      monster_die(1);
      Me_HP--;
      monster_shake();
  }
  if(Mon[2].mon_y == 15){
      monster_die(2);
      if(Boss) Me_HP -= 2; else Me_HP--;
      monster_shake();
  }
  if(Mon[3].mon_y == 15){
      monster_die(3);
      Me_HP--;
      monster_shake();
  }
  if(Mon[4].mon_y == 15){
      monster_die(4);
      Me_HP--;
      monster_shake();
  }
  // Abnormal time
  if(Mon[0].slow_state) Monster_slow(0);
  if(Mon[1].slow_state) Monster_slow(1);
  if(Mon[2].slow_state) Monster_slow(2);
  if(Mon[3].slow_state) Monster_slow(3);
  if(Mon[4].slow_state) Monster_slow(4);
  
  if(Mon[0].stun_state) Monster_stun(0);
  if(Mon[1].stun_state) Monster_stun(1);
  if(Mon[2].stun_state) Monster_stun(2);
  if(Mon[3].stun_state) Monster_stun(3);
  if(Mon[4].stun_state) Monster_stun(4);
  
  // motion_slow
  if(Mon[0].slow_state && Mon[0].monState) Motion_slow(0);
  else slowmotion_time[0] = 0;
  if(Mon[1].slow_state && Mon[1].monState) Motion_slow(1);
  else slowmotion_time[1] = 0;
  if(Mon[2].slow_state && Mon[2].monState) Motion_slow(2);
  else slowmotion_time[2] = 0;
  if(Mon[3].slow_state && Mon[3].monState) Motion_slow(3);
  else slowmotion_time[3] = 0;
  if(Mon[4].slow_state && Mon[4].monState) Motion_slow(4);
  else slowmotion_time[4] = 0;
  
  // motion_stun
  if(Mon[0].stun_state && Mon[0].monState) Motion_stun(0);
  else stunmotion_time[0] = 0;
  if(Mon[1].stun_state && Mon[1].monState) Motion_stun(1);
  else stunmotion_time[1] = 0;
  if(Mon[2].stun_state && Mon[2].monState) Motion_stun(2);
  else stunmotion_time[2] = 0;
  if(Mon[3].stun_state && Mon[3].monState) Motion_stun(3);
  else stunmotion_time[3] = 0;
  if(Mon[4].stun_state && Mon[4].monState) Motion_stun(4);
  else stunmotion_time[4] = 0;

  // display Monster HP
  if(Mon[0].monState) display_mon_HP(0);
  if(Mon[1].monState) display_mon_HP(1);
  if(Boss && Mon[2].monState){
    gb.display.drawRect(Mon[2].mon_x, Mon[2].mon_y-5 + camera_y, 16, 3);
    if(King_default_HP*0.9 <= Mon[2].mon_HP) gb.display.fillRect(Mon[2].mon_x, Mon[2].mon_y-4 + camera_y, 16, 1);
    else if(King_default_HP*0.8 <= Mon[2].mon_HP) gb.display.fillRect(Mon[2].mon_x, Mon[2].mon_y-4 + camera_y, 13, 1);
    else if(King_default_HP*0.6 <= Mon[2].mon_HP) gb.display.fillRect(Mon[2].mon_x, Mon[2].mon_y-4 + camera_y, 10, 1);
    else if(King_default_HP*0.4 <= Mon[2].mon_HP) gb.display.fillRect(Mon[2].mon_x, Mon[2].mon_y-4 + camera_y, 7, 1);
    else if(King_default_HP*0.2 <= Mon[2].mon_HP) gb.display.fillRect(Mon[2].mon_x, Mon[2].mon_y-4 + camera_y, 4, 1);
    else gb.display.fillRect(Mon[2].mon_x, Mon[2].mon_y-4 + camera_y, 1, 1);
  }else if(Mon[2].monState) display_mon_HP(2);
  if(Mon[3].monState) display_mon_HP(3);
  if(Mon[4].monState) display_mon_HP(4);
}
////////////// Boss skil /////////////
void monsterDrop(){
  if(droping){
    if(Mon[2].mon_y == 72){
      if(Mon[0].monState == 0){
        Mon[0].mon_x = 15;
        Mon[0].mon_y = Mon[2].mon_y + 7; 
        Mon[0].mon_HP = 10 + mon_HPup;
        Mon[0].mon_Speed = 3 + mon_SpeedUp;
        Mon[0].mon_SpeedMAX = 12;
      }
      if(Mon[4].monState == 0){
        Mon[4].mon_x = 59;
        Mon[4].mon_y = Mon[2].mon_y + 7; 
        Mon[4].mon_HP = 10 + mon_HPup;
        Mon[4].mon_Speed = 3 + mon_SpeedUp;
        Mon[4].mon_SpeedMAX = 12;
      }
      Mon[0].monState = true; Mon[4].monState = true; mon_max += 2; droping = false;
    }
    if(Mon[2].mon_y == 47){
      if(Mon[1].monState == 0){
        Mon[1].mon_x = 23;
        Mon[1].mon_y = Mon[2].mon_y + 7; 
        Mon[1].mon_HP = 10 + mon_HPup;
        Mon[1].mon_Speed = 3 + mon_SpeedUp;
        Mon[1].mon_SpeedMAX = 12;
      }
      if(Mon[3].monState == 0){
        Mon[3].mon_x = 51;
        Mon[3].mon_y = Mon[2].mon_y + 7; 
        Mon[3].mon_HP = 10 + mon_HPup;
        Mon[3].mon_Speed = 3 + mon_SpeedUp;
        Mon[3].mon_SpeedMAX = 12;
      }
      Mon[1].monState = true; Mon[3].monState = true; mon_max += 2; droping = false;
    }
  }
}
////////////// display Monster_HP /////////////////////
void display_mon_HP(byte u){
  gb.display.drawRect(Mon[u].mon_x, Mon[u].mon_y-4 + camera_y, 10, 3);
  if(Monster_default_HP*0.9 <= Mon[u].mon_HP)gb.display.fillRect(Mon[u].mon_x+1, Mon[u].mon_y-3 + camera_y, 8, 1);
  else if(Monster_default_HP*0.8 <= Mon[u].mon_HP) gb.display.fillRect(Mon[u].mon_x+1, Mon[u].mon_y-3 + camera_y, 6, 1);
  else if(Monster_default_HP*0.5 <= Mon[u].mon_HP) gb.display.fillRect(Mon[u].mon_x+1, Mon[u].mon_y-3 + camera_y, 4, 1);
  else if(Monster_default_HP*0.2 <= Mon[u].mon_HP) gb.display.fillRect(Mon[u].mon_x+1, Mon[u].mon_y-3 + camera_y, 2, 1);
  else gb.display.fillRect(Mon[u].mon_x+1, Mon[u].mon_y-3 + camera_y, 0, 1); 
}
void Monster_slow(byte k){
  if(Boss && k == 2){
    if(Mon[k].slow_time++ >= (70 + slowUP)/2 ){ 
      if(!Mon[k].stun_state) Mon[k].mon_Speed = default_Speed; 
      Mon[k].slow_time = 0; 
      Mon[k].slow_state = false;
    }
  }else if(Mon[k].slow_time++ >= 70 + slowUP ){ 
    if(!Mon[k].stun_state) Mon[k].mon_Speed = default_Speed;
    Mon[k].slow_time = 0; 
    Mon[k].slow_state = false; 
  } 
}
void Monster_stun(byte g){
  if(Boss && g == 2){
    if(Mon[g].stun_time++ >= (50 + stunUP)/2 ){ 
      if(!Mon[g].slow_state) Mon[g].mon_Speed = default_Speed;
      Mon[g].stun_time = 0; 
      Mon[g].stun_state = false;
    }
  }else if(Mon[g].stun_time++ >= 50 + stunUP ){ 
    if(!Mon[g].slow_state) Mon[g].mon_Speed = default_Speed; 
    Mon[g].stun_time = 0; 
    Mon[g].stun_state = false; 
  }
}
//////// Motion ///////////////
void Motion_slow(byte a){
  if(Boss && a==2) gb.display.drawBitmap(Mon[a].mon_x + 11, Mon[a].mon_y + camera_y + slowmotion_time[a], motion_slow); 
  else gb.display.drawBitmap(Mon[a].mon_x + 5, Mon[a].mon_y + camera_y + slowmotion_time[a], motion_slow); 
  if(slowmotion_time[a] <= 3) slowmotion_time[a]++; 
  else slowmotion_time[a] = 0;
}
void Motion_stun(byte b){
  if(Boss && b==2) gb.display.drawBitmap(Mon[b].mon_x - 1, Mon[b].mon_y + camera_y - 4, motion_stun[stunmotion_time[b]]);
  else gb.display.drawBitmap(Mon[b].mon_x - 4, Mon[b].mon_y + camera_y - 7, motion_stun[stunmotion_time[b]]); 
  if(stunmotion_time[b] <= 1) ++stunmotion_time[b]; 
  else stunmotion_time[b] = 0;
}
/////////////// Monster Make ////////////////
void Mon_setting(byte mon_num){
  if(Mon[mon_num].monState == 0){ // initialize Monster
    switch(mon_num){
      case 0 : Mon[mon_num].mon_x = 15; break;
      case 1 : Mon[mon_num].mon_x = 26; break;
      case 2 : if(Boss) Mon[mon_num].mon_x = 34; else Mon[mon_num].mon_x = 37; break;
      case 3 : Mon[mon_num].mon_x = 48; break;
      case 4 : Mon[mon_num].mon_x = 59; break;
    }
    Mon[mon_num].mon_y = 96; 
    if(Boss) Mon[mon_num].mon_HP = 30 * mon_HPup; else Mon[mon_num].mon_HP = 10 + mon_HPup;
    Mon[mon_num].mon_Speed = 3 + mon_SpeedUp;
    if(Boss) Mon[mon_num].mon_SpeedMAX = 18; else Mon[mon_num].mon_SpeedMAX = 12;
    Mon[mon_num].monState = true;
    mon_max++;
  }
}
/////////////// monster draw ////////////////
void monster_draw(byte z){
   gb.display.drawBitmap(Mon[z].mon_x, Mon[z].mon_y + camera_y, monster[Mon[z].monMove]); 
   if((Mon[z].monMovement += Mon[z].mon_Speed) > Mon[z].mon_SpeedMAX){
     Mon[z].mon_y--;
     Mon[z].monMovement = 0; 
     if(Mon[z].monMove)Mon[z].monMove = false; 
     else Mon[z].monMove = true;
 
  }
}
/////////////// monster die //////////////////
void monster_die(byte j){
  Mon[j].monState = false;
  if(Boss && j==2) BossDie = true;
  Mon[j].slow_state = false; 
  Mon[j].stun_state = false; 
  Mon[j].mon_Speed = default_Speed; 
  Mon[j].slow_time = 0; 
  Mon[j].stun_time = 0; 
  Mon[j].mon_y = 87; 
  mon_max--; 
  kill++;
}
void all_kill(){
  if(BossDie && mon_max <= 0) { 
    Boss = false; 
    Shop_State = true; 
    weapon = 0; 
    BossDie = false; 
  } 
}
void monster_shake(){
  gb.sound.playCancel();
  shake_timeLeft = 2;
  shake_magnitude = 1;
  shake_state = true; 
}
