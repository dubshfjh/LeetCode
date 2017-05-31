他人的优雅解法：一次性分割字符串，将String转化为Stream后进行操作
public class Solution {
    public String fractionAddition(String expression) {
        Scanner sc = new Scanner(expression).useDelimiter("/|(?=[+-])");//分隔符包括 {/} {Special constructs(?=X)：X, via 宽度为0的 positive lookahead}，避免将第一个代表正负的加减号当作分隔符
        int preNume = 0;
        int preDenomi = 1;
        while (sc.hasNext()) {
            int curNume = sc.nextInt();//如果分子前为-，则nextInt()将自动将分子转化为负数
            int curDenomi = sc.nextInt();
            preNume = preNume*curDenomi + curNume*preDenomi;
            preDenomi *= curDenomi;
            int curgcd = gcd(preNume, preDenomi);
            preNume /= curgcd;
            preDenomi /= curgcd;
        }
        return preNume + "/" + preDenomi;
    }

    private int gcd(int x, int y) {//gcd 直接返回最大公约数的"绝对值"即可
        int temp;
        while ((temp = x % y) != 0) { //若 x<y (e.g 2/5)，则第一次 temp = 2 = x，于是第一次实质上就交换了x和y的值 x = 5,y = temp = 2
            x = y;
            y = temp;
        }
        return Math.abs(y);
    }
}
/*
public class Solution {
    int gcd(int x, int y) {
        int temp;
        // if(x < y) {
        //     temp = x;
        //     x = y;
        //     y = temp;
        // }

        while ((temp = (x % y)) != 0) {
            x = y;
            y = temp;
        }
        return y;
    }

    int ngcd(int[] nums){
        int res = nums[0];
        for (int i = 1; i < nums.length; i++) {
            res = gcd(res, nums[i]);
        }
        return res;
    }

    int nlcm(List<Integer> nums){//x,y的最小公倍数 = (x*y)/(x,y的最大公约数)
        int res = nums.get(0);
        for (int i = 1; i < nums.size(); i++) {
            res = (res * nums.get(i)) / gcd(res, nums.get(i));
        }
        return res;
    }

    public String fractionAddition(String expression) {
        boolean positive = true;
        StringBuilder twoNum = new StringBuilder();
        List<Integer> numerator = new ArrayList<Integer>();
        List<Integer> denominator = new ArrayList<Integer>();
        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);
            if (i == expression.length() - 1 || (c != '+' && c != '-')) {//将所有非分隔符的元素，以及作为分隔符的last char 记录在twoNum中
               twoNum.append(c);
            }
            if (c == '-' || c == '+' || i == expression.length() - 1) {//当遇到分隔符时
                if (i > 0) {//如果此时的c不是开头的'负'号，则说明[...i-1]为1个分数，需要记录
                    String[] temp = twoNum.toString().split("/");
                    int tempNumerator = Integer.parseInt(temp[0]);
                    numerator.add(positive ? tempNumerator : -tempNumerator);
                    denominator.add(Integer.parseInt(temp[1])); // 此时已经将last char 添加到了 twoNum 里面，所以 temp数组.length == 2，不需要再单独分析最后的分母了
                    //当最后一个数字为 3/10时，twoNum=="3/1"，c=='0'，如果不将last char与前面拼接"3/1"+"0"，则认为最后的分母为"0"... denominator.add(temp.length == 2 ? Integer.parseInt(temp[1]) : c - '0');
                    twoNum.delete(0,twoNum.length());
                }
                positive = (c == '+');
            }
//            else {
//                twoNum.append(c);
//            }
        }

        int leastCM = nlcm(denominator);
        int tempres = 0;
        String res = "";
        for(int i = 0; i < denominator.size(); i++) {
            tempres += leastCM / denominator.get(i) * numerator.get(i);
        }
        if(tempres % leastCM == 0){ //只有当 b == 2^n时，a%b == a&(b-1)
            tempres /= leastCM;
            res = tempres + "/1";
        }
        else{
            //int tempgcd = gcd(tempres, leastCM); //由于分母必然都 > 0，所以 leastCM > 0 ,因此总体结果的正负由 分子累加和的正负决定， 在计算 分子分母的 最大公约数时取正数即可
            int tempgcd = Math.abs(gcd(tempres, leastCM));
            res = (tempres/tempgcd) + "/" + (leastCM/tempgcd);
        }
        return res;
    }
}
*/

个人解法，a/b + c/d + e/f + ... 一次性计算出所有分母的最小公倍数后，再对分子进行累加，其实没必要这样啊，依次计算相邻的两个数即可：
令temp = (ad + cb)/(bd)，对temp的分子分母z同时约去二者的gcd，然后依次向后计算 temp + (e/f)
public class Solution {
    int gcd(int x, int y) {
        int temp;
        // if(x < y) {
        //     temp = x;
        //     x = y;
        //     y = temp;
        // }
        while ((temp = (x % y)) != 0) {
            x = y;
            y = temp;
        }
        return y;
    }

    int ngcd(int[] nums){
        int res = nums[0];
        for (int i = 1; i < nums.length; i++) {
            res = gcd(res, nums[i]);
        }
        return res;
    }

    int nlcm(List<Integer> nums){//x,y的最小公倍数 = (x*y)/(x,y的最大公约数)
        int res = nums.get(0);
        for (int i = 1; i < nums.size(); i++) {
            res = (res * nums.get(i)) / gcd(res, nums.get(i));
        }
        return res;
    }

    public String fractionAddition(String expression) {
        boolean positive = true;
        StringBuilder twoNum = new StringBuilder();
        List<Integer> numerator = new ArrayList<Integer>();
        List<Integer> denominator = new ArrayList<Integer>();
        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);
            if (i == expression.length() - 1 || (c != '+' && c != '-')) {//将所有非分隔符的元素，以及作为分隔符的last char 记录在twoNum中
               twoNum.append(c);
            }
            if (c == '-' || c == '+' || i == expression.length() - 1) {//当遇到分隔符时
                if (i > 0) {//如果此时的c不是开头的'负'号，则说明[...i-1]为1个分数，需要记录
                    String[] temp = twoNum.toString().split("/");
                    int tempNumerator = Integer.parseInt(temp[0]);
                    numerator.add(positive ? tempNumerator : -tempNumerator);
                    denominator.add(Integer.parseInt(temp[1])); // 此时已经将last char 添加到了 twoNum 里面，所以 temp数组.length == 2，不需要再单独分析最后的分母了
                    //当最后一个数字为 3/10时，twoNum=="3/1"，c=='0'，如果不将last char与前面拼接"3/1"+"0"，则认为最后的分母为"0"... denominator.add(temp.length == 2 ? Integer.parseInt(temp[1]) : c - '0');
                    twoNum.delete(0,twoNum.length());
                }
                positive = (c == '+');
            }
//            else {
//                twoNum.append(c);
//            }
        }

        int leastCM = nlcm(denominator);
        int tempres = 0;
        String res = "";
        for(int i = 0; i < denominator.size(); i++) {
            tempres += leastCM / denominator.get(i) * numerator.get(i);
        }
        if(tempres % leastCM == 0){ //只有当 b == 2^n时，a%b == a&(b-1)
            tempres /= leastCM;
            res = tempres + "/1";
        }
        else{
            //int tempgcd = gcd(tempres, leastCM); //由于分母必然都 > 0，所以 leastCM > 0 ,因此总体结果的正负由 分子累加和的正负决定， 在计算 分子分母的 最大公约数时取正数即可
            int tempgcd = Math.abs(gcd(tempres, leastCM));
            res = (tempres/tempgcd) + "/" + (leastCM/tempgcd);
        }
        return res;
    }
}