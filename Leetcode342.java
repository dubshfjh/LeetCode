public class Leetcode342 {
    // 所有奇数位都为1的32位整数
    private static final int ALL_ONE_IN_ODD = 0x55555555;
    /**
     * 4^x = 2^（2i），因此它的二进制仅1位为1（满足2^i），而且这个1处于奇数位，（E.g. 1，100,10000）
     * 转换为两个子条件：1) 它为2^i  2)它在任意1个奇数位取值为1
     * @param num
     * @return
     */
    public boolean isPowerOfFour(int num) {
        if (0 == num) {
            return false;
        }
        boolean isPowerofTwo = (num & num - 1) == 0;
        boolean hasOneInOddBit = (num & ALL_ONE_IN_ODD) == num;
        return isPowerofTwo && hasOneInOddBit;
    }

    public static void main(String[] args) {
        int nums = 1;
        Leetcode342 leetcode342 = new Leetcode342();
        for (int i = 0; i < 32; i++) {
            if (leetcode342.isPowerOfFour(nums)) {
                System.out.println("i = " + i + ", nums = " + nums);
            } else {
                System.out.println("not power of 4, i = " + i + ", nums = " + nums);
            }
            nums = nums << 1;
        }
    }
}
