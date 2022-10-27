#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

// structure for arguments
typedef struct
{
    int *arr; // array
    int n;    // size of array
} arguments;

int array_ptr[10];
int b[10];
int c[5], d[5];
int low = 0, high = 9, high1 = 4;
void *run(void *array_ptr);
void *run1(void *array_ptr);

void merge1(int low, int mid, int high1)
{
    int l1, l2, i;

    for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high1; i++)
    {
        if (c[l1] <= c[l2])
            d[i] = c[l1++];
        else
            d[i] = c[l2++];
    }

    while (l1 <= mid)
        d[i++] = c[l1++];

    while (l2 <= high1)
        d[i++] = c[l2++];

    for (i = low; i <= high1; i++)
    {
        c[i] = d[i];
    }
}

void mergesort1(int low, int high1)
{
    int mid;
    int *elements = (int *)c;

    if (low < high1)
    {
        mid = (low + high1) / 2;
        mergesort1(low, mid);
        mergesort1(mid + 1, high1);
        merge1(low, mid, high1);
    }
    else
    {
        return;
    }
}
int c1[5], d1[5];

void *merging(void *array_ptr)
{
    int i = 0;

    int j = 0;
    int k = 0;
    int m = 5, n = 5;

    while (i < m && j < n)

    {

        if (c1[i] < d1[j])

        {

            b[k] = c1[i];

            i++;
        }

        else

        {

            b[k] = d1[j];

            j++;
        }

        k++;
    }

    if (i >= m)

    {

        while (j < n)

        {

            b[k] = d1[j];

            j++;

            k++;
        }
    }
    if (j >= n)

    {

        while (i < m)

        {

            b[k] = c1[i];

            i++;

            k++;
        }
    }
    printf("\n After merging: \n");
    for (i = 0; i < m + n; i++)
    {
        printf("%d\t", b[i]);
    }
	printf("\n");
}

void *run(void *c)
{
    mergesort1(low, high1);
}

void printArray(arguments *arg)
{
    for (int i = 0; i < arg->n; i++)
    {
        printf("%d ", arg->arr[i]);
    }
    printf("\n");
}

void *bubble_asc(void *arg)
{
    arguments *array = (arguments *)arg;
    pthread_mutex_lock(&mutex);
    printf("\nBubble sort ascending:\n");
    printArray(array);
    sleep(1);
    // loop to access each array element
    for (int step = 0; step < array->n - 1; ++step)
    {

        // loop to compare array elements
        for (int i = 0; i < array->n - step - 1; ++i)
        {

            // compare two adjacent elements
            // change > to < to sort in descending order
            if (array->arr[i] > array->arr[i + 1])
            {

                // swapping occurs if elements
                // are not in the intended order
                int temp = array->arr[i];
                array->arr[i] = array->arr[i + 1];
                array->arr[i + 1] = temp;
                sleep(1);
                printArray(array);
            }
        }
    }
    pthread_mutex_unlock(&mutex);
}

void *bubble_dsc(void *arg)
{

    arguments *array = (arguments *)arg;
    pthread_mutex_lock(&mutex);
    printf("\nBubble sort descending:\n");
    printArray(array);
    sleep(1);
    // loop to access each array element
    for (int step = 0; step < array->n - 1; ++step)
    {

        // loop to compare array elements
        for (int i = 0; i < array->n - step - 1; ++i)
        {

            // compare two adjacent elements
            // change > to < to sort in descending order
            if (array->arr[i] < array->arr[i + 1])
            {

                // swapping occurs if elements
                // are not in the intended order
                int temp = array->arr[i];
                array->arr[i] = array->arr[i + 1];
                array->arr[i + 1] = temp;
                sleep(1);
                printArray(array);
            }
        }
    }
    pthread_mutex_unlock(&mutex);
}

// func to swap 2 variables
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// sorts array in ascending using insertion sort
void *insertion_asc(void *arg)
{

    pthread_mutex_lock(&mutex);
    printf("\nInsertion sort ascending:\n");
    arguments *a = (arguments *)arg;
    sleep(1);
    printArray(a);
    int i, key, j;
    for (i = 1; i < (a->n); i++)
    {
        key = a->arr[i];
        j = i - 1;
        /* Move elements of arr[0..i-1], that are
       greater than key, to one position ahead
       of their current position */
        while (j >= 0 && a->arr[j] > key)
        {
            a->arr[j + 1] = a->arr[j];
            j = j - 1;
        }
        a->arr[j + 1] = key;
        sleep(1);
        printArray(a);
    }
    pthread_mutex_unlock(&mutex);
}

// sorts array in descending using insertion sort
void *insertion_dsc(void *arg)
{

    pthread_mutex_lock(&mutex);
    printf("\nInsertion sort descending:\n");
    arguments *a = (arguments *)arg;
    sleep(1);
    printArray(a);

    int i, key, j;
    for (i = 1; i < (a->n); i++)
    {
        key = a->arr[i];
        j = i - 1;
        /* Move elements of arr[0..i-1], that are
       greater than key, to one position ahead
       of their current position */
        while (j >= 0 && a->arr[j] < key)
        {
            a->arr[j + 1] = a->arr[j];
            j = j - 1;
        }
        a->arr[j + 1] = key;
        sleep(1);
        printArray(a);
    }

    pthread_mutex_unlock(&mutex);
}

// sorts array in ascending using selection sort
void *sel_asc(void *arg)
{

    pthread_mutex_lock(&mutex);
    printf("\nSelection sort ascending:\n");
    arguments *a = (arguments *)arg;
    sleep(1);
    printArray(a);

    for (int step = 0; step < (a->n) - 1; step++)
    {
        int min = step;
        for (int i = step + 1; i < a->n; i++)
        {
            if (a->arr[i] < a->arr[min])
                min = i;
        }

        swap(&a->arr[min], &a->arr[step]);
        sleep(1);
        printArray(a);
    }

    pthread_mutex_unlock(&mutex);
}

// sorts array in descending using selection sort
void *sel_dsc(void *arg)
{

    pthread_mutex_lock(&mutex);
    printf("\nSelection sort descending:\n");
    arguments *a = (arguments *)arg;
    sleep(1);
    printArray(a);

    for (int step = 0; step < (a->n) - 1; step++)
    {
        int min = step;
        for (int i = step + 1; i < a->n; i++)
        {
            if (a->arr[i] > a->arr[min])
                min = i;
        }

        swap(&a->arr[min], &a->arr[step]);
        sleep(1);
        printArray(a);
    }

    pthread_mutex_unlock(&mutex);
}

int main()
{
    int ch;
    while (1)
    {
        printf("\n1. Bubble\n2. Insertion\n3. Selection\n4. Merge\n5. Exit\n\nEnter Choice\n");
        scanf("%d", &ch);
        if (ch == 5)
        {
            printf("Exiting\n");
            break;
        }
        if (ch == 1)
        {
            arguments arg;
            pthread_t thread[2];
            pthread_mutex_init(&mutex, 0);

            printf("Number of elements: ");
            scanf("%d", &arg.n);

            arg.arr = (int *)malloc(arg.n * sizeof(int));

            printf("\nEnter the elements: \n");

            for (int i = 0; i < arg.n; i++)
            {
                printf("Element %d: ", i + 1);
                scanf("%d", &arg.arr[i]);
            }
            pthread_create(&thread[0], NULL, &bubble_asc, (void *)&arg);
            pthread_create(&thread[1], NULL, &bubble_dsc, (void *)&arg);
            pthread_join(thread[0], NULL);
            pthread_join(thread[1], NULL);
            pthread_mutex_destroy(&mutex);
        }
        else if (ch == 2)
        {
            arguments arg;
            pthread_t thread[2];
            pthread_mutex_init(&mutex, 0);

            printf("Number of elements: ");
            scanf("%d", &arg.n);

            arg.arr = (int *)malloc(arg.n * sizeof(int));

            printf("\nEnter the elements: \n");

            for (int i = 0; i < arg.n; i++)
            {
                printf("Element %d: ", i + 1);
                scanf("%d", &arg.arr[i]);
            }
            pthread_create(&thread[0], NULL, &insertion_asc, (void *)&arg);
            pthread_create(&thread[1], NULL, &insertion_dsc, (void *)&arg);
            pthread_join(thread[0], NULL);
            pthread_join(thread[1], NULL);
            pthread_mutex_destroy(&mutex);
        }
        else if (ch == 3)
        {
            arguments arg;
            pthread_t thread[2];
            pthread_mutex_init(&mutex, 0);

            printf("Number of elements: ");
            scanf("%d", &arg.n);

            arg.arr = (int *)malloc(arg.n * sizeof(int));

            printf("\nEnter the elements: \n");

            for (int i = 0; i < arg.n; i++)
            {
                printf("Element %d: ", i + 1);
                scanf("%d", &arg.arr[i]);
            }
            pthread_create(&thread[0], NULL, &sel_asc, (void *)&arg);
            pthread_create(&thread[1], NULL, &sel_dsc, (void *)&arg);
            pthread_join(thread[0], NULL);
            pthread_join(thread[1], NULL);
            pthread_mutex_destroy(&mutex);
        }
        else if (ch == 4)
        {
            int n = 10;
            printf(" 10 elements you want to enter\n");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &array_ptr[i]);
            }
            for (int i = 0; i < 5; i++)
            {
                c[i] = array_ptr[i];
            }

            printf("\n 2 sorted subarray are:\n ");

            pthread_t t1, t2, t3;
            pthread_create(&t1, NULL, run, (void *)c);
            pthread_join(t1, NULL);

            for (int i = 0; i < 5; i++)
            {
                printf("%d\t", c[i]);
                c1[i] = c[i];
            }
            printf("\n");

            for (int i = 0; i < 5; i++)
            {
                c[i] = array_ptr[i + 5];
            }
            pthread_create(&t2, NULL, run, (void *)c);
            pthread_join(t2, NULL);
            for (int i = 0; i < 5; i++)
            {
                printf("%d\t", c[i]);
                d1[i] = c[i];
            }

            pthread_create(&t3, NULL, merging, (void *)array_ptr);
            pthread_join(t3, NULL);
        }
        else
            printf("Invalid Choice\n");
    }
}