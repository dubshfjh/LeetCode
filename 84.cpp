首先想到一种最直观的方法：把平面看做大矩阵，条形看做1，非条形看做0，寻找最大全1矩阵。

思路上是正确的，可以用DP来做，不过会超时。

 

网上看到一种借助栈的做法，代码很漂亮，但是解释都非常模糊，我看懂之后，决定仔细描述思路如下：

1、如果已知height数组是升序的，应该怎么做？

比如1,2,5,7,8

那么就是(1*5) vs. (2*4) vs. (5*3) vs. (7*2) vs. (8*1)

也就是max(height[i]*(size-i))

2、使用栈的目的就是构造这样的升序序列，按照以上方法求解。

但是height本身不一定是升序的，应该怎样构建栈？

比如 2,1,5,6,2,3

（1）2进栈。s={2}, result = 0

（2）1比2小，不满足升序条件，因此将2弹出，并记录当前结果为2*1=2。

将2替换为1重新进栈。s={1,1}, result = 2

（3）5比1大，满足升序条件，进栈。s={1,1,5},result = 2

（4）6比5大，满足升序条件，进栈。s={1,1,5,6},result = 2

（5）2比6小，不满足升序条件，因此将6弹出，并记录当前结果为6*1=6。s={1,1,5},result = 6

2比5小，不满足升序条件，因此将5弹出，并记录当前结果为5*2=10（因为已经弹出的5,6是升序的）。s={1,1},result = 10

2比1大，将弹出的5,6替换为2重新进栈。s={1,1,2,2,2},result = 10

（6）3比2大，满足升序条件，进栈。s={1,1,2,2,2,3},result = 10

栈构建完成，满足升序条件，因此按照升序处理办法得到上述的max(height[i]*(size-i))=max{3*1, 2*2, 2*3, 2*4, 1*5, 1*6}=8<10

综上所述，result=10
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res=0;
        stack<int> mystk;
        for(int i=0;i<heights.size();i++){
            if(mystk.empty()){
                mystk.push(heights[i]);
            }
            else{
                if(mystk.top()<=heights[i]){
                    mystk.push(heights[i]);
                }
                else{
                    int count=0;
                    while(!mystk.empty() && mystk.top()>heights[i]){//将大于heights[i]的值全部pop出来，并按照这个升序的大值序列更新res
                        count++;
                        res=max(res,mystk.top()*count);//因为mystk只存储升序数字，所以栈的取值由底至顶依次增加
                        mystk.pop();
                    }

                    while(count--){//将被pop出来的count个大值全部替换为当前的heights[i]入栈
                        mystk.push(heights[i]);
                    }
                    mystk.push(heights[i]);//将[i]本身push入栈
                }
            }
        }

        int count=1;
        while(!mystk.empty()){
            res=max(res,mystk.top()*count);
            count++;
            mystk.pop();
        }

        return res;
    }
};