/*
 Name:		DMX_WallFader.ino
 Created:	7/14/2015
 Author:	Nathan Durnan
*/
#include <DmxSimple.h>
#include <BitBool.h>
#include "Fader.h"
#include "Ramp.h"

/*------------------------------------------
	DMX OUTPUT CHANNEL DEFINITIONS
	--> These can be edited based on the DMX Addressing of each zone/fixture
	--> Address number must be between 1 to DMX_CHANNEL_BLOCK (see Fader.h)
	--> New fixtures/zones can be added using the "#define {name} {value}" format.
	\/\/\/ EDIT BELOW \/\/\/
------------------------------------------*/
#define DMX_HOUSE      1 // Main House Ceiling Lights
#define DMX_STAGE_MAIN 2 // Stage Ceiling Lights - Center Zone
#define DMX_STAGE_SIDE 6 // Stage Ceiling Lights - Side Zone
#define DMX_OVERFLOW   7 // Overflow Seating Ceiling Lights
#define DMX_ENTRY      8 // Entryway Ceiling Lights
/*------------------------------------------
	END DMX OUTPUT CHANNEL DEFINITIONS
------------------------------------------*/

/*------------------------------------------
	FADER CHANNEL DEFINITIONS
------------------------------------------*/
#define FADER_ENTRY    0  // Entryway Ceiling Lights
#define FADER_HOUSE    1  // Main House Ceiling Lights
#define FADER_STAGE    2  // All Stage Ceiling Lights
#define FADER_CHANNELS 3  // Total number of Faders defined for the controller.
Fader Channel[FADER_CHANNELS]; // Fader Channel Object
/*------------------------------------------
	END FADER CHANNEL DEFINITIONS
------------------------------------------*/

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Serial.println("<setup...>");
	setup_io();
	/*------------------------------------------
		CONFIGURE FADER CHANNEL MAPPING
		--> Edit the lines below to change which
			DMX channels are controlled by each Fader.
		--> One Fader can control multiple DMX channels.
		--> Do NOT map a DMX channel to multiple Faders!
			(The output will be unstable)
		\/\/\/ EDIT BELOW \/\/\/
	------------------------------------------*/
	Channel[FADER_ENTRY].setDmxMap(DMX_ENTRY, true);
	Channel[FADER_HOUSE].setDmxMap(DMX_HOUSE, true);
	Channel[FADER_STAGE].setDmxMap(DMX_STAGE_MAIN, true);
	Channel[FADER_STAGE].setDmxMap(DMX_STAGE_SIDE, true);
	/*------------------------------------------
		END FADER CHANNEL MAPPING
	------------------------------------------*/
	Serial.println("<End setup>");
}

// the loop function runs over and over again until power down or reset
void loop() {
	for (byte i = 0; i < FADER_CHANNELS; i++)
	{
		Channel[i].update();
	}
	delay(RAMP_UPDATE_DELAY);  // slow down the loop so fading is visible
}

// Configure the io connections
void setup_io() {
	// Set up DMX Interface
	DmxSimple.usePin(3);
	DmxSimple.maxChannel(DMX_CHANNEL_BLOCK);
	// Assign channels DMX Output Universe
	for (byte i = 0; i < FADER_CHANNELS; i++)
	{
		Channel[i].setDmxUniverse(&DmxSimple);
		Channel[i].clearDmxMap();
	}
	// Assign IO Pins
	/* 1st Fader */
	Channel[FADER_ENTRY].setFaderPin(0);
	Channel[FADER_ENTRY].setOffPin(8);
	Channel[FADER_ENTRY].setOnPin(9);
	/* 2nd Fader */
	Channel[FADER_HOUSE].setFaderPin(1);
	Channel[FADER_HOUSE].setOffPin(12);
	Channel[FADER_HOUSE].setOnPin(10);
	/* 3rd Fader */
	Channel[FADER_STAGE].setFaderPin(2);
	Channel[FADER_STAGE].setOffPin(13);
	Channel[FADER_STAGE].setOnPin(11);

}