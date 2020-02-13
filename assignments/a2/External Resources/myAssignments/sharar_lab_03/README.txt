****************************************************
Sharar Mahmood                          0955835
CIS 2520                                Lab 3
sharar@uoguelph.ca                    Oct 01, 2017
****************************************************

Program Description
****************************************************
Main Program : Creates two linked lists one for books structs and another for integers storage. The book is printed in order of last in first out. The integers are inserted in sorted manner and are printed in both ascending and descending order.

Testing Program : This tests all the functions in the provided LinkeListAPI.h library. Test cases contain both edge cases and normal cases and provide a pass or a fail feedback upon success or failure

Additional Program  Details
****************************************************
Complie and Run Main Program:

To compile main program give the command "make program" on the command line 

Executable “program” will be created in the bin upon successful compilation.

To run the program go to command line and type "cd bin" to change directory to bin and give the command "./program" to run


Complie and Run Test Program:

To compile main program give the command "make testProgram" on the command line 

Executable “testProgram” will be created in the bin upon successful compilation.

To run the program go to command line and type "cd bin" to change directory to bin and give the command "./testProgram" to run

Assumptions or Limitations
****************************************************
No known limitations
No other additional features

Answers to questions
****************************************************

1) Testing with mulitple data types allows making a stronger and a more abstract data type by identifying errors that are not revealed using some of the common data types.
   So, to make an adaptive code and providing sufficient abstraction testing with multiple data types is very important.

2) The print functions testing is type specific that is dependent on the data type that is being contained in the linked list. However, the function signature provide
   is capable of taking in any data type provided that the user writes his own print function based on the data that is being added to list. However, for type specific lists
   a function signature should be modified with the same type as the type of data that is being added to the list.
   For testing the pront functions we can simply pass in a print function compatible with data being tested as the parameter for the 
   print function pointer and that will take care of printing for us.

3) No. getFromFront() only returns the data stored in the list head without making any modifications to the data or the list.

