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
            int res = obj.calMinNum(s);
            System.out.println(res);
        }
    }

    public int calMinNum(String s) {
        if (s == null || s.length() <= 1) {
            return 0;
        }
        int bwMinNum = helpCal(s, 'B', 'W'); //[0,2,4...]为'b'；[1,3,5...]为'w'
        int wbMinNum = helpCal(s, 'W', 'B'); //
        return Math.min(bwMinNum, wbMinNum);
    }

    public int helpCal(String s, char evenColor, char oddColor) {
        int res = 0;
        for (int i = 0; i < s.length(); i++) {
            if ((i & 1) != 0) {
                if (s.charAt(i) != evenColor) {
                    res++;
                }
            } else {
                if (s.charAt(i) != oddColor) {
                    res++;
                }
            }
        }
        return res;
    }
}
