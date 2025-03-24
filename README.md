# 178_Final_Project
Team Name – The Enigma

Project Title – Morse code sender/receiver

Project Style – Hardware/Arduino Based

Project Reason
It involves a lot of hardware components to give us experience and practice using many components in the kit. It allows us to explore several data structures including queues and further our knowledge of the combination of more complicated data structures with hardware. 

Course Topics
-	Queues/Linked Lists – to store each the morse code form of each letter entered
-	Multi-dimensional Arrays – to store translations
-	Other structures and algorithms learned throughout the course

Preliminary Design
Start
-	Write morse code into screen using buttons which gets sent to the other Arduino and printed in morse code and text to the other screen 
	- Enter dots and dashes using buttons on screen (Buttons for dash, dot, end of a letter and space)
    - Display the . and – when they are typed and the letters after the end of the letter is entered
    - Scroll across screen as typing (top separate from bottom so both are visible)
  - Translate dots and dashes to number values (ACSII)
  - Linked listed containing 4 int values to store numbers associating with dot/dash
    - Store int values in linked list in a queue to send to the other Arduino 
    - Ignore the end of letter input to make translation to a word easier
  - All values empty for spaces/separating words
  - 2D Array to hold translation of each combination
    - Static array to reference for translation
    - Stores 4 ints to indicate the morse code and one to store the letter Ex.
  - Error checking for incorrect or invalid codes
    - If a morse code doesn’t exist inform the user and restart from the last full letter or full word depending on code capabilities
    - Translate using number to get character
    -	When list is received translate to numbers and print both morse code and text to the screen 
Goal: The Arduinos can be run completely disconnected form a laptop only plugged in to a power source, no interaction with the serial monitor etc. (Serial monitor wil be used for testing and trouble shooting)

45(Decimal):  - (ASCII)
46(Decimal): . (ASCII) 

Advances
-	An option to enter text that gets translated to morse code
  - Option to enter text or morse code 
	- Use a scroll to move up and down through a list of letters, like the number scrolling from lab 1_3
-	Light to flash the morse code on both Arduinos
  - Use numbers (Decimal translation) to indicate how many times and the length of the light flash and a longer pause for spaces
-	Buzzer to audibly output morse code 
  - Use numbers (Decimal translation) to indicate how many times and the length of the buzz and a longer pause for spaces
-	3D print case for Arduino, screen, buzzer and light
  - Design a case to enclose set up in SolidWorks and print for at least two Arduinos
-	Network for Arduinos – morse code sends/receives to multiple Arduinos
  - Connect multiple Arduinos and send the morse code to all of them and receive from any
-	Ability to select which Arduino you are sending to
  - Option to select which Arduino you are sending to, select one or all

