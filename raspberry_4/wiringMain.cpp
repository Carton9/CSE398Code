#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringPi.h>
#include <softPwm.h>
#include "Motor.h"
#include "MJPEGWriter.h"
// #include <wiringSerial.h>
// #include <wiringPiI2C.h>
#include <unistd.h>
// #include "Adafruit_PWMServoDriver.h"
// #include "rfcomm-server.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include <thread>
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
using namespace cv;
using namespace std;
// void motor_control(int motor, int speed){
//   int dir=speed>0;
//   if (motor==0)
//   {
//     digitalWrite (24, dir) ;
//     digitalWrite (25, !dir) ;
//     softPwmWrite (23, abs(speed));
//   }else{
//     digitalWrite (28, dir) ;
//     digitalWrite (27, !dir) ;
//     softPwmWrite (26, abs(speed));
//   }
// }
MJPEGWriter test(7777);
VideoCapture cap;
void run(){
  Mat frame;
  cap >> frame;
  test.write(frame);
  test.start();
  while(cap.isOpened()){cap >> frame; test.write(frame); frame.release();}
  test.stop();
}
int main(int argc, char** argv)
{
  wiringPiSetup () ;
  // pinMode (24, OUTPUT) ;
  // pinMode (25, OUTPUT) ;

  // pinMode (28, OUTPUT) ;
  // pinMode (27, OUTPUT) ;
  
  // softPwmCreate (23, 0, 100) ;
  // softPwmCreate (26, 0, 100) ;
  Motor motor1(23,24,25);
  Motor motor2(26,28,27);



   
    bool ok = cap.open(0);
    if (!ok)
    {
        printf("no cam found ;(.\n");
        pthread_exit(NULL);
    }
    thread t1(run);
    // Mat frame;
    // cap >> frame;
    // test.write(frame);
    // frame.release();
    // test.start();
    // while(cap.isOpened()){cap >> frame; test.write(frame); frame.release();}
    // test.stop();
    cout << "TP01" << endl;
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        string data((char*)request.data());
        cout << "Command Get " << data << endl;
        int i=80;
        if (data=="FW"){
          motor1.motor_control(i);
          motor2.motor_control(i);
        }
        if (data=="BW"){
          motor1.motor_control(-1*i);
          motor2.motor_control(-1*i);
        }
        if (data=="LF"){
          motor1.motor_control(-1*i);
          motor2.motor_control(i);
        }
        if (data=="RG"){
          motor1.motor_control(i);
          motor2.motor_control(-1*i);
        }
        usleep(10000);
        motor1.motor_control(0);
        motor2.motor_control(0);
        // std::cout << "Received Hello" << std::endl;

        // //  Do some 'work'
        // sleep(1);

        // //  Send reply back to client
        // zmq::message_t reply (5);
        // memcpy (reply.data (), "World", 5);
        // socket.send (reply);
    }



  // while(1){
  //   for (int i = -100; i < 100; i++)
  //   {
  //     // softPwmWrite (23, i);
  //     // softPwmWrite (26, i);
  //     motor1.motor_control(i);
  //     motor2.motor_control(i);
  //     usleep(10000);
  //   }
  // }
  return 0;
}