/** Simple On-board LED flashing program - written by Derek Molloy
    for the ee402 module 
    This program uses USR LED 0 and can be executed in three ways:
         makeLED on
         makeLED off
         makeLED flash  (flash at 100ms intervals - on 50ms/off 50ms)
         makeLED status (get the trigger status)
*/

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define LED0_PATH "/sys/class/leds/beaglebone:green:usr0"
#define LED1_PATH "/sys/class/leds/beaglebone:green:usr1"

// chosen LED Path
#define LED LED1_PATH

void removeTrigger(){
   // remove the trigger from the LED
   std::fstream fs;
   fs.open( LED "/trigger", std::fstream::out);
   fs << "none";
   fs.close();
}

int main(int argc, char* argv[]){
   if(argc!=2){
	cout << "Usage is makeLED and one of: on, off, flash or status" 
<< endl;
	cout << "e.g. makeLED flash" << endl;
   }

   string cmd(argv[1]);
   std::fstream fs;
   cout << "Starting the LED flash program" << endl;
   cout << "The LED Path is: " << LED << endl;     

   // select whether it is on, off or flash
   if(cmd=="on"){
     cout << "Turning on LED" << endl;
        removeTrigger();
	fs.open (LED "/brightness", std::fstream::out);
	fs << "1";
	fs.close();
   }
   else if (cmd=="off"){
     cout << "Turning off LED" << endl;
        removeTrigger();
	fs.open (LED "/brightness", std::fstream::out);
	fs << "0";
	fs.close();
   }
   else if (cmd=="flash"){
     cout << "Flashing LED" << endl;
        fs.open (LED "/trigger", std::fstream::out);
	fs << "timer";
	fs.close();
	fs.open (LED "/delay_on", std::fstream::out);
	fs << "50";
	fs.close();
	fs.open (LED "/delay_off", std::fstream::out);
	fs << "50";
	fs.close();
   }
   else if (cmd=="status"){
	// display the current trigger details
	fs.open( LED "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line;
	fs.close();      
   }
   else{
	cout << "Invalid command" << endl;
   }
   cout << "Finished the LED flash program" << endl;
   return 0;
}
