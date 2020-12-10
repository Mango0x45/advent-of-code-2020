#include <stdio.h>

#ifdef BUFSIZ
#   undef BUFSIZ
#endif
#define BUFSIZ 108

int array[BUFSIZ], temp[BUFSIZ];

void merge(int low, int mid, int high);
void merge_sort(int low, int high);

/**
 * Mergesort Algorithm
 */
void merge(int low, int mid, int high)
{
    int l1, l2, i;

    for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        if (array[l1] <= array[l2])
            temp[i] = array[l1++];
        else
            temp[i] = array[l2++];
    }

    while (l1 <= mid)
        temp[i++] = array[l1++];

    while (l2 <= high)
        temp[i++] = array[l2++];

    for (i = low; i <= high; i++)
        array[i] = temp[i];

    return;
}

/**
 * Does the mergesort swapping
 */
void merge_sort(int low, int high)
{
    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
    
    return;
}

int main(void)
{
	int i = 0;

	FILE* fpt = fopen("input", "r");
    while (fscanf(fpt, "%d", &array[i++]) == 1);
    fclose(fpt);

    merge_sort(0, BUFSIZ);

    /* Init to 1 because of the original charger, and the devices adaptor */
    int difo = 1, dift = 1;
    for (i = 1; i < BUFSIZ; i++) {
        if (array[i] - array[i - 1] == 1)
            difo++;
        else if (array[i] - array[i - 1] == 3)
            dift++;
    }

    printf("%d\n", difo * dift);
    return 0;
}