/////////////// Me Attack ////////////////////
void Attack(){
  if(Guns[weapon].shot_state && !weapon){
    gb.sound.playOK();
    Guns[weapon].Ammo --;
    if( Guns[weapon].Ammo == 0 ) Guns[weapon].shot_state = false;
      if(Boss){
        if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[2].mon_x, Mon[2].mon_y + camera_y, 18, 16) && Mon[2].monState) Attacking(2);
      }else if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[2].mon_x, Mon[2].mon_y + camera_y, 10, 9) && Mon[2].monState) Attacking(2);
      if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[0].mon_x, Mon[0].mon_y + camera_y, 10, 9) && Mon[0].monState) Attacking(0);
      if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[1].mon_x, Mon[1].mon_y + camera_y, 10, 9) && Mon[1].monState) Attacking(1);
      if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[3].mon_x, Mon[3].mon_y + camera_y, 10, 9) && Mon[3].monState) Attacking(3);
      if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[4].mon_x, Mon[4].mon_y + camera_y, 10, 9) && Mon[4].monState) Attacking(4);
    }else if(Guns[weapon].shot_state && Guns[weapon].shot_delay){
    if(weapon == 2) gb.display.drawBitmap(player_x-32, player_y-20, shot);
    shake_timeLeft = 2;
    if(weapon == 1) shake_magnitude = 2; 
    else shake_magnitude = 4;
    shake_state = true;
    gb.sound.playOK();
    Guns[weapon].Ammo --;
    if( Guns[weapon].Ammo == 0 ) Guns[weapon].shot_state = false;
      if(Boss){
        if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[2].mon_x, Mon[2].mon_y + camera_y, 18, 16) && Mon[2].monState) Attacking(2);
      }else if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[2].mon_x, Mon[2].mon_y + camera_y, 10, 9) && Mon[2].monState) Attacking(2);
      if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[0].mon_x, Mon[0].mon_y + camera_y, 10, 9) && Mon[0].monState) Attacking(0);
      if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[1].mon_x, Mon[1].mon_y + camera_y, 10, 9) && Mon[1].monState) Attacking(1);
      if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[3].mon_x, Mon[3].mon_y + camera_y, 10, 9) && Mon[3].monState) Attacking(3);
      if(gb.collidePointRect(player_x + 4, player_y + 4, Mon[4].mon_x, Mon[4].mon_y + camera_y, 10, 9) && Mon[4].monState) Attacking(4);
    Guns[weapon].shot_delay = false;  
    }
}

void Attacking(byte m){
  Mon[m].mon_HP -= Guns[weapon].power;
  if(weapon == 1 && (Mon[m].mon_HP + mon_HPup) >= 1){ Mon[m].slow_time = 0; Mon[m].mon_Speed = 1; Mon[m].slow_state = true; }
  if(weapon == 2 && (Mon[m].mon_HP + mon_HPup) >= 1){ Mon[m].stun_time = 0; Mon[m].mon_Speed = 0; Mon[m].stun_state = true; }
  if(Mon[m].mon_HP <= 0){
    monster_die(m);
    if(Boss) coin += 10; else coin += 2; 
  }
}
