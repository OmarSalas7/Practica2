#include "ripes_system.h"
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
unsigned int mask = 0;
unsigned int snake_pos_x=5;
unsigned int snake_pos_y=5;
unsigned int dir=RIGHT;

while (1){


    *(led_base+snake_pos_x+snake_pos_y*LED_MATRIX_0_WIDTH)=BORRAR;
    *(led_base+snake_pos_x+snake_pos_y*LED_MATRIX_0_WIDTH+1)=BORRAR;
    *(led_base+snake_pos_x+snake_pos_y*LED_MATRIX_0_WIDTH+LED_MATRIX_0_WIDTH)=BORRAR;
    *(led_base+snake_pos_x+snake_pos_y*LED_MATRIX_0_WIDTH+LED_MATRIX_0_WIDTH+1)=BORRAR;
    
    if (dir==UP){
        snake_pos_y-=2;}
    if (dir==DOWN){
        snake_pos_y+=2;}
    if (dir==LEFT){
        snake_pos_x-=2;}
    if (dir==RIGHT){
        snake_pos_x+=2;}

    if(*d_pad_up == 1){
        dir=UP;}

    if(*d_pad_down == 1){
        dir=DOWN;}

    if(*d_pad_left == 1){
        dir=LEFT;}

    if(*d_pad_right == 1){
        dir=RIGHT;}

    *(led_base+snake_pos_x+snake_pos_y*LED_MATRIX_0_WIDTH)=SNAKE;
    *(led_base+snake_pos_x+snake_pos_y*LED_MATRIX_0_WIDTH+1)=SNAKE;
    *(led_base+snake_pos_x+snake_pos_y*LED_MATRIX_0_WIDTH+LED_MATRIX_0_WIDTH)=SNAKE;
    *(led_base+snake_pos_x+snake_pos_y*LED_MATRIX_0_WIDTH+LED_MATRIX_0_WIDTH+1)=SNAKE;
    
}}
