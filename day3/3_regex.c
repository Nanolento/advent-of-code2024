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
#include <regex.h>


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
    const char* num_pattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)";
    regex_t regex;
    regmatch_t matches[3]; // full plus two groups
    char* current = command_string;
    int sum = 0;
    if (regcomp(&regex, num_pattern, REG_EXTENDED) != 0) {
        printf("Could not compile regex!\n");
        free(command_string);
        return 1;
    }
    while (regexec(&regex, current, 3, matches, 0) == 0) {
        if (matches[1].rm_so != -1 && matches[2].rm_so != -1) {
            int num1_strlen = matches[1].rm_eo - matches[1].rm_so;
            int num2_strlen = matches[2].rm_eo - matches[2].rm_so;
            char num1_str[num1_strlen + 1];
            char num2_str[num2_strlen + 1];
            memcpy(num1_str, current + matches[1].rm_so, num1_strlen);
            memcpy(num2_str, current + matches[2].rm_so, num2_strlen);
            num1_str[num1_strlen] = '\0';
            num2_str[num2_strlen] = '\0';
            int num1 = atoi(num1_str);
            int num2 = atoi(num2_str);
            sum += (num1 * num2);
        }
        current += matches[0].rm_eo;
    }
    
    regfree(&regex);
    printf("Sum: %d\n", sum);
    free(command_string);
    return 0;
}
