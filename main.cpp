#include "mbed.h"
#include "motor.h"
#include "tunes.h"
#include "pwm_tone.h"
#include "PROJ100_Encoder.h"
#include "PROJ100_Encoder_Tests.h"

#define TIME_PERIOD 10             //Constant compiler Values here 10 equates to 10ms or 100Hz base Frequency
#define ENCODER_PIN_LEFT            D8
#define ENCODER_PIN_RIGHT           D6 
#define PULSES_PER_ROTATION         20
#define DEBOUNCE_US                 30000


void myOneMetreCode(void){

    //do my 1 metre movement

printf("1 metre\n");

jingle_bells(2);


}


DigitalIn microswitch1(D4);         //Instance of the DigitalIn class called 'microswitch1'
DigitalIn microswitch2(D3);         //Instance of the DigitalIn class called 'microswitch2'
DigitalIn myButton(USER_BUTTON);    //Instance of the DigitalIn class called 'myButton'   
DigitalOut greenLED(LED1);          //Instance of the DigitalOut class called 'greenLED'

Motor Wheel(D13,D11,D9,D10);      //Instance of the Motor Class called 'Wheel' see motor.h and motor.cpp

PROJ100_Encoder right_encoder (ENCODER_PIN_RIGHT,PULSES_PER_ROTATION);  //Instance of the PROJ100Encoder class called 'right_encoder'
PROJ100_Encoder left_encoder(ENCODER_PIN_LEFT,PULSES_PER_ROTATION);     //Instance of the PROJ100Encoder class called 'left_encoder'

UnbufferedSerial ser(USBTX,USBRX,115200);   // Serial object for printing info

int code_sec=0;
int main ()
{


   /*  if(myButton==1){
        code_sec = 1;
    }

    wait_us(2000000);

    if (myButton==1){
        code_sec = 2;
    }
    if (code_sec ==1){
        */

    
    // Clear the terminal and print an intro
    printf("\033[2J\033[1;1H\r\n");
    printf("Plymouth University PROJ100 2023/24 Optical Encoder Demonstration\n\r");

    // Set the PWM frequency
    Wheel.Period_in_ms(TIME_PERIOD);                

    // Ensure our motors and encoders are stopped at the beginning
    right_encoder.stop();
    left_encoder.stop();
    Wheel.Stop();

    // The encoder pulses can be noisy and so are debounced within the class
    // You can experiment with changing the debouce time if you wish
    left_encoder.setDebounceTimeUs(DEBOUNCE_US);
    right_encoder.setDebounceTimeUs(DEBOUNCE_US);

    // Wait for the blue button to be pressed
    printf("Press Blue Button To Begin\n\r");
    while (myButton == 0){greenLED = !greenLED; ThisThread::sleep_for(100ms);}

    // Start the encoders
    left_encoder.start();
    right_encoder.start();

    /*********************ENCODER TESTS***************/
    // These contain while(1) loops so ensure that they are removed or commented out when running your own code
    // If these lines are left in the lines below will never run
    /*************************************************/
// speed_test();
    
    //new_test();


   //jingle_bells(2);
   
   
   
   while(true){

     

        //   if(code_sec==0){
        //poush beads
        //    }
       //else{
       // other
    

        // Write the parts of your code which should run in a loop between here..
 // simple_test();
   

   
   // go forwarrd for 12cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(500000);

   // little turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(80000);

  
    // go forwarrd for 18 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(800000);

   Wheel.Stop();
   wait_us(100000);

    
    // go forwarrd for 20 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(1000000);


   // little turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(80000);

   
   //go reverse for 25 cm
   Wheel.Speed(-0.8f,-0.9f);//Forward 80%
   wait_us(1000000);


   // little turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(120000);

   
    Wheel.Stop();
   wait_us(100000);


   //go reverse for 25 cm
   Wheel.Speed(-0.8f,-0.9f);//Forward 80%
   wait_us(900000);

    // go forwarrd for 30 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(1000000);


   // little turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(80000);

    Wheel.Stop();
   wait_us(100000);



    // go forwarrd for 30 cm
   Wheel.Speed(0.7f,0.8f);//Forward 80%
   wait_us(1000000);

   
    Wheel.Stop();
   wait_us(100000);


   //go reverse for 30 cm
   Wheel.Speed(-0.7f,-0.8f);//Forward 80%
   wait_us(1000000);


    // little turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(110000);


   //go reverse for 30 cm
   Wheel.Speed(-0.7f,-0.8f);//Forward 80%
   wait_us(1000000);

    
    Wheel.Stop();
   wait_us(100000);
  

    // first turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

    //stop wheels for sometime
   Wheel.Stop();
   wait_us(100000);


   //go forward for 50 cm
   Wheel.Speed(0.7f,0.8f);//Forward 80%
   wait_us(2000000);
    
   Wheel.Stop();
   wait_us(100000);

    //go reverse for 30 cm
   Wheel.Speed(-0.8f,-0.9f);//Forward 80%
   wait_us(1200000);


  
    // first turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(1000000);

   // go forwarrd for 50 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(1500000);
 

   //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.9f);//Forward 80%
   wait_us(1800000);

    Wheel.Stop();
   wait_us(100000);


    // second turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(700000);

   
    Wheel.Stop();
   wait_us(100000);

    //go forward
   Wheel.Speed(0.8f,0.6f);//Forward 80%
   wait_us(4000000);

    Wheel.Stop();
   wait_us(100000);

    //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.6f);//Forward 80%
   wait_us(3000000);

    Wheel.Stop();
   wait_us(100000);

    // third turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(200000);

     Wheel.Stop();
   wait_us(100000);

   //go forward
   Wheel.Speed(0.8f,0.6f);//Forward 80%
   wait_us(4000000);

    Wheel.Stop();
   wait_us(100000);

    //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.6f);//Forward 80%
   wait_us(3000000);





   









  
    





        // ..and here

    }


if (code_sec==2){

void myOneMetreCode();

}
}
