# ArduinoDMX_WallFader
##Architectural lighting control over DMX using an Arduino hardware platform.

This project started out of frustration in finding a suitable architectural lighting interface that could control several zones of lights over DMX.  The primary challenges were:

- **DMX Interface:** Most off-the-shelf architectural lighting controls are designed around a direct analog interface or proprietary communication interface with the specific dimmer units that are installed.  The goal of this project was to have a generic DMX interface for architectural lighting control.
- **Simplicity:** The human interface needed to be simple and straightforward enough for a non-technical person to be able to walk into the room and turn on the lights without prior knowledge of the system.
- **Cost:** A handful of off-the-shelf controllers were found that meet the above requirements, but at a significantly high cost.  The Arduino platform provided a much lower cost alternative as well as the flexibility for customization.

##Hardware Design

### Controller

The original concept was built around an Arduino UNO, but could easily be adapted to any of the Arduino family.  The only limitations are the number of IO pins available.

The basic IO requirements are:

- (1x) Digital Output for DMX Output signal.
- Additional IO per Fader Channel
    - (1x) Analog Input
    - (1x) Digital Output (for standby light - optional)
    - (1x) PWM Output (for feedback light - optional)

The DMX output could be achieved using any of the methods described here:

- [http://playground.arduino.cc/Learning/DMX](http://playground.arduino.cc/Learning/DMX)
- [http://playground.arduino.cc/DMX/DMXShield](http://playground.arduino.cc/DMX/DMXShield)

Ultimately, the Tinker.it! [DMX Master Shield](https://store.arduino.cc/product/T040060) (other sources available) and [DMXSimple library](https://code.google.com/p/tinkerit/wiki/DmxSimple) were chosen for off-the-shelf simplicity and convenience.  Other shields and libraries are available and could be implemented for extended features (galvanic isolation, RDM, etc.), but were beyond the original scope of this project.

###Human Interface

The familiarity of a basic household light switch was desired for simplicity of operation.  Several models of switches are available with dimmer functionality as well.  The challenge with these off-the-shelf dimmer switches is that they are designed for controlling AC light fixtures.  For this project, all that is needed is the switch and potentiometer components from the dimmer switches.  All of the AC control circuitry can be bypassed or removed.  A walk-thru of the modifications to the original hardware used for this project can be found here:

[TBD...](TBD)

###Hardware Interface

Additional circuitry was required to connect the hardware dimmer switch to the Arduino controller.  The schematic is not complication and should only require basic soldering skills to create a suitable interface shield.  A schematic and diagrams for the original hardware used for this project can be found here:

[TBD...](TBD)

##Software Design

###Dependencies:

- **DMXSimple:** for DMX communication 
- **BitBool:** for mapping DMX output channels to Fader input channels

###Classes:

- **Fader:** the primary supporting class for this project.  It handles dimmer switch input, LED indicator output, DMX channel mapping, and DMX output.
- **Ramp:** a supporting class that limits the rate at which the output values can change to smooth out changes in lighting intensity.

###Compiling & Installation

This project can be compiled and uploaded to the hardware using the standard Arduino IDE.  Alternatively, the project can also be opened in Microsoft Visual Studio using the [Visual Micro Arduino plug-in](http://www.visualmicro.com/).