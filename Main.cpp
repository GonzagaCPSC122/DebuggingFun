// demo of a few things
// 1. how to figure out if your program has memory leaks with valgrind
// 2. why we never return the mem addr of a local variable
// 3. how to figure out what line number causes a seg fault using GDB

#include <iostream>

using namespace std;

int * doBadThings();

int main() {	
	// 1. USING VALGRIND TO DETECT MEMORY LEAKS
	// when you dynamically allocate memory with new, you should later deallocate (AKA free) that memory with delete
	// if you forget to free dynamic memory, you have a "memory leak"
	// use the valgrind program to find memory leaks in your program
	// may first need to install valgrind
	// e.g. sudo apt install valgrind
	// compile your program with -g for debugging symbols
	// e.g. g++ -g Main.cpp
	// then run valgrind
	// valgrind --leak-check=yes ./a.out
	// here is an example
	int * intPtr = new int;
	*intPtr = 7;
	cout << *intPtr << endl;
	// should delete intPtr but lets say I forget...
	// compile and run valgrind
	// you'll see output showing the following for this program:
	/*
	==19214== HEAP SUMMARY:
	==19214==     in use at exit: 4 bytes in 1 blocks
	==19214==   total heap usage: 3 allocs, 2 frees, 73,732 bytes allocated
	==19214== 
	==19214== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
	==19214==    at 0x4838DBF: operator new(unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
	==19214==    by 0x109196: main (Main.cpp:24)
	==19214== 
	==19214== LEAK SUMMARY:
	==19214==    definitely lost: 4 bytes in 1 blocks
	==19214==    indirectly lost: 0 bytes in 0 blocks
	==19214==      possibly lost: 0 bytes in 0 blocks
	==19214==    still reachable: 0 bytes in 0 blocks
	==19214==         suppressed: 0 bytes in 0 blocks
	==19214== 
	==19214== For counts of detected and suppressed errors, rerun with: -v
	==19214== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

	*/
	
	// 2. NEVER RETURN ADDRESS OF A LOCAL VARIABLE
	int * badPtr = NULL;
	badPtr = doBadThings();
	// doesn't crash til we try to go to what badPtr points to
	// uncomment next line to see program with seg fault
	//cout << *badPtr << endl; 
	
	// 3. USING GDB TO DEBUG A PROGRAM
	// remember how I said "cout is your friend" and you can use it to trace your program and isolate where a seg fault is occurring?
	// here is another, more practical way to find which line of code is causing the seg fault (line 12 in this example)
	// compile with -g
	// e.g. g++ -g Main.cpp
	// this puts "debugging symbols" into the exectuable that GDB needs to debug your program
	// GDB is the "Gnu Debugger"
	// run GDB on your program
	// e.g. GDB a.out
	// this will take you to the GDB shell where it waits for commands
	// enter the "run" command to run your program until it terminates or crashes (crashes in this case)
	// e.g. (gdb) run
	// you'll see output showing the following for this program:
	/*
	Starting program: /home/student/Desktop/CPSC122/DebuggingFun/a.out 

	Program received signal SIGSEGV, Segmentation fault.
	0x0000555555555192 in main () at Main.cpp:12
	12              cout << *badPtr << endl; 
	*/
	// type q or hit CTRL + D to exit GDB

	return 0;
}

int * doBadThings() {
	int localVar = 5;
	return &localVar; // bad!! why??
}
