//This is a text file that outlines my implementation of
//the random tester for the function testme() in testme.c



//the first thing I did was implemented the inputChar() function
//This function creates a random character from ascii value 32 (' ')
//up to value 127 (DEL)
//
//
//
//Then I implemented the inputString() function to create a string 
//of length 6 with a terminating character at index 5
//This function creates 5 random chars from 'a'-'z' and fills the
//string to send to testme()
//
//
//
//The testme() function runs a while loop which takes a random char from
//inputChar() and a random string from inputString() and runs until the
//error condition is met (which a string that read 'r' 'e' 's' 'e' 't')
//and a state value of 9 (which is achieved through producing multiple 
//random characters like '[' '{' and ' ')
//
//
//
//This random test suite covers 97.14% of the lines in testme.c
//the only line that is not covered is the last line of the 
//void function because it always exits after the error condition is produced,
//hence never reaching the end of the function