/*
  Advent of Code 2024 Day 1
  Copyright 2024 Jelmer Smit

  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

// from: https://stackoverflow.com/questions/1787996
int sortcomp(const void* elem1, const void* elem2) {
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int main() {
    int* array1 = NULL;
    int* array2 = NULL;
    // since the lists are going to be the same size,
    // we only to need to keep track of one size.
    int size = 0;
    int capacity = 0;
    int a, b;

    while (scanf("%d %d", &a, &b) == 2) {
        if (size + 1 > capacity) {
            if (capacity == 0) {
                capacity = 4; // init to 4.
            } else {
                capacity *= 2; // double it
            }
            int *new_array1 = realloc(array1, capacity * sizeof(int));
            int *new_array2 = realloc(array2, capacity * sizeof(int));
            if (new_array1 == NULL | new_array2 == NULL) {
                printf("Failed to allocate more memory to expand array.\n");
                return 1;
            }
            array1 = new_array1;
            array2 = new_array2;
        }
        array1[size] = a;
        array2[size] = b;
        size++;
    }

    // sort the array
    qsort(array1, size, sizeof(int), sortcomp);
    qsort(array2, size, sizeof(int), sortcomp);
    
    int total_distance = 0;
    int similarity_score = 0;

    // get "similarity"
    for (int i = 0; i < size; i++) {
        int array2count = 0; // amount of times array1[i] appears in array2
        for (int j = 0; j < size; j++) {
            if (array1[i] == array2[j]) {
                array2count++;
            }
        }
        int similarity = array1[i] * array2count;
        similarity_score += similarity;
    }
    
    // now do the puzzle.
    for (int i = 0; i < size; i++) {
        int distance = abs(array2[i] - array1[i]);
        total_distance += distance;
        printf("[1] %d, [2] %d, [D] %d, [T] %d\n", array1[i], array2[i],
               distance, total_distance);
    }
    printf("Total distance: %d\n", total_distance);
    printf("Similarity score: %d\n", similarity_score);

    free(array1);
    free(array2);
    return 0;
}
