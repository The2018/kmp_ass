#include <time.h>
#include "string_matching.h"

int string_matching_kmp(char *text, int N, char* pattern, int M){
	int count = 0;
	int *overlap_list = overlap_array(pattern, M);
	//printf("overlap function: ");
	//print_array(overlap_list,M);
	
	//TODO - implement kmp search
    int i = 0;
    int j = 0;

    while (i < N){
    	if (text[i] == pattern[j]){
    		i++;
    		j++;
    	}

    	if (j == M){
    		count++;
    		j = overlap_list[j-1];
    	}

    	if (text[i] != pattern[j]){
    		if (j != 0){
    			j = overlap_list[j-1];
    		}
    		else {
    			i++;
    		}
    	}
    }
    
	free(overlap_list);
	return count;
}


 /*
    General computation of an overlap function in linear time:
    overlap function of position i is a length
    of the longest suffix in substring pattern[0:i]
    which is at the same time a prefix of pattern[0:i]
    parameters - pattern: string to be preprocessed, M: pattern length
    return: an array with the values of an overlap function for each pattern position
 */
int * overlap_array(char* pattern, int M){
	int *ol_list = calloc(M, sizeof(int));    

    int pos = 1;  // first is always zero
    while (pos < M){
        int ol_prev = ol_list[pos - 1];

        if (pattern[pos] == pattern[ol_prev])
            ol_list[pos] = ol_prev + 1;
        else {
            int found = 0;
            int j = ol_prev;
            int curr_overlap = ol_prev;
            while (!found && j >= 1){
                if (pattern[pos] == pattern[j]){
                    found = 1;
                    ol_list[pos] = curr_overlap + 1;
				}
                else {// try extend a smaller prefix - based on pattern [ol[pos-1]]
                    curr_overlap = ol_list[j-1];
                    j = ol_list[j-1];
				}
			}
            if (!found) { // compare with the first
                if (pattern[pos] == pattern[0])
                    ol_list[pos] = 1;
			}
		}
        pos++;
	}
    return ol_list;
}

int main(){
	time_t start, end;
	int i = 0;
	double difference;

	start = clock();
	for (i = 0; i < 18000000; i++){
	string_matching_kmp("tictictictac", 12, "tictic", 6);
	}
	end = clock();

	difference = (double)(end - start)/CLOCKS_PER_SEC;
	printf("%lf\n", difference);

	static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  	srand(time(NULL));   
	char *pattern = NULL;
    for (int i=0; i<400; i++){
    int pos = rand() % (int)(sizeof(charset) -1);
      pattern[i] = charset[pos];      
    }
    printf("%s", pattern);

}


