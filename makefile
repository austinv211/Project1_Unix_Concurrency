all: MyCompress.cpp MyDecompress.c ForkExecl.cpp PipeCompress.c MultiFork.cpp MiniShell.c MoreShell.c DupShell.c
	g++ MyCompress.cpp -o MyCompress
	gcc MyDecompress.c -o MyDecompress
	g++ ForkExecl.cpp -o ForkExecl
	gcc PipeCompress.c -o PipeCompress
	g++ MultiFork.cpp -o MultiFork
	gcc MiniShell.c -o MiniShell
	gcc MoreShell.c -o MoreShell
	gcc DupShell.c -o DupShell
