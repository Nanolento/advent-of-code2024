/*
  Advent of Code 2024 Day 2
  Copyright 2024 Jelmer Smit

  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_sign(int x) {
    return x >= 0 ? 1 : -1;
}

int report_safe(int* array, int size) {
    int sign = 0;
    for (int i = 1; i < size; i++) {
        int distance = array[i] - array[i-1];
        if (sign == 0) {
            sign = get_sign(distance);
        }
        printf("val %d and %d have dist of %d. sign = %d\n",
               array[i], array[i-1], distance, sign);
        // do "safety checks"
        if (abs(distance) < 1 || abs(distance) > 3) {
            printf("Distance <1 or >3, unsafe!\n");
            return 0; // unsafe
        }
        if (get_sign(distance) != sign) {
            printf("distance sign does not match! unsafe.\n");
            return 0; // unsafe
        }
    }
    return 1; // safe
}


int* get_report_array(const int* array, int size, int* report_size) {
    int rsize = 0;
    while (rsize < size && array[rsize] != -1) {
        rsize++;
    }
    int* report_array = malloc(rsize * sizeof(int));
    if (!report_array) {
        printf("Failed to allocate memory for the report array.\n");
        free(report_array);
        *report_size = 0;
        return NULL;
    }
    // fill the report array
    for (int i = 0; i < rsize; i++) {
        report_array[i] = array[i];
    }
    *report_size = rsize;
    return report_array;
}


int main() {
    // get input
    int* array = NULL;
    int size = 0;
    int capacity = 0;
    char line[1024];
    int num;
    while (fgets(line, sizeof(line), stdin)) {
        char* ptr = line;
        while (sscanf(ptr, "%d", &num) == 1) {
            if (size + 1 > capacity) {
                if (capacity == 0) {
                    capacity = 4;
                } else {
                    capacity *= 2;
                }
                int* new_array = realloc(array, capacity * sizeof(int));
                if (new_array == NULL) {
                    printf("Failed to allocate more memory to expand array.\n");
                    free(array);
                    return 1;
                }
                array = new_array;
            }
            array[size++] = num;

            // move pointer
            char* next_ptr = strchr(ptr, ' '); // find next space
            if (next_ptr) {
                ptr = next_ptr + 1; // add 1 to skip the space
            } else {
                break; // end of line, since no space was found
            }
        }
        if (size + 1 > capacity) {
            capacity = capacity == 0 ? 4 : capacity * 2;
            int* new_array = realloc(array, capacity * sizeof(int));
            if (new_array == NULL) {
                printf("Failed to allocate more memory to expand array.\n");
                free(array);
                return 1;
            }
            array = new_array;
        }
        array[size++] = -1;
    }
    
    int safe_reports = 0;
    // collect the array and check it.
    for (int i = 0; i < size; i++) {
        if (array[i] == -1) {
            continue; // skip -1's.
        }
        // assemble array
        int report_size;
        int* report_array = get_report_array(&array[i], size - i, &report_size);
        if (report_array) {
            for (int j = 0; j < report_size; j++) {
                printf("%d ", report_array[j]);
            }
            printf("\n");
            if (report_safe(report_array, report_size)) {
                safe_reports++;
            }
        } else {
            printf("Failed to get the report array.\n");
            return 1;
        }
        free(report_array);
        while (array[i] != -1) {
            i++; // skip to next row.
        }
    }
    printf("Safe reports: %d\n", safe_reports);
    return 0;
}
