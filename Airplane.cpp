#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;
vector<string> v1d;

int main()
{
std::vector<std::vector<std::vector<int> > > vect3d;
int rowMax=0, queue;
int aisle=0, window=0, middle=0;
vector<vector<int>> input;
//vector<string> v1d;

    string s = "[[1,1],[1,1],[1,1]]";
    regex rgx("[1-9][0-9]*");
    smatch match;


//Input 2D Array
    do {
        vector<string> v1d;
        cout << "Enter 2D array. Input Pattern: Numbers seperated by any characters except space, tab or new line. e.g. [[3,2],[4,3],[2,3],[3,4]]" << endl;
        cin >> s;
         while (regex_search(s, match, rgx)) {
            v1d.push_back(match.str(0));
            s = match.suffix().str();
        }
        ::v1d = v1d;
    }
    while (v1d.size()%2==1);
    
        for(int i = 0; i < v1d.size(); i=i+2){
            vector<int> vec1d;
            vec1d.push_back(stoi(v1d[i]));
            vec1d.push_back(stoi(v1d[i+1]));
            input.push_back(vec1d);
            
        }
    
    
//Initialize and count aisle, window, middle
for (int i = 0; i < input.size(); i++) {
    vector<vector<int>> v2d;
    for (int j = 0; j < input[i][1]; j++) {
        vector<int> v1d;
        for (int k = 0; k < input[i][0]; k++) {
            v1d.push_back(-1);
            if((i!=0 and k==0 and i!=(input.size()-1)) or (i!=(input.size()-1) and k==(input[i][0]-1) and i!=0) or (k==0 and i==(input.size()-1) and input[i][0]>1 and input.size()>1) or (k==(input[i][0]-1) and i==0 and input.size()>1 and input[i][0]>1))
                aisle++;
            else if ((i==0 and k==0) or (i==(input.size()-1) and k==(input[i][0]-1)))
                window++;
            else middle++;
            
        }
        //block[i] = block[i] + v1d.size();
        v2d.push_back(v1d);
    }
    vect3d.push_back(v2d);
}

//cout << aisle << " " << window << " " << middle << " " << rowMax << " " << input.size() << endl;

cout << "Enter queue" << endl;
cin >> queue;
while(queue>(aisle+middle+window) or queue<=0){
    cout << "Enter right queue. It cant be more than seat number or zero or negative." << endl;
    cin >> queue;
}


//Allocate seats
int sCounter=0;
bool bFlag1=false;

for(int x=0; x<input.size(); x++)
    if(input[x][1]>rowMax)
        rowMax = input[x][1];

//cout << aisle << " " << window << " " << middle << " " << rowMax << " " << input.size() << endl;
int queueHolder=queue;


while(queue>0){
    int *bCounter = new int(input.size());
    for(int x=0; x<input.size(); x++)
        bCounter[x]=0;

    for(int j = 0; j<rowMax; j++){ 
        if(queue<1 or bFlag1){
            bFlag1=false;
            break;
        }
        for(int i = 0; i < input.size(); i++){ //value of a
            if(queue<1 or bFlag1)
                break;
            for (int k = 0; k < input[i][0]; k++){
                if((input[i][0]*input[i][1])==bCounter[i] or queue<1)
                    break;
                else {
                    bCounter[i]++;
                    if((i!=0 and k==0 and i!=(input.size()-1)) or (i!=(input.size()-1) and k==(input[i][0]-1) and i!=0) or (k==0 and i==(input.size()-1) and input[i][0]>1 and input.size()>1) or (k==(input[i][0]-1) and i==0 and input.size()>1 and input[i][0]>1)){  //aisle
                        if(vect3d[i][j][k]<0){  //if the seat is empty
                            sCounter++;
                            vect3d[i][j][k]=sCounter;
                            queue--;
                            //cout << queue-- << " ";
                            aisle--;
                            if(aisle==0){
                                bFlag1 = true;
                                break;
                            }
                        }
                        else
                            continue;
                    }
                
                    else if(((i==0 and k==0) or (i==(input.size()-1) and k==(input[i][0]-1))) and aisle<=0){ //window and aisle all booked
                        if(vect3d[i][j][k]<0){  //if the seat is empty
                            sCounter++;
                            vect3d[i][j][k]=sCounter;
                            queue--;
                            //cout << queue-- << " ";
                            window--;
                        }
                        else
                            continue;
                    }
                
                    else if(window<=0){   //middle
                        if(vect3d[i][j][k]<0){  //if the seat is empty
                            sCounter++;
                            vect3d[i][j][k]=sCounter;
                            queue--;
                            //cout << queue-- << " ";
                            middle--;
                        }
                        else
                            continue;
                    }
                }
            }
        }
    }
    delete [] bCounter;
}

//cout << aisle << " " << window << " " << middle << " " << queue<< " " << rowMax << endl;

    int *bCounter = new int(input.size());
    for(int x=0; x<input.size(); x++){
        bCounter[x]=0;
    }

//Display Output 2      

    for(int j = 0; j<rowMax; j++){ 
        //cout << "j=" << j <<endl;
        for(int i = 0; i < input.size(); i++){ //value of a
            //cout << "i=" << i <<endl;
            for (int k = 0; k<input[i][0]; k++){
                if((input[i][0]*input[i][1])==bCounter[i])
                    cout << "   ";
                else {
                    bCounter[i]++;
                    //cout << "bcounter:" << bCounter[i] <<" " << "k=" << k << " " << input[i][0] << endl;
                    if(vect3d[i][j][k]<10 and vect3d[i][j][k]>0)
                        cout << vect3d[i][j][k] <<"  ";
                        else if(vect3d[i][j][k]>9 and vect3d[i][j][k]<=queueHolder) 
                            cout << vect3d[i][j][k] <<" ";
                        else cout << "   ";
                }   
            }
            cout << "  ";
        }
        cout << endl;
    }
delete [] bCounter;

return 0;
}