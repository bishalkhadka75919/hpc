
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>
/***
Cracking Password using thread with two initial and two numbers encrypted Password by using a simple
  "brute force" algorithm .Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer.
  Compile with:
    cc -o thread thread.c -lcrypt -pthread
To run and store the result in txt file:
    ./thread > p1.txt
***/

int no_of_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$H8s0k9/1RQ783G9gF69Xkn.MI.Dq5Ox0va/dFlkknNjO7trgekVOjTv1BKCb.nm3vqxmtO2mOplhmFkwZXecz0",
"$6$KB$VDUCASt5S88l82JzexhKDQLeUJ5zfxr16VhlVwNOs0YLiLYDciLDmN3QYAE80UIzfryYmpR.NFmbZvAGNoaHW.",
"$6$KB$LIQ21WOW2T678MQ//wddYygf4uuWaMWVM8vG9Pj9O.7sDQ1GVgmw8KqqNfjjU6BtBgJvE5nXbborTU/uwrnVz1",
"$6$KB$cU/6LrcqQGvsvRGllyfGDU1Wuvd1roXp.IEr3UYKQjBbT1sdP1PZPrZKrTGfFuRqD97EsgDalOwwn3OedIIjn0"
};

/**
 Required by lack of standard function in C.  
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found Password found, is put at the
 start of the line. 
*/

void thread(char *encrypted_passwords){

  pthread_t Th1,Th2;

  void *kernel_function_1();
  void *kernel_function_2();

  pthread_create(&Th1, NULL, kernel_function_1, (void *)encrypted_passwords);
  pthread_create(&Th2, NULL, kernel_function_2, (void *)encrypted_passwords);
 
  pthread_join(Th1, NULL);
  pthread_join(Th2, NULL);
}

void *kernel_function_1(char *salt_and_encrypted){
  int bi, sh, al;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(bi='A'; bi<='M'; bi++){
    for(sh='A'; sh<='Z'; sh++){
      for(al=0; al<=99; al++){
        sprintf(plain, "%c%c%02d", bi, sh, al);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("Password found %-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

void *kernel_function_2(char *salt_and_encrypted){
  int bi, sh, al;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(bi='N'; bi<='Z'; bi++){
    for(sh='A'; sh<='Z'; sh++){
      for(al=0; al<=99; al++){
        sprintf(plain, "%c%c%02d", bi, sh, al);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("Password found %-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}


int time_difference(struct timespec *start,
                    struct timespec *finish,
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}
int main(int argc, char *argv[]){
  int i;
 //calculating time difference 
 struct timespec start, finish;  
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i=0;i<n_passwords;i<i++) {
    thread(encrypted_passwords[i]);
  }
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9));
  return 0;
}
