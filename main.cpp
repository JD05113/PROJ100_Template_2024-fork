#include "mbed.h"
#include "motor.h"
#include "tunes.h"
#include "pwm_tone.h"
#include "PROJ100_Encoder.h"
#include "PROJ100_Encoder_Tests.h"
#include <chrono>
#include <cstdint>
#include <cstdio>

#define TIME_PERIOD 10             //Constant compiler Values here 10 equates to 10ms or 100Hz base Frequency
#define ENCODER_PIN_LEFT            D8
#define ENCODER_PIN_RIGHT           D6 
#define PULSES_PER_ROTATION         20
#define DEBOUNCE_US                 30000




DigitalIn microswitch1(D4);         //Instance of the DigitalIn class called 'microswitch1'
DigitalIn microswitch2(D3);         //Instance of the DigitalIn class called 'microswitch2'
DigitalIn myButton(USER_BUTTON);    //Instance of the DigitalIn class called 'myButton'   
DigitalOut greenLED(LED1);          //Instance of the DigitalOut class called 'greenLED'

Motor Wheel(D13,D11,D9,D10);      //Instance of the Motor Class called 'Wheel' see motor.h and motor.cpp

PROJ100_Encoder right_encoder (ENCODER_PIN_RIGHT,PULSES_PER_ROTATION);  //Instance of the PROJ100Encoder class called 'right_encoder'
PROJ100_Encoder left_encoder(ENCODER_PIN_LEFT,PULSES_PER_ROTATION);     //Instance of the PROJ100Encoder class called 'left_encoder'

UnbufferedSerial ser(USBTX,USBRX,115200);   // Serial object for printing info

int32_t left_pulse_time;
int32_t right_pulse_time;
int right_encoder_count;
int left_encoder_count;
int metre_flag = 0;
int turn_flag = 0;
int pulse_delay = 1;


void ForwardDistance(){
    Wheel.Speed(0.8f,0.9f);
    while(metre_flag == 0){
        printf("right encoder %c",right_encoder_count);
        left_pulse_time = left_encoder.getLastPulseTimeUs();
        right_pulse_time = right_encoder.getLastPulseTimeUs();
        if(left_pulse_time > 0){
            left_encoder_count += 1;


        }
        if(right_pulse_time > 0){
            right_encoder_count += 1;
        }
        if((left_encoder_count > 44)||(right_encoder_count > 44)  ){
            Wheel.Stop();
            metre_flag = 1;
        }
        ThisThread::sleep_for(std::chrono::milliseconds(pulse_delay));
    }

   // uint16_t PROJ100_Encoder::getPulsesPerRotation(){
   // return _pulses_per_rotation;
}
void FastRotate(){
    left_pulse_time = 0;
    right_pulse_time = 0;
    turn_flag = 0;
    Wheel.Speed(0.6f,-0.6f);
    while(turn_flag == 0){
        left_pulse_time = left_encoder.getLastPulseTimeUs();
        right_pulse_time = right_encoder.getLastPulseTimeUs();
        if(left_pulse_time > 0){
            left_encoder_count += 1;


        }
        if(right_pulse_time > 0){
            right_encoder_count += 1;
        }
        if((left_encoder_count > 10)||(right_encoder_count > 10)  ){
            //diameter of turning circle is 147mm, half circ is 461.8  mm
            //461.8/21.99mm(1 pulse) = 20.99 pulses
            //both wheels move so half?
            Wheel.Stop();
            turn_flag = 1;
        }
        ThisThread::sleep_for(std::chrono::milliseconds(pulse_delay));
    }
}


void myOneMetreCode(){
    ForwardDistance();
    FastRotate();
    ForwardDistance();
    FastRotate();
    
}




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
    /***********************************************/
 //speed_test();
    
    //new_test();

   Buzz(int (1));

   code_sec= 1;


   wait_us(1500000);

   if (myButton==1)
    { 
        Buzz(int (1));

        code_sec= 2;
       
        wait_us(1500000);

        if (myButton==1)
        {

            Buzz(int (1));

            code_sec= 3;

            wait_us(1500000);

        }
    }

    if (code_sec== 1){

    
     while(true){

  

     

        //   if{
        //poush beads
        //    }
       //else{
       // other
    

        // Write the parts of your code which should run in a loop between here..
     // simple_test();
   

   

   // go forwarrd for 12cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(600000);

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
   wait_us(800000);


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
  
/*
   // first turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

    //stop wheels for sometime
   Wheel.Stop();
   wait_us(100000);

    // go forwarrd for 30 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(10000);


   
    // first turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(700000);

   // go forwarrd for 50 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(1500000);
 

   //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.9f);//Forward 80%
   wait_us(1800000);

    Wheel.Stop();
   wait_us(100000);
   */

   
   // first turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

    //stop wheels for sometime
   Wheel.Stop();
   wait_us(100000);

    // go forwarrd for 30 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(300000);

    //stop wheels for sometime
   Wheel.Stop();
   wait_us(100000);

   
   // first turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(600000);



    // go forwarrd for 50 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(1700000);

   //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.9f);//Forward 80%
   wait_us(1700000);

 
   // first turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

    //stop wheels for sometime
   Wheel.Stop();
   wait_us(100000);


    // go forwarrd for 30 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(300000);

    //stop wheels for sometime
   Wheel.Stop();
   wait_us(100000);

   
   // first turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(700000);



    // go forwarrd for 50 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(1500000);

   //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.9f);//Forward 80%
   wait_us(1500000);






   // go forwarrd for 50 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(1500000);
 
 


    // second turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

   
    Wheel.Stop();
   wait_us(100000);

    //go forward
   Wheel.Speed(0.8f,0.6f);//Forward 80%
   wait_us(3000000);

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
   wait_us(5000000);

    Wheel.Stop();
   wait_us(100000);

    //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.6f);//Forward 80%
   wait_us(4000000);

    // first turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

    //stop wheels for sometime
   Wheel.Stop();
   wait_us(100000);

    // go forwarrd for 30 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(100000);

    //stop wheels for sometime
   Wheel.Stop();
   wait_us(100000);

   
   // first turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(700000);



    // go forwarrd for 50 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(1500000);

   //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.9f);//Forward 80%
   wait_us(1800000);






   // go forwarrd for 50 cm
   Wheel.Speed(0.8f,0.9f);//Forward 80%
   wait_us(1500000);
 
 


    // second turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

   
    Wheel.Stop();
   wait_us(100000);

    //go forward
   Wheel.Speed(0.8f,0.6f);//Forward 80%
   wait_us(3000000);

    Wheel.Stop();
   wait_us(100000);

    //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.6f);//Forward 80%
   wait_us(3000000);

    Wheel.Stop();
   wait_us(100000);

      // go forwarrd for 18 cm
     Wheel.Speed(0.8f,0.9f);//Forward 80%
     wait_us(800000);

     Wheel.Stop();
     wait_us(100000);


    
      // go forwarrd for 20 cm
     Wheel.Speed(0.8f,0.9f);//Forward 80%
     wait_us(1000000);

    Megalovania(2);

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

     }

    }

    


   



        // ..and here
    

if (code_sec == 2){
    Megalovania(2);
}
if (code_sec==3){
printf("ran");
myOneMetreCode();
}

}
