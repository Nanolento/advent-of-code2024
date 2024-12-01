/*
Advent of Code 2024 Day 1
Copyright 2024 Jelmer Smit

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

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
  while (size > 0) {
	int smallest1 = array1[0];
	int smallest2 = array2[0];
	int s1index = 0;
	int s2index = 0;
	for (int i = 1; i < size; i++) {
	  if (smallest1 < array1[i]) {
		s1index = i;
		smallest1 = array1[i];
	  }
	  if (smallest2 < array2[i]) {
		s2index = i;
		smallest2 = array2[i];
	  }
	}
	int distance = abs(smallest2 - smallest1);
	total_distance += distance;
	printf("[1] %d, [2] %d, [D] %d, [T] %d\n", smallest1, smallest2,
		   distance, total_distance);
	// shrink arrays.
	array1[s1index] = array1[size - 1];
	array2[s2index] = array2[size - 1];
	size--; // this does not free memory, but lowers the
	        // logical size.
  }
  printf("Total distance: %d\n", total_distance);
  printf("Similarity score: %d\n", similarity_score);

  free(array1);
  free(array2);
  return 0;
}
