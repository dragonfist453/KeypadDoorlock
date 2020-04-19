# KeypadDoorlock
This is a project on the ARM7 LPC2148 purely in embedded C. 
The idea is to implement a door lock system guarded by a certain number pattern.

## Features
1. Lock the door
By pressing a certain key, the door is locked by the rotation of a servo motor

2. Unlock the door
By pressing a certain key, the door is unlocked if the right code is entered. If wrong, a buzzer rings to indicate incorrect attempt

3. Set the pattern
By pressing a certain key, the pattern may be set according to user by entering the previous pattern

4. Reset the pattern
By pressing a certain key, the manufacturer may reset it to a default pattern by entering manufacturer's code after pressing the key.

## Assumptions
1. Designs of the lock were assumed.
2. Pin numbers of servo were put as a default P0.1 which can be changed later on finding the right pin number for servo input
