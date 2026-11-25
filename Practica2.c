#include "ripes_system.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define SW0 (0x01)
#define SW1 (0x02)
#define SW2 (0x04)
#define SW3 (0x08)
#define SNAKE (0x0BF020)
#define MANZANA (0xFF0000)
#define BORRAR (0x000000)
#define UP (1)
#define DOWN (2)
#define LEFT (3)
#define RIGHT (4)
volatile unsigned int * led_base = LED_MATRIX_0_BASE;
volatile unsigned int * switch_base = SWITCHES_0_BASE;
volatile unsigned int * d_pad_up = D_PAD_0_UP;
volatile unsigned int * d_pad_down = D_PAD_0_DOWN;
volatile unsigned int * d_pad_left = D_PAD_0_LEFT;
volatile unsigned int * d_pad_right = D_PAD_0_RIGHT;

void main()
{
srand((unsigned int)time(NULL));
int ancho = LED_MATRIX_0_WIDTH;
int alto = LED_MATRIX_0_HEIGHT;
unsigned int mask = 0;
unsigned int snake_pos_x[100]={1};
unsigned int snake_pos_y[100]={1};
unsigned int manzana_pos_x=1;
unsigned int manzana_pos_y=1;

while (snake_pos_x[0]%2!=0){
    snake_pos_x[0]=(rand()%(ancho-2));}
while (snake_pos_y[0]%2!=0){
    snake_pos_y[0]=(rand()%(alto-2));}

while (manzana_pos_x%2!=0 || snake_pos_x[0]==manzana_pos_x){
    manzana_pos_x=(rand()%(ancho-2));}
while (manzana_pos_y%2!=0 || snake_pos_y[0]==manzana_pos_y){
    manzana_pos_y=(rand()%(alto-2));}


unsigned int dir=RIGHT;
unsigned int size = 1;

while (1){


    *(led_base+snake_pos_x[size-1]+snake_pos_y[size-1]*LED_MATRIX_0_WIDTH)=BORRAR;
    *(led_base+snake_pos_x[size-1]+snake_pos_y[size-1]*LED_MATRIX_0_WIDTH+1)=BORRAR;
    *(led_base+snake_pos_x[size-1]+snake_pos_y[size-1]*LED_MATRIX_0_WIDTH+LED_MATRIX_0_WIDTH)=BORRAR;
    *(led_base+snake_pos_x[size-1]+snake_pos_y[size-1]*LED_MATRIX_0_WIDTH+LED_MATRIX_0_WIDTH+1)=BORRAR;
    
    for (int i=size;i>0;i--){
        snake_pos_x[i]=snake_pos_x[i-1];
        snake_pos_y[i]=snake_pos_y[i-1];
    }
    
    if (dir==UP){
        snake_pos_y[0]-=2;}
    if (dir==DOWN){
        snake_pos_y[0]+=2;}
    if (dir==LEFT){
        snake_pos_x[0]-=2;}
    if (dir==RIGHT){
        snake_pos_x[0]+=2;}
    
    if (snake_pos_x[0]==manzana_pos_x&&snake_pos_y[0]==manzana_pos_y){
        size++;
    while (manzana_pos_x%2!=0 || snake_pos_x[0]==manzana_pos_x){
        manzana_pos_x=(rand()%(ancho-2));}
    while (manzana_pos_y%2!=0 || snake_pos_y[0]==manzana_pos_y){
        manzana_pos_y=(rand()%(alto-2));}

    }

    

    *(led_base+manzana_pos_x+manzana_pos_y*LED_MATRIX_0_WIDTH)=MANZANA;
    *(led_base+manzana_pos_x+manzana_pos_y*LED_MATRIX_0_WIDTH+1)=MANZANA;
    *(led_base+manzana_pos_x+manzana_pos_y*LED_MATRIX_0_WIDTH+LED_MATRIX_0_WIDTH)=MANZANA;
    *(led_base+manzana_pos_x+manzana_pos_y*LED_MATRIX_0_WIDTH+LED_MATRIX_0_WIDTH+1)=MANZANA;

    for (int i=0;i<size;i++){
        *(led_base+snake_pos_x[i]+snake_pos_y[i]*LED_MATRIX_0_WIDTH)=SNAKE;
        *(led_base+snake_pos_x[i]+snake_pos_y[i]*LED_MATRIX_0_WIDTH+1)=SNAKE;
        *(led_base+snake_pos_x[i]+snake_pos_y[i]*LED_MATRIX_0_WIDTH+LED_MATRIX_0_WIDTH)=SNAKE;
        *(led_base+snake_pos_x[i]+snake_pos_y[i]*LED_MATRIX_0_WIDTH+LED_MATRIX_0_WIDTH+1)=SNAKE;}

    for(volatile unsigned int i=0;i<5000;i++){
    if(*d_pad_up==1 && dir!=DOWN){
        dir=UP;}

    if(*d_pad_down == 1 && dir!=UP){
        dir=DOWN;}

    if(*d_pad_left == 1 && dir!=RIGHT){
        dir=LEFT;}

    if(*d_pad_right == 1 && dir!=LEFT){
        dir=RIGHT;}
    }
    
}}
