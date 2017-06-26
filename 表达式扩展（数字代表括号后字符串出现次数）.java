迭代版思想：使用Stack存放 3[ 2 [ a b ] 3 [ c d]]，每当遇到']'时，就不停地pop栈顶直到遇到'['，再pop一次获取num，
然后将 '[]' 中间部分的子串重复num次后入栈
1. 必须注意字符串的顺序！！！
	a. 在获取 '[]' 中间部分的子串时，以'a b c'为例，由于栈顶依次为c b a，所以 curStr = 栈顶 + curStr
	b. 最后的栈中情况类似 abc de fg，每个元素都是最外层的[]构成的字符串，此时不能 通过 {.append(新栈顶) + reverse} 产生 "cba ed gf"这种
	   而是应该通过 insert(0, 新栈顶) 达到类似于 abc + de + fg的效果
2. 在统计num时，在遇到']'时需要使用当前num ，但'[' 作为 curNum 的终结符（即定界符），
	在遇到'['将当前num入栈后，都必须将num 重置为0，否则会出现 1[a2[b]]出现12个b
	ps: '['作为定界符的情况：1[a 1[b]]，first '[' 时，num = 1,此时若不将num置为0，则遇到'2'时，num = 1*10 + 2 = 12
	// b. ']'作为定界符的情况：2[a] 3[b]，如果在遇到 first']'时
public class Solution {
    /**
     * @param s  an expression includes numbers, letters and brackets
     * @return a string
     */
    public String expressionExpand(String s) {
        // Write your code here
        if (s == null || s.length() == 0) {
            return s;
        }
        Integer num = 0;
        StringBuilder res = new StringBuilder();
        Stack<String> allStr = new Stack<String>();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == ']') {
                String curStr = allStr.pop();
                while (!allStr.peek().equals("[")) {
                    curStr = allStr.pop() + curStr;
//                    curStr += allStr.pop();
                }
                allStr.pop();
                int tempnum = Integer.parseInt(allStr.pop());
                StringBuilder temp = new StringBuilder();
                for (int j = 0; j < tempnum; j++) {
                    temp.append(curStr);
                }
                System.out.println(tempnum);
//                num = 0;
                allStr.push(temp.toString());
            } else if (c == '[') {
                allStr.push(num.toString());
                num = 0; //左右括号都可能为终结符，在遇到终结符时，都需要将num复位！！！否则 1[2[b]1[a]] ==> 2个b 21个a
                allStr.push("[");
            } else if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
            } else {
                allStr.push("" + c);
            }
        }

        while (!allStr.empty()) {
            res.insert(0, allStr.pop());
        }
        //不能用"cd".append("ab")后再reverse，这会产生"badc" res.reverse();
        return res.toString();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            String s = sc.nextLine();
            Solution obj = new Solution();
            System.out.println(obj.expressionExpand(s));
        }
    }
}