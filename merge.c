#include "pthread.h"
#include "stdio.h"
#include "malloc.h"
#include <unistd.h>
struct input{
    int l;
    int r;
    int *arr;
};
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
void *mergeSort(void* arguments)
{
    struct input *args = arguments;
    if (args->l < args->r) {
        int m = args->l + (args->r - args->l) / 2;
        pthread_t left_t ;
        struct input left ;
        left.arr=args->arr;
        left.l=args->l;
        left.r=m;
        pthread_t right_t ;
        struct input right ;
        right.arr=args->arr;
        right.l=m+1;
        right.r=args->r;
        pthread_create(&left_t,NULL,mergeSort,(void *)&left);
        pthread_create(&right_t,NULL,mergeSort,(void *)&right);
        pthread_join(left_t,NULL);
        pthread_join(right_t,NULL);
        merge(args->arr, args->l, m, args->r);
    }
}
int main()
{
    FILE *fp = fopen("C:\\Users\\zeyad\\Desktop\\untitled8\\input-sort.txt", "r");
        if (!fp) {
            fprintf(stderr, "Error opening file\n");
            return 1;
        }
        int n_elements;
        if (fscanf(fp, "%d", &n_elements) != 1) {
            fprintf(stderr, "Error reading number of elements\n");
            fclose(fp);
            return 1;
        }
        int arr[n_elements];
        // Read the elements of the array
        for (int i = 0; i < n_elements; i++) {
            if (fscanf(fp, "%d", &arr[i]) != 1) {
                fprintf(stderr, "Error reading element %d\n", i + 1);
                fclose(fp);
                return 1;
            }
        }
        fclose(fp);
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    printf("Given array is \n");
    printArray(arr, arr_size);
    struct input start;
    start.arr=arr;
    start.l=0;
    start.r=arr_size-1;
    pthread_t main;
    pthread_create(&main,NULL,mergeSort,(void *)&start);
    pthread_join(main,NULL);
    printf("AFTER MERGE SORT\n");
    printArray(arr,arr_size);
    return 0;
}
