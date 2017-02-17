"逻辑错误！！！因为只有{m...2^b-1}能保证第b位为1；2^b在第b位必然取值为0！！！"
/*
设 2^a <= m <= 2^b；2^c <= n <= 2^d，由于d>=c>=b>=a，而且d=c+1,b=a+1
第d+1位   第c+1(第d)位   第b+1位   第a+1(第b)位   第a位
n: 0          1...         ...      ...       ...
n-1
...
2^b -1：0        0...       0         1         1...1
...
m: 0          0...          0         1       ...
由于m的最高位为第a+1位(即第a+2位到第d位都是 0 )，对于递归每一层的m和n而言,(m & m+1 & .. & n) == (m & m+1 & .. & 2^b -1)
因为从m到(2^b -1)的所有数字都为2^a+x，所以这些数字在第 a+1 位的取值都为1，所以本轮递归得到(2^a)这个数值，第a+1位已经分析过了,
下一轮递归中的 new_m == m的 0到a位 == m-2^a ；new_n == (2^b -1)的 0到a位 == 2^(a+1) - 1

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int a,b,c,d,num,res,temp;
        int i,j;
        if(m == 0){
            return 0;
        }
        a = log(m)/log(2);
        c = log(n)/log(2);
        if(a == 0){
            res = m;
            while(m++ < n){
                res &= m;
            }
            cout<<"a==0:"<<res<<endl;
            return res;
        }
        // c = log(n)/log(2);
        temp = 1<<a;
        cout<<m<<",,,"<<n<<",,temp:"<<temp<<endl;
        if(a >= c){
            return temp+rangeBitwiseAnd(m-temp,n-temp);
        }
        else{
            return temp+rangeBitwiseAnd(m-temp,(temp<<1)-1);
        }
    }
};
*/
Consider the bits from low to high. if n > m, the lowest bit will be 0, 
    当n>m时，(n&n-1&...&m)的最低位一定为0！！！原因：不管m的最低位取0/1，(m+1)的最低位必定取对应的1/0
and then we could transfer the problem to sub-problem: rangeBitwiseAnd(m>>1, n>>1)<<1.
    因此，只有当m和n的前k位都相等时(即在某层递归中m==n时)，(m&m+1&...&n)的前k段取值才与m相同，最终结果为 {m的前k位 00....0}

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        if(n > m){
            return (rangeBitwiseAnd(m>>1,n>>1)<<1);
        }
        else{
            return m;
        }
    }
};