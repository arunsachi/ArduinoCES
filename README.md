# ArduinoCES
Arduino Sketches for CES Lab

# IP2IR
This program sends IR signals using Arduino Ethernet corresponding to get requests from a web server.

## Version - 1.00

## Folders: 
1. Schematic - Schematic Circuit Diagram
2. Implementation - Source code
3. Testing - Output Screenshots

## IP and MAC configuration:
1. MAC of Arduino Ethernet is hard coded in the sketch
2. An IP belonging to the same local network as the Web Server is assigned to the Arduino.

## External library configuration: 
1. IRremote Arduino Library (https://github.com/shirriff/Arduino-IRremote/releases) page. 
2. Download the latest release. 
3. Extract the zip file 
4. Move the "IRremote" folder that has been extracted to your libraries directory already.

## Current Implementation Details:
The current implementation sends sample IR code whenever a get request is received from web server.

## Further Implementation: 
1. Issuing different commands on get request.
2. Switch case for different consumer devices.

## Testing Serial Communication
This can be done using a loopback test in Windows Hyperterminal.
Screenshots provided in the Testing folder

## Contributors
Arun Sachidanandan - 54781 <br />
Muhammad Umair - 52883
