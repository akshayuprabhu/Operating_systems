
/*
assignment 1 question no 2 zombie
b. Implement the C program in which main program accepts the integers to be sorted. Main program uses the fork system call to create
 a new process called a child process. Parent process sorts the integers using merge sort and waits for child process using wait system
  call to sort the integers using quick sort. Also demonstrate zombie and orphan states.
*/
#include <sys/types.h>
#include <stdio.h>

void swap(int *a,int *b)
{
    int t=*a;
        *a=*b;
        *b=t;
}


void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int main(){
	printf("parent process created\n");

		int n,a[1000],i;
	    
		printf("Enter n:\n");
		scanf("%d",&n);

	    printf("Enter numbers to be sorted:\n");
	    for(i=0;i<n;i++)
	    	scanf("%d",&a[i]);

	pid_t pid=fork();
	if(pid<0){
		printf("failed to create child process\n");
	}else if(pid==0){
		printf("child process created..\n");
		quickSort(a,0,n-1);
		printf("the sorted array by child process(QUICK SORT):\n");
		for(i=0;i<n;i++)
			printf("%d ",a[i]);
		printf("child process got terminated...\n");
	}else{
		sleep(10);
		mergeSort(a,0,n-1);
		printf("the sorted array by parent process(MERGE SORT): \n");
		for(i=0;i<n;i++)
			printf("%d ",a[i]);

	}

	if(pid!=0){
		printf("parent process ends\n");
	}
return 0;	
}
