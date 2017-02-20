Hint:

1. Let's start with a isPrime function. To determine if a number is prime, we need to check if it is not divisible by any number less than n. 
    The runtime complexity of isPrime function would be O(n) and hence counting the total prime numbers up to n would be O(n^2). 
    Could we do better?

2. As we know the number must not be divisible by any number > n / 2, we can immediately cut the total iterations half 
    by dividing only up to n / 2. Could we still do better?

3. Let's write down all of 12's factors:

2 × 6 = 12
3 × 4 = 12
4 × 3 = 12
6 × 2 = 12
As you can see, calculations of 4 × 3 and 6 × 2 are not necessary. Therefore, we only need to consider factors up to sqrt(n) 
    because, if n is divisible by some number p, then n = p × q and since p ≤ q, we could derive that p ≤ sqrt(n).

Our total runtime has now improved to O(n1.5), which is slightly better. Is there a faster approach?

4. The Sieve of Eratosthenes is one of the most efficient ways to find all prime numbers up to n. But don't let that name scare you, 
    I promise that the concept is surprisingly simple.

    We start off with a table of n numbers. Let's look at the first number, 2. We know all multiples of 2 must not be primes,
    so we mark them off as non-primes. Then we look at the next number, 3. Similarly, all multiples of 3 such as 
    3 × 2 = 6, 3 × 3 = 9, ... must not be primes, so we mark them off as well. Now we look at the next number, 4, 
    which was already marked off. What does this tell you? Should you mark off all multiples of 4 as well?

以下为"The Sieve of Eratosthenes"的改进
5. 4 is not a prime because it is divisible by 2, which means all multiples of 4 must also be divisible by 2 and were already marked off. 
    So we can skip 4 immediately and go to the next number, 5. Now, all multiples of 5 such as 5 × 2 = 10, 5 × 3 = 15, 5 × 4 = 20, 5 × 5 = 25, ... 
    can be marked off. There is a slight optimization here, we do not need to start from 5 × 2 = 10. Where should we start marking off?

6. In fact, we can mark off multiples of 5 starting at 5 × 5 = 25, because 5 × 2 = 10 was already marked off by multiple of 2, similarly 5 × 3 = 15 was already marked off by multiple of 3. 
    Therefore, if the current number is p, we can always mark off multiples of p starting at p^2, then in increments of p: p^2 + p, 
    p^2 + 2p, ... Now what should be the terminating loop condition?

7. It is easy to say that the terminating loop condition is p < n, which is certainly correct but not efficient. 
    Do you still remember Hint #3?

8. Yes, the terminating loop condition can be p < √n, as all non-primes ≥ √n must have already been marked off. 
    When the loop terminates, all the numbers in the table that are non-marked are prime.

    The Sieve of Eratosthenes uses an extra O(n) memory and its runtime complexity is O(n log log n).
'
时间复杂度为 O(n^1.5)，太容易超时了
class Solution {
public:
    int countPrimes(int n) {//找出<n的质数num
        int res = 0;
        for(int i=2;i<n;i++){//当n<3时，必然没有质数
            if(isPrime(i)){
                res++;
            }
        }
        return res;
    }

    bool isPrime(int n){
        for(int i=2;i*i<=n;i++){//2是第一个质数，i不需要从1开始寻找n的factor
            if(n % i == 0){
                return false;
            }
        }
        return true;
    }
};

The Sieve of Eratosthenes "完全无优化版"
设置一个bool数组标记n是否为prime，初始化每个prime[num]为true。从2开始分析，由于 2*2,2*3...(all 2*i <= n-1) 都不是素数，于是标记prime[2*i]=false；
然后分析next prime[num]为true的数字num，然后标记 (all num*i <= n-1)的prime[num*i]为false。遍历分析每个没在之前被标记prime[j]为false的j直到j == n-1

class Solution {
public:
    int countPrimes(int n) {//找出<n的质数num
        vector<bool> tempPrime(n+1,true);
        int res = 0;
        for(int i=2;i<n;i++){
            if(tempPrime[i]){
                res++;
                for(int j=2;i*j<n;j++){
                    tempPrime[i*j] = false;
                }
            }
        }
        return res;
    }
};

优化：1. 对于j(all 整数*因子i <= n-1),在分析prime[i]==true的i的(j*i)时，不需要从1*i,2*i...(i-1)*i开始分析，因为这些数字在分析1,2...i-1时已经分析过了
      2. 对于因子i,当i分析到int(sqrt(n))时，所有>=sqrt(n)的非质数都必然被标记为false了！
class Solution {
public:
    int countPrimes(int n) {//找出<n的质数num
        vector<bool> isPrime(n+1,true);
        int res = 0;
        // Loop's ending condition is i * i < n instead of i < sqrt(n)
        // to avoid repeatedly calling an expensive function sqrt().
        for(int i=2;i*i < n;i++){
            if(isPrime[i]){
                for(int j=i;i*j<n;j++){
                    isPrime[i*j] = false;
                }
            }
        }

        for(int i=2;i<n;i++){
            if(isPrime[i]){
                res++;
            }
        }
        return res;
    }
};