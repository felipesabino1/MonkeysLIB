const int N = 1000500;
const int mod=1e9+7;
typedef long long ll;
struct node{
    bool leaf;
    map<int,int> prox;
    node(){
        leaf = false;
    }
};
int id=0;
node nodes[N];
void insert_trie(string s){
    int curr=0;
    for(char c: s){
        if(nodes[curr].prox[c-'a']==0)
            nodes[curr].prox[c-'a']=++id;
        curr=nodes[curr].prox[c-'a'];
    }
    nodes[curr].leaf=true;
}
bool find_trie(string s){
    int curr=0;
    for(char c: s){
        if(!nodes[curr].prox[c-'a'])
            return false;
        curr=nodes[curr].prox[c-'a'];
    }
    if(nodes[curr].leaf) return true;
    return false;
}