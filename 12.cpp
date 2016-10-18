罗马字符    I   V   X   L   C   D   M
整数数字    1   5   10  50  100 500 1000

相同的数字连写，所表示的数等于这些数字相加得到的数，如：III = 3；
小的数字在大的数字的右边，所表示的数等于这些数字相加得到的数， 如：VIII = 8；XII = 12；
小的数字，（限于I、X 和C）在大的数字的左边，所表示的数等于大数减小数得到的数，如：IV= 4；IX= 9；
正常使用时，连写的数字重复不得超过三次。（表盘上的四点钟“IIII”例外）
在一个数的上面画一条横线，表示这个数扩大1000倍。（本题用不到这点）
有几条须注意掌握：

1.基本数字I、X、C中的任何一个，自身连用构成数目，或者放在大数的右边连用构成数目，都不能超过三个；放在大数的左边只能用一个。
2.不能把基本数字V、L、D中的任何一个作为小数放在大数的左边采用相减的方法构成数目；放在大数的右边采用相加的方式构成数目，只能使用一个。
3.V和X左边的小数字只能用I，且只能有1个。
4.L和C左边的小数字只能用X，且只能有1个。
5.D和M左边的小数字只能用C，且只能有1个。
看懂了上面的规则后，就可以对数字的每位逐个判断即可。可以归纳出如下4种情形：

如果该位数字是9，则说明是上面3、4、5这三种情况中的一种，即把I、X、C中的一个放到了大数字的左侧；
如果该位数字是5~8，则说明是上面1这种情况，即I、X、C中的一个，自身连用或者放在大数的右边连用；
如果该位数字是4，则说明同样是上面3、4、5这三种情况中的一种，即把I、X、C中的一个放到了大数字的左侧；
如果该位数字是0~3，则同样说明是上面1这种情况，即I、X、C中的一个，自身连用或者放在大数的右边连用。

class Solution {
public:
    string intToRoman(int num) {
        int roman[]={1000,100,10,1};
        char ch_1[]={'M','C','X','I'};
        char ch_2[]={' ','D','L','V'};//1000在本项目中无需对应更大的数，注意字符初始化为' '可以，但不能为''!!!!!
        int temp,temp_1;
        string res="";
        for(int i=0;i<4;i++){
    		temp=num/roman[i];
    		if(temp==9){
    			res=res+ch_1[i]+ch_1[i-1];//例子：当roman/100=9时，res+="CM"，此时roman[i]=100,ch_1[i]=C
    		}
    		else if(temp>=5&&temp<=8){//当roman/100=7时，res+="DCC"
    			res+=ch_2[i];
    			temp_1=(num-5*roman[i])/roman[i];//本质上就是temp_1=num-5
    			for(int j=0;j<temp_1;j++){
    				res+=ch_1[i];
    			}
    		}
    		else if(temp==4){//当roman/100=4时，res+="CD"
    			res=res+ch_1[i]+ch_2[i];
    		}
    		else{//temp为0-3，当roman/100=2时.res+="CC"
    			for(int j=0;j<temp;j++){
    				res+=ch_1[i];
    			}
    		}
    		num=num%roman[i];
        }
        return res;
    }
};

/*
1.基本数字I、X、C中的任何一个，自身连用构成数目，或者放在大数的右边连用构成数目，都不能超过三个；放在大数的左边只能用一个。
2.不能把基本数字V、L、D中的任何一个作为小数放在大数的左边采用相减的方法构成数目；放在大数的右边采用相加的方式构成数目，只能使用一个。
3.V和X左边的小数字只能用I，且只能有1个。
4.L和C左边的小数字只能用X，且只能有1个。
5.D和M左边的小数字只能用C，且只能有1个。

进一步，可以看到，罗马数字可以分为1、4、5、9这四种构成方式，而1-3999中，
共有1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1，共计13种，
依次分别对应"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"，即：

整数数字  1000 900 500 400 100 90 50 40 10 9  5 4  1
罗马数字  M    CM  D   CD  C   XC L  XL X  IX V IV I
*/

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string intToRoman(int num){
    	int temp;
    	string res="";
        int roman[]={1000,900,500,400,100,90,50,40,10,9,5,4,1};
        string str[]={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        for(int i=0;i<13;i++){
        	if(num>=roman[i]){
        		temp=num/roman[i];
        		for(int j=0;j<temp;j++){
        			res+=str[i];
        		}
        		num=num%roman[i];
        	}
        }
		cout<<res<<endl;
		return res;
    }
};

int main(){
    int num=3999;

    Solution sol=Solution();
    sol.intToRoman(num);
    return 0;
}