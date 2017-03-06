回溯法，定义递归函数compute_sum(int k,int n,vector<int> path),代表本层还有k个数字的指标，还需要凑成数字n，到本层为止已选择的数字序列为path。
对于某一层的递归：如果 k==0 && n==0,则此时的path用初始的k个数凑成了初始的n，保存本层的path后return；如果 k==0 && n!=0，则k个数字的指标已经用完，但没有凑成n，直接return
对于k=3,n=7的情况，为避免找到[1,2,4]后，再去找[1,4,2],[2,1,4]等情况，只需要保证path的[i+1]>[i].
因此当path为空时，本层的i从1开始遍历直到 min(n,9)；当path不为空时，本层的i从 "1+path[末尾元素]"开始遍历直到 min(n,9)。
对于每个i递归分析 compute_sum(k-1, n-i, 在末尾增加了i后的path)
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> path;
        compute_sum(k,n,path);
        return res;
    }

    void compute_sum(int k,int n,vector<int> path){//本层还有k个数字的指标，还需要凑成n
        // cout<<k<<",,"<<n<<endl;
        if(k == 0 && n==0){
            res.push_back(path);
            return;
        }
        else if(k == 0){
            return;
        }
        int i = (path.size()==0)?1:1+path.back();//对于k=3,n=7的情况，为避免找到[1,2,4]后，再去找[1,4,2],[2,1,4]等情况，只需要保证path的[i+1]>[i]，因此当path为空时，本层的i从1开始遍历；当path不为空时，本层的i从 1+path[size-1]开始遍历
        int max = min(9,n);
        for(;i<=max;i++){
            path.push_back(i);
            compute_sum(k-1,n-i,path);
            path.pop_back();
        }
    }
};