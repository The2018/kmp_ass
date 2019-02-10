#include "string_matching.h"

int string_matching_naive(char *text, int N, char* pattern, int M){
	int count = 0;

	for (int i = 0; i < N - M + 1; i++){
		for (int j = 0; j < M;  j++){
			if (text[i+j] != pattern[j]){
				break;
			}
			if (j == M-1) {
			count += 1;
			}
		}
	}
	return count;
}
