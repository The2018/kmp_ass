#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "string_matching.h"

void print_array(int *arr, int size){
  for (int i=0; i<size; i++){
    printf("%d ",arr[i]);
  }
  printf("\n");
}

void short_test (char *text, int N, char * pattern, int M){
	printf("text='%s', pattern='%s'\n", text, pattern);
	int result1 = string_matching_naive(text, N, pattern, M);
	int result2 = string_matching_kmp(text, N, pattern, M);
	printf("Number of occurrences: result1=%d, result2=%d\n", result1, result2);
}

void stress_test(int N, int M){
  static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  srand(time(NULL));  // Initialization, should only be called once.
  
  while (1) {
    int n = rand() % (N-3) + 3;      // Returns a pseudo-random integer between 3 and N.
	int m = rand() % M + 1; 
    
	char *text = malloc(n);
    for (int i=0; i<n; i++){
	  int pos = rand() % (int)(sizeof(charset) -1);
      text[i] = charset[pos];      
    }
	
	char *pattern = malloc(m);
    for (int i=0; i<m; i++){
	  int pos = rand() % (int)(sizeof(charset) -1);
      pattern[i] = charset[pos];      
    }
    
    printf("text='%s', pattern='%s'\n", text, pattern);
	
    int result1 = string_matching_naive(text, n, pattern, m);
    int result2 = string_matching_kmp(text, n, pattern, m);
    
    if (result1==result2)
      printf("OK\n");
    else {
      printf("Wrong answer: correct=%d, got instead=%d\n", result1, result2);
	  exit(0);
	}
	free(text);
	free(pattern);
  }  
}

void performance_test(){
  static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  srand(time(NULL));   

  time_t start, end;

  FILE *fp;
  fp = fopen("performance.csv", "w+");
  fprintf(fp,"N,Naive,KMP");

  for (int N = 10000; N < 1000000; N += 10000){

    fprintf(fp, "\n%d", N);

    char *text = malloc(N+1);
    for (int i=0; i<N; i++){
    int pos = rand() % (int)(sizeof(charset) -1);
      text[i] = charset[pos];      
    }
    text[N] = '\0';
  
    char *pattern = malloc(400+1);
    for (int i=0; i<400; i++){
    int pos = rand() % (int)(sizeof(charset) -1);
      pattern[i] = charset[pos];      
    }
    pattern[400] = '\0';

    double difference1 = 0, difference2 = 0;
    start = clock();
    string_matching_naive(text, N, pattern, 400);
    end = clock();

    difference1 = (double)(end - start)/CLOCKS_PER_SEC;

    start = clock();
    string_matching_kmp(text, N, pattern, 400);
    end = clock();

    difference2 = (double)(end - start)/CLOCKS_PER_SEC;
    fprintf(fp,",%lf,%lf", difference1,difference2);


  }

}

int main(int argc, char **argv ){
  int mode = atoi(argv[1]);
  if (argc < 2){
    printf("To run: test <1> <text> <N> <pattern> <M>\n or test <2> <N> <M>\n or test <3>\n");
    return 0;
   }
   
  if (mode == 1){
	 if (argc < 6){
			printf("To run: test <1> <text> <N> <pattern> <M>\n");
			return 0;
	   }
	   char *text = argv[2];
	   int N = atoi(argv[3]);
	   char *pattern = argv[4];
	   int M = atoi(argv[5]);
	   printf("M=%d\n",M);
	   short_test(text, N, pattern, M);
   }
   
    if (mode == 2){
      if (argc < 4){
        printf("To run: test <2> <N> <M>\n");
        return 0;
       }
     int N = atoi(argv[2]);
     int M = atoi(argv[3]);
     
     stress_test(N, M);
     return 0;
   }
printf("wtf");
    if (mode == 3){
      printf("wtf");
     //int N = atoi(argv[2]);
     //int M = atoi(argv[3]);
      if (argc < 1){
        printf("To run: test <3>\n");
        return 0;
       }
     performance_test();
     return 0;
  }

   return 0;
  
}
