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








void metre_test(){ //function to travel forward one metre
    uint16_t lcounter = 0;        // Variable to hold a count of the number of pulses received
    uint16_t rcounter = 0;        // Variable to hold a count of the number of pulses received
    float pwm_increment = 0.01f;
    int inccount = 0; //counts how many times the wheel speed has been incremented
    // Apply power to motors
    Wheel.Speed(0.37f,0.52f);
    lcounter = 0;
    rcounter = 0;
    pwm_increment = 0.01f;
    inccount = 0;
   

    // This loops runs for 1 metre
    while((lcounter < 93) && (rcounter < 93     )){
        
        // Check to see if we have received a new pulse
        if(left_encoder.pulseReceived()>0){
            lcounter++;
            if(lcounter>rcounter){
                Wheel.Speed(Wheel.getSpeedRight()+pwm_increment,Wheel.getSpeedLeft()); //increase right wheel speed
                inccount +=1;
            }
            printf("Speed is %f %f counters are %i %i pwm is %f \n",Wheel.getSpeedLeft(),Wheel.getSpeedRight(),lcounter,rcounter, pwm_increment);
            
        }
        // Check to see if we have received a new pulse
        if(right_encoder.pulseReceived()>0){
            rcounter++;
            if(rcounter>lcounter){
                Wheel.Speed(Wheel.getSpeedRight(),Wheel.getSpeedLeft()+pwm_increment); // increase left wheel speed
                inccount +=1;
            }
            printf("Speed is %f %f counters are %i %i pwm is %f \n",Wheel.getSpeedLeft(),Wheel.getSpeedRight(),lcounter,rcounter, pwm_increment);
        }
       
       /*if((lcounter > 50)&&(rcounter > 50)){
            pwm_increment = 0;
        }*/
        
        
    }
    Wheel.Stop();
}





void turn_test(){ //function to rotate 180 degrees
          
    uint16_t lcounter = 0;        // Variable to hold a count of the number of pulses received
    uint16_t rcounter = 0;        // Variable to hold a count of the number of pulses received
    float pwm_increment = 0.02f;
    // Apply power to the left motor only 
    Wheel.Speed(0.3f,-0.4f);
   

    // This loop runs for 180 degrees
    while((lcounter < 21) && (rcounter < 21)){
        
        // Check to see if we have received a new pulse
        if(left_encoder.pulseReceived()>0){
            lcounter++;
            if(lcounter>rcounter){
                Wheel.Speed(Wheel.getSpeedRight()+pwm_increment,Wheel.getSpeedLeft());
            }
            printf("Speed is %f %f \n",Wheel.getSpeedLeft(),Wheel.getSpeedRight());
            
        }

        if(right_encoder.pulseReceived()>0){
            rcounter++;
            if(rcounter>lcounter){
                Wheel.Speed(Wheel.getSpeedRight(),Wheel.getSpeedLeft()-pwm_increment);
            }
        }
        
    }
    Wheel.Stop();
}




int code_sec=0;
int main ()
{

    
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
    
   //
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

            if (myButton==1)
            {
                Buzz(int (1));

                code_sec= 4;

            wait_us(1500000);

             
            }

        }
    }

    if (code_sec== 1){

    
     while(true){
    

        // Write the parts of your code which should run in a loop between here..
     // simple_test();
   

   
   // go forwarrd for 12cm
   Wheel.Speed(0.6f,0.8f);//Forward 80%
   wait_us(600000);

    // go forwarrd for 12cm
    Wheel.Speed(0.6f,0.8f);//Forward 80%
    wait_us(500000);


    // little turn right 
    Wheel.Speed(-0.8f,0.8f);//Forward 80%
    wait_us(80000);

  

    // go forwarrd for 18 cm
   Wheel.Speed(0.6f,0.8f);//Forward 80%
   wait_us(800000);

   Wheel.Stop();
   wait_us(100000);

    
    // go forwarrd for 20 cm
   Wheel.Speed(0.6f,0.8f);//Forward 80%
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
   wait_us(700000);
  


   
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
   Wheel.Speed(0.6f,0.8f);//Forward 80%
   wait_us(2000000);



   //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.9f);//Forward 80%
   wait_us(1800000);

 
   // second turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

    //stop wheels for sometime
   Wheel.Stop();
   wait_us(100000);


    // go forwarrd for 30 cm
   Wheel.Speed(0.6f,0.8f);//Forward 80%
   wait_us(300000);

    //stop wheels for sometime
   Wheel.Stop();
   wait_us(100000);

   
   // second turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(700000);



    // go forwarrd for 50 cm
   Wheel.Speed(0.6f,0.8f);//Forward 80%
   wait_us(1700000);

   //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.9f);//Forward 80%
   wait_us(1500000);
 
 


    // third turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

   
    Wheel.Stop();
   wait_us(100000);

    //go forward
   Wheel.Speed(0.8f,0.6f);//Forward 80%
   wait_us(300000);

    Wheel.Stop();
   wait_us(100000);

    // third turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(700000);

    // go forwarrd for 50 cm
   Wheel.Speed(0.6f,0.8f);//Forward 80%
   wait_us(1700000);


    //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.6f);//Forward 80%
   wait_us(1500000);

    Wheel.Stop();
   wait_us(100000);

    // forth turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

    Wheel.Stop();
   wait_us(100000);

   //go forward
   Wheel.Speed(0.8f,0.6f);//Forward 80%
   wait_us(300000);

    Wheel.Stop();
   wait_us(100000);

    // forth turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(700000);

    // go forwarrd for 50 cm
   Wheel.Speed(0.6f,0.8f);//Forward 80%
   wait_us(2000000);


    //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.6f);//Forward 80%
   wait_us(1700000);

    // fifth turn right 
   Wheel.Speed(-0.8f,0.8f);//Forward 80%
   wait_us(750000);

    Wheel.Stop();
   wait_us(100000);

   //go forward
   Wheel.Speed(0.8f,0.6f);//Forward 80%
   wait_us(300000);

    Wheel.Stop();
   wait_us(100000);

    // fifth turn left
   Wheel.Speed(0.7f,-0.5f);//Forward 80%
   wait_us(700000);

    // go forwarrd for 50 cm
   Wheel.Speed(0.6f,0.8f);//Forward 80%
   wait_us(2000000);


    //go reverse for 50 cm
   Wheel.Speed(-0.8f,-0.6f);//Forward 80%
   wait_us(1700000);


    Wheel.Stop();
   wait_us(10000000);



    }

    }

        // ..and here
    

if (code_sec == 2){

    


    //go forward
    Wheel.Speed(0.6f,0.8f);//Forward 80%
    wait_us(300000);

    // third turn right 
    Wheel.Speed(-0.8f,0.8f);//Forward 80%
    wait_us(800000);

    //go forward
    Wheel.Speed(0.5f,0.8f);//Forward 80%
    wait_us(100000);
  

    Wheel.Stop();
    wait_us(100000);


    //go forward
    Wheel.Speed(0.5f,0.9f);//Forward 80%
    wait_us(1500000);

    // little turn left
    Wheel.Speed(0.8f,-0.8f);//Forward 80%
    wait_us(120000);

   Wheel.Stop();
    wait_us(100000);

    //go forward
    Wheel.Speed(0.5f,0.9f);//Forward 80%
    wait_us(1000000);



    // third turn left
    Wheel.Speed(0.8f,-0.8f);//Forward 80%
    wait_us(600000);



    //go forward
    Wheel.Speed(0.6f,0.8f);//Forward 80%
    wait_us(1500000);

    Wheel.Stop();
    wait_us(100000);

    //go forward
    Wheel.Speed(0.6f,0.8f);//Forward 80%
    wait_us(1500000);

    Wheel.Stop();
    wait_us(100000);


    //go reverse for 50 cm
    Wheel.Speed(-0.8f,-0.8f);//Forward 80%
    wait_us(1500000);

    Wheel.Stop();
    wait_us(100000);

    // little turn right
    Wheel.Speed(-0.8f,0.8f);//Forward 80%
    wait_us(200000);


    //go reverse for 50 cm
    Wheel.Speed(-0.6f,-0.8f);//Forward 80%
    wait_us(1500000);


    // third turn right 
    Wheel.Speed(-0.8f,0.8f);//Forward 80%
    wait_us(800000);

    Wheel.Stop();
    wait_us(100000);

    //go forward
    Wheel.Speed(0.6f,0.8f);//Forward 80%
    wait_us(100000);

    // third turn left
    Wheel.Speed(0.8f,-0.8f);//Forward 80%
    wait_us(600000);

     //go forward
    Wheel.Speed(0.6f,0.8f);//Forward 80%
    wait_us(1500000);

    Wheel.Stop();
    wait_us(100000);

    //go forward
    Wheel.Speed(0.6f,0.8f);//Forward 80%
    wait_us(1500000);

    Wheel.Stop();
    wait_us(100000);


    //go reverse for 50 cm
    Wheel.Speed(-0.8f,-0.8f);//Forward 80%
    wait_us(1500000);

    Wheel.Stop();
    wait_us(100000);

    // little turn right
    Wheel.Speed(-0.8f,0.8f);//Forward 80%
    wait_us(200000);


    //go reverse for 50 cm
    Wheel.Speed(-0.6f,-0.8f);//Forward 80%
    wait_us(1500000);






    








    






  

    
}
//Travel 1 metre and return with noise for Task B
if (code_sec==3){ 
printf("ran");
metre_test();
ThisThread::sleep_for(std::chrono::milliseconds(1000));
turn_test();
ThisThread::sleep_for(std::chrono::milliseconds(1000));
metre_test();

ThisThread::sleep_for(std::chrono::milliseconds(1000));
turn_test();
Megalovania(2);


}
// 1 metre straight line
if (code_sec==4){ 
   metre_test(); 
}

}





