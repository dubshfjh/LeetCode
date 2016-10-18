class Solution {
public:
    int lengthOfLastWord(string s) {
        int i,len;
        i=s.size()-1;
        len=0;
        cout<<s[i]<<"...";
    	while(s[i]==' '){
    		i--;
    		cout<<i<<",,,";
    	}
    	
    	while(i>=0 && s[i]!=' '){
    		len++;
    		i--;
    	}

        return len;
    }
};