题意：判断是否为回文字符串(忽略字母大小写，忽略除了字母和数字以外的其它字符,比如空格)
思想：设置左右两个指针left和right，跳过其它字符后比较[left]==[right] or [left]和[right]都为字母，而且abs([left]-[right])=='a'-'A'（97-65）。
如果不满足则return false，如果直到left>=right都未结束则return true。
另一种思路：在判断[left]和[right]是否互为大小写字母时，可以转换一下思路，比如强制将其中的大写字母通过[]+'a'-'A'转化为小写字母后，再直接比较
class Solution {
public:
    bool is_alpha(char c){
        if((c>='a'&&c<='z')||(c>='A'&&c<='Z')){
            return true;
        }
        return false;
    }

    bool is_numeric(char c){
        if(c>='0' && c<='9'){
            return true;
        }
        return false;
    }

    bool isPalindrome(string s) {
        bool res = true;
        if(s.length()==0){
            return res;
        }
        int left = 0;
        int right = s.length()-1;
        while(left<right){
            while(left<right && (!is_alpha(s[left]) && !is_numeric(s[left]))){
                left++;
            }
            while(right>left && (!is_alpha(s[right]) && !is_numeric(s[right]))){
                right--;
            }
            if(s[left]!=s[right]){
                if(is_alpha(s[left]) && is_alpha(s[right]) && abs(s[left]-s[right])=='a'-'A'){
                    left++;
                    right--;
                }
                else{
                    return false;
                }
            }
            else{
                left++;
                right--;
            }
        }
        return res;
    }
};