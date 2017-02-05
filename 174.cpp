"核心思想错了！！！！ 在[i][j]处能满足最小初始HP的路径，不一定是min(init_hp[i-1][j], init_hp[i][j-1])对应的那条！！！"
"因为当[i][j]为较大负数时，尽量优秀的temp1 比 尽量优秀的temp2更重要，所以init_hp[i-1][j]/[i][j-1]中较小的点不一定为最佳路径
参见下方测试用例中计算init_hp[1][2]的情况"
"修正思路：只使用一个dp[i][j]存储：为保证King在走过[row-1][col-1]点("即接受了右下角的兵力补充/战斗损耗")后的HP>=1，在[i][j]点要求初始点提供的额外兵力。
    逆向地从右下角分析到左上角。由于在经过右下角的点[row-1][col-1]后，需要保证HP>=1。为了简化代码设置dummy position，
    认为King在到达[row-1][col-1]之后仍然需要downwards到达[row][col-1]，或者rightward到达[row-1][col]。
    由于要求 最少HP && 到达[row][col-1]和[row-1][col]这两点时的HP>=1，所以初始化dp[row][col-1]=1，dp[row-1][col]=1"

1 -3   3
0 -2   0
-3 -3 -3
i,j,temp1,temp2，init_hp
0,1,-2,,-2,,3
0,2,1,,-2,,3

1,0,1,,1,,1
2,0,-2,,-2,,3//"3"所在点，此时init_hp[0][2]=3，temp2[0][2]=-2(较差的temp2),temp1[0][2]=3(较优的temp1)

1,1,-1,,-1,,2//"-2"所在点，此时init_hp[1][1]=2，temp2[1][1]=-1(较优的temp2),temp1[0][2]=-1(较差的temp1)
1,2,-1,,-1,,2//"0"所在点，此时init_hp[1][1] < init_hp[0][2]，乍一看应该选择[1][1]作为前一点
//但实际上[0][2]的正增益temp1很优秀，若选择[1][1]作为pre，则init_hp[1][2]=3；若选择[0][2]作为pre，则init_hp[1][2]=1

2,1,-4,,-4,,5
2,2,-4,,-4,,5

/*
动态规划：dp[i][j]：从左上角到达[i][j]格子的累积HP消耗，到达[i][j]有2种方法：1.从[i][j-1]downward  2.从[i-1][j]rightward
同时需要保证从[0][0]到[i][j]的过程中每一步的HP都>0
temp1 = [i][j] + max{[i][j-1],[i-1][j]} //我们希望 (增益 - 损耗) 为尽量大的 剩余增益
temp2 = min{[0][0]到[i][j]路径上每一点的剩余增益} //存储整条路径上最小的每一步增益，因为要保证最差步的临时hp>=1，e.g. [0][0]到[i][j]的路径为[0,0],[0,1],[1,1]...[i-1][j],[i][j]，则king在[0,0],[0,1],[1,1]...[i-1,j],[i,j]的每一步的HP都需要>=1
 //设当前路径上任意两点为[i-1][j]和[i][j]，到达[i-1][j]之前的temp1 = -1,temp2 = -2,[i-1][j]=-5000，而[i][j]=5001
 //则[i-1][j]的temp1 = -5001,temp2 = -5002，init[i-1][j]=5003；[i][j]的temp1=-5001+5001=0,temp2 = min(-5002,[i][j]对应的temp1) = min(-5002,0) = -5002，init[i][j]=5003
以[i][j]为终点所需的init_hp = (min{temp1,temp2}>=0)?1:1+abs(min{temp1,temp2})

初步思路："设定三维数组dp[i][j][3]。dp[i][j][0]为temp1，存储到[i][j]时的整体累计消耗；dp[i][j][1]为temp2，存储到[i][j]每一步的最高消耗(即最小负数)；dp[i][j][2]为以[i][j]为终点所需的init_hp"
简化思路：1.对于[i][j]而言，应该选择min(init_hp[i-1][j],init_hp[i][j-1]) 对应的节点作为前一个节点 2.还是用3个二维数组吧，清晰一点
ps：由于临时最优路径 随时可能遇到 极小负数 使得到[i][j]所需的init_hp极大，此时抵达[i][j]的2条路径都应该放弃，应该考虑从[i][j]之外的节点进入右下角

[[-2,-3,3],[-5,-10,1],[10,30,-5]]
踩到的坑：
    1. [[2],[1]] "行列数很可能不相等！！！！"
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int row = dungeon.size();
        int col = dungeon[0].size();
        if(row < 1 || col < 1){
            return INT_MIN;
        }
        int temp,temp_left,temp_up;
        int temp1[row][col],temp2[row][col],init_hp[row][col];
        temp1[0][0] = temp2[0][0] = dungeon[0][0];
        init_hp[0][0] = (temp1[0][0]>=0)?1:1+abs(temp1[0][0]);
        //初始化从[0][0] rightwards 走到 [0][col-1]
        for(int i=1;i<col;i++){
            temp1[0][i] = temp1[0][i-1] + dungeon[0][i];//存储到[i][j]时的整体累计消耗
            temp2[0][i] = min(temp2[0][i-1],temp1[0][i]);//存储到[i][j]路径上，每一步的最高消耗(即最小负数)
            temp_left = min(temp1[0][i],temp2[0][i]);//要保证king到达[i][j]时HP>=1，需要承担min(累计消耗，每一步的最高消耗)
            init_hp[0][i] = (temp_left >= 0)?1:1+abs(temp_left);//当消耗为非负数时(此时实际上就是增益)，第一步的初始HP为1即可
            //当消耗为负数时，初始HP需要保证在经受了消耗后的hp>=1
            cout<<0<<","<<i<<","<<temp1[0][i]<<",,"<<temp2[0][i]<<",,"<<init_hp[0][i]<<endl;
            
        }
        //初始化从[0][0] downwards 走到 [row-1][0]        
        for(int i=1;i<row;i++){    
            temp1[i][0] = temp1[i-1][0] + dungeon[i][0];
            temp2[i][0] = min(temp2[i-1][0],temp1[i][0]);
            temp_up = min(temp1[i][0],temp2[i][0]);
            init_hp[i][0] = (temp_up>=0)?1:1+abs(temp_up);       
            cout<<i<<","<<0<<","<<temp1[i][0]<<",,"<<temp2[i][0]<<",,"<<init_hp[i][0]<<endl;

        }
        
        //到达[i][j]的路径有着从[i-1][j]downwards，从[i][j-1]rightwards两种选择，应该选择min(init_hp[i-1][j],init_hp[i][j-1])对应的那条路径。因为[i][j]这一点带来的损耗or增益 is same to 这两条路径，所以主要看之前路径的累积损耗
        for(int i=1;i<row;i++){
            for(int j=1;j<col;j++){
                if(init_hp[i-1][j] < init_hp[i][j-1]){//到达[i][j]上邻居[i-1][j]所需的hp更小
                    temp1[i][j] = temp1[i-1][j] + dungeon[i][j];
                    temp2[i][j] = min(temp2[i-1][j], temp1[i][j]);
                    temp = min(temp1[i][j], temp2[i][j]);//temp实际上就是temp_up
                }
                else if(init_hp[i-1][j] > init_hp[i][j-1]){//到达[i][j]左邻居[i][j-1]所需的hp更小
                    temp1[i][j] = temp1[i][j-1] + dungeon[i][j];
                    temp2[i][j] = min(temp2[i][j-1], temp1[i][j]);
                    temp = min(temp1[i][j], temp2[i][j]);//temp实际上就是temp_left
                }
                else{//当上邻居和左邻居所需的初始hp相等时，选择temp1较大(即累积增益较高的那个邻居)
                    cout<<"equal"<<temp1[i-1][j]<<","<<temp1[i][j-1]<<endl;
                    temp = max(temp1[i-1][j], temp1[i][j-1]);
                    temp1[i][j] = dungeon[i][j] + temp;
                    temp2[i][j] = (temp==temp1[i-1][j])?min(temp2[i-1][j],temp1[i][j]):min(temp2[i][j-1],temp1[i][j]);
                    temp = min(temp1[i][j], temp2[i][j]);
                }
                init_hp[i][j] = (temp>=0)?1:1+abs(temp);
                cout<<i<<","<<j<<","<<temp1[i][j]<<",,"<<temp2[i][j]<<",,"<<init_hp[i][j]<<endl;

            }
        }

        return init_hp[row-1][col-1];
    }
};
*/


Use hp[i][j] to store the min hp needed at position (i, j), then do the calculation from right-bottom to left-up.
Note: adding dummy(额外的) row and column would make the code cleaner.

只使用一个dp[i][j]存储：为保证King在走过[row-1][col-1]点("即接受了右下角的兵力补充/战斗损耗")后的HP>=1，在[i][j]点要求初始点[0][0]提供的兵力。
    逆向地从右下角分析到左上角。由于在经过右下角的点[row-1][col-1]后，需要保证HP>=1。为了简化代码设置dummy position，
    认为King在到达[row-1][col-1]之后仍然需要downwards到达[row][col-1]，或者rightward到达[row-1][col]。
    由于要求 最少HP && 到达[row][col-1]和[row-1][col]这两点时的HP>=1，所以初始化dp[row][col-1]=1，dp[row-1][col]=1"

状态转移方程为：need = min(hp[i+1][j], hp[i][j+1]) - dungeon[i][j]
    need：已知经过[i][j]并且向右/向下走一步后，所到达点[i][j+1]/[i+1][j]要求初始点提供的额外兵力后，减去[i][j]点的兵力补充/战斗损耗
    如果[i][j]为较大的正数使得 need <= 0，即[i][j]补充的兵力就可以支撑King"经过"下一步的节点(以及之后的path)，则它不要求初始点提供额外兵力，此时初始点只需要提供最少兵力1即可
    如果[i][j]不够大导致need > 0，则[i][j]自己补充的兵力并不能支撑King"经过"下一步的节点，所以它要求初始点提供need个额外兵力


class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int row = dungeon.size();
        int col = dungeon[0].size();
        //hp[i][j]代表:为保证King在走过[row-1][col-1]点后的HP>=1，在[i][j]点所需要的最小HP。
        //假定King在到达[row-1][col-1]之后仍然需要downwards到达[row][col-1]，或者rightward到达[row-1][col]。
        //增加额外的终点位置[row][col-1]，[row-1][col-1]
        vector<vector<int>> hp(row+1, vector<int>(col+1, INT_MAX));
        hp[row][col-1] = 1;
        hp[row-1][col] = 1;
        for(int i=row-1;i>=0;i--){
            for(int j=col-1;j>=0;j--){//need表示[i][j]点要求初始点提供的额外兵力，如果need<=0，则初始点只需要提供最少兵力1即可
                int need = min(hp[i+1][j], hp[i][j+1]) - dungeon[i][j];
                hp[i][j] = (need <= 0)?1:need;
            }
        }

        return hp[0][0];
    }
};
