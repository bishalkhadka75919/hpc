#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
/***
Cracking Password with three initial and two numbers encrypted Password by using a simple
  "brute force" algorithm.Works on passwords that consist only of 3 uppercase
  letters and a 2 digit integer.
  Compile with:
    cc -o threeinitial threeinitial.c -lcrypt
To run and store the result in txt file:
    ./threeinitial > resultthreeinitial.txt
***/
int no_of_passwords = 4;
char *encrypted_passwords[] = {
  "$6$KB$/B53sd.H45Cys4TU2/BQm.PcsoxGwNJWJfncz502dUks7KzswAQRhrtuMr2G1L17uPV05TkxzGLaanzmWf5.z0",
  "$6$KB$nQJZ3xbUH4nWxYKkBtO1jIPjCkd6gZ00FKK88k2AFM43PGzxRHr34ZFNQcPMRp8pMiYDwiGlr2xtZg0heqv.I.",
  "$6$KB$PLEw.VlzhUdt7y1Lo04CUpFjlZpLg3uXR4Ob77pw1YCZFYxf4rRwqjwW53gONjZYJpfTogYiXCQXe1mV2yito/",
  "$6$KB$9Kf9hYiattXoyh4rTJI2ORr9EXy.eK4kToz8xG8U83Ky6vAl3XwErM.393EgpdJ1mBssJ5u/pBWnlDdDKrma7."
};
//returns the substring of given string between two given indices.
void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}
/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, password found is put at the 
 start of the line.
*/
void crack(char *salt_and_encrypted){
  int l1, l2, l3,l4;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);
  // l1, l2, l3 and l4 are four loop variables
  for(l1='A'; l1<='Z'; l1++){
    for(l2='A'; l2<='Z'; l2++){
	for(l3='A'; l3<='Z'; l3++){
       for(l4=0; l4<=99; l4++){
        sprintf(plain, "%c%c%c%02d", l1, l2, l3, l4); 
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
//calculating time difference 
 struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  int i;
  for(i=0;i<no_of_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }
clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 
  return 0;
}
