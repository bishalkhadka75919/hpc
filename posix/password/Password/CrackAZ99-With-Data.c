#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$H8s0k9/1RQ783G9gF69Xkn.MI.Dq5Ox0va/dFlkknNjO7trgekVOjTv1BKCb.nm3vqxmtO2mOplhmFkwZXecz0",
  "$6$KB$VDUCASt5S88l82JzexhKDQLeUJ5zfxr16VhlVwNOs0YLiLYDciLDmN3QYAE80UIzfryYmpR.NFmbZvAGNoaHW.",
  "$6$KB$LIQ21WOW2T678MQ//wddYygf4uuWaMWVM8vG9Pj9O.7sDQ1GVgmw8KqqNfjjU6BtBgJvE5nXbborTU/uwrnVz1",
  "$6$KB$cU/6LrcqQGvsvRGllyfGDU1Wuvd1roXp.IEr3UYKQjBbT1sdP1PZPrZKrTGfFuRqD97EsgDalOwwn3OedIIjn0"
};
void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}
void crack(char *salt_and_encrypted){
  int l1, l2, l3;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(l1='A'; l1<='Z'; l1++){
    for(l2='A'; l2<='Z'; l2++){
      for(l3=0; l3<=99; l3++){
        sprintf(plain, "%c%c%02d", l1, l2, l3); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("Password Found%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}
int time_difference(struct timespec *start, struct timespec *finish, 
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
 struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  int i;
  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }
clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 
  return 0;
}
