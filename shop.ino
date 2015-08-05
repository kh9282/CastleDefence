void display_Shop(){
  if(Shop_State){
     if(scroll <= 0){
       gb.display.drawBitmap(9, scroll, shop);
       if(gb.collidePointRect(player_x + 4, player_y + 4, 12, 9, 16, 11)){
         displaymessage(0,0);
       }
       if(gb.collidePointRect(player_x + 4, player_y + 4, 30, 9, 19, 11)){
         displaymessage(1,0);
       }
       if(gb.collidePointRect(player_x + 4, player_y + 4, 50, 9, 22, 11)){
         displaymessage(2,0);
       }
    
       if(gb.collidePointRect(player_x + 4, player_y + 4, 12, 21, 16, 11)){
         displaymessage(0,1);
       }
       if(gb.collidePointRect(player_x + 4, player_y + 4, 30, 21, 19, 11)){
         displaymessage(1,1);
       }
       if(gb.collidePointRect(player_x + 4, player_y + 4, 50, 21, 22, 11)){
         displaymessage(2,1);
       }
       
       if(gb.collidePointRect(player_x + 4, player_y + 4, 12, 32, 16, 10)){
         displaymessage(0,2);
       }
       if(gb.collidePointRect(player_x + 4, player_y + 4, 30, 32, 19, 10)){
         displaymessage(1,2);
       }
       if(gb.collidePointRect(player_x + 4, player_y + 4, 50, 32, 22, 10)){
         displaymessage(2,2);
       }
       if(gb.buttons.pressed(BTN_C)){
         gb.sound.playCancel(); 
         Shop_State = false;
       }
     }else gb.display.drawBitmap(9, scroll--, shop);
  }
}

void displaymessage(byte weapons, byte type){ // weapons 0 = rifle, 1 = shotgun, 2 = sniper
  gb.display.cursorX = 60;                    // type 0 = damage, 1 = Ammo, 2 = special 
  gb.display.cursorY = 2;
  switch(weapons){
    case 0 : if(type != 2) gb.display.println("50");      // rifle damage +
             else gb.display.println("80"); // rifle special +
             break;
    case 1 : if(type != 2) gb.display.println("60");     // shotgun damage +
             else gb.display.println("80"); // shotgun sepcial +
             break;
    case 2 : if(type==0) gb.display.println("70");     // sniper damage +
             else if(type==1) gb.display.println("60");// sniper Ammo +
             else if(type==2) gb.display.println("80");// sniper sepcial +
             break;
  }
  if(gb.buttons.pressed(BTN_A)){
  gb.sound.playOK();
  while(1){
    if(gb.update()){
      gb.display.cursorX = 5;
      gb.display.cursorY = 5;
      gb.display.setFont(font5x7);
      switch(weapons){
        case 0 : if(weapons == mainweapon || weapons == subweapon){
                   if(type==0) {gb.display.println("Rifle Damage"); gb.display.println(" Upgrade(+1)");gb.display.setFont(font3x5);gb.display.print("  Your Damage : ");gb.display.println(Guns[0].power);}
                   else if(type==1) {gb.display.println("Rifle Ammo"); gb.display.println(" Upgrade(+2)");gb.display.setFont(font3x5);gb.display.print("  Your Ammo : ");gb.display.println(Guns[0].Ammo_MAX + 20);}
                 }else {gb.display.println(" Impossible!"); }
                 if(type==2) {gb.display.println(" Life"); gb.display.println(" Recovery(+1)");gb.display.setFont(font3x5);gb.display.print("  Your Life : ");gb.display.println(Me_HP);}
                 break;
        case 1 : if(weapons == mainweapon || weapons == subweapon){
                   if(type==0) {gb.display.println("ShotgunDamage"); gb.display.println(" Upgrade(+2)");gb.display.setFont(font3x5);gb.display.print("  Your Damage : ");gb.display.println(Guns[1].power);}    
                   else if(type==1) {gb.display.println("Shotgun Ammo"); gb.display.println(" Upgrade(+2)");gb.display.setFont(font3x5);gb.display.print("  Your Ammo : ");gb.display.println(Guns[1].Ammo_MAX + 10);}
                   else if(type==2) {gb.display.println("Slow time"); gb.display.println(" Upgrade(+10)");gb.display.setFont(font3x5);gb.display.print(" Your slow time : ");gb.display.println(70+slowUP);}
                 }else {gb.display.println(" Impossible!"); }
                 break;
        case 2 : if(weapons == mainweapon || weapons == subweapon){
                   if(type==0) {gb.display.println("Sniper Damage"); gb.display.println(" Upgrade(+4)");gb.display.setFont(font3x5);gb.display.print("  Your Damage : ");gb.display.println(Guns[2].power);}     
                   else if(type==1) {gb.display.println("Sniper Ammo"); gb.display.println(" Upgrade(+2)");gb.display.setFont(font3x5);gb.display.print("  Your Ammo : ");gb.display.println(Guns[2].Ammo_MAX + 4);}
                   else if(type==2) {gb.display.println("Stun time"); gb.display.println(" Upgrade(+10)");gb.display.setFont(font3x5);gb.display.print(" Your stun time : ");gb.display.println(50+stunUP);}
                 }else {gb.display.println(" Impossible!"); }
                 break;
      }
      gb.display.setFont(font3x5);
      gb.display.println("");
      if((weapons == mainweapon || weapons == subweapon) || (weapons == 0 && type == 2 )) gb.display.println("\25:Buy        \26:cancel");
      if(gb.buttons.pressed(BTN_A)){
        switch(weapons){
        case 0 :  if(weapons == mainweapon || weapons == subweapon){
                   if(type==0){ if(coin >= 50) { gb.sound.playTick(); coin -= 50; Guns[0].power += 1; gb.popup(F(" Upgrade complete!"), 10); } else gb.popup(F("   Have no money."), 10);}
                   else if(type==1){ if(coin >= 50) { gb.sound.playTick(); coin -= 50; Guns[0].Ammo_MAX += 2; gb.popup(F(" Upgrade complete!"), 10); } else gb.popup(F("   Have no money."), 10);}
                  }
                  if(type==2){ if(coin >= 80) { gb.sound.playTick(); if(Me_HP == 7){gb.popup(F(" Your Life is full."), 10);} else {Me_HP++; coin -= 80; gb.popup(F(" Upgrade complete!"), 10);}} else gb.popup(F("   Have no money."), 10);}
                 break;
        
        case 1 : if(weapons == mainweapon || weapons == subweapon){
                   if(type==0){ if(coin >= 60) { gb.sound.playTick(); coin -= 60; Guns[1].power += 2; gb.popup(F(" Upgrade complete!"), 10); } else gb.popup(F("   Have no money."), 10);}
                   else if(type==1){ if(coin >= 60) { gb.sound.playTick(); coin -= 60; Guns[1].Ammo_MAX += 2; gb.popup(F(" Upgrade complete!"), 10); } else gb.popup(F("   Have no money."), 10);}
                   else if(type==2){ if(coin >= 80) { gb.sound.playTick(); coin -= 80; slowUP += 10; gb.popup(F(" Upgrade complete!"), 10); } else gb.popup(F("   Have no money."), 10);}
                 }
                 break;
        case 2 : if(weapons == mainweapon || weapons == subweapon){
                   if(type==0){ if(coin >= 70) { gb.sound.playTick(); coin -= 70; Guns[2].power += 4; gb.popup(F(" Upgrade complete!"), 10); } else gb.popup(F("   Have no money."), 10);}
                   else if(type==1){ if(coin >= 60) { gb.sound.playTick(); coin -= 60; Guns[2].Ammo_MAX += 2; gb.popup(F(" Upgrade complete!"), 10); } else gb.popup(F("   Have no money."), 10);}
                   else if(type==2){ if(coin >= 80) { gb.sound.playTick(); coin -= 80; stunUP += 10; gb.popup(F(" Upgrade complete!"), 10); } else gb.popup(F("   Have no money."), 10);}
                 }
                 break;
        }
        }else if(gb.buttons.pressed(BTN_B)) {
          gb.sound.playCancel(); 
          mon_max = 0;
          break;
        }
      }
    }
  }
}
