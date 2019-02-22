all: MyDecompress.c PipeCompress.c MiniShell.c MoreShell.c DupShell.c
	gcc MyDecompress.c -o MyDecompress
	gcc PipeCompress.c -o PipeCompress
	gcc MiniShell.c -o MiniShell
	gcc MoreShell.c -o MoreShell
	gcc DupShell.c -o DupShell
