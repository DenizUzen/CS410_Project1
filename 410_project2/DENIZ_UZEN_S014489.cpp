#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class CFG{
    public:
    vector<string> nonTerminals;
    vector<string> terminals;
    vector<string> rules;
    string start;

};

class CNF{
    public:
    vector<string> nonTerminals;
    vector<string> terminals;
    vector<string> rules;
    string start;

};
void readFun(CFG& cfg){
    string text;
    string state="";
   

    ifstream readFile("G1.txt");

    while (getline (readFile, text)){

        //cout<<text<<endl;

    if(text=="NON-TERMINAL"){
        state="nt";
        continue;
    }
    else if(text=="TERMINAL"){
        state = "t";
        continue;
    }
    else if(text == "RULES"){
        state = "r";
        continue;
    }
    else if(text == "START"){
        state = "s";
        continue;
    }



      if(state == "nt"){
        cfg.nonTerminals.push_back(text);
    }
    else if(state == "t"){
        cfg.terminals.push_back(text);
    }
    else if(state == "r"){
        cfg.rules.push_back(text);
    }
    else if(state =="s"){
        cfg.start = text;
    }
    }
    readFile.close();
}

void removeEpsilon(CFG& cfg, CNF& cnf){

    
    vector<char> eNonTerms;
    int counter=0;

    for(auto i = cfg.rules.begin(); i<cfg.rules.end(); i++){

        for(int j=0; j< (*i).length(); j++){
            if((*i)[j] == 'e'){
                eNonTerms.push_back((*i)[0]);
                
                cfg.rules.erase(cfg.rules.begin()+counter);     
            
            }
        }
    counter++;
    }
    
    for(auto i = cfg.rules.begin(); i != cfg.rules.end(); i++){
        cnf.rules.push_back(*i);
    }


    for(auto i =eNonTerms.begin(); i<eNonTerms.end(); i++){
        for(auto j=cfg.rules.begin(); j<cfg.rules.end(); j++){
            for(int k=2; k< (*j).length(); k++){
                if((*j)[k] == *i){
                    cnf.rules.push_back((*j).substr(0,k)+(*j).substr(k+1,(*j).length()));
                }
            }
        }
    }
    //search for unit remove

    for(auto i= cnf.rules.begin(); i<cnf.rules.end(); i++){
        if((*i).length() == 3){
            //search for non-terminal on the rhs

            for(auto j=cnf.rules.begin(); j<cnf.rules.end(); j++){
                if((*j)[0] == (*i)[2]){
                    cnf.rules.push_back((*i)[0] + ":" + (*j).substr(2,(*j).length()));
                }
            }
        }
    }

//remove xX
/*
int counterTerminal=0;
int counterNTerminal=0;

    for(auto i = cnf.rules.begin(); i<cnf.rules.end(); i++){
        for(auto j = cnf.terminals.begin(); j<cnf.terminals.end(); j++){
            for(auto k = cnf.nonTerminals.begin(); k<cnf.nonTerminals.end();k++){
                for(int l = 2 ; l<(*i).length(); l++){
                    if((*i)[l]==(*k)[0])
                        counterNTerminal++;
                    else if((*i)[l]==(*j)[0])
                        counterTerminal++;
                }
                if(counterNTerminal>0 && counterTerminal >0){
                    char random = char(rand() % 26 + 65);
                    cnf.rules.push_back(random+(":")+(*j)+(*k));
                    cnf.rules.push_back((*i)[0]+":"+ random + )
                    cnf.rules.erase(i);
                }
                counterNTerminal = 0;
                counterTerminal = 0;
            }
        }
    }
    */
   /*
   for(auto i = cnf.rules.begin()+1; i<cnf.rules.end(); i++){
    if((*i).length()>4) {
        char random = char(rand() % 26 + 65);
         cnf.rules.push_back(random + 
                                ":"+
                                (*i).substr(2,((*i).length()/2)+2)+ 
                                (*i).substr(((*i).length()/2)+2), (*i).length()); 

        cnf.rules.push_back(random + ":" + (*i)[2]+(*i)[3]);
        
    }
   }
   */

}


int main(){

    CFG cfg;
    CNF cnf;
    readFun(cfg);

    cnf.start = cfg.start+"0";
    cnf.nonTerminals.push_back(cnf.start);

    for(auto i = cfg.nonTerminals.begin(); i!= cfg.nonTerminals.end();i++){
        cnf.nonTerminals.push_back(*i);
    }
    for(auto i = cfg.terminals.begin(); i!= cfg.terminals.end(); i++){
        cnf.terminals.push_back(*i);
    }

    cnf.rules.push_back(cnf.start+":"+cfg.start);




    removeEpsilon(cfg, cnf);

    
    
    cout<<"NON-TERMINAL"<<endl;
    for(auto i = cnf.nonTerminals.begin(); i != cnf.nonTerminals.end(); i++){
        cout << *i <<endl;
    }
    cout<<"TERMINAL"<<endl;
    for(auto i = cnf.terminals.begin(); i != cnf.terminals.end(); i++){
        cout << *i <<endl;
    }
    cout<<"RULES"<<endl;
    for(auto i = cnf.rules.begin(); i != cnf.rules.end(); i++){
        cout << *i <<endl;
    }
    cout<<"START"<<endl;
    cout<<cnf.start<<endl;
  

   
/*

   for(auto i = cnf.rules.begin(); i != cnf.rules.end(); i++){
        cout << *i <<endl;
    }
*/
    return 0;
}