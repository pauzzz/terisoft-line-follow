#include <QTRSensors.h> //not inherently in particle libraries... idk if that'll be an issue.


int num_sensors=8; //number of sensors we're using
int emit_pin=D0; //set emit pin to D0 for now - can change to open pin later
int Timeout=10000; //10 second time out for setting up the sensors and calib.
int calibrationCheck=0; //initialize calibration number
QTRSensorsRC qtrrc((unsigned char[]) {8,7,6,5,4,3,2,1}, num_sensors, Timeout, emit_pin);// define pin# later when I know which ones are free - prolly wont need all 8
unsigned int sensorValues[num_sensors]; //array of the number of sensors

//positioning

unsigned int position = qtrrc.readLine(sensorValues);
unsigned char k = 0;

int line1=sensorValues[1]; //value for sensor 1 and so on... remove if we use less sensors
int line2=sensorValues[2];
int line3=sensorValues[3];
int line4=sensorValues[4];
int line5=sensorValues[5];
int line6=sensorValues[6];
int line7=sensorValues[7];
int line8=sensorValues[8];

void setup() {

}


void loop() {
    
//CALIBRATION
do {
for (int i=0; i<400;i++) //400 made up num, can increase to extend calibration time.
{
    qtrrc.calibrate(); // reads sensors idk speed or frequency here - not arduino
}

digitalWrite(A0, LOW)// MAJOR!!! CHANGE A0 TO APPROPRIATE PIN LATER - runs once calibrations is finished - connect to an LED to say its finished.
calibrationCheck=0;
}

while (calibrationCheck != 100000)// i think this is the syntax for every 100 sec. calibration


calibrationCheck++;
}

