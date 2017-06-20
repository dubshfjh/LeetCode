class TriNode{
    boolean isWord;
    TriNode[] children;
    public TriNode(){
        isWord = false;
        children = new TriNode[26];
    }
}

public class WordDictionary {
    TriNode root;
    /** Initialize your data structure here. */
    public WordDictionary() {
        root = new TriNode();
    }

    /** Adds a word into the data structure. */
    public void addWord(String word) {
        TriNode node = root;
        for(int i=0;i<word.length();i++){
            int index = word.charAt(i)-'a';
            if(node.children[index] == null){
                node.children[index] = new TriNode();
            }
            node = node.children[index];
        }
        node.isWord = true;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    public boolean search(String word) {
        return searchHelper(word,0,root);
    }

    public boolean searchHelper(String word,int curPos,TriNode node){
        if(node == null){
            return false;
        }
        if(curPos == word.length()){
            return node.isWord;
        }
        if(word.charAt(curPos) == '.'){
            for(int i=0;i<26;i++){
                if(node.children[i] != null){
                    if(searchHelper(word,curPos+1,node.children[i])){
                        return true;
                    }
                }
            }
            //比较TKW的return false整合情况！！！代码要精简！！！
            //return false; 
        }
        else{
            int index = word.charAt(curPos) - 'a';
            if(node.children[index]!=null){
                return searchHelper(word,curPos+1,node.children[index]);
            }
            //代码要精简！！！！！！！！！！！！！！！！！！！！！！！！！！
            // if(node.children[index] == null){
            //     return false;
            // }
            // else{
            //     return searchHelper(word,curPos+1,node.children[index]);
            // }
        }
        return false;
    }

    // public static void main(String[] args) {
    //     String s = "barfoothefoobarman";
    //     WordDictionary obj = new WordDictionary();
    //     obj.addWord(s);
    //     System.out.println(obj.search("barfoo.hefo.barman"));
    // }
}