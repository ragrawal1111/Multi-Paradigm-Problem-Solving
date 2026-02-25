/*
 * Assignment 7: Multi-Paradigm Problem Solving
 * C Implementation - Procedural Approach
 *
 * Calculates mean, median, and mode of a list of integers.
 */

#include <stdio.h>
#include <stdlib.h>

/* Sort an array of integers in ascending order (selection sort) */
void sort_array(int arr[], int n)
{
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

/* Calculate the mean (average) of the array */
double calculate_mean(int arr[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum / n;
}

/* Calculate the median of the array (assumes array is already sorted) */
double calculate_median(int sorted_arr[], int n)
{
    if (n % 2 == 0)
    {
        return (sorted_arr[n / 2 - 1] + sorted_arr[n / 2]) / 2.0;
    }
    else
    {
        return (double)sorted_arr[n / 2];
    }
}

/*
 * Calculate the mode(s) of the array (assumes array is already sorted).
 * Stores modes in the 'modes' output array and returns the count of modes.
 */
int calculate_mode(int sorted_arr[], int n, int modes[], int *mode_freq)
{
    int max_count = 1;
    int current_count = 1;
    int mode_count = 0;

    /* First pass: find the maximum frequency */
    for (int i = 1; i < n; i++)
    {
        if (sorted_arr[i] == sorted_arr[i - 1])
        {
            current_count++;
        }
        else
        {
            current_count = 1;
        }
        if (current_count > max_count)
        {
            max_count = current_count;
        }
    }

    *mode_freq = max_count;

    /* Second pass: collect all values with the maximum frequency */
    current_count = 1;
    for (int i = 1; i <= n; i++)
    {
        if (i < n && sorted_arr[i] == sorted_arr[i - 1])
        {
            current_count++;
        }
        else
        {
            if (current_count == max_count)
            {
                modes[mode_count++] = sorted_arr[i - 1];
            }
            current_count = 1;
        }
    }

    return mode_count;
}

/* Print the array */
void print_array(int arr[], int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("]");
}

int main()
{
    /* Sample dataset */
    int data[] = {4, 7, 2, 9, 1, 5, 7, 3, 7, 2, 8, 6, 5, 3, 7};
    int n = sizeof(data) / sizeof(data[0]);

    printf("=== Statistics Calculator (C - Procedural) ===\n\n");

    printf("Input data: ");
    print_array(data, n);
    printf("\n");
    printf("Number of elements: %d\n\n", n);

    /* Calculate mean before sorting */
    double mean = calculate_mean(data, n);

    /* Sort the array for median and mode calculations */
    sort_array(data, n);

    printf("Sorted data: ");
    print_array(data, n);
    printf("\n\n");

    /* Calculate median and mode on sorted array */
    double median = calculate_median(data, n);

    int *modes = (int *)malloc(n * sizeof(int));
    if (modes == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    int mode_freq;
    int mode_count = calculate_mode(data, n, modes, &mode_freq);

    /* Display results */
    printf("--- Results ---\n");
    printf("Mean:   %.2f\n", mean);
    printf("Median: %.2f\n", median);
    printf("Mode:   ");
    if (mode_freq == 1)
    {
        printf("No mode (all values appear once)\n");
    }
    else
    {
        print_array(modes, mode_count);
        printf(" (each appears %d times)\n", mode_freq);
    }

    /* Free dynamically allocated memory */
    free(modes);

    /* --- Second dataset to demonstrate flexibility --- */
    printf("\n========================================\n\n");

    int data2[] = {10, 20, 20, 30, 30, 40, 50};
    int n2 = sizeof(data2) / sizeof(data2[0]);

    printf("Input data: ");
    print_array(data2, n2);
    printf("\n");
    printf("Number of elements: %d\n\n", n2);

    double mean2 = calculate_mean(data2, n2);
    sort_array(data2, n2);

    printf("Sorted data: ");
    print_array(data2, n2);
    printf("\n\n");

    double median2 = calculate_median(data2, n2);

    int *modes2 = (int *)malloc(n2 * sizeof(int));
    if (modes2 == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    int mode_freq2;
    int mode_count2 = calculate_mode(data2, n2, modes2, &mode_freq2);

    printf("--- Results ---\n");
    printf("Mean:   %.2f\n", mean2);
    printf("Median: %.2f\n", median2);
    printf("Mode:   ");
    if (mode_freq2 == 1)
    {
        printf("No mode (all values appear once)\n");
    }
    else
    {
        print_array(modes2, mode_count2);
        printf(" (each appears %d times)\n", mode_freq2);
    }

    free(modes2);

    return 0;
}
