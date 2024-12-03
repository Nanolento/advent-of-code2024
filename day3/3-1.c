/*
  Advent of Code 2024 Day 3
  Copyright 2024 Jelmer Smit

  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_str_only_digits(char num_str[], int length) {
    for (int i = 0; i < length; i++) {
        if (!isdigit(num_str[i])) {
            return 0;
        }
    }
    return 1;
}


int main() {
    char* command_string = malloc(sizeof(char) * 1024);
    int size = 0;
    char line[1024];
    int capacity = 1024;
    while (fgets(line, sizeof(line), stdin)) {
        for (int i = 0; line[i] != '\0'; i++) {
            if (size + 1 > capacity) {
                capacity *= 2;
                char* new_array = realloc(command_string, capacity * sizeof(char));
                if (new_array == NULL) {
                    printf("Failed to allocate more memory to expand array.\n");
                    return 1;
                }
                command_string = new_array;
            }
            command_string[size++] = line[i];
        }
    }
    char* current = command_string;
    int nums[2];
    int sum = 0;
    while (current) {
        char* next = strstr(current, "mul(");
        if (!next) {
            break;
        }
        current = next + 4;
        char* delim = strchr(current, ',');
        if (!delim) {
            printf("X ");
            break; // end of text reached before finding comma.
        }
        int length = delim - current;
        if (length >= 4) {
            continue; //continue searching since this was garbage, too many nums
        }
        char num_str[length + 1];
        memcpy(num_str, current, length);
        num_str[length] = '\0';
        if (!check_str_only_digits(num_str, length)) {
            // invalid string
            continue;
        }
        int num = atoi(num_str);
        printf("%d*", num);
        nums[0] = num;
        current = delim + 1;
        
        char* end = strchr(current, ')');
        if (!end) {
            break; // broken syntax, no closing parenthesis.
        }
        length = end - current;
        if (length >= 4) {
            printf("X ");
            continue; // too long num.
        }
        char num_str2[length + 1];
        memcpy(num_str2, current, length);
        num_str2[length] = '\0';
        //printf("[%s|%d]", num_str2, length);
        if (!check_str_only_digits(num_str2, length)) {
            // invalid string
            continue;
        }
        num = atoi(num_str2);
        printf("%d ", num);
        sprintf(num_str2, "%d", num);
        
        nums[1] = num;
        current = end + 1;
        sum += (nums[0] * nums[1]);
    }
    printf("\nSum: %d\n", sum);
    free(command_string);
    return 0;
}
