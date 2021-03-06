Given an integer n, return the number of trailing zeroes in n!.//只计算尾部的0数目

Note: Your solution should be in logarithmic time complexity.
对于1*...*i*...n："...000..0" => 在乘法中拆解为"2×5"{a*2^b提供 a 个 2，c*5^b提供b个5}和尾部自带"0"{10,20,100,200...}的情形

由于所有偶数都能提供 1 个以上的 2，所以对于"2×5"的情形只需要考虑"5"的数量,必须注意以 5 结尾的数字不一定只提供1个5 (a*25=5^2都能提供2个5；a*125=a*5^3都能提供3个5)
    对于任何数字n，{1...n}中(a* 5^i)这类能提供i个5的数字，i = log5(n)；a = n/(5^i)。e.g. n=126时，log5(126) = 3.0049, 即126 = 5^3.0049，
    说明n=126时最多提供到a*5^3，由于n/(5^3)=1，所以a=1。
    当i>2时，对于 5^i 需要意识到在之前分析(5^1...5^i-1)时，每次都从5^i中取走了1个5，所以在分析5^i时只需认为多出了1个5即可； 

注意:10^i 属于 (a* 5^i)!!!因此10^i在上面分析(a* 5^i)时已经出现过了!!!不应该重复统计 
PS：当i>2时，对于 5^i 需要意识到在之前分析(5^1...5^i-1)时，每次都从5^i中取走了1个5，所以在分析5^i时只需认为多出了1个5即可； 

class Solution {
public:
    int trailingZeroes(int n) {
        int num_5,num_10;//分别存储 5,10 对应的次幂pow,但是注意10^i 属于 (a* 5^i)!!!因此10^i已经分析过了
        int res = 0;
        num_5 = log(n)/log(5.0);
        // num_10 = log(n)/log(10.0);
        for(int i=1;i<=num_5;i++){
            res += n/(pow(5.0,i));
        }
        //10^i在上面分析(a* 5^i)时已经出现过了!!!不应该重复统计
        // for(int i=1;i<=num_10;i++){
        //     res += n/(pow(10.0,i));
        // }
        return res;
    }
};