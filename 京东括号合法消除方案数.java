当 A,B 分别合法时，{AB}本身也合法，将大问题拆解到最小粒度(合法A,合法B,合法C...)，先计算小问题再累乘得到大问题：
A合法去除方法数 * B合法去除方法数 * C合法去除方法数 * ...

1. 按照题目的思考顺序，从“删除每个左括号”的角度出发，判断从stack中该 左括号 ==> 栈顶路程中, 有几个"尚可用于抵消"的右括号
2. 由于初始字符串s为合法字符串，所以对每个s[i]而言，{0...i}段的 左括号数 >= 右括号数；{i + 1...n - 1}段 的左括号数 <= 右括号数
3. 因此只需要从s[n - 1]开始遍历，分析每个 '(' 的右半段 还剩下几个 能抵消的 ')'，并且自身抵消掉栈顶的 1 个')'
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        while (in.hasNext()) {
            String s = in.nextLine();
            char []cs = s.toCharArray();
            Stack<Character> stack = new Stack<>();
            int count = 1;
            for(int i = cs.length-1; i>=0; i--) {
                if(cs[i] ==')'){
                    stack.push(cs[i]);
                } else {
                    count *= stack.size();
                    stack.pop();
                }
            }
            System.out.println(count);
        }
    }
}

换位思考，既然初始字符串s为合法括号串, 即对每个s[i]而言，{0...i}段的 左括号数>=右括号数；{i + 1...n - 1}段 的左括号数 <= 右括号数
那么 "删除每个左括号，判断右侧还剩几个右括号可以抵消"  <==>  "删除每个右括号, 判断左侧还剩几个左括号可以抵消"
因此只需要从s[0]开始遍历，分析每个 ')' 的左半段 还剩下几个 能抵消的 '('，并且自身抵消掉栈顶的 1 个'('

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            String s = sc.nextLine();

            int res = calBracket(s);
            System.out.println(res);
        }
    }

    static int calBracket(String s) { //当A,B分别合法时，AB本身也合法，将大问题拆解到最小粒度(合法A,合法B,合法C...)，先计算小问题再累乘得到大问题：A合法去除方法数*B合法去除方法数*C...
        char[] brackets = s.toCharArray();
        Stack<Character> stk = new Stack<>();
        int res = 1;
        for (int i = 0; i < s.length(); i++) {
            if (brackets[i] == '(') {
                stk.add('(');
            } else {
                res *= stk.size();
                stk.pop();
            }
        }
        return res;
    }
}


