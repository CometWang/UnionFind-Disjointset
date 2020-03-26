/*
 * Jia Wang 251041197
 * */

#include <iostream>
#include <fstream>
#include <string>
#define maxlinesize 71
/* /Users/apple/CLionProjects/3340_2/girl.img */
using namespace std;


class UnionFind{
public:
    //variables
    int amount; // # of elements
    int* index;// index[i] points to the parent of i, if index[i]=i then i is root
    int* rank;// store the size of each component
    //int numofcom;

public:
    //methods
    UnionFind uandf(int n);//constructor
    void make_set(int i);//create representative
    void union_sets(int i, int j);// union the sets
    int find_set(int i);// find certain element in the sets
    int final_sets();//return amount of sets and finalized them

};

/*
 * constructs an union-find data type with n elements, 1, 2, . . . , n
 * */
UnionFind UnionFind:: uandf(int n){
    //numofcom = n;
    amount = n;
    index = new int[n];//used to point to the parent
    rank = new int[n];

}

/*
 *creates a new set whose only member (and thus representative) is i
 * */
void UnionFind::make_set(int i){
  index[i]=i;
  //printf("index now:%d\n", index[i]);
  rank[i]=0;

}

/*
 * unites the dynamic sets that contains i and j, respectively, into a new
 * set that is the union of these two sets.
 * */
void UnionFind::union_sets(int i, int j){
    int root1 = find_set(i);
    int root2 = find_set(j);

    //when they are already in the same set
    //if(root1 == root2 ) return;
    //compare the weight of both sets
    if(rank[root1]<=rank[root2]){
        index[root1] = root2;
    }
    else {
        //merge the lower rank to the higher one
        index[root2] = root1;
        // rank[root1] = rank[root2]+1;
    }
    if(rank[root1]==rank[root2]){
        rank[root2]++;
        //rank[root2] = rank[root1]+1;
    }
    //else
    //numofcom--;

}

/*
 * returns the representative of the set containing i.
 * */
int UnionFind::find_set(int i){
    if(i == index[i])
        return i;
    else{
        index[i] = find_set(index[i]);
        return index[i];
    }
}

/*
 * returns the total number of current sets and finalizes the current sets:
 * (i) make_set() and union_sets() will have no effect after this operation and
 * (ii) resets the representatives of the sets so that integers from 1 to final_sets()
 * will be used as representatives.
 * */
int UnionFind::final_sets(){
    int num = 1;
    int arr[26];
    //path compression
    for (int j = 0; j < amount; j++){
        if (index[j] != j){
            find_set(j);
        }
    }
    //record the amount of all components
    for (int i = 0; i < amount; i++){
        if (index[i] == i){
            //find the representative
            for (int j = 0; j < amount ; j++){
                //find the index that has the same parent as the root in order to divide them into same set
                if (index[j] == i){
                    index[j] = num;
                }
            }
            index[i] = num;
            num++;
        }
    }
    //return the amount of component
    return num -1;

}



int main() {

    //ifstream infile("/Users/apple/CLionProjects/3340_2/infile", ios::binary | ios::in);
    ifstream infile("infile", ios::binary| ios::in);
    if(!infile){
        printf("Error to open the file");
        return -1;
    }
    //**************************question b 1)**************************
    // read file line by line and store the components into 1,0 in the array then print out
    //store the binary number in the matrix
    int matrix[maxlinesize][maxlinesize];
    int count=0;
    string line;
    int i=0;
    cout<< " ---------------------------Original picture----------------------------"<<endl;
    cout<<'\n'<<endl;
    while(getline(infile, line)){
        cout << line <<endl;
            for(int j=0; j<maxlinesize; j++){
                if(line[j]=='+'){
                    matrix[i][j]=1;
                    count++;
                }else{
                    matrix[i][j]=-1;
                }
            }
            i++;
   }
    //initialize the object
    UnionFind disjointset;
    disjointset.uandf(maxlinesize*maxlinesize);

    //**************************question b 2)**************************
    //construct the ds from the 1 in the matrix
    int num=0;
    for(int i =0; i<maxlinesize; i++){
        for(int j=0; j<maxlinesize; j++){
           if (matrix[i][j]==1){
               disjointset.make_set(num);
           }
            num++;

        }
    }

   //verify the connection in the matrix and union the connected elements

   //num = 0;

    for(int i =0; i<maxlinesize; i++){
        for(int j=0; j<maxlinesize; j++){
            //compare the elements in horizon and vertical
            if (matrix[i][j]==1 &&j+1<maxlinesize&& matrix[i][j+1]==1){
                disjointset.union_sets(i*71+j, i*71+j+1);
            }
            if (matrix[i][j]==1 && i+1<maxlinesize &&matrix[i+1][j]==1){
                disjointset.union_sets(i*71+j, i*71+j+71);
            }
           // num++;
        }


    }
    /*
     * test for union result
     *
    for(int i=0; i<count; i++){

        disjointset.find_set(disjointset.index[i]);
    }*/

    //print out the pic with unique characters replaced
    cout<< '\n'<<endl;
    int total =disjointset.final_sets();
    cout<< "----------After union and find we got "<<total<<" groups of components----------"<<endl;

    /*
     * store each component and its size into array
     *
     * */

    int cmpnt[total];
    char character[total];
    for(int i=0; i<total; i++){
        cmpnt[i]=0;
        character[i] = 65+i;//USE ascii table
    }
    /*
     * use matrix(original pic) to control the whole array inorder to print out the pic
     * */
    for(int i =0; i<maxlinesize; i++){
        for(int j=0;j<maxlinesize; j++){
            if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 1){
                printf("A");
                cmpnt[0]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 2){
                printf("B");
                cmpnt[1]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 3){
                printf("C");
                cmpnt[2]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 4){
                printf("D");
                cmpnt[3]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 5){
                printf("E");
                cmpnt[4]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 6){
                printf("F");
                cmpnt[5]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 7){
                printf("G");
                cmpnt[6]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 8){
                printf("H");
                cmpnt[7]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 9){
                printf("I");
                cmpnt[8]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 10){
                printf("J");
                cmpnt[9]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 11){
                printf("K");
                cmpnt[10]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 12){
                printf("L");
                cmpnt[11]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 13){
                printf("M");
                cmpnt[12]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 14){
                printf("N");
                cmpnt[13]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 15){
                printf("O");
                cmpnt[14]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 16){
                printf("P");
                cmpnt[15]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 17){
                printf("Q");
                cmpnt[16]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 18){
                printf("R");
                cmpnt[17]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 19){
                printf("S");
                cmpnt[18]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 20){
                printf("T");
                cmpnt[19]++;
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 21){
                printf("U");
                cmpnt[20]++;
            }else{
                printf(" ");
            }
            if(j==70){cout<<""<<endl;}
        }
    }

    /*
     * -----------------------b 3)------------------------
     * */
    //bubble sort: sort the character and also the coresponding number
    for(int i = 0;i < total;i++){
        for(int j = 0;j < total-i-1;j++){
            if(cmpnt[j] > cmpnt[j+1]){
                int t = cmpnt[j];
                char m = character[j];
                cmpnt[j] = cmpnt[j+1];
                character[j]=character[j+1];
                cmpnt[j+1] = t;
                character[j+1] = m;

            }
        }
    }
    int numchar=0;
    //char* newchar;
    cout<<" "<<endl;
    cout<< "-------------------------After sorting in ascending---------------------"<<endl;
    /*
     * record the component which has elements that less than 4
     * */
    for(int i=0; i<total; i++){
        if(cmpnt[i]<4){
            numchar++;
        }
        cout<< character[i]<<":"<<cmpnt[i]<<endl;

    }
    /*
     * -----------------------------b 4)--------------------------------------
     * */
     cout<<"------------------------after deleting----------------------"<<endl;
    /*
     * same way to print the pic with less than 4 elements deleted
     * set a flag in each inner loop to verify whether the character should be printed out
     * */
    for(int i =0; i<maxlinesize; i++){
        for(int j=0;j<maxlinesize; j++){
            //when flag is 1, the character has less than 4 -> not print out
            int flag = 0;
            if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 1){
                for(int m = 0; m<numchar;m++){
                   if(character[m]=='A'){
                       flag=1;
                   break;}

                }
                if(flag==0){
                printf("A");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 2){
                for(int m = 0; m<numchar;m++){
                    if(character[m]=='B'){
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("B");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 3){
                for(int m = 0; m<numchar;m++){
                    if(character[m]=='C'){
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("C");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 4){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'D') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("D");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 5){
                for(int m = 0; m<numchar;m++) {
                    if (character[numchar] == 'E') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("E");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 6){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'F') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("F");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 7){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'G') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("G");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 8){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'H') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("H");}
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 9){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'I') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("I");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 10){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'J') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("J");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 11){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'K') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("K");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 12){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'L') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("L");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 13){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'M') {
                        flag=1;
                        break;}
                }
                if(flag==0){
                    printf("M");}
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 14){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'N') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("N");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 15){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'O') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("O");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 16){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'P') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("P");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 17){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'Q') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("Q");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 18){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'R') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("R");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 19){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'S') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("S");}
            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 20){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'T') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("T");}

            }else if(matrix[i][j]==1&&disjointset.index[i*maxlinesize+j] == 21){
                for(int m = 0; m<numchar;m++) {
                    if (character[m] == 'U') {
                        flag=1;
                        break;}

                }
                if(flag==0){
                    printf("U");}

            }else{
                printf(" ");
            }
            if(j==70){cout<<""<<endl;}
        }
    }

    return 0;
}
