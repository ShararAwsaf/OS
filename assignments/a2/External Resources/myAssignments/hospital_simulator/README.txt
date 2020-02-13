****************************************************
Sharar Mahmood                          0955835
CIS 2520                              Assignment 2
sharar@uoguelph.ca                    Oct 16, 2017
****************************************************

Program Description
****************************************************
Main Program : Creates a Priority Queue for storing patient structs to generate a hospital emergency section simulation report. The priority of patients are printed in order of their entry times. The patients are inserted in priority queue in ascending sorted manner based on their priority. 

A file containing list of patients their names and priority values and symtom codes are provided line by line. A simulation where a priority queue each node representing a patient

are filled with patient details and computed proccessing time from symptom code and are processed priority based using given parameters of global clock simulation. The outputs are displayed as soon as processing of all patients are completed.


Testing of Program : The program is given an experimental test case and also allows users to input any case as necessary in addition to file passing from command line. 

Test cases contain both edge cases and normal cases.

The functions are checked using the patient struct.

Outputs are stored in an output file for future use.

Additional Program  Details
****************************************************
Complie and Run Main Program:

To compile main program give the command "make program" on the command line 

Executable “program” will be created in the bin upon successful compilation.

To run the program go to command line and type "cd bin" to change directory to bin and give the command "./program" to run

Requires user to give his own set of inputs

Complie and Run testMain Program:

To compile main program give the command "make testProgram" on the command line 

Executable “program” will be created in the bin upon successful compilation.

To run the program go to command line and type "cd bin" to change directory to bin and give the command "./testProgram" to run

Complie and Run Test Case given with Program:

To compile main program give the command "make program" on the command line 

Executable “program” will be created in the bin upon successful compilation.

To run the program go to command line and type "cd bin" to change directory to bin and give the command "./program (file_name.ext)" to run

any files prepared

Outputs in both cases will be stored in a file named OUTPUT.txt

Assumptions or Limitations
****************************************************
No known limitations
No other additional features

In comments the aging starvation algorithm has been provided which allows 
reduction of starvation for the low priority nodes by increasing their priority 
after every 500 globalClock seconds

****************************************************

