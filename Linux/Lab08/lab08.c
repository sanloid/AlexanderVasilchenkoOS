#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
int n = 0;
char buffer[13] = "";
char note1[12] = "Novosibirsk";
char note2[12] = "Semipalatink";
char note3[12] = "Ekaretinburg";
pthread_mutex_t mutexS, mutexW;
pthread_t read1, read2, read3, write1, write2, write3;
void writer(void *arg)
{
    int i;
    int delay;
    int vary = (long)arg;
    char notebook[13];
    if (vary == 1)
    {
        for (int i = 0; i < 13; i++)
            notebook[i] = note1[i];
        delay = 3;
    }
    else if (vary == 2)
    {
        for (int i = 0; i < 13; i++)
            notebook[i] = note2[i];
        delay = 2;
    }
    else
    {
        for (int i = 0; i < 13; i++)
            notebook[i] = note3[i];
        delay = 2;
    }
    while (1)
    {
        pthread_mutex_lock(&mutexW);
        for (i = 0; i < 5; i++)
            buffer[i] = notebook[i];
        sleep(1);
        for (i = 5; i < 13; i++)
            buffer[i] = notebook[i];
        buffer[13] = '\0';
        pthread_mutex_unlock(&mutexW);
        sleep(delay);
    }
}

void reader(void *args)
{
    int i, iter;
    int color, pos, delay;
    int vary = (long)args;
    if (vary == 1)
    {
        color = 31;
        pos = 20;
        delay = 1;
    }
    else if (vary == 2)
    {
        color = 33;
        pos = 40;
        delay = 2;
    }
    else
    {
        color = 37;
        pos = 60;
        delay = 1;
    }
    for (i = 0; i < 20; i++)
    {
        pthread_mutex_lock(&mutexS);
        n++;
        if (n == 1)
            pthread_mutex_lock(&mutexW);
        pthread_mutex_unlock(&mutexS);
        printf("\033[%d;%dH\033[%dm %s \n", i + 3, pos, color, buffer);
        pthread_mutex_lock(&mutexS);
        n--;
        if (n == 0)
            pthread_mutex_unlock(&mutexW);
        pthread_mutex_unlock(&mutexS);
        sleep(delay);
    }
}
int main()
{
    pthread_create(&write1, NULL, (void *)writer, (void *)1);
    pthread_create(&read1, NULL, (void *)reader, (void *)1);
    pthread_create(&write2, NULL, (void *)writer, (void *)2);
    pthread_create(&read2, NULL, (void *)reader, (void *)2);
    pthread_create(&write3, NULL, (void *)writer, (void *)3);
    pthread_create(&read3, NULL, (void *)reader, (void *)3);
    sleep(60);
    return 0;
}