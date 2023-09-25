// priorityqueue.h

#include <iostream>
#include <sstream>
#include <set>
#include <string>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root; // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)

    // helper function to clean up adding a new node
    NODE* newNodePtr(int priority, T value,NODE* link)
    {
        NODE* tempNode = new NODE();
    
        tempNode->priority = priority;
        tempNode->value = value;
        tempNode->dup = false;
        tempNode->link = link;
        tempNode->parent = nullptr;
        tempNode->left = nullptr;
        tempNode->right = nullptr;
        tempNode->parent = nullptr;
    
        return tempNode;
    }
    //private helper functions
    // function for outputting the nodes inorder
    void _recursiveFunction(NODE* node, ostream& output)
    {
        // base case 
        if(node == nullptr)
        {
            return;
        }
        // traverse left side of tree
        _recursiveFunction(node->left,output);
        // push back values to stringstream
        output<<node->priority<< " value: "<<node->value << endl;
        // if the node has duplicates push the values back
        if(node->dup == true)
        {
            node = node->link;
            while(node->link != nullptr)
            {
                output<<node->priority<< " value: "<<node->value << endl;
                node = node->link;
            }
            output<<node->priority<< " value: "<<node->value << endl;
        }
        // traverse right side of tree
        _recursiveFunction(node->right,output);
    }
    void deleteLink(NODE* link)
    {
        // two pointers to traverse the list
        NODE* current = newNodePtr(link->priority,link->value,nullptr);
        NODE* next = nullptr;
        // looping through linked list and deleting the values
        while (current != nullptr)
        {
            next = current->link;
            delete current;
            current = next;
            size--;
        }
        link = nullptr;
    }
    // function for deleteing the nodes in postorder
    void deleteTree(NODE* node){
        if(node != nullptr)
        {
            // if has duplicates call function that deletes linked list
            if(node->dup == true)
            {
                deleteLink(node->link);
            }
            // if left child not null perform recursion on left subtree
            if(node->left != nullptr)
            {
                deleteTree(node->left);
            }
            // if right child not null perform recursion on left subtree
            if(node->right != nullptr)
            {
                deleteTree(node->right);
            }
            // if node has duplicates delete linked list
            //delete node and set to nullptr
            delete node;
            node = nullptr;
            //update size
            size--;
        }

    }
    // function that deletes a certain node found by priority and value
    NODE* deleteNode(NODE* node,int priority,T value)
    {
        //base case
        if(node == nullptr)
        {
            return node;
        }
        // recursion to find the position of the node
        if(priority < node->priority)
        {
            node->left = deleteNode(node->left,priority,value);
        }
        else if(priority > node->priority)
        {
            node->right = deleteNode(node->right,priority,value);
        }
        else
        {
            //if node has duplicates
            if(node->dup == true)
            {
                // makes first queued duplicate the new node
                NODE* temp = node->link;
                delete node;
                if(temp->link != nullptr)
                {
                    temp->dup = true;
                }
                return temp;
            }
            //if node has no children
            if(node->left == nullptr && node->right == nullptr)
            {
                //delete node and return nullptr
                delete node;
                node = nullptr;
                return node;
            }
            else if (node->left == nullptr)
            {
                // if left child is empty
                // delete node and return the right node "rotation"
                
                NODE* temp = node->right;
                delete node;
                return temp;
            }
            else if(node->right == nullptr)
            {
                // if right child is empty
                //delete node and return left node "rotation"
                NODE* temp = node->left;
                delete node;
                return temp;
            }
            // if the node has two children
            NODE* temp = findMinNode(node->right);
            node->priority = temp->priority;
            node->right = deleteNode(node->right,temp->priority,value);
        }
        return node;
    }

    // helper function that clones the tree
    NODE* cloneBinaryTree(NODE* node){
        //base case
        if (node == nullptr) {
            return nullptr;
        }
        //pre order traversal
        //copies root
        NODE* copy = newNodePtr(node->priority,node->value,node->link);

        // if node has duplicates copy over
        // couldnt implement

        // copies left subtrees
        copy->left = cloneBinaryTree(node->left);
        //copies right subtrees
        copy->right = cloneBinaryTree(node->right);
        // returns the copy root to the priorityqueue 
        return copy;
        }
    // helper function that finds the lowest node in the tree
    NODE* findMinNode(NODE* root)
    {
        while(root->left != nullptr)
        {
            root = root->left;
        }
        return root;
    }
    // helper function that finds the next lowest priority node in the tree
    NODE* nextHelper(NODE* node)
    {
        NODE* parentNode = node->parent;
        NODE* tempNode;
        // if the node has duplicates
        if(node->dup == true)
        {
            //check if the next node in the list is empty
            node->dup = false;
            NODE* linkNode = node;
            if(linkNode->link != nullptr)
            {
                // if not return that node
                linkNode = linkNode->link;
                linkNode->dup = true;
                return linkNode;
            }
            // else return the next function on its parent ex: if the duplicate list is done call on the parent
            if(linkNode->link == nullptr)
            {
                return nextHelper(linkNode->parent);
            }
        }
        // if nodes right subtree is not empty find the min value because that will be the next inorder node
        if (node->right != nullptr)
        {
            return findMinNode(node->right);
        }
        // otherwise  find the parent of the last node
        while (parentNode != nullptr && node == parentNode->right) {
            node = parentNode;
            parentNode = parentNode->parent;
        }
        return parentNode;
    }
    bool equalTrees(NODE* current ,NODE* other)
    {
        // if both trees are empty return true
        if(current == nullptr && other == nullptr)
        {
            return true;
        }
        // if one or the other is empty return false
        else if(current == nullptr)
        {
            return false;
        }
        else if(other == nullptr)
        {
            return false;
        }
        else
        {
            // checks if the nodes contain duplicates
            if(current->dup == true && other->dup == true)
            {
                //simple while loop
                while(current->link != nullptr && other->link != nullptr)
                {
                    // if any of the conditions break return false
                    if(current->value != other->value || current->priority != other->priority)
                    {
                        return false;
                    }
                    current = current->link;
                    other = other->link;
                }
            }
            //call recursion on left and right subtrees and check if the current nodes are equal
            if(equalTrees(current->left,other->left) &&
                (current->value == other->value) &&
                (equalTrees(current->right,other->right))){
                    return true;
                }
            else 
            {
                return false;
            }
        }
        
    }
 
public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
    
        root = nullptr;
        this->size = 0;
        curr = nullptr;
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        

        if(this->root != nullptr)
        {
            (*this).clear();
        }
        // calls recursion
        root = cloneBinaryTree(other.root);
        // returns the copied tree
        this->size = other.size;
        return *this;
    
    }

    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        //calls helper function
        deleteTree(root);
        root = nullptr;
            
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        //calls helper function
        clear();

    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    void enqueue(T value, int priority) {
        NODE* tempNode = newNodePtr(priority,value,nullptr);
        NODE* prev = new NODE();
        prev = nullptr;
        curr = root;
        while(curr != nullptr)
        {
            if(priority == curr->priority)
            {
                curr->dup = true;
                tempNode->parent = curr;
                while(curr->link != nullptr)
                {
                    curr = curr->link;
                }
                curr->link = tempNode;
                size++;
                return;

            } else if(priority < curr->priority)
            {
                prev = curr;
                curr = curr->left;
            } else 
            {
                prev = curr;
                curr = curr->right;
            }
        }
         
        tempNode->parent = prev;

        if(prev == nullptr){
            root = tempNode;

        } else if(priority < prev->priority){
            prev->left = tempNode;

        }else{
            prev->right = tempNode;
        }
        size++;
    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T dequeue() {
        
        // sets curr equal to lowest value
        (*this).begin();
        T valueOut;
        // grabs value from current
        valueOut = curr->value;
        // calls helper function to delete the lowest node
        root = deleteNode(root,curr->priority,valueOut);
        size--;
        // returns the value of deleted node
        return valueOut; 

    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        
        //function that returns the size of the priority queue / binary tree
        if(root == nullptr)
        {
            this->size = 0;
        }
        return this->size;
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        // calls helper function
        curr = findMinNode(root);
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
        // grabs the value and priority
        value = curr->value;
        priority = curr->priority;
        // gets next node
        curr = nextHelper(curr);

        //returns false if the node is empty
        if(curr == nullptr)
        {
            return false;
        }
        // returns true if not empty
        return true;
    }

    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        
        //vars
        string str = "";
        stringstream ss;

        //starts recursion at root
        _recursiveFunction(this->root,ss);

        // converts stringstream to string
        str = ss.str();
        return str;
        
    }

    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T peek() {
        
        // finds lowest value
        (*this).begin();
        T valueOut;
        // if node is empty go to next node
        if(curr == nullptr)
        {
            (*this).next(curr->value,curr->priority);
        }
        // return value
        valueOut = curr->value;
        return valueOut; 
        
        
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) {
        // calls helper function to check if trees are equal
        if(equalTrees(this->root,other.root) == false)
        {
            return false;
        }
        return true;
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
