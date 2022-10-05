Code for Car Parking System


#include<reg51.h>
#define lcdport P2
sbit senin=P1^0;                         
sbit senout=P1^1;                        
sbit door1_a=P3^4;                
sbit door1_b=P3^5;                
sbit door2_a=P3^6;
sbit door2_b=P3^7;
sbit rs=P3^0;
sbit rw=P3^1;
sbit en=P3^2;
sbit led=P1^7;
sbit pulse=P3^5;
int k,p;
unsigned int count=8;                
unsigned int digit[5];
void entry_door_open();
void exit_door_open();
void entry_door_close();
void exit_door_close();
void exit_door_stop();
void entry_door_stop();
void lcdcmd(char);
void lcdint();
void lcddata(char);
void lcdstring(char *);
void delay(unsigned int);
void convert(unsigned int);
void ldelay(unsigned int);
            
void main()
{
        lcdint();
        led=0;
        senin=0;
        senout=0;
                                lcdcmd(0x38);  
                                delay(6000);                        
                                lcdcmd(0x10);         
                                delay(6000);
                                lcdcmd(0x0c);                
                                delay(6000);
                                lcdcmd(0x80);        
                                delay(6000);
                                lcdstring("HELLO SIR");        
                                delay(90000);
                                lcdcmd(0x01);
        lcdstring("WELCOME TO CAR");
                                delay(9000);
        lcdcmd(0xc0);
        lcdstring("PARKING SYSTEM");
        delay(50000);
        lcdcmd(0x01);
        lcdstring("PARKING LEFT:");
        lcdcmd(0x8d);
        convert(count);
        while(1)                                        
        {
        lcdcmd(0x8d);
        led=1;
        ldelay(10);
        if(senin==1)
        {
        count=count-1;
        convert(count);
        entry_door_open();
        while(senin==1);
        delay(60000);
        delay(60000);
        entry_door_close();
        entry_door_stop();
        delay(5000);
       }
       else if(senout==1)
       {
        count=count+1;
        convert(count);
        exit_door_open();
        while(senout==1);
        delay(60000);
        delay(60000);
        exit_door_close();
        exit_door_stop();
        delay(5000);
        }
          }
            }
void convert(unsigned int value)
{
 led=0;      
  for(k=0;k<2;k++)
  {
        digit[k]=value%10;
        value=value/10;
        }  
        for(p=1;p>=0;p--)
        {
       lcddata(digit[p]+48);
        ldelay(1);
        }
        if (count==0)
        {
        lcdcmd(0x8d);
        lcdstring("NIL");
        }
      
        ldelay(10);
        }
 void delay(unsigned int x)
 {
        unsigned int i;
        for(i=0;i<x;i++);
} 
 void lcdint()
{
         lcdcmd(0x38);
         delay(500);
         lcdcmd(0x01);
         delay(500);
         lcdcmd(0x0c);
         delay(500);
         lcdcmd(0x80);
         delay(500);
         lcdcmd(0x0e);
         delay(500);
    }
 
void lcdcmd(char value)
       {
         lcdport = value;
         rw=0;
         rs=0;
         en=1;
         delay(500);
         en=0;
       }   
void lcdstring(char *p)
      {
         while(*p!='\0')
          {
            lcddata(*p);
            delay(2000);
            p++;
          }
      }
 void lcddata(char value)
{
         lcdport=value;
         rs=1;
         rw=0;
         en=1; 
         delay(500);
         en=0;
}
void ldelay(unsigned int x)
          {
               unsigned int i,j;
           for (i=0;i<=x;i++)
           for (j=0;j<=1275;j++);
       }
void entry_door_open()                                        
{
lcdcmd(0xc0);
lcdstring("               ");
lcdcmd(0xc0);
lcdstring("OPENING DOOR");
door1_a=1;
door1_b=0;
delay(60000);
delay(60000);
}
void entry_door_close()
{
lcdcmd(0xc0);
lcdstring("               ");
lcdcmd(0xc0);
lcdstring("CLOSING DOOR");
door1_a=0;
door1_b=1;
delay(60000);
delay(60000);
}
void entry_door_stop()
{
lcdcmd(0xc0);
lcdstring("               ");
lcdcmd(0xc0);
lcdstring("DOOR CLOSED");
door1_a=0;
door1_b=0;
delay(60000);
delay(60000);
lcdcmd(0xc0);
lcdstring("               ");
}
void exit_door_open()
{
lcdcmd(0xc0);
lcdstring("               ");
lcdcmd(0xc0);
lcdstring("OPENING DOOR");
door2_a=0;
door2_b=1;
delay(60000);
delay(60000);
}
void exit_door_close()
{
lcdcmd(0xc0);
lcdstring("               ");
lcdcmd(0xc0);
lcdstring("CLOSING DOOR");
door2_a=1;
door2_b=0;
delay(60000);
delay(60000);
}
void exit_door_stop()
{
lcdcmd(0xc0);
lcdstring("               ");
lcdcmd(0xc0);
lcdstring("DOOR CLOSED");
door2_a=0;
door2_b=0;
delay(60000);
delay(60000);
lcdcmd(0xc0);
lcdstring("               ");
}