import java.util.*;
/**
 * Created by dubangshi on 2017/6/17.
 */
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Main obj = new Main();
        while (sc.hasNext()) {
            String s = sc.nextLine();
            int res = obj.calChangeNum(s);
            System.out.println(res);
        }
    }

    public int calChangeNum(String s) {
        if (s == null || s.length() < 1) {
            return 0;
        }
        int length = s.length();
        Set<String> exist = new HashSet<>();
        StringBuilder left = new StringBuilder();
        StringBuilder right = new StringBuilder(s);
        for (int i = 0; i < s.length(); i++) {//依次删除第i个字符
            if (i >= 1) {
                left.append(s.charAt(i - 1));
            }
            StringBuilder temp = new StringBuilder(left);
            right.deleteCharAt(0); //依次将right这个右半字符串的最左1个字符删除
            temp.append(right);
            exist.add(temp.toString());
        }
        return exist.size();
    }
}
