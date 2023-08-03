#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void sort()
{
	printf("Please enter the number of elements in the array : ");
	int n;
	scanf("%d", &n);
	printf("Please enter the elements in the array ");
	int arr[n];
	for (int i = 0; i < n; i++)
	{
		int a;
		scanf("%d", &a);
		arr[i] = a;
	}

	printf("Your array is : ");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
	for (int i = 0; i < n; i++)
	{
		// For loop for total number of passes
		for (int j = 0; j < n - 1; j++)
		{
			// For loop for compairing each element in an array of struct
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	printf("Your sorted array is : ");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{
	sort();
	int pipefd[2];
	pid_t cpid;
	char buf;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0)
	{ /*Child reads from pipe */

		printf("This is a child process \n");

		int childprocess_id = getpid();

		int parentprocess_id = getppid();

		printf("The process id  of child is  %d \n", childprocess_id);

		printf("The process id  of parent is  %d \n", parentprocess_id);

		sleep(1);

		int childprocess_id_new = getpid();

		int parentprocess_id_new = getppid();

		printf("The new process id  of child is  %d \n", childprocess_id_new);

		printf("The new process id  of parent is  %d \n", parentprocess_id_new);	// parent process id is chnaged the shows that child is orphand and adopted by init process

	}
	else if (cpid > 0)
	{ /*Parent writes argv[1] to pipe */
		printf("This is a parent process \n");
	}
}
