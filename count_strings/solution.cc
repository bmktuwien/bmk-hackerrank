#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <queue>

using namespace std;

struct nst {
    vector<int> a[2], e;
    bool f=0;
};

struct dst {
    int a[2] = {-1,-1};
    bool f=0;
};

vector<nst> nfa;
vector<dst> dfa;

stack<int> st;

int nfa_size, dfa_size;

struct nst init_nfa_state;
struct dst init_dfa_state;

//------------------------------------------------------

string insert_concat(const string& regexp) {
    string ret="";
    char c,c2;
    for(unsigned int i=0; i<regexp.size(); i++){
        c=regexp[i];
        if(i+1<regexp.size()){
            c2=regexp[i+1];
            ret+=c;
            if((c==')'||c=='a'||c=='b') &&
               (c2=='('||c2=='a'||c2=='b')){
                ret+='.';
            }
        }
    }

    ret+=regexp[regexp.size()-1];
    return ret;
}

int priority(char c) {
    switch(c){
    case '*': return 3;
    case '.': return 2;
    case '|': return 1;
    default: return 0;
    }
}

string regexp_to_postfix(const string& regexp) {
    string postfix="";
    stack<char> op;
    char c;
    for(unsigned int i=0; i<regexp.size(); i++) {
        switch(regexp[i])
        {
            case 'a':
            case 'b':
                postfix+=regexp[i]; break;
            case '(':
                op.push(regexp[i]); break;
            case ')':
                while(op.top()!='('){
                    postfix+=op.top();
                    op.pop();
                }
                op.pop();
                break;
            default:
                while(!op.empty()){
                    c=op.top();
                    if(priority(c)>=priority(regexp[i])){
                        postfix+=op.top();
                        op.pop();
                    }
                    else break;
                }
                op.push(regexp[i]);
        }
        //cout<<regexp[i]<<' '<<postfix<<endl;
    }

    while(!op.empty()) {
        postfix += op.top();
        op.pop();
    }
    return postfix;
}

void character(int i) {
    nfa.push_back(init_nfa_state);
    nfa.push_back(init_nfa_state);
    nfa[nfa_size].a[i].push_back(nfa_size+1);
    st.push(nfa_size);
    nfa_size++;
    st.push(nfa_size);
    nfa_size++;
}

void union_() {
    nfa.push_back(init_nfa_state);
    nfa.push_back(init_nfa_state);
    int d = st.top(); st.pop();
    int c = st.top(); st.pop();
    int b = st.top(); st.pop();
    int a = st.top(); st.pop();
    nfa[nfa_size].e.push_back(a);
    nfa[nfa_size].e.push_back(c);
    nfa[b].e.push_back(nfa_size+1);
    nfa[d].e.push_back(nfa_size+1);
    st.push(nfa_size);
    nfa_size++;
    st.push(nfa_size);
    nfa_size++;
}

void concatenation() {
    int d = st.top(); st.pop();
    int c = st.top(); st.pop();
    int b = st.top(); st.pop();
    int a = st.top(); st.pop();
    nfa[b].e.push_back(c);
    st.push(a);
    st.push(d);
}

void kleene_star() {
    nfa.push_back(init_nfa_state);
    nfa.push_back(init_nfa_state);
    int b = st.top();
    st.pop();
    int a = st.top();
    st.pop();
    nfa[nfa_size].e.push_back(a);
    nfa[nfa_size].e.push_back(nfa_size+1);
    nfa[b].e.push_back(a);
    nfa[b].e.push_back(nfa_size+1);
    st.push(nfa_size);
    nfa_size++;
    st.push(nfa_size);
    nfa_size++;
}

void postfix_to_nfa(string postfix){
    for(unsigned int i=0; i<postfix.size(); i++)
    {
        switch(postfix[i])
        {
        case 'a':
        case 'b': character(postfix[i]-'a'); break;
        case '*': kleene_star(); break;
        case '.': concatenation(); break;
        case '|': union_();
        }
    }
}

void epsilon_closure(int state,set<int>&si){
    for(unsigned int i=0;i<nfa[state].e.size();i++){
        if(si.count(nfa[state].e[i])==0){
            si.insert(nfa[state].e[i]);
            epsilon_closure(nfa[state].e[i],si);
        }
    }
}

set<int> state_change(int c,set<int>&si){
    set<int> temp;
    if(c==1){
        for (std::set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            for(unsigned int j=0;j<nfa[*it].a[0].size();j++){
                temp.insert(nfa[*it].a[0][j]);
            }
        }
    }
    else{
        for (std::set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            for(unsigned int j=0;j<nfa[*it].a[1].size();j++){
                temp.insert(nfa[*it].a[1][j]);
            }
        }
    }
    return temp;
}

void nfa_to_dfa(set<int> &si,queue<set<int> >&que,int start_state){
    map<set<int>, int> mp;
    mp[si]=-1;
    int ct=0;
    si.clear();
    si.insert(0);
    epsilon_closure(start_state,si);
    if(mp.count(si)==0){
        mp[si]=ct++;
        que.push(si);
    }
    int p=0;
    bool f1=false;
    while(que.size()!=0){
        dfa.push_back(init_dfa_state);
        si.empty();
        si=que.front();
        f1=false;
        for (auto it=si.begin(); it!=si.end(); ++it){
            if(nfa[*it].f==true)
                f1=true;
        }
        dfa[p].f=f1;
        si=state_change(1,si);
        for (auto it=si.begin(); it!=si.end(); ++it){
            epsilon_closure(*it,si);
        }
        if(mp.count(si)==0){
            mp[si]=ct++;
            que.push(si);
            dfa[p].a[0]=ct-1;
        }
        else{
            dfa[p].a[0]=mp.find(si)->second;
        }

        si=que.front();
        si=state_change(2,si);
        for (auto it=si.begin(); it!=si.end(); ++it){
            epsilon_closure(*it,si);
        }
        if(mp.count(si)==0){
            mp[si]=ct++;
            que.push(si);
            dfa[p].a[1]=ct-1;
        }
        else{
            dfa[p].a[1]=mp.find(si)->second;
        }
        que.pop();
        p++;
    }
    for(int i=0;i<p;i++){
        if(dfa[i].a[0]==-1)dfa[i].a[0]=p;
        if(dfa[i].a[1]==-1)dfa[i].a[1]=p;
    }
    dfa.push_back(init_dfa_state);
    dfa[p].a[0]=p;
    dfa[p].a[1]=p;
    //cout<<p<<endl;
}

void print_dfa(){
    cout<<endl;
    cout<<"NFA TO DFA CONVERSION"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"STATE\t|\t"<<"a"<<"\t|\t"<<"b"<<"\t|\t"<<"FINAL"<<"\t|"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for(int i=0;i<dfa.size();i++){
        cout<<i<<"\t|\t"<<dfa[i].a[0]<<"\t|\t"<<dfa[i].a[1]<<"\t|\t"<<dfa[i].f<<"\t|"<<endl;
    }
    cout<<"---------------------------------------------------------"<<endl;
}

vector<vector<int>> matrix_mult(int n, const vector<vector<int>> &a, const vector<vector<int>> &b) {
    vector<vector<int>> result(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c = 0;
            for (int k = 0; k < n; k++) {
                c += a[i][k]*b[k][j];
            }
            result[i][j] = c;
        }
    }

    return result;
}

vector<vector<int>> matrix_power(const vector<vector<int>> &a, int k) {
    int n = a.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }

    auto A = a;

    while (k > 0) {
        if (k & 1) {
            result = matrix_mult(n, result, A);
        }

        A = matrix_mult(n, A, A);

        k = k >> 1;
    }

    return result;
}

int main() {
    string inp;
    int k;
    cin >> inp;
    cin >> k;

    auto postfix = regexp_to_postfix(insert_concat(inp));

    std::cout << postfix << std::endl;

    postfix_to_nfa(postfix);

    int final_state=st.top();st.pop();
    int start_state=st.top();st.pop();
    //cout<<start_state<<' '<<final_state<<endl;
    nfa[final_state].f=1;

    set<int> si;
    queue<set<int> > que;
    nfa_to_dfa(si,que,start_state);

    print_dfa();
    vector<vector<int>> trans_matrix(dfa.size());
    for (int i = 0; i < dfa.size(); i++) {
        for (int j = 0; j < dfa.size(); j++) {
            trans_matrix[i].push_back(0);
        }
    }

    for (int i = 0; i < dfa.size(); i++) {
        trans_matrix[i][dfa[i].a[0]]++;
        trans_matrix[i][dfa[i].a[1]]++;
    }

    for (int i = 0; i < trans_matrix.size(); i++) {
        for (int j = 0; j < trans_matrix.size(); j++) {
            std::cout << trans_matrix[i][j] << " , ";
        }
        std::cout << std::endl;
    }

    auto M = matrix_power(trans_matrix, k);

    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M.size(); j++) {
            std::cout << M[i][j] << " , ";
        }
        std::cout << std::endl;
    }

    int result = 0;
    for (int i = 0; i < dfa.size(); i++) {
        if (dfa[i].f) {
            result += M[0][i];
        }
    }

    std::cout << "result: " << result << std::endl;
}
