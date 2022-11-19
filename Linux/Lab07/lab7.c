#include <pthread.h>
#include <stdio.h>

char alphabet[] = "ABCDEFGHIKLMNOPQRSTU";

void thread(void *arg)
{
	int k, j;
	if ((int)arg == 1 || (int)arg == 3)
	{
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	}
	for (k = 0; k < 21; k++)
	{
		printf("\033[%d;%d0H\033[1;3%dm", k + 1, 2 * (int)arg, 4 - (int)arg);
		for (j = 0; j < (int)arg * 2; j++)
		{
			printf("%c", alphabet[k]);
		}
		printf("\n");

		if (k == 12 && (int)arg == 3)
		{
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
			pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
		}
		if (k == 16 && (int)arg == 3)
		{
			pthread_testcancel();
			usleep(1000000 + 750000 * (int)arg);
			pthread_testcancel();
		}
		else
		{
			usleep(1000000 + 500000 * (3 - (int)arg));
		}
	}
}

void main()
{

	int k;
	int rc;
	pthread_t tid1, tid2, tid3;

	printf("\033[2J\n");

	for (int i = 0; i < 20; i++)
	{
		printf("\033[%d;1H%d", i + 1, i + 1);
	}

	rc = pthread_create( // create a new thread
		&tid1,			 // pointer to pthread_t variable
		NULL,			 // Указатель на структуру pthread_attr_t, которая определяет атрибуты нового потока. Если attr равен NULL, то будут использоваться атрибуты по умолчанию
		(void *)thread,	 //
		(void *)1		 //
	);

	if (rc != 0)
	{
		printf("Error: start first thread failed");
		return;
	}

	rc = pthread_create(&tid2, NULL, (void *)thread, (void *)2);

	if (rc != 0)
	{
		printf("Error: start second thread failed");
		return;
	}

	rc = pthread_create(&tid3, NULL, (void *)thread, (void *)3);

	if (rc != 0)
	{
		printf("Error: start third thread failed");
		return;
	}

	for (k = 0; k <= 20; k++)
	{
		printf("\033[%d;1H\033[1;37m", k + 1);
		// printf("%c\n", alphabet[k]);

		if (k == 5)
		{
			rc = pthread_cancel(tid1);
			if (rc != 0)
			{
				printf("\033[25;1H\033[1;34mError: cancel first thread failed");
			}
			else
			{
				printf("\033[25;1H\033[1;34mTrying first thread cancel");
			}
		}

		if (k == 10)
		{
			rc = pthread_cancel(tid3);
			if (rc != 0)
			{
				printf("\033[25;1H\033[1;32mError: cancel third thread failed");
			}
			else
			{
				printf("\033[25;1H\033[1;32mCancel third thread is successfull");
			}
		}

		usleep(1500000);
	}

	getchar();
	printf("\033[0m");
}
