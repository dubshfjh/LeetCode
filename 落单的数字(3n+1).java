对于空间复杂度为 O(1) 的问题分为2种情况：1. 利用参数数组原有的空间，比如二维数组的第1列；
2. 就使用1个常量来解，此时它只能用于统计最终结果

本题思想：位运算，统计每个 int 变量的 32-bit中1的个数，对于出现了3次的元素x，如果x的第 i-bit 为1，则3个x为第i-bit贡献了3个1
于是利用1个变量sum依次统计第 0...32 bit 中1的个数，则 (sum % 3) 即为第 0...32 bit中Single Number的二进制取值


ps: 对于 2*n + 1 中求解 Single Number 问题
1. 可以利用 a xor a = 0的思想，对每一个元素 累计异或得到 single Number
2. 如果A[0...n - 1] 都处于 {1...n}这个范围，则在遇到元素nums[i]时，将 index == abs(nums[i]) - 1 位置的元素取反
	由于其余元素"取反了"偶数次，singleNumber "取反了"奇数次，所以当最后遍历发现 nums[j] < 0，意味着 j + 1 这个元素只执行了"奇数次"取反
	因此 SingleNumber 为 j + 1
	
public class Solution {
	/**
	 * @param A : An integer array
	 * @return : An integer 
	 */
    public int singleNumberII(int[] A) {
        // write your code here
        if (A == null || A.length == 0) {
        	return Integer.MIN_VALUE;
        }
        int res = 0;
        for (int i = 0; i < 32; i++) {
        	int sum = 0;
        	for (int num : A) {
        		sum += (num >> i) & 1; //统计所有数字第i-bit上1的个数
        	}
        	sum %= 3; //sum % (2^i) = sum & (2^i - 1)，相当于取sum的后i位;但是 sum%（2^i - 1）就没有位运算层次的含义了！！！注意别混淆
        	res |= (sum << i);
        }
        return res;
    }
}