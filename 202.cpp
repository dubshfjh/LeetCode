Happy number要求循环地将(n每位数字的平方和)作为新的n，直到某次的n=1，之后每次的new_n都为1
类比求166判断分数是否为"无限循环小数"的思想：如果第j次循环的n_j不为1，而且n_j == 第i次循环的n_i，则n_j之后的new_n将取{n_i...n_j-1}这种循环
踩到的坑：
    Happy NUmber不能使用sum%10==0来判断，因为可能某一步的sum==1，此时sum%10 == 1，所以只能将 sum == 1作为判断条件
class Solution {
public:
    bool isHappy(int n) {
        int sum;
        map<int,bool> new_n;//标识当前的sum是否在之前的循环中出现过
        while(true){
            sum = 0;
            for(;n>0;n/=10){
                sum += (n%10)*(n%10); 
            }
            // cout<<sum<<endl;
            if(new_n.find(sum) != new_n.end()){
                if(sum == 1){//ps:不能使用sum%10==0来判断，因为可能某一步的sum==1!!!
                    return true;
                }
                else{
                    return false;
                }
            }
            new_n[sum] = true;
            n = sum;
        }
        return false;
    }
};