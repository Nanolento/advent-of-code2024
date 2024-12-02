/*
  Advent of Code 2024 Day 2
  Copyright 2024 Jelmer Smit

  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

int get_sign(int x) {
    return x > 0 ? 1 : -1;
}

int report_safe(int* array) {
    int sign = 0;
    for (int i = 1; i < 5; i++) {
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


int main() {
    // get input
    int* array = NULL;
    int size = 0;
    int capacity = 0;
    int a, b, c, d, e;
    while (scanf("%d %d %d %d %d", &a, &b, &c, &d, &e) == 5) {
        if (size + 5 > capacity) {
            if (capacity == 0) {
                capacity = 8;
            } else {
                capacity *= 2;
            }
            int* new_array = realloc(array, capacity * sizeof(int));
            if (new_array == NULL) {
                printf("Failed to allocate more memory to expand array.\n");
                return 1;
            }
            array = new_array;
        }
        array[size] = a;
        array[size+1] = b;
        array[size+2] = c;
        array[size+3] = d;
        array[size+4] = e;
        size += 5;
    }
    int safe_reports = 0;
    // check if sorted and 1 <= diff <= 3
    for (int i = 0; i < size; i += 5) {
        printf("Array: %d %d %d %d %d\n",
               array[i],
               array[i+1],
               array[i+2],
               array[i+3],
               array[i+4]);
        if (report_safe(&array[i])) {
            safe_reports++;
        }
    }
    printf("Safe reports: %d\n", safe_reports);
    return 0;
}
