#include"GPIO_INTERFACE.h"
#include "seven_segment.h"
u8 number[10]={0x3F , 0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D , 0x07 , 0x7F , 0x6F};
void Seven_Segment_inti(u8 copy_u8port){
    GPIO_VidSetPortDirection(copy_u8port , 0xFF);

}
void Seven_Segment_Display(u8 number , u8 copy_u8port){
    GPIO_VidSetPortValue(copy_u8port , numbers[number]);
}