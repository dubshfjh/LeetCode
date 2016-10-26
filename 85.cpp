本题相当于84的推广，84中的每个柱子(高为n)可以转换为底部为n个1，顶部用0填充的平面矩阵
对85题中的平面矩阵从某一行横切，假设上半部分为柱状图，则只要从第0行到第n-1行每一行切一次（从第i行横切，并与上面的i-1行组合得到新图），
就会有n个不同柱状图。每个柱状图求最大矩形，最后复杂度为O(n*m)，n和m分别为矩阵的行和列。


关于生成柱状图，因为我们已经知道从row-1行切开生成的柱状图的“形状”，对于row行来说，如果matrix[row][j]==’0’说明该行与上一行脱节了，
不能将其计算进入矩形，所以直接另该列高度为0.否则该列高度为上一行的高度加1。
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.size()==0 || matrix[0].size()==0){
            return 0;
        }
        int res=0;
        vector<int> height(matrix[0].size(),0);
        for(int row=0;row<matrix.size();row++){
            createHistograph(matrix,height,row);
            stack<int> height_stk;
            for(int i=0;i<height.size();i++){//分析第row行的每一列，对每一行加入后构成的新柱状图使用84题的解法
                if(height_stk.empty() ||height_stk.top() <= height[i]){
                    height_stk.push(height[i]);
                }
                else{//height[top]>height[i]
                    int count=0;
                    while(!height_stk.empty() && height_stk.top() > height[i]){
                        count++;
                        res=max(res,height_stk.top()*count);
                        height_stk.pop();
                    }

                    while(count--){
                        height_stk.push(height[i]);
                    }
                    height_stk.push(height[i]);
                }
            }

            int count=1;
            while(!height_stk.empty()){
                res=max(res,height_stk.top()*count);
                count++;
                height_stk.pop();
            }
        }
        return res;
    }

    void createHistograph(vector<vector<char>> matrix,vector<int>& height,int row){
        // cout<<"row: "<<row<<endl;
        for(int i=0;i<matrix[0].size();i++){
            height[i]=(matrix[row][i]=='0')?0:height[i]+1;
            // cout<<i<<": "<<height[i]<<",";
        }
    }
};


网上的思路都差不多，不过在计算每一层柱状图的面积方面，其余的做法貌似优化程度更高一点
所谓的动态规划思想，大概就是用在求height数组上吧

int largestRectangleArea(vector<int> &height) {
        int maxArea = 0;
        int n = height.size();//共有n列
        stack<int> st;//st存储元素的下标
        int h, w;

        for (int i = 0; i < n; i++) {
            if (st.empty() || height[st.top()] < height[i])//对于递增序列则push进去
                st.push(i);
            else {
                while (!st.empty() && height[st.top()] > height[i]) {//不停地pop掉大于[i]的栈顶，由于栈中元素已经保存了下标
                    h = height[st.top()];                           //所以当pop掉count个元素之后，没必要再push 额外count个height[i]进栈了
                    st.pop();                                       //在pop了此时栈顶后，刚才pop掉的元素下标为top()+1，该元素与i之间的线长=（点数-1）= i-(top()+1)
                    w = st.empty() ? i : i - (st.top() + 1);
                    maxArea = max(maxArea, h * w);
                }
                st.push(i);
            }
        }

        return maxArea;
    }

