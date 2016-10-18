#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits){//digits中理论上只包含"2-9"几个数字
        int i,j,k,index,size;
        vector<string> int_char(10);
        vector<string> res;
        if(digits.size()==0){
        	return res;//c++已经初始化过了
        }

        //int_char[0]="";
        //int_char[1]="";
        int_char[2]="abc";
        int_char[3]="def";
        int_char[4]="ghi";
        int_char[5]="jkl";
        int_char[6]="mno";
        int_char[7]="pqrs";
        int_char[8]="tuv";
        int_char[9]="wxyz";
		//c++ char是基本不能通过""+char这种方法转换为string的！！！会出现乱码！！！必须声明string s=""; s+char可以构成新的string
		res.push_back("");//提前注入一个""，可以避免判断初次res是否为空的情况
        for(i=0;i<digits.size();i++){
			size=res.size();//必须提前记录固定的size值！
			index=digits[i]-'0';
			//cout<<int_char[index][0]<<endl;
			for(j=0;j<size;j++){
				string temp=res[0];
				res.erase(res.begin());
				for(k=0;k<int_char[index].size();k++){
					res.push_back(temp+int_char[index][k]);
				}
			}
        }
        /*
        for(i=0;i<res.size();i++){
        	cout<<res[i]<<",,,";
        }
        */
        return res;
    }
};

int main(){
	string digits="23";

    Solution sol=Solution();
    sol.letterCombinations(digits);
	system("pause");
    return 0;
}