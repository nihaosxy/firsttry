#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
#include<math.h>
using namespace std;
template <class T>
class BinaryTreeNode{
public:
    T element;
    BinaryTreeNode<T>* leftChild;
    BinaryTreeNode<T>* rightChild;
    BinaryTreeNode(const T&ele){
        element = ele;
        leftChild = NULL;
        rightChild = NULL;
    }
};
template <class T>
class BinarySearchTree{
private:
    BinaryTreeNode<T>* root;
public:
    BinarySearchTree(){
        root=0;
    }
    void insertNode(const T&value){
        BinaryTreeNode<T> *p=root,*prev=NULL;
        while(p!=0){
            prev=p;
            if(p->element < value)
                p=p->rightChild;
            else
                p=p->leftChild;
        }
        if(root==NULL)
            root=new BinaryTreeNode<T>(value);
        else if(prev->element<value){
            prev->rightChild =new BinaryTreeNode<T>(value);
        }
        else
            prev->leftChild =new BinaryTreeNode<T>(value);
    }
    void PostOrderRecusion(BinaryTreeNode<T>* S){
        if(S!=NULL){
            PostOrderRecusion(S->leftChild);
            PostOrderRecusion(S->rightChild);
            cout << S->element << " ";
        }
    }
    BinaryTreeNode<T>* searchy(BinaryTreeNode<T>*S,T key){
        BinaryTreeNode<T>* current = S;
        while((current!=NULL)&&(key!=current->element)){
            current=(key<current->element)?searchy(current->leftChild,key):searchy(current->rightChild,key);
        }
        if(current==NULL)
            throw 1;
        return current;
    }
    BinaryTreeNode<T>* searchyforpre(BinaryTreeNode<T>*S,T key){
        BinaryTreeNode<T>* current = S;
        BinaryTreeNode<T>* pes = S;
        while((current!=NULL)&&(key!=current->element)){
            if(current->leftChild->element==key || current->rightChild->element==key)
                pes=current;
            current=(key<current->element)?searchyforpre(current->leftChild,key):searchyforpre(current->rightChild,key);
        }
        current=pes;
        return current;
    }
    void search(){
        try{
            T s;
            cin >> s;
            BinaryTreeNode<T>* p=searchy(root,s);
            cout << "found!" << endl;
        }catch(int){cout << "not found!" << endl;};
    }
    void deleteByMerging(BinaryTreeNode<T>*& node){
        BinaryTreeNode<T> *tmp=node;
        if(node->leftChild==NULL && node->rightChild==NULL)
        {
            BinaryTreeNode<T>* current =searchyforpre(root,node->element);
            T key=node->element;
            if(current->leftChild->element==key){current->leftChild=NULL;}

            if(current->rightChild->element==key)
                current->rightChild=NULL;

        }
        else if(node!=NULL){

            if(!node->rightChild){
                node->element=node->leftChild->element;
                tmp=node->leftChild;
                node->leftChild=tmp->leftChild;
                node->rightChild=tmp->rightChild;
            }
            else if(node->leftChild==NULL){
                node->element=node->rightChild->element;
                tmp=node->rightChild;
                node->leftChild=tmp->leftChild;
                node->rightChild=tmp->rightChild;
            }
            else{
                tmp=node->leftChild;
                while(tmp->rightChild!=NULL)
                    tmp=tmp->rightChild;
                tmp->rightChild=node->rightChild;
                node->element=node->leftChild->element;
                tmp=node->leftChild;
                node->leftChild=tmp->leftChild;
                node->rightChild=tmp->rightChild;
            }
            //delete tmp;
        }
    }
    void deleteByCopying(BinaryTreeNode<T>*& node){
        BinaryTreeNode<T> *previous,*tmp=node;
        if(node->leftChild==NULL && node->rightChild==NULL)
        {
            BinaryTreeNode<T>* current =searchyforpre(root,node->element);
            T key=node->element;
            if(current->leftChild->element==key){current->leftChild=NULL;}

            if(current->rightChild->element==key)
                current->rightChild=NULL;

        }
        else if(!node->rightChild){
                node->element=node->leftChild->element;
                tmp=node->leftChild;
                node->leftChild=tmp->leftChild;
                node->rightChild=tmp->rightChild;
            }
        else if(node->leftChild==NULL){
                node->element=node->rightChild->element;
                tmp=node->rightChild;
                node->leftChild=tmp->leftChild;
                node->rightChild=tmp->rightChild;
            }
        else{
            tmp=node->leftChild;
            previous=node;
            while(tmp->rightChild!=NULL){
                previous=tmp;
                tmp=tmp->rightChild;
            }
            node->element=tmp->element;
            if(previous==node)
                previous->leftChild=tmp->leftChild;
            else
                previous->rightChild=tmp->leftChild;
        }
        //delete tmp;
    }
    BinaryTreeNode<T>* getRoot(){
        return root;
    }
    void PostOrder(){
        PostOrderRecusion(root);
    }
    void levelOrder(){
        queue<BinaryTreeNode<T>*> nodeQueue;
        BinaryTreeNode<T>* pointer = root;
        if(pointer)
            nodeQueue.push(pointer);
        while(!nodeQueue.empty())
        {
            pointer = nodeQueue.front();
            cout << pointer->element << " ";
            nodeQueue.pop();
            if(pointer->leftChild)
            {
                nodeQueue.push(pointer->leftChild);
            }

            if(pointer->rightChild)
            {
                nodeQueue.push(pointer->rightChild);
            }

        }
        cout << endl;
    }
};
int main()
{
    BinarySearchTree<int> A;
    int num;
    cin >> num;
    int m;
    for(int i=0;i<num;i++){
        cin >> m;
        A.insertNode(m);
    }
    A.PostOrder();
    cout << endl;
    A.levelOrder();
    cout << endl;
    A.insertNode(98);
    A.levelOrder();
    cin >> m;
    BinaryTreeNode<int>*p=A.searchy(A.getRoot(),m);
    A.deleteByCopying(p);
    A.levelOrder();
}
/*
7
122 99 110 105 250 200 300
*/
