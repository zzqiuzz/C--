#include <iostream>
using std::cout;
using std::endl;

//定义链表节点
struct Node{
    int val = 0;
    Node *next = nullptr;
    Node() = default;
    Node(int value) : val(value), next(nullptr){};
};
//定义链表类

class LinkedList{
    private: 
        Node *head_node = nullptr;
        Node *tail_node = nullptr;
        int size = 0;
 
    public:
        LinkedList() : head_node(nullptr), tail_node(nullptr), size(0){};

        ~LinkedList(){
            clear();
        }
        
        // 判断链表是否为空
        bool isEmpty(){return size == 0;}

        //获取链表的大小
        int Size(){return size;}
    
        //在头部插入元素
        void insertAtHead(int value){
            Node *new_node = new Node(value);
            if(size == 0)
                head_node = tail_node = new_node;
            else{ 
                new_node->next = head_node;
                head_node = new_node; 
            }
            size++;
        }

        //在尾部插入元素
        void insertAtTail(int value){
            Node *new_node = new Node(value);
            if(isEmpty())
                head_node = tail_node = new_node;
            else{
                tail_node->next = new_node;
                tail_node = new_node;
            }
            size++;
            
        }

        //在指定位置插入元素
        void insertAt(int index, int value){
            Node *new_node = new Node(value);
            if(index < 0 || index > size)
                throw std::out_of_range("insertAt: Index out of range.");
            if(index == 0){
                insertAtHead(value);
            }
            else if(index == size){
                insertAtTail(value);
            }
            else{
                int count = 0;
                Node *head = head_node; // 这里非常重要 不能直接对head_node操作
                while(head){
                    if(++count == index){
                        Node *tmp = head->next;
                        head->next = new_node;
                        new_node->next = tmp;
                        break;

                    }
                    head = head->next;
                    
                }
            }
            size++;
        }

        //删除链表头部节点
        void deleteHead(){
            if(isEmpty())
                throw std::out_of_range("deleteHead: Index out of range.");
            Node *tmp = head_node;
            head_node = head_node->next;
            if(head_node == nullptr)tail_node = nullptr;
            delete tmp; 
            size--; 
        }

        //删除链表尾部节点
        void deleteTail(){
            if(isEmpty())
                throw std::out_of_range("deleteTail: Index out of range.");
            if(size == 1)
            {
                delete head_node;
                head_node = tail_node = nullptr;
            }
            else{ // 至少两个元素
                Node *cur = head_node;
                Node *pre = head_node;
                while(cur->next != tail_node){
                    pre = cur;
                    cur = cur->next;
                }
                delete tail_node;
                cur->next = nullptr;
                tail_node = cur;
                
            } 
            size--;
        }

        //删除链表指定位置的节点
        void deleteAt(int index){
            if(index < 0 || index > size)
                throw std::out_of_range("deleteAt: Index out of range.");
            Node dummy_node;
            dummy_node.next = head_node;
            Node *cur = &dummy_node;
            for(int idx = 0; idx < size; idx++){ // d 0 1 2 3
                if(idx == index){
                    Node *node_to_delete = cur->next;
                    Node *tmp = node_to_delete->next;
                    cur->next = tmp;
                    delete node_to_delete;
                    node_to_delete = nullptr;
                    size--;

                }
                cur = cur->next;
            }
            head_node = dummy_node.next;
            if(size == 1)tail_node = head_node;
        }

        //获取指定位置的节点值 
        int findAt(int index){
            if(index < 0 || index > size)
                throw std::out_of_range("findAt: Index out of range.");
            Node *cur = head_node;
            while(index){
                cur = cur->next;
                index --;
            }
            return cur->val;
        }


        //查找节点所在的位置
        int find(const int value){
            if(size == 0) return -1;
            int count = 0;
            Node *cur_node = head_node;
            for(int i = 0; i < size; i++){
                if(cur_node->val == value)
                    return count;
                cur_node = cur_node->next;
                count++;
            }
            return -1;
        }

        //清空链表
        void clear(){
            while(head_node){
                cout << "deleting node " << head_node->val << endl;
                Node *tmp = head_node->next;
                delete head_node; 
                head_node = tmp; 
            }
            cout << "LinkedList has been cleared" << endl;
            size = 0;
        }

        //打印链表
        void print(){
            Node *cur_node = head_node;
            while(cur_node){
                cout << cur_node->val << " -> ";
                cur_node = cur_node->next;
            }
            cout << "nullptr" << endl;
        }
};

int main(int argc, char *argv[]){
    LinkedList l;
    l.insertAtHead(2);
    l.insertAtHead(1);
    l.insertAtHead(0);
    l.insertAtTail(3);
    l.insertAt(0, 100);
    l.print();
    cout << "Index of Node 1 is: " << l.find(1) << endl;
    cout << "find index at 1: " << l.findAt(1) << endl;
    cout << "-------------------------------" << endl; // 100 0 1 2 3
    l.deleteHead(); 
    l.deleteTail();
    l.print();
    cout << "-------------------------------" << endl;
    l.deleteAt(1);
    l.print();
    l.deleteAt(0);
    l.print();
    l.deleteAt(0);
    l.print();
}




