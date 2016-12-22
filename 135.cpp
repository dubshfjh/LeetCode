分析如下：小孩的分数 > 邻居分数时，小孩candy = 邻居candy+1；小孩分数 <= 邻居分数时，小孩candy取尽量小正数 
开出一个O(n)大小的数组，用来记录每个小孩的那糖数，因为每个小孩至少要拿1颗糖，所以数组元素初始化为1.
case 1. 假设有小孩A, B ， rating分别是{1,1},显然每个人各拿1颗糖就够，显然每个人拿糖颗数是{1, 1}，最后答案为2.
case 2. 假设有小孩A, B, C, D, rating分别是{10, 32, 43, 55}, 那么每个人拿糖的颗数依次为{1, 2, 3, 4},最后答案为10. 
    这说明可以顺序扫描数组，找到一个递增序列，拿糖数从1开始递增。比如这里找到了递增序列A, B, C, D, 拿糖数从A = 1开始依次递增。
case 3. 假设有小孩A, B ,C ,D E, F, rating 分别是{10, 32, 43, 55, 40, 40}, 那么每个人拿糖颗数是 {1, 2, 3, 4, 2, 1}， 

直观思路：i = 0,candy[0]=1。使用一次正向遍历，循环寻找递增、递减、递增、递减序列...直至结束。"缺陷"：对于递减序列需要先正向寻找，再反向赋值。"优化"：直接整体反向遍历寻找反向递增序列，并且在反向遍历过程时赋值
    while(i < size-1)
        step 1: 寻找递增序列([i]<=[i+1])，if([i] < [i+1]):candy[i+1]=1+candy[i]；直到遇到某个 i 使得[i]>=[i+1]为止,if([i] >= [i+1]):candy[i+1] = 1
        step 2: 使用变量k从上个[i+1]开始寻找递减序列([i]>[i+1])直到遇到某个j使得[j]<=[j+1]为止，设置candy[j]=1，对于k={i+1,i+2,...j-1}，if([k] > [k+1])：candy[k]=1+candy[k+1]；if([k] == [k+1])：candy[k]=1

优化思路：i = 0,candy_1[0]=1，首先使用一次正向遍历寻找递增序列，一旦遇到[i]>=[i+1]就贪心地设置"正向递减序列"中的candy_1[i+1]=1；
        i = size-1,candy_2[size-1]=1然后使用一次反向遍历寻找反向递增序列(即正向递减)，一旦遇到[i-1]<=[i]就贪心地设置"反向递减序列"中的candy_2[i-1]=1
        对于每个i ，real_candy[i] = max (candy_1[i], candy_2[i])

case 3. 假设有小孩A, B ,C ,D E, F, rating 分别是{10, 32, 43, 55, 40, 40},         
    这说明可以在顺序扫描数组之后，再反序扫描数组，得到反序扫描数组时的递减序列。比如顺序扫描了A, B ,C, D, E, F之后，得到{1, 2, 3, 4, 1, 1}，
    之后再反序扫描数组，找寻递增数列，每段递增数列的拿糖颗数也从1开始递增。反序扫到F，得到F=1, 扫到E 因为E == F, 所以E = 1。扫到D，因为D> E ,所以D= 2，
    是其实这里的D和E， F不一样，D是之前顺序扫描时候已经被赋值过的值，D = 4，而反序扫描的时候，D = 2， 显然只能取大值才能满足要求。
    所以反序扫描的时候，如果遇到已经在顺序扫描中赋值的小孩，要两个值中取较大的值。
上面描述的是贪心算法的思想。

PS：下面的Wong Answer 代码理解错了题目意思，两邻居rating相等时其中一个人的candy可以重新为 1 。如果递增序列中 ratings[i]==ratings[i+1]，则candy[i+1]=1！！！而不要求candy[i+1]=candy[i]！！！
/*
class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.size() <= 1){
            return 1;
        }
        vector<int> candy_1(ratings.size(),1);
        vector<int> candy_2(ratings.size(),1);
        //正向扫描一次，对于正向递增序列设置c[i+1] = c[i]+1 or c[i]，对于正向递减序列贪心地全部设置为1
        for(int i=0;i<ratings.size()-1;i++){
            if(ratings[i] <= ratings[i+1]){
                candy_1[i+1] = (ratings[i] < ratings[i+1])?candy_1[i]+1:candy_1[i];
            }
            else{//其实我设置了candy_1[i]的初值为1，这个代码块都没有必要执行 
                candy_1[i+1] = 1;
            }
        }

        //反向扫描一次，对于反向递增序列设置new_c[i-1] = new_c[i]+1 or new_c[i]，对于反向递减序列贪心地全部设置为1，然后更新new_c[i] = max(new_c[i],c[i])
        for(int i=ratings.size()-1;i>0;i--){
            if(ratings[i-1] >= ratings[i]){
                candy_2[i-1] = (ratings[i-1] > ratings[i])?candy_2[i]+1:candy_2[i];
            }
            else{
                candy_2[i-1] = 1;
            }
        }

        int sum = 0;
        for(int i=0;i<ratings.size();i++){
            cout<<candy_1[i]<<"...."<<candy_2[i]<<endl;
            sum += max(candy_1[i],candy_2[i]);
        }
        return sum;
    }
};
*/


class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.size() <= 1){
            return 1;
        }
        vector<int> candy_1(ratings.size(),1);
        vector<int> candy_2(ratings.size(),1);
        //正向扫描一次，对于正向递增序列设置c[i+1] = c[i]+1 or c[i]，对于正向递减序列贪心地全部设置为1
        for(int i=0;i<ratings.size()-1;i++){
            if(ratings[i] < ratings[i+1]){
                candy_1[i+1] = candy_1[i]+1;
            }
            else{//其实我设置了candy_1[i]的初值为1，这个代码块都没有必要执行 
                candy_1[i+1] = 1;
            }
        }

        //反向扫描一次，对于反向递增序列设置new_c[i-1] = new_c[i]+1 or new_c[i]，对于反向递减序列贪心地全部设置为1，然后更新new_c[i] = max(new_c[i],c[i])
        for(int i=ratings.size()-1;i>0;i--){
            if(ratings[i-1] > ratings[i]){
                candy_2[i-1] = candy_2[i]+1;
            }
            else{
                candy_2[i-1] = 1;
            }
        }

        int sum = 0;
        for(int i=0;i<ratings.size();i++){
            cout<<candy_1[i]<<"...."<<candy_2[i]<<endl;
            sum += max(candy_1[i],candy_2[i]);
        }
        return sum;
    }
};