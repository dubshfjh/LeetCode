边界用例
"10" =>10
"-1" => -1
"123123123123123" => 2147483647
"1.12314" => 1
"   -5211314  " => 5211314
"   -521 1314  " => 521
public class Solution {
    /**
     * @param str: A string
     * @return An integer
     */
    public int atoi(String str) {
        // write your code here
        boolean illegal = false; //表示atoi()在跳过前置空格后，可能出现的几种非法状况：null；空串；只包含+-号；全为空格；包含分界符(非digit)；超出[MIN_VALUE, MAX_VALUE]范围
        if (str == null || str.length() == 0) {//但是本题对于 不同非法状况的处理策略不一致：所有的非digit符号视作 分界符，取第一个分界符前的结果返回； 超出整数范围的positive->MAX；negative->MIN
        	illegal = true;
            return 0;
        }

        int i = 0;
        boolean flag = true;
        double res = 0;
        while (str.charAt(i) == ' ') { //while (str.charAt(i++) == ' ') 会自动将下一层的if()作为while的子块
            //最左侧的空格直接忽略，从第一个 "+/-/digit" 开始后的空格
            i++; //不能直接使用 while(str.charAt(i++)){} ，这样的话如果第一个字符为digit，则必然会忽略第一个合理整数
        }

        if (str.charAt(i) == '-' || str.charAt(i) == '+') {
            flag = str.charAt(i++) == '+';
        }
        if (i == str.length()) {
        	illegal = true;
        	return 0;
        } else {
        	while (i < str.length()) {//如果字符串只包含 "+","-",则认为是不合法字符，应该返回0;此处res==0只是因为没有进入while循环，侥幸保持初值而已！！！
	            char c = str.charAt(i++);
	            if (!isDigit(c)) {//每个非法字符全部视为分界符，E.g. "234a" "234." "234 " ==> 234
	                illegal = true;
	                break;//所谓的非法字符串(本题定义" ","+"," -"," a"这类在分界符之前没有digit的而已)返回0，也只是因为它们的分界符之前是没有整数的！！！
	                // if (c == '.' || c == ' ') {// +-(123.1) or +-(123  1)，此时直接取整数部分即可，小数点后忽略不计
	                //     break;
	                // } else {//不合法字符
	                //     return 0;
	                // }
	            } else {
	                if (res >= Integer.MAX_VALUE) {
	                	illegal = true;
	                    break;
	                }
	                res = res * 10 + (c - '0');
	            }
	        }
	        res = flag ? res : -res; // double a = MAX, double b = MIN; a == MAX返回true，b == MIN 返回true
	        // if (equalDouble(res, Integer.MAX_VALUE) || equalDouble(res, Integer.MIN_VALUE)) {
	        // 	return res;
	        // } else if (res > Integer.MIN_VALUE || res < Integer.MAX_VALUE) {
	        // 	return res;
	        if (res >= Integer.MIN_VALUE && res <= Integer.MAX_VALUE) {
	            return (int) res;
	        } else {
	            return flag ? Integer.MAX_VALUE : Integer.MIN_VALUE;
	        }
        }
        
    }

    boolean isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    boolean equalDouble(double res, int value) {
        return Math.abs(res - value) < 0.00001;
    }
}