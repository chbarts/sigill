#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ucontext.h>

void sighandler(int signo, siginfo_t * si, void *data)
{
    ucontext_t *uc = (ucontext_t *) data;
    unsigned long long int rip;
    unsigned char *code;

    /* REG_RIP */
    rip = uc->uc_mcontext.gregs[REG_RIP];
    printf("RIP: %llx\n", rip);

    code = (unsigned char *) rip;

    printf("%02hhx %02hhx\n", code[0], code[1]);
    uc->uc_mcontext.gregs[REG_RIP] += 2;
}

int main(void)
{
    struct sigaction sa, osa;

    sa.sa_flags = SA_ONSTACK | SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = sighandler;
    sigaction(SIGILL, &sa, &osa);

    printf("Before\n");
    asm("ud2\n");
    printf("After\n");

    exit(EXIT_SUCCESS);
}
