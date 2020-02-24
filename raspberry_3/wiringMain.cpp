#include <stdio.h>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include "Adafruit_PWMServoDriver.h"
#include "rfcomm-server.h"
#include "opencv2/opencv.hpp"
#include <vector>
using namespace cv;
using namespace std;
#define SERVOMIN  500 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  1000 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


String face_cascade_name = "haarcascade_frontalface_alt.xml";
 String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
 CascadeClassifier face_cascade;
 CascadeClassifier eyes_cascade;
 string window_name = "Capture - Face detection";
 RNG rng(12345);
 struct FaceLoc
 {
   int x;
   int y;
 };
 
FaceLoc detectAndDisplay( Mat frame )
{
  std::vector<Rect> faces;
  Mat frame_gray;
  int frame_y= frame.rows;
  int frame_x= frame.cols;
  // cout <<endl; 
  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );
    
  //-- Detect faces
  // resize(frame,frame_gray,frame.size(),0.5,0.5,INTER_CUBIC);
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(100, 100) );
  // face_cascade.detectMultiScale( frame, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
  Point center( frame_x*0.5, frame_y*0.5 );
  ellipse( frame, center, Size( 20, 20), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
// cout << "TP" << endl;
  FaceLoc f;
  f.x=0;
  f.y=0;
  for( size_t i = 0; i < faces.size(); i++ )
  {
    cout << faces[i].x+ faces[i].width*0.5-(frame_x*0.5) << " " <<  faces[i].y + faces[i].height*0.5-(frame_y*0.5)<<" "<< frame_x << " " <<frame_y << endl;
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
    f.x=faces[0].x+ faces[0].width*0.5-(frame_x*0.5);
    f.x=faces[0].y + faces[0].height*0.5-(frame_y*0.5);
  }
  imshow("this is you, smile! :)", frame);
  waitKey(1);
  return f;
        //   if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
 }
int main(int argc, char** argv)
{
    VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    cout << "tp1"<<endl;
    if(!cap.open(0))
        return 0;
      cout << "tp2"<<endl;
  printf ("Raspberry Pi - Gertboard Blink\n") ;
  wiringPiSetup () ;
  // int fd=wiringPiI2CSetup(0x70);
  Adafruit_PWMServoDriver pwm(0x40);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  int turn[3]={460,300,130};
  int rise[3]={420,400,250};
  int h=300;
  int v=400;
  rfcomm_server rout;
  rout<< "good news";
  pwm.setPWM(0, 0, turn[1]);
  pwm.setPWM(1, 0, rise[1]);
    face_cascade.load(face_cascade_name);
    for(;;)
    {
          Mat frame;
          // cout << i << endl;
          // cout << "tp3 " << frame <<endl;
          cap >> frame;
          if( frame.empty() ) continue; // end of video stream
          FaceLoc f=detectAndDisplay(frame);
          h+=-1*f.x*0.1;
          v+=-1*f.y*0.1;
          cout << h << " " << v << endl;
          if (h>turn[0])
          {
            h=turn[0];
          }
          if (h<turn[2])
          {
            h=turn[2];
          }
          if (v>rise[0])
          {
            v=rise[0];
          }
          if (v<rise[2])
          {
            v=rise[0];
          }
          pwm.setPWM(0, 0, h);
          pwm.setPWM(1, 0, v);
          // imshow("this is you, smile! :)", frame);
          // waitKey(10);
    }
    // cap.close();
    return 0;
}

    // for (int i = 0; i < dp2->length; i++)
    // {
    //     cout << hex << (uint)dp2->data[i] << " ";
    // }
    // cout << endl;
    // if (dp2->length<1)continue;
    
    // // cout << dp2->length ;
    // cout << "Value" << (cod<<dp2) << endl;

        // sh << dp;
    // cout  << "DP1" << dp->data << endl;

    // sh >>dp2;
    // if (dp2->length<1)continue;
    // cod>=dp2;
    // FloatArray fa;
    // memcpy(fa.data,dp2->data,40);
    // for (int i = 0; i < 10; i++)
    // {
    //   cout << fa.array[i] << " ";
    // }
    // cout << endl;
    


    // usleep(100000);



    // union FloatArray
// {
//   float array[10];
//   char data[sizeof(float)*10];
// };
// int main (void)
// {
  // printf ("Raspberry Pi - Gertboard Blink\n") ;
  // wiringPiSetup () ;
  // // int fd=wiringPiI2CSetup(0x70);
  // Adafruit_PWMServoDriver pwm(0x40);
  // pwm.begin();
  // pwm.setOscillatorFrequency(27000000);
  // pwm.setPWMFreq(SERVO_FREQ);
  // int turn[3]={460,300,130};
  // int rise[3]={420,400,250};
  // rfcomm_server rout;
  // rout<< "good news";
  
//   cout << "TP1" << endl;
//   cout << "TP2" << endl;
//   // cout << goodone<< endl;
//   pwm.setPWM(0, 0, turn[0]);
//   pwm.setPWM(1, 0, rise[0]);
//   for (int i = 0; i < 5; i++)
//   {
//     // string* goodone=new string;
//     // rout >> goodone;
//     string goodone=rout.readRF();
//     cout <<goodone.size()<<endl;
//     cout << goodone.substr(0,2) << endl;
//     if ((goodone)[0]=='M')
//     {
//       cout << "TP3" << endl;
//       pwm.setPWM(0, 0, turn[1]);
//       pwm.setPWM(1, 0, rise[1]);
//     }
//     else if ((goodone)[0]=='L')
//     {
//       cout << "TP4" << endl;
//       pwm.setPWM(0, 0, turn[0]);
//       pwm.setPWM(1, 0, rise[0]);
//     }
//     else if ((goodone)[0]=='O')
//     {
//       cout << "TP5" << endl;
//        rout.closeServer();
//        return 0;
//     }
//   }
  
//   rout.closeServer();
//   //  while (1)
//   //  {
//   //   int value;
//   //   cin >>value;

    
    
//   //  }
   
   
//   // cout << fd;
//   return 0 ;
// }

