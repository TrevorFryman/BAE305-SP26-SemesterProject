 # Semester Project Online Design File

 **Group Members:**
   * Gretchen Wahoff
   * Jasmyne Huynh
   * Emily Culver
   * Cole Crumbaker
   * Trevor Fryman
     
# Summary
Unattended cooking is the leading cause of house fires in the US. Roughly 70% of people admit to leaving the kitchen unattended while cooking. There is also a risk of harm to children, energy waste, accidental gas leaks, or electrical overheating. ​

The purpose of this project was to create a system with automatic detection and shut-off to reduce preventable hazards and unnecessary energy consumption. We decided that to achieve this, our system should detect whether a pan is on the stovetop and turn it off when it isn't, and also be capable of turning the stove off after a set timer runs out. To better allow the user to understand the system, a green LED will be on when a pan is detected, and a red LED will blink and stay on when the system has turned the stove off. 

This project allowed us to practice and demonstrate a variety of engineering skills, such as wiring, coding, scrum, and team collaboration. 

Project Video Description: 

# Design Description
Engineering Drawings, code, and assembly instructions are complete and correct

<p align="center">
<img width="500" height="655" alt="image" src="https://github.com/user-attachments/assets/1b114d6f-ee6c-4344-8506-00b20bf07833" /> <br>
<em>Figure 1. Circuit schematic.<em>
<p>

<p align="center">
<img width="500" height="655" alt="Screenshot 2026-04-16 at 4 32 32 PM" src="https://github.com/user-attachments/assets/bc0cc32b-d25f-4fbf-b44f-cc24b090dd3f" /> <br>
<em>Figure 2. Wiring Diagram <em>
<p></p>

``` cpp

```
# Testing Description
All test equipment (model numbers) and procedures are fully described
Test equipment:
- Our system
- A pot or pan
- A phone timer
  
A series of tests were conducted to verify that our system works properly. To start off, we tested the timer mechanism by putting our pot in place and turning the knob on the front of the control board to turn the burner on. Once this was done, we set and started our timer. We also started a phone timer to see if our system timer is accurate. Once a series of ten tests are finished, we moved on to the next set of tests. For these tests, we verified that the ultrasonic sensor worked properly. In order to do this, we set a pot on the burner for 10 seconds and then removed it and started a timer on a phone to verify that the burner would not turn off for 90 seconds. After ten tests were done, we did our final test. This test was the verify that the ultrasonic sensor would de activate the 90 second burner turn off count down when a pot or pan is placed back on the burner after being removed. For this test, we set the pot/ pan on the burner for 10 seconds and then removed it for 10. Once the 10 seconds was up, we replaced the pot on the burner while keeping our original timer going from when the pot was initially removed. Once the timer hits 90 seconds, we observed whether or not the stove top was turned off. We tested our design a total of 10 times for each scenario. 

# Design Decision Discussion
Design decisions are described completely. This is an excellent reference design for this type of system. 

# Test Results Discussion 
It is clear what the system can do, cannot do, and where it works best

# Testing Results
Proper test results were conducted, and the results were clearly documented
