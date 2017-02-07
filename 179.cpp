遇到的坑("compare函数的小科普")
    1. 我最开始定义的compare函数出现Compile Error: comparison does not meet irreflexive requirements, assert(!(a < a))
    即a==b时，a<b = false! 但是 a>=b = true!!! 这个编译错误是因为我的compare函数 在left==right时随意地定义了 return true，于是GG了
    个人感叹：怪不得compare函数的升序排列模板为：return left<right ，如果 return right>=left则会GG (必须保证left==right时,return false)
    2. 当排序后的数组元素有多个 0 时，res不能直接返回"000...0"。因此需要跳过nums数组中前方的 0 ，并且当nums中只有 0 时还需要给res赋值为"0"
For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.
"9">"5","5">"34","34">"3","3">"30"( 330>303，因为"30"的第2个数字"0" < "3"的最后一个数字"3")
算法思想：重定义对于元素left和right的比较函数，如果left在前(应该 return true)，则要求[lr] > [rl]; 如果 left >= right(应该 return false)，则要求 [lr] <= [rl]

算法运行时间过长：由于在排序和组合res时重复地调用了很多次int_str()，为了加速应该设定一个vector<string>存放nums的数字，于是排序函数和组合res时都针对string数组
class Solution {
public:
    static bool compare(int left,int right){//自定义排序函数，使得 left 优先级高于 right
        string l_str,r_str,lr,rl;
        l_str = int_str(left);
        r_str = int_str(right);
        int i = 0;
        lr = l_str+r_str;//如果lr > rl 则return true；如果lr <= rl 则return false
        rl = r_str+l_str;
        
        while(i<lr.length()){
            if(lr[i] > rl[i]){//e.g 134 > 12，因为13412 > 12134
                return true;
            }
            else if(lr[i] < rl[i]){//e.g 301 < 31，因为31301 > 30131
                return false;
            }
            else{//e.g 123456...目前等于 123456...，因为123456..123456.. 目前== 123456...123456
                i++;
            }
        }
        /*
        while(i<lr.length()){//此时l较长，return true 对应l在前的情况[lr]，即对应[lr]]从i开始子串中包含大数字
            if(lr[i] > lr[i-r_len]){// 因为l左侧子串{0...i-1} == r，所以l<r时合成数字[rl]为{r[0]..r[] l[0]...l[size-1]}。
            //l>r时在合成数字[lr]为{l[0]...l[i-1],l[i]...l[size-1] r[0]...r[]}，为了使l>r时的组合数字[lr]>[rl]，只需要满足[lr]中的子串{l[i]...} 与 [rl]的子串{l[0]...}相比是大数即可
                return true;
            }
            else if(lr[i] < lr[i-r_len]){
                return false;
            }
            else{
                i++;
            }
        }

        while(j<rl.length()){//此时r较长，由于return true 对应l在前的情况[lr]，所以return false 对应[rl]从j开始子串 包含大数字
            if(rl[j] > rl[j-l_len]){
                return false;
            }
            else if(rl[j] < rl[j-l_len]){
                return true;
            }
            else{
                j++;
            }
        }
        */
        //return true;//此时left优先级 == right优先级
        return false;//Compare函数必须满足断言 assert(!(a < a))，即a==a时 return falses
    }

    static string int_str(int num){
        stringstream buffer;
        buffer<<num;
        return buffer.str();
    }

    string largestNumber(vector<int>& nums) {
        int i;
        string res;
        sort(nums.begin(), nums.end(), compare);
        for(i=0;i<nums.size();i++){//需要将结果前方的0跳过，nums={0,0,...}
            if(nums[i] != 0){
                break;
            }
        }
        if(i == nums.size()){//避免将0全部取出后，res为""，此时需要为res赋值为"0"
            return "0";
        }
        while(i<nums.size()){
            res += int_str(nums[i]);
            i++;
        }
        return res;
    }
};