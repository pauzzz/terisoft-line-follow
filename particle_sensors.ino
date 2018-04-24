#include "QTRSensors.h" 	//not inherently in particle libraries... idk if that'll be an issue. upload to src/
#include "PhoBot.h"			// for motor
#include <string>

PhoBot go=PhoBot(9.0, 6.0);

int KD = 0.2; 	//experiment from 0-> 1 for good value
int KP = 5; 	//experiment from 1-> 10 for good value
int M1_DEFAULT_SPEED=130;
int M2_DEFAULT_SPEED=130;
int rightMaxSpeed=200;
int leftMaxSpeed=200;
int lastError;

int calibrationCheck=0;
int DEBUG = digitalRead(D3);//D3 random port for now, need to write debugging code


const int num_sensors=8; 		//number of sensors we're using - CHANGE if not using all 8
int emit_pin=D2; 		//set emit pin to D2 for now - can change to open pin later
int Timeout=10000; 		//10 second time out for setting up the sensors

QTRSensorsA qtra((unsigned char[]) {8,7,6,5,4,3,2,1}, num_sensors, Timeout, emit_pin);    // define pin# later when I know which ones are free - prolly wont need all 8
unsigned int sensorValues[num_sensors]; 													//array of the number of sensors

//positioning

unsigned int position = qtra.readLine(sensorValues);
unsigned char k = 0;

int line1=sensorValues[1]; 	//value for sensor 1 and so on... remove if we use less sensors
int line2=sensorValues[2];
int line3=sensorValues[3];
int line4=sensorValues[4];
int line5=sensorValues[5];
int line6=sensorValues[6];
int line7=sensorValues[7];
int line8=sensorValues[8];

void setup() {
pinMode(D2, INPUT);
pinMode(D0, OUTPUT);

//calibrate on setup
calibration();
}



void loop() {
//Error reporting and compensation

int error = position - 3500; 							//3500 is for 8 sensors

int motorSpeed = KD * error + KP * (error - lastError);
lastError = error;


	motorSpeedLimit(motorSpeed);
    
//CALIBRATION
do {
calibration();
}

while (calibrationCheck==1);//

if(DEBUG){
calibrationCheck++; // run calibration when debug
}
}

void calibration() {
for (int i=0; i<400;i++) //400 made up num, can increase to extend calibration time.
{
    qtra.calibrate(); // reads sensors idk speed or frequency here - not arduino
	delay(20); //added delay to ensure calibration finishes
}

digitalWrite(D0, LOW);//CHANGE D0 TO APPROPRIATE PIN LATER - runs once calibrations is finished - connect to an LED to say its finished.
calibrationCheck=0;
lastError=0;
}


void motorSpeedLimit(int MSpd){
	
//speed limiting

int leftMSpd = ((M1_DEFAULT_SPEED + MSpd)/(leftMaxSpeed))*100;	//the math should give us scaling to use for PhoBot -> PhoBot uses 0 to 100 duty
int rightMSpd = ((M2_DEFAULT_SPEED - MSpd)/(rightMaxSpeed))*100; 	//these will turn the bot - change signs if wrong direction

			
if (leftMSpd > 100 ) leftMSpd = 100; 			// prevent the motor from going beyond max speed
if (rightMSpd > 100 ) rightMSpd = 100;		// prevent the motor from going beyond max speed
if (leftMSpd < 0) leftMSpd = 0; 				// keep the motor speed positive
if (rightMSpd < 0) rightMSpd = 0; 			// keep the motor speed positive



go.setMotors("M1-F-"+String(leftMSpd)); 						//will this work? 
go.setMotors("M2-F-"+String(rightMSpd));
}