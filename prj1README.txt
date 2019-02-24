List of file(s):

1. MyCompress.ccp takes 2 arguements, source.txt and destination.txt, where 15 or more consecutive 
0's and 1's from the source file are compressed and appended into the destination file.
    author: Julio Aguilar

2. MyDecompress.c takes in a compressed source file and decpresses "-n-" and "+n+" to n number of 
0's and 1's respectively into an output file.
    author: Austin Vargason

3. ForkExecl.cpp executes MyCompress.cpp using linux command execl() via a fork system call.
    author: Julio Aguilar

4. PipeCompress.c forks pipes two process where the first reads and compresses a source file and the second
writes the the compressed content into a destination file - data is send through a pipe.
    author: Austin Vargason

5. ParFork.cpp splits a source file into n pieces and forks n process to compress each split.
    author: Julio Aguilar

6. MiniShell.c reads and executes a user command.
    author: Austin Vargason

7. MoreShell.c is a stronger version of MiniShell.c that reads and executes user commands that MiniShell
cant.
    author: Austin Vargason

8. DupShell.c is a version of MoreShell.c that has the ability to execute user commands connected by pipes.
    author: Austin Vargason

9. ParThread.cpp splits a source file into n pieces and creates n threads to compress each split.
    author: Julio Aguilar
    
10. MeasureRunningSpeed.c
    author: Austin Vargason

    *** Program Output for Program: ./MyCompress ****
    File compressed.

    ./MyCompress took 0.000326 seconds to execute

    *** Program Output for Program: ./ParFork ****
    Splitting File...
    Compressing.. 
    Compressed Data outputted to: ./testFiles/measureOutput2.txt

    ./ParFork took 0.000203 seconds to execute

    *** Program Output for Program: ./ParThread ****
    Splitting File...
    Splitting complete...
    Number of split(s): 5999

    ./ParThread took 0.000190 seconds to execute