//
//  main.cpp
//  Project4DataStructures
//
//  Created by Feras Salous  on 3/14/19.
//  Copyright © 2019 Feras Salous . All rights reserved.
//

#include <iostream>
using namespace std;
class Tree
{
protected:
    int* myParent; //my tree array
    int* data;// pointer to data in my tree.
    int root;
    int count;
    int height;
    
public:
    Tree();
    Tree(int numberOfNodes);
    virtual ~Tree();
    void setParent(int node, int parent);
    void setRoot(int root);
    void display();
    int Root();
    int size;
    int& getMyParent();
    void children(int index);
    void parent(int index);
    void siblings(int index);
    int rootNug(int index);
    bool isEmpty();
    int Height();
    void nodesAtLevel(int level);
    void LCM(int choice1, int choice2);
    int Level(int index);
    Tree(const Tree& t);
    int& childrenArray(int Node);
    friend ostream& operator << (ostream& s, const Tree& tree);
    void PrintPreOrder(int root);
    void PreOrder();
};
//default constructor
Tree::Tree()
{
    data = NULL;
    myParent = new int[size];
}
// Construcrtor which takes in number of nodes and allocates my array to that size.
Tree::Tree(int numberOfNodes)
{
    data = NULL;
    myParent = new int[numberOfNodes];
    size = 0;
    count = 1;
    height = 0;
}
// destructor which deletes my tree.
Tree::~Tree()
{
    cout << "Tree Deleted"<<endl;
    delete [] myParent;
    
}
//copy constructor
Tree::Tree(const Tree& t)
{
    size = t.size;
    myParent = new int[size];
    for(int i=0; i < size; ++i)
    {
        myParent[i] = t.myParent[i];
    }
}
// given a node value and its parent, set the myParent[node] = to the corrresponding parent.
void Tree:: setParent(int node, int parent)
{
    myParent[node] = parent;
    ++ size;
}
//sets my root node.
void Tree:: setRoot(int val)
{
    root = val;
    
}
// return the root.
int Tree:: Root()
{
    //cout << "Reached Here"<< endl;
    return  root;
    
}
// gets the child of a specfic Node.
void Tree::children(int index)
{
    for(int i = 0; i < size; ++i) // loop thru the array.
    {
        if(index == myParent[i]) // if the index passed in, is the parent of a of a node in the array., then print that index it was equal at.
        {
            cout<< i << " ";
        }
    }
}
// gets the parent of a node.
void Tree::parent(int index)
{
    bool found = false;
    for(int i = 0; i < size; ++i) // loop thru the array.
    {
        if(index == i) // if the index passed in == Node
        {
            cout<< myParent[i]; // then print its parent.
            found = true;
            
        }
    }
    if(!found)
    {
        cout << "This Parent Does Not Exisit";
    }
}
void Tree::siblings(int index)
{
    int* temp = myParent; // temp array which holds my parents arrays values
    for(int i = 0; i < size; i++)
    {
        // make sure index is not equal to i and then comapare which elements contain the same parent and print that index
        if(i!= index && myParent[i] == temp[index])
        {
            cout << i << " ";
        }
    }
}
int& Tree::getMyParent()
{
    return *myParent;
}
void Tree::LCM(int choice1,int choice2)
{
    int val1 = choice1;
    int val2 = choice2;
    int sizeOftemp = 1;
    int sizeOftemp2 = 1;
    int* tempParent1 = new int[sizeOftemp];
    int* tempParent2 = new int[sizeOftemp2];
    
    if(val1 == val2) // if the vals passed in are equal, then print out that val.
    {
        cout <<  val1;
    }
    else
    {
        int parents = rootNug(choice1); // gets the parent of choice 1
        int parents2 = rootNug(choice2); // gets the parent of choice 2
        // a loop for parent array 1
        for (int i = 0; i < sizeOftemp; ++i) {
            if(parents != -1) // if the values are not equal to the root then keep going.
            {
                tempParent1[i] = parents; // store the parent of choice 1 in the array.
                parents = rootNug(parents); // call root nug to get the next parent val.
                ++sizeOftemp; // incremnt the size of the array.
            }
        }
        // a loop for parent array 2
        for(int j = 0; j < sizeOftemp2; ++j)
        {
            if(parents2 != -1) // if the value of parent2 is not equal to the root then keep going
            {
                tempParent2[j] = parents2; // store those values into the array of parent 2.
                parents2 = rootNug(parents2); // update parents 2 to equal the next parent.
                ++sizeOftemp2; // increment the size of parent array 2.
            }
        }
        bool found = false; // to know if my elements equaled each other.
        while(!found)
        {
            // a loop for the first array.
            for (int i = 0; i < sizeOftemp -1; ++i) {
                
                if(found == true) // if found == true in the nested for loop, then stop searching.
                {
                    break; //STOP.
                }
                // loop for second array.
                for (int j = 0; j < sizeOftemp2 -1 ; ++j) {
                    if(tempParent1[i] == tempParent2[j]) // if my parent at parent1[i] array == parent2 array[j]
                    {
                        cout << tempParent1[i]; // print that equal value.
                        found = true; // set found equal to true.
                    }
                }
            }
        }
    }
    
}
int Tree::rootNug(int index)
{
    bool found = false;
    int rootNug = 0;
    for(int i = 0; i < size; ++i)
    {
        if(index == i)
        {
            found = true;
            rootNug = myParent[i];
            //cout << "I came here" <<  rootNug << endl;
            //return rootNug;
        }
    }
    if(!found)
    {
        rootNug = -2;
    }
    return rootNug;
}
//returns what level a specified node is at.
int Tree:: Level(int index)
{
    int temp = 1;
    count = temp;
    int parent = rootNug(index); // gets the parent of the index passed in
    if(parent == -1) // if it equals -1 then the level is 1 as that is the root
    {
        return count;
    }
    //keep going until you climb up to the root, incrementing a count variable to keep track of the number of attempts it took to climb to that roor.
    else{
        Level(parent);
        count++;
    }
    return count;
}
int Tree:: Height()
{
    int maxOfNodes =0;
    for(int i = 0; i < size; ++i)
    {
        int pos = i; // postion of index in my array to access the next node.
        int counter = 1; // counter to keep track of deep a specfic node is.
        while(myParent[pos] != -1)
        {
            counter++; // increment count every time you go thru a node and reach -1
            pos = myParent[pos]; // then move to the next parent of that node.
        }
        maxOfNodes = max(maxOfNodes, counter); // take the max of the value if it 0 then there is no elements.
    }
    return maxOfNodes;
}
void Tree::nodesAtLevel(int level)
{
    for(int i = 0; i < size; ++i) // loop thru parent array.
    {
        if(level == Level(i)) // if level == the Level(i) as this will return the level a certain node is at.
        {
            cout << i << " "; // print out that index.
        }
    }
    
}
void Tree::PrintPreOrder(int root)
{
    cout << root << " ";
    for (int i = 0; i < size; ++i) {
        if(root == myParent[i])
        {
            PrintPreOrder(i);
        }
        
    }
}
void Tree::PreOrder()
{
    PrintPreOrder(Root());
}
//display my tree.
void Tree::display()
{
    for (int i =0; i < size; ++ i)
    {
        //  cout << i << endl;
        cout  << i << ":" << myParent[i] << "\t";
    }
    
}
//ostream operator to display the tree.
ostream& operator <<(ostream& s, const Tree& tree)
{
    for (int i =0; i < tree.size; ++ i)
    {
        s << i << ":" << tree.myParent[i] << "\t";
    }
    return s;
}
bool Tree::isEmpty()
{
    if(myParent == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int main()
{
    int numNodes;
    int node;
    int parent;
    cin >> numNodes;
    Tree* myTree = new Tree(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        cin >> node >> parent;
        myTree -> setParent(node, parent);
        if(parent == -1)
        {
            myTree -> setRoot(node);
        }
    }
    cout<< "This Is The Original Tree:"<<endl;
    cout << *myTree << endl;
    Tree* newTree = new Tree(*myTree);
    cout << "The Tree we just copied:" <<endl;
    cout << *newTree << endl;
    cout << "The Root Of The Tree is:" << endl << myTree -> Root() <<endl;
    cout << "This is the Least Common Ancestor of Node 3 and Node 8:" << endl; myTree -> LCM(3, 8); cout << endl;
    cout << "This is the Least Common Ancestor of Node 13 and Node 11:" << endl; myTree -> LCM(13, 11); cout << endl;
    cout << "This is the Least Common Ancestor of Node 13 and Node 8:" << endl; myTree -> LCM(13, 8); cout << endl;
    
    cout << "These are the children of Node 10 is/are:"<< endl;myTree -> children(10);cout << endl;
    cout << "These are the children of Node 12 is/are:"<< endl;myTree -> children(12);cout << endl;
    
    cout << "These are the siblings of Node 3 is/are:"<<endl; myTree -> siblings(3);cout<< endl;
    cout << "These are the siblings of Node 12:"<<endl; myTree -> siblings(12);cout<< endl;
    
    cout << "These are the Nodes at Level 3:" << endl;  myTree -> nodesAtLevel(3); cout << endl;
    
    cout << "This is the Height of the tree:" << endl << myTree -> Height() << endl;
    
    cout << "The Level of node 3 in the tree is: " << endl; cout <<  myTree -> Level(3);cout<<endl;
    cout << "The Level of node 12 in the tree is" << endl;cout <<  myTree -> Level(12);cout<<endl;
    
    cout << "This is the parent of Node 5: "<< endl; myTree -> parent(5); cout << endl;
    
    
    cout << "This is the LCM OF Node 1 and Node 1:" << endl; myTree -> LCM(1,1); cout << endl;
    cout << "This is my Tree in PreOrder:" << endl; myTree -> PreOrder(); cout << endl;
    // cout << "These are the Nodes at Level 3:"; myTree -> nodesAtLevel(3);
    
    
    
    delete myTree;
    delete newTree;
    return 0;
}

