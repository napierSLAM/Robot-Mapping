# Robot-Mapping
A simple autonomous mapping bot for Napier 17/18 Yr 3 Computer School Group Project
# Code for DC Motors

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

This was a nice 'dumb' bot that acted as a POC for a noving bot

