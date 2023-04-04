#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "extapp_api.h"

//0xE0C4eur de fond  0x343C
//0xE0C4eur 2 0x1B9B

void init_app(void){
    extapp_pushRectUniform(0, 18, 320, 222,  0x343C);
}

void gride(void){

    int y = 40;
    int x = 70;

    extapp_pushRectUniform(0 + x, 0 + y, 50, 50,  0x651D);
    extapp_pushRectUniform(0 + x, 60 + y, 50, 50,  0x651D);
    extapp_pushRectUniform(60 + x, 0 + y, 50, 50,  0x651D);
    extapp_pushRectUniform(60 + x, 60 + y, 50, 50,  0x651D);
    extapp_pushRectUniform(0 + x, 120 + y, 50, 50,  0x651D);
    extapp_pushRectUniform(60 + x, 120 + y, 50, 50,  0x651D);
    extapp_pushRectUniform(120 + x, 120 + y, 50, 50,  0x651D);
    extapp_pushRectUniform(120 + x, 0 + y, 50, 50,  0x651D);
    extapp_pushRectUniform(120 + x, 60 + y, 50, 50,  0x651D);
}

void circle(int cx,int cy,int rayon, int color){
  int d, y, x;
 
  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;
 
  while (y >= x) {
    extapp_pushRectUniform(cx - x, cy - y, 2 * x + 1, 1, color);
    extapp_pushRectUniform(cx - x, cy + y, 2 * x + 1, 1, color);
    extapp_pushRectUniform(cx - y, cy - x, 2 * y + 1, 1, color);
    extapp_pushRectUniform(cx - y, cy + x, 2 * y + 1, 1, color);
 
    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }
 
    x++;
  }
}

void pion_1(int x,int y){
    circle((60 * x) + 95,(60 * y) + 65, 25, 0xFBC0);
    circle((60 * x) + 95,(60 * y) + 65, 17, 0x651D);
}

void pion_2(int x,int y){
    int len = 8;
    for(int i = 0;i<42; i++){
        extapp_pushRectUniform((60 * x) + 70 + i, (y * 60) + 45 + i,len, 1, 0x000F);
        extapp_pushRectUniform((60 * x) + 70 + i, (y * 60) + 45 + (42-i),len, 1, 0x000F);
    }
}

int victoire(int *T){
    for (int i = 0; i < 3; i++){
        if (T[0+i] * T[3+i] * T[6+i] == 1){
            return 1;
        } else if (T[0+i] * T[3+i] * T[6+i] == 8){
            return 2;
        }
    }

    for (int i = 0; i < 3; i++){
        if (T[0+(i*3)] * T[1+(i*3)] * T[2+(i*3)] == 1){
            return 1;
        } else if (T[0+(i*3)] * T[1+(i*3)] * T[2+(i*3)] == 8){
            return 2;
        }
    }

    if (T[0] * T[4] * T[8] == 1){
        return 1;
    } else if (T[0] * T[4] * T[8] == 8){
        return 2;
    }

    if (T[2] * T[4] * T[6] == 1){
        return 1;
    } else if (T[2] * T[4] * T[6] == 8){
        return 2;
    }

    return 0;
}

bool valueinarray(int val, int *arr){
    int i;
    for(i = 0; i < 9; i++){
        if(arr[i] == val) return true;
    }
    return false;
}

void main_game(void){

    while (extapp_scanKeyboard()) {
        extapp_msleep(10);
    }

    init_app();
    gride();

    int plat[9] = {0,0,0,0,0,0,0,0,0};
    int tour = 1;

    while (victoire(plat) == 0 && valueinarray(0, plat)){
        int key = extapp_getKey(0,false);

        if (tour == 1){
            tour = 2;
        }else{
            tour = 1;
        }

        while (key == 0){
            key = extapp_getKey(0,false);
        }
        
        if(key == 5){
            return;
        } else if (key == 49){
            if (tour == 1){
                pion_1(0,2);
                plat[6] = 1;
            } else {
                pion_2(0,2);
                plat[6] = 2;
            }
        } else if (key == 50){
            if (tour == 1){
                pion_1(1,2);
                plat[7] = 1;
            } else {
                pion_2(1,2);
                plat[7] = 2;
            }
        } else if (key == 51){
            if (tour == 1){
                pion_1(2,2);
                plat[8] = 1;
            }else {
                pion_2(2,2);
                plat[8] = 2;
            }
        } else if (key == 52){
            if (tour == 1){
                pion_1(0,1);
                plat[3] = 1;
            }else {
                pion_2(0,1);
                plat[3] = 2;
            }
        } else if (key == 53){
            if (tour == 1){
                pion_1(1,1);
                plat[4] = 1;
            }else {
                pion_2(1,1);
                plat[4] = 2;
            }
        } else if (key == 54){
            if (tour == 1){
                pion_1(2,1);
                plat[5] = 1;
            }else {
                pion_2(2,1);
                plat[5] = 2;
            }
        } else if (key == 55){
            if (tour == 1){
                pion_1(0,0);
                plat[0] = 1;
            }else {
                pion_2(0,0);
                plat[0] = 2;
            }
        } else if (key == 56){
            if (tour == 1){
                pion_1(1,0);
                plat[1] = 1;
            }else {
                pion_2(1,0);
                plat[1] = 2;
            }
        } else if (key == 57){
            if (tour == 1){
                pion_1(2,0);
                plat[2] = 1;
            }else {
                pion_2(2,0);
                plat[2] = 2;
            }
        }
    }

    if (victoire(plat) == 1){
        extapp_drawTextLarge("victoir joueur rond ", 70, 20 * 5, 0xffff,  0x1B9B, false);
    } else if (victoire(plat) == 2){
        extapp_drawTextLarge("victoir joueur croix", 70, 20 * 5, 0xffff,  0x1B9B, false);
    }else {
        extapp_drawTextLarge("matche nule", 80, 20 * 5, 0xffff,  0x1B9B, false);
    }

    extapp_msleep(5000);
}

void extapp_main(void) {

while (true){
        init_app();
        //titel
        extapp_drawTextLarge("       MORPION MASTER!", 0, 20 * 2, 0xffff,  0x343C, false);
        extapp_drawTextLarge("+ play", 110, 20 * 5, 0xffff,  0x1B9B, false);
        extapp_drawTextLarge("+ exit", 110, 20 * 6, 0xffff,  0x343C, false);
        extapp_drawTextLarge("                     by cartoone", 0, 20 * 11, 0xffff,  0x343C, false);

        // main

        int key = extapp_getKey(0,false);
        int menu = 0;

        while (true){
            extapp_msleep(10);
            key = extapp_getKey(0,false);

            if (key == 2){

                if (menu < 2){
                    menu ++;
                }
            
            } else if (key == 1){
            
                if (0 < menu){
                    menu --;
                }
            
            } else if (key == 4){
                if (menu == 0){
                    
                    main_game();
                    break;
                } else {
                    return;
                }

            } else if (key == 5){

                return;
            
            }

            if (menu == 0){
                extapp_drawTextLarge("+ play", 110, 20 * 5, 0xffff,  0x1B9B, false);
                extapp_drawTextLarge("+ exit", 110, 20 * 6, 0xffff,  0x343C, false);
            } else if (menu == 1){
                extapp_drawTextLarge("+ play", 110, 20 * 5, 0xffff,  0x343C, false);
                extapp_drawTextLarge("+ exit", 110, 20 * 6, 0xffff,  0x1B9B, false);
            }
        }

        
    }
    return;
}
