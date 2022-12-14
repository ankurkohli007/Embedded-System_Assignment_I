[Embedded System](https://corsi.unige.it/en/off.f/2022/ins/59432?codcla=10635)<br>
**Author:** [Ankur Kohli](https://github.com/ankurkohli007), [Ammar Iqbal](https://github.com/ammariqbal48) & [Basit Akram](https://github.com/abdulbasit656)<br>
[M.Sc Robotics Engineering](https://corsi.unige.it/corsi/10635)<br>
[University of Genoa (UniGe)](https://unige.it/en)<br>
**Supervisor:** [Prof. Enrico Simetti](https://rubrica.unige.it/personale/UkNGW15g)

## Abstract ##

This assignemnt report is about the **Embedded Systems** in which the of ***timers, interrupts, SPI, UART,*** and so on to determine about the operations performance. The specific goal in this case is that to know the implementation of operations with the real-time hardware. This report to bring the light on Embedded Systems for operations. Furthermore, the purpose of this report is to provide the approaches used during the development of code and implementation on microcontroller board. For this assignment, ***MPLAB IDE Software, XC16 Compiler and Microchip Microcontroller Board, HTerm serial software*** is used and also ***Embedded C programming*** is platform for the development of code.

## Introduction ##

A microprocessor-based computer system with software that is intended to carry out a specific task, either independently or as a component of a larger system, is known as an embedded sys- tem. An integrated circuit built to perform computing for real-time processes is at the heart of the system. 

From a single microcontroller to a group of connected processors with networks and peripherals, complexity can range from having no user interface to having intricate graphical user interfaces. Depending on the task for which it is created, an embedded system’s complexity varies greatly. 

Applications for embedded systems include hybrid cars, avionics, digital watches, microwaves, and more. Embedded systems consume up to 98 percent of all produced microprocessors.

## Requirements for the Assignment ##

* Simulate an algorithm that needs 7 ms for its execution, and needs to work at 100 Hz.
* Read characters from UART and display the characters received on the first row of the LCD.
* When the end of the row has been reached, clear the first row and start writing again from the first row first column.
* Whenever a CR ’\r’ or LF ’\n’ character is received, clear the first row.
* On the second row, write "Char Recv: XXX", where XXX is the number of characters received from the UART2. (use sprintf(buffer, “%d”, value) to convert an integer to a string to be displayed.
* Whenever button S5 is pressed, send the current number of chars received to UART2.
* Whenever button S6 is pressed, clear the first row and reset the characters received counter.

## Tips for Writing to LCD with SPI


