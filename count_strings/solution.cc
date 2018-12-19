#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <stack>

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

string insert_concat(const string& regexp){
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

int priority(char c){
    switch(c){
    case '*': return 3;
    case '.': return 2;
    case '|': return 1;
    default: return 0;
    }
}

string regexp_to_postfix(const string& regexp)
{
    string postfix="";
    stack<char> op;
    char c;
    for(unsigned int i=0; i<regexp.size(); i++)
    {
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
    while(!op.empty())
    {
        postfix += op.top();
        op.pop();
    }
    return postfix;
}

int main() {
    string inp;
    cin >> inp;

    cout << regexp_to_postfix(insert_concat(inp)) << endl;
}
