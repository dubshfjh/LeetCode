import java.util.ArrayList;
import java.util.List;

public class Leetcode22 {
    public List<String> generateParenthesis(int n) {
        List<String> result = new ArrayList<>();
        if (0 == n) {
            return result;
        }
        recurseGenerate(0, 0, n, "", result);
        return result;
    }

    /**
     * 每一层递归可以加上1个(，或者1个)，但必须保证
     * 1. "( 数目" >= ") 数目"，否则括号对不合法
     * 2. "( 数目" <= limit， 否则递归永远不会停止
     * @param leftBracketNum
     * @param rightBracketNum
     * @param limit
     * @param path
     * @param result
     */
    public void recurseGenerate(int leftBracketNum, int rightBracketNum, int limit, String path, List<String> result) {
        if (leftBracketNum < rightBracketNum || leftBracketNum > limit) {
            return;
        }
        if (limit == rightBracketNum) {
            result.add(path);
            return;
        }
        recurseGenerate(leftBracketNum + 1, rightBracketNum, limit, path + "(", result);
        recurseGenerate(leftBracketNum, rightBracketNum + 1, limit, path + ")", result);
    }
}
