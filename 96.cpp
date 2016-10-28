首先参照95题的思想，规定当前位置节点的取值范围[low,high]后，对于每个取值i，先计算节点的左子树num1，再计算节点的右子树num2。
num1*num2就是以i节点为根的子树组合数目
PS：当本层节点没有取值 or 只能取1个值时，以该节点为根的子树num都得视为1
当数字过大时，容易超时，参照思想编写动态规划思路
class Solution {
public:
    int numTrees(int n) {
        if(n==0){
            return 0;
        }
        return getoneLayer(1,n);
    }

    int getoneLayer(int low,int high){//取值范围为[low,high]时，本层可以构建的子树数目
        int res=0;
        if(low>high || low==high){//当前节点为NULL || 当前节点只能取1个值，以该节点为根的子树num都得视为1
            return 1;
        }
        for(int i=low;i<=high;i++){//对于本层的每个可取值i，以i为根节点的树 =(不同的左子树num)*(不同的右子树num)
            res += getoneLayer(low,i-1)*getoneLayer(i+1,high);
        }
        return res;
    }
};


class Solution {
public:
    int numTrees(int n) {
        int dp[n+2][n+2];//dp[low][high]，由于k在遍历low-high时，k范围为[1,n]，所以k左子范围为[0,n-1]，k右子范围为[1,n+1]
                        //为了简化对边界条件的计算，直接设置dp大小为n+2
        for(int low=0;low<=n+1;low++){
            for(int high=0;high<=n+1;high++){
                if(low>=high){//low>=high时，该取值区间的子树只有1种组合情况(low>high:NULL,low==high:low)
                    dp[low][high]=1;
                }
                else{//low<high时子树数目的尚需计算，初始化为0
                    dp[low][high]=0;
                }
            }
        }

        for(int low=n-1;low>=1;low--){//low从m-1开始递减,low每次--后，就向左延长1次取值区间
            for(int high=low+1;high<=n;high++){//只需要再计算low<high的情况,high从low+1开始递增,high每次++后，就向右延长1次取值区间
                // cout<<low<<",,"<<high<<":"<<endl;
                for(int k=low;k<=high;k++){
                    dp[low][high]+=dp[low][k-1]*dp[k+1][high];
                    // cout<<"左子:"<<dp[low][k-1]<<".....右子："<<dp[k+1][high]<<"temp_res:"<<dp[low][high]<<endl;
                }
                // cout<<low<<",,"<<high<<":"<<dp[low][high]<<endl;
            }
        }
        return dp[1][n];
    }
};