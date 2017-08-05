每次从 剩余序列中 删除第m个元素，然后从下一个元素开始重新报数0，报数到 m 的元素再次删除
1. 记每次删除的元素报数号为 k，则 k = (m - 1) % n
2. 设 f(n, m) 为从 n 个元素序列中循环删除 m 个元素后，最后剩下的 元素序号
3. 分析 f(n, m) 删除第 k 个元素后，新格式的序列为 {k+1, k+2...n, 1, 2...k-1}，因此 f(n, m) = g(n-1, m)
	g(n-1, m)代表从长度为 n-1 的新格式序列中 循环删除第 m 个元素，最后剩下的 元素序号
4. 新格式序列中元素的序号 newx：  k+1, k+2 ... 1, 2, ... , k-1
   旧格式序列中元素的序号 oldx：  0,	  1,	  ...	 , n-2
将新序列的元素序号 映射到 长度为n-1的旧格式序列中： newx = (oldx + k + 1) % n
由于 f(), g() 最终的结果也是元素序号，所以将new转化为oldx的表现形式： g(n-1, m) = (f(n-1, m) + k + 1) % n

5. 由于 k = (m - 1)%n，f(n, m) = g(n-1, m) = (f(n-1, m) + m) % n；公式里的n并非初始size n !!!! 而是指删除几次元素后的当前size 
6. 当 n = 1时最后剩下的元素必然为第0个元素, f(1, m) = 0

public class Solution {
    public int LastRemaining_Solution(int n, int m) {
        if (m <= 0 || n <= 0) {
            return -1;
        }
        int[] index = new int[n];
        index[0] = 0;
        for (int i = 2; i <= n; i++) {
        	// index[i - 1] = (index[i - 2] + m) % n;公式里的n并非初始size n !!!! 而是指删除几次元素后的当前size!!!
        	index[i - 1] = (index[i - 2] + m) % i;
        }
        return index[n - 1];
    }
}


递归版，此时每一层的 n 代表当前的规模，相当于 迭代版的 i

public class Solution {
    public int LastRemaining_Solution(int n, int m) {
    	if (n <= 0 || m <= 0) {
    		return -1;
    	} else if (n == 1) {
    		return 0;
    	} else {
    		int subRes = LastRemaining_Solution(n - 1, m);
    		return (subRes + m) % n;
    	}
    }
}