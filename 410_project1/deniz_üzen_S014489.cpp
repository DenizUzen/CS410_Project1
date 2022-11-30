#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class NfaState{
public:

string Name;
string Alphabet;
vector<char> Transitions;


};

class DfaState{
    public:
    string Name;
    string Alphabet;
    vector<char>Transitions;
};

int main(){

int a = 0;

string myText;

vector<string> alphabetInput;
vector<string> stateInput;
vector<string> transitionInput;

string startState;
string finalState;

string readingState;

ifstream MyReadFile("NFA1.txt");

while(getline(MyReadFile, myText)){
    
    if(myText.compare("ALPHABET")==0 || myText.compare("STATES")==0 || myText.compare("START")==0 || myText.compare("FINAL")==0 || myText.compare("TRANSITIONS")==0 || myText.compare("END")==0)
    {
        readingState = myText;
        continue;
    }
    if(readingState.compare("ALPHABET")==0){
        alphabetInput.push_back(myText);
        for(auto i = alphabetInput.end()-1; i !=alphabetInput.end(); i++)
            cout<< *i << endl;
    }
    else if(readingState.compare("STATES")==0){
        stateInput.push_back(myText);
        for(auto i = stateInput.end()-1; i !=stateInput.end(); i++)
            cout<< *i << endl;
      
        
    }
    else if(readingState.compare("START")==0){
        startState = myText;
        cout<<startState<<endl;
        
    }
    else if(readingState.compare("FINAL")==0){
        finalState = myText;
        cout<<finalState<<endl;
    }
    else if(readingState.compare("TRANSITIONS")==0){
        transitionInput.push_back(myText);
        for(auto i = transitionInput.end()-1; i !=transitionInput.end(); i++)
            cout<< *i << endl;
        
    }

}
MyReadFile.close();

int stateLength = stateInput.size();
int transitionLength = transitionInput.size();
//State* state = new State[stateInputLength];
NfaState state[stateLength];


int index = 0;

for(auto i = alphabetInput.begin(); i!= alphabetInput.end(); i++){
    state[index].Alphabet = *i;
    index++;
}

index = 0;
for (auto i = stateInput.begin(); i != stateInput.end(); i++){
    state[index].Name =*i;
    cout<<(state[index].Name)<<endl;
    index++;
}
index=0;

for(auto i = transitionInput.begin(); i != transitionInput.end(); i++){
    string val = *i;
    for(int k = 0; k<stateLength; k++){
            if(val[0] == state[k].Name[0]){
                state[k].Transitions.push_back(val[4]);
                state[k].Transitions.push_back(val[2]);
            }
    }
}
cout<<"________________________________"<<endl;
for(int i=0; i<stateLength; i++){
    for(auto k = state[i].Transitions.begin(); k != state[i].Transitions.end(); k++){
        cout<<state[i].Name+ " " +*k + *(k+1) <<endl;
        if(k+2 <=state[i].Transitions.end())
            k++;
    }
}

////////////////////////////////////////////////////////
int nameCounter1 =0;
int nameCounter2 = 0;
vector<DfaState> dfas;

for (int i = 0; i< stateLength; i++){
    nameCounter1 = 0;
    nameCounter2 = 0;
    for( auto j = state[i].Transitions.begin(); j != state[i].Transitions.end(); j++){
        if(state[i].Name[0] == *j){
            nameCounter1++;
        }
        else if (*j != state[i].Alphabet[0] && *j != state[i].Alphabet[1] ){
            nameCounter2++;
        }
        if(nameCounter1>=2 && nameCounter2>0){
            DfaState dfa;
            dfa.Name = state[i].Name + "1";
            dfas.push_back(dfa);
            
        }
    }

}

return 0;
}