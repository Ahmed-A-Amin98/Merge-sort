#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void readfile(); // prototype for reading from file function
void MergeProcess(int low, int high); // Merge function that takes 2 bounds and calculates the mid point
void * MergeThrding(void *Arrp); // Using threads to preform the merging process

int Arraysize; // Arraysize
int *Arrp ; // Array scanned from file

typedef struct // struct used to traverse between the lines of
{
    int low;
    int high;
} TRVRS;

int main()
{
readfile(); // calling readfile funciton
    TRVRS arr; // create a traverse point
    arr.low = 0; // lowerbound of the array
    arr.high = Arraysize-1; //higher bound of the array (Array size -1) since the array starts at index 0
    pthread_t thrd; // thrd initialize


    pthread_create(&thrd, NULL, MergeThrding, &arr); // executing thread by calling the threading func
    pthread_join(thrd, NULL); // joining threads in ordere to get final value

printf("\nThe sorted array is :\n");
    for (int i = 0; i < Arraysize; i++) // printing the sorted array
        printf ("%d ", Arrp[i]);

    printf ("\n");

    pthread_exit(NULL); // exiting the thread

    return 0;
}

void readfile()
{
    FILE *fp; // creation of file pointer

    fp = fopen("input.txt", "r"); // openning file on reading only

    if (fp == NULL) // checking if file is found or not
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d\n",&Arraysize); //scanning array size from file
    Arrp= (int*) malloc(Arraysize*sizeof(int)); // allocating the size of the initalized array to the Array size
    printf("The size of Array is:\n");
    printf("%d\n",Arraysize);
    for(int i=0; i<Arraysize; i++) // scanning the array from the file
    {
        fscanf(fp,"%d",&Arrp[i]);
        while(!feof) // scan a space if it's not the end of file
            fscanf(fp," ");
    }
    fclose(fp);
    printf("The input array is :\n"); // printing the input array.
    for(int i=0; i<Arraysize; i++)
       {
        printf("%d ",Arrp[i]);

}
}

void MergeProcess(int low, int high)
{
    int mid = (low+high)/2; // calculating the middle bounds
    //dividing the array into 2 parameters  one from
    //strt1(low bound) -> mid   & the second from strt2 (mid+1) ->  high bound
    int strt1 = low;
    int strt2 = mid+1;
    int NewArray[high-low+1], newstrt = 0;
//merging process between the array using divide and conquer then putting the content of the array in the main array
    while(strt1 <= mid && strt2 <= high)
    {
        if (Arrp[strt1] > Arrp[strt2])
            NewArray[newstrt++] = Arrp[strt2++];
        else
            NewArray[newstrt++] = Arrp[strt1++];
    }

    while(strt1 <= mid)
    {
        NewArray[newstrt++] = Arrp[strt1++];
    }

    while(strt2 <= high)
    {
        NewArray[newstrt++] = Arrp[strt2++];
    }

    for (strt1 = 0; strt1 < (high-low+1) ; strt1++)
        Arrp[low+strt1] = NewArray[strt1];

}


void * MergeThrding(void *Arrp)
{
    TRVRS *point; //creating pointer node of traversal
     point = (TRVRS *)Arrp;
    TRVRS node1, node2;
    int mid = (point->low+point->high)/2;
    pthread_t tid1, tid2; //initalizing 2 threads used in threading

    //Using the same idea of 2 nodes used in the merge process by creating low n high bounds
    node1.low = point->low;
    node1.high = mid;

    node2.low = mid+1;
    node2.high = point->high;
// if location of the low point is less than the location of the high one , the code should be executed correctly
// else either there's an error in reading the location or the array is consisted of one element so it'd be readily sorted
    if (point->low < point->high)
{
    pthread_create(&tid1, NULL, MergeThrding, &node1);
    pthread_create(&tid2, NULL, MergeThrding, &node2);


    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    MergeProcess(point->low, point->high);
    pthread_exit(NULL);
}
else return;

}

