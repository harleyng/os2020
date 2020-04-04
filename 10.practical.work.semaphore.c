#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock; 

int isPrime(int n, int i) {
    if (i == 1) return 1;
    else
    {
        if (n % i == 0) return 0;
        else
        {
            return isPrime(n, i - 1);
        }
    }
}
void *func1() {
    pthread_mutex_lock(&lock); 
    int n = 2;
    printf("Print all prime numbers from 2 to 1.000.000: ");
    while (n <= 10000) {
        int check = n/2;
        if (isPrime(n, check) == 1) {
            printf ("%d ",n);
        } 
        n++;
    }
    pthread_mutex_unlock(&lock); 
}
void *func2() {
    pthread_mutex_lock(&lock); 
    int a = 1, b = 1, c = 0;
    printf("Print all numbers in Fibonacci sequence from 2 to 1.000.000: ");
    while (c <= 10000) {
        c = a + b;
        a = b;
        b = c;
        printf ("%d ",c);
    };    
    pthread_mutex_unlock(&lock); 
}
int main() {
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
    pthread_t id1, id2;
    pthread_create(&id1, NULL, func1, NULL);
    pthread_create(&id2, NULL, func2, NULL);
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    pthread_mutex_destroy(&lock); 
    return 0;
}