Compiling the code files:
1. You can compile the AM Layer code by first compiling the PF layer using 'make' and then using 'make' in the AM layer folder. (If ypu don't compile the PF layer first, the AM layer doesnt get compiled)
2. You can compile the correctness test cases by going to the correctness folder in the test cases folder and running 'make test'. Several executables pertaining to each check are created and can be run independently. Any segmentaton fault encountered can be probably resolved using 'make clean' and then 'make' again.
3. Compiling the performance test cases is also similar to above (although, the command is 'make' instead of 'make test') and the code is present in the performance folder of the test cases folder. (There is a makefile in that folder too)
