all: MyCompress.cpp MyDecompress.c ForkExecl.cpp PipeCompress.c ParFork.cpp MiniShell.c MoreShell.c DupShell.c ParThread.cpp MeasureRunningSpeed.c
	g++ MyCompress.cpp -o MyCompress
	gcc MyDecompress.c -o MyDecompress
	g++ ForkExecl.cpp -o ForkExecl
	gcc PipeCompress.c -o PipeCompress
	g++ ParFork.cpp -o ParFork
	gcc MiniShell.c -o MiniShell
	gcc MoreShell.c -o MoreShell
	gcc DupShell.c -o DupShell
	g++ ParThread.cpp -o ParThread
	gcc MeasureRunningSpeed.c -o MeasureRunningSpeed
