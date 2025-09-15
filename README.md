## ATmega32 Digital Clock & Multi-Function Utility 🕒
This project is a comprehensive digital clock system built on the ATmega32 microcontroller. It goes beyond simple time-telling by integrating a stopwatch, a countdown timer, and a configurable alarm. All features are managed through an intuitive keypad interface and displayed on a 16x2 character LCD.

Pro Tip: Consider recording a short GIF of the clock in action (e.g., using a screen recorder on your Proteus simulation) and embedding it here. A visual demonstration is a great way to showcase your project!

## Key Features ✨
⏰ Real-Time Clock: Displays the current time in a 12-hour format (HH:MM:SS) with an AM/PM indicator.

📅 Full Calendar: Keeps track of the date (DD-MMM-YYYY) and automatically adjusts for leap years, ensuring February has 29 days when appropriate.

 Alarm System: Allows you to set a specific time for a daily alarm, which triggers an audible alert using a buzzer.

⏱️ Stopwatch: A precise stopwatch function capable of measuring time in minutes, seconds, and milliseconds.

⏳ Countdown Timer: A versatile timer that can be set for up to 25 hours. A buzzer sounds when the countdown is complete.

⚙️ Intuitive Menu Navigation: A user-friendly menu system allows for easy setup and control of all the clock's features using a simple keypad.

## Hardware & Software Requirements
### Hardware Components 🛠️
Microcontroller	ATmega32
Display	16x2 Character LCD
Input	4x3 Keypad
Sound Output	Piezo Buzzer
Driver Component	NPN BJT (e.g., 2N2222) to drive the buzzer


### Software & Drivers 💾
The entire application is written in C and is built upon a set of custom-developed drivers for the ATmega32 platform.

GPIO: For managing digital input/output pin configurations and states.

LCD: To control the 16x2 Liquid Crystal Display.

KPD: For scanning and reading input from the matrix keypad.

TIMER: Utilizes hardware Timer0 in CTC mode to create a precise 1ms tick for timekeeping.

GINT: Manages global interrupts to ensure non-blocking operation.

## How to Use 🕹️
The system is controlled via the keypad. Here is a quick guide to the button functions and menu navigation.

### Keypad Controls
M (Mode): Enters the main menu (SETUP) or returns to the previous menu/main screen.

E (Enter): Selects the current menu option or confirms a setting.

R (Right): Navigates to the next menu item on the right.

L (Left): Navigates to the previous menu item on the left.

U (Up): Increments a value (e.g., hours, minutes, days).

D (Down): Decrements a value.

### Menu Flow
Main Screen: The default screen displays the current time and date.

Setup Menu: Press 'M' to enter the SETUP screen. From here, you can navigate to different functions:

Time Setting: SETUP -> 'E' -> TIME -> 'E' -> Adjust time with U/D, move cursor with R/L, and confirm with 'E'.

Date Setting: SETUP -> TIME -> 'R' -> DATE -> 'E' -> Adjust date with U/D.

Stopwatch: SETUP -> 'R' -> STOPWATCH -> 'E' -> Press 'E' again to start.

Alarm: STOPWATCH -> 'R' -> ALARM -> 'E' -> Select ALARM ON or ALARM OFF. In the ALARM ON screen, press 'E' to set the alarm time.

Timer: ALARM -> 'R' -> TIMER -> 'E' -> TIMER SET -> 'E' -> Set the countdown duration and press 'E' to start.


