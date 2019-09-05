/*****************************************************************
	FPS_IDFinger.ino - Library example for controlling the GT-511C3 Finger Print Scanner (FPS)
	Created by Josh Hawley, July 23rd 2013
	Licensed for non-commercial use, must include this license message
	basically, Feel free to hack away at it, but just give me credit for my work =)
	TLDR; Wil Wheaton's Law

	Description: This sketch will attempt to identify a previously enrolled fingerprint
	saved in its database.
*****************************************************************/

#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

// FPS (TX) is connected to pin 8 (Arduino's Software RX)
// FPS (RX) is connected through a converter to pin 7 (Arduino's Software TX)
FPS_GT511C3 fps(8, 7); // (Arduino SS_RX = pin 8, Arduino SS_TX = pin 7)

void setup()
{
	Serial.begin(9600); //set up Arduino's hardware serial UART
  Serial1.begin(9600); //The pro micro uses a different serial protocol, which is defined with the Serial1 call
	delay(100);
	fps.Open();         //send serial command to initialize fps
	fps.SetLED(true);   //turn on LED so fps can see fingerprint
}

void loop()
{
  String idName[] = {"Ethan Rose", "Will Hammond" , "Javier Herrera", "Paul Kraus", "Chanseton Goodman", "Collin Newman", "Tristan Brownjohn",
  "Roberto Jimenez", "Santiago Romero", "Christian Ontiveros", "Katie Bird", "Shakira Avila", "Kyle Davis", "Elias Saucedo", "Michael Kavas", "Archer Hasbany"}; //It is critical that the index of the persons name is the same as their ID in the fps 
  
	// Identify fingerprint test
	if (fps.IsPressFinger()) // detects when a finger is present
	{
		fps.CaptureFinger(false);
		int id = fps.Identify1_N(); //temporary variable that stores current persons ID
		   
		if (id <200) // this number is dependent on the number of prints your scanner can hold, in my case it is 200, on the newest scanner it is 3000
		{//if the fingerprint matches, provide the matching template ID
			Serial.println(idName[id]); //prints the name that is at the index of the scanned ID to the arduinos COM port
      fps.SetLED(false);          //turns the fps led off to both signify a successful scan and prevent a double sign in
      delay(1000);
      fps.SetLED(true);     //turns the led bad on before the next loop
   
		}
	delay(200);
  }
}

