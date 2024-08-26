// g++ -o prob prob.cpp -no-pie
#include <bits/stdc++.h>
using namespace std;

int sz;
char buf[0x100];
char *buf_ptr;

void win()
{
    system("/bin/sh");
}

void alpharacer(int wait)
{
    sleep(wait);
    printf("Enter size: ");
    scanf("%d", &sz);
    if(sz > 0x100)
    {
        printf("Alpharacer validate input~\n");
        return;
    }
    sleep(wait);
    read(0, buf_ptr, sz);
}

void betaracer(int wait)
{
    sleep(wait);
    printf("Enter size: ");
    scanf("%d", &sz);
    sleep(wait);
    write(1, buf_ptr, sz);
}

int main()
{
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);

    buf_ptr = buf;

    while(true)
    {
        int wait1, wait2;
        printf("Enter wait time for alpha: ");
        scanf("%d", &wait1);
        printf("Enter wait time for beta: ");
        scanf("%d", &wait2);

        thread t1(alpharacer, wait1);
        thread t2(betaracer, wait2);

        t1.join();
        t2.join();
    }
}