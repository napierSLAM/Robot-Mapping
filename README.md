# Robot-Mapping
A simple autonomous mapping bot for Napier 17/18 Yr 3 Computer School Group Project

# Initial Bot
The bot is moved by 2 DC motors controlled by an arduino

An initial build was done to get a moving bot that was aware of its environment
The bot had a single forward facing sonar, the HC-SR04
This was mounted on a servo that swept a range of 30 degrees
This enabled the bot to avoid anything that would be in sonar blind spot (detailed sonar talk in Robot-Mapping/sonar/notes.txt)
The DC motors were just off and on and direction.
When the bot detected an obstacle it would then move the servo 90 degrees left from forward and 90 degrees right from forward
A sonar reading was taken in these positions and the bot would then turn to face the direction that had the furthest obstacle
Or if no obstacle was in range, then a random side was chosen
(Code still to be uploaded to Robot-Mapping/obstacle_avoid/) 

This was a nice 'dumb' bot that acted as a POC for a moving bot

But the purpose is a mapping bot which has different needs

The bot needs awareness of where it is - either relative to a starting position or by using external info like GPS co-ords.  
The easiest for a basic demo is to make location awareness relative to an arbitary start position.  

For relative positioning, awareness needs to be maintained through 'traversing'

# Traversing 
Traversing is recording heading and distance travelled:

A heading is taken  
The bot moves  
The distance is recorded  
The bot turns  
A new heading is taken   
The bot moves  
The distance is recorded  
The bot turns  
A new heading is taken  
etc.  

## Distance
For this purpose, distance can be recorded using an optical sensor (see motor folder)  
A disc with slots cut in it is mounted on the inside (opposite to wheel) of a drive shaft  
The drive shaft is connected to a geared dc motor  

The optical sensor has a slot with a beam of infra red light.  
The disk sits in the slot and as the disk spins the slots break the beam. A count is kept of each slot.  
(For the test bot each slot represents 10.4mm of travel, which is going to be treated as 10mm (1cm).)  
Without adjustment and calibration this method is somewhat inaccurate, but close enough for the moment.  
(See motors folder for more discussion on this point.)  

## Heading
A simple magnometer, reading in 3 axis, can be used for heading.  
The magnometer can take a compass reading (a reading relative to magnetic North,) and then turn to the cardinal points etc.
A slightly simpler method (though prone to errors) is to use relative headings.
The bot turns a certain number of +ve/-ve degrees relative to it's current position.
Again adjustment and calibration is needed to make this accurate but for present purposes it suffices

## Mapping
The purpose of this bot is map the locale, so sensor readings are taken using sonar(, see Robot-Mapping/sonar/notes.txt).   
The sonar gives a reading in the form of distance to an obstacle by sending a soundwave out, which will hit a solid object and bounce (echo) back.  
The time for the echo to return is measured and then converted to a distance
Once the bot has spatial awareness or 'localisation', these readings can then be plotted relative to the bot, creating a map of the environment.

### Plotting Readings
The most important issue in plotting the readings is the resolution, meaning the level of detail.
A simple way to think of this, is to consider a square room 500cm by 500cm with a grid superimposed on top.
- If the grid was made of squares 250cm by 250cm there would be 4 squares
- If the grid was made of squares 100cm by 100cm there would be 25 squares
- If the grid was made of squares 50cm by 50cm there would be 100 squares
- If the grid was made of squares 20cm by 20cm there would be 625 squares

The more squares, the higher the resoltion.  
As the bot takes readings, it determines if a square is 'occupied' and records this information

For this demo bot the chosen resolution is 20cm by 20cm. A full discussion of this choice can be found in the mapping folder, but one reason is that the bot has a footprint of approx 18cm x 18cm.





