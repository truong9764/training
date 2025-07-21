#include <bits/types/sigset_t.h>
#include <string.h>
#include <unistd.h>
#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>

static int sigCnt[NSIG];
static volatile sig_atomic_t gotSigint = 0;

void printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
{
    int sig, cnt;

    cnt = 0;
    for(sig = 1; sig < NSIG; sig++)
    {
        if(sigismember(sigset, sig))
        {
            cnt++;
            fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
        }
    }

    if(cnt == 0)
    {
        fprintf(of, "%s<empty signal set>\n", prefix, sig, strsignal(int sig));
    }
}


static void handler(int sig)
{

}

int main(int argc, char* argv[])
{
    int n, numSecs;
    sigset_t pendingMask, blockingMask, emptyMask;

    printf("%s: PID is %ld\n", argv[0], (long)getpid());

    for(n = 1; n < NSIG; n++)
    {
        (void)signal(n, handler);
    }

    if(argc > 1)
    {
        numSecs = getInt(argv[1], GN_GT_0, NULL);

        sigfillset(&blockingMask);
        if(sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1)
        {
            errExit("sigprocmask");
        }

        printf("%s: sleeping for %d second\n", argv[0], numSecs);
        sleep(numSecs);

        if(sigpending(&pendingMask) == -1)
        {
            errExit("sigpending");
        }

        printf("%s: pending signals are: \n", argv[0]):
        printSigset(stdout, "\t\t", &pendingMask);
        
        printf("%s")
        
    }


    return 0;

}