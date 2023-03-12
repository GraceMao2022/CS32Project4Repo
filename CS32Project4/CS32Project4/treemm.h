#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>
#include <string>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    private:
      struct Node
      {
          Node(KeyType keyValue) {key = keyValue;}
          std::vector<ValueType> values; //stores values under key of this node
          KeyType key;
          Node*    right;
          Node*    left;
      };
      Node* m_head; //root node of tree
    
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            currIndex = 0;
            node = nullptr;
        }
        
        Iterator(Node* node)
        {
            this->node = node;
            currIndex = 0;
        }

        ValueType& get_value() const
        {
            return node->values[currIndex];
        }

        bool is_valid() const
        {
            //if node has an actual node and if the currIndex is within the range of the node's vector of ValueTypes
            return node != nullptr && (currIndex >= 0 && currIndex < node->values.size());
        }

        void advance()
        {
            currIndex++;
        }

      private:
        Node* node; //used to access all the values under the given key for this iterator
        int currIndex; //accesses the current value iterator is pointing to
    
    };

    TreeMultimap()
    {
        m_head = nullptr;
    }

    ~TreeMultimap()
    {
        deleteNode(m_head);
        m_head = nullptr;
    }
    
    void deleteNode(Node* node)
    {
        if(node == nullptr)
            return;
        
        deleteNode(node->left);
        deleteNode(node->right);
        
        delete node;
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        //if there are no nodes in tree yet
        if(m_head == nullptr)
        {
            m_head = new Node(key);
            m_head->left = nullptr;
            m_head->right = nullptr;
            m_head->values.push_back(value);
            return;
        }
        Node* currNode = m_head;
        for(;;)
        {
            //if inserted key already exists in the tree
            if(key == currNode->key)
            {
                //add value to node with same key
                currNode->values.push_back(value);
                return;
            }
            //if inserted key should go to the left of current node
            else if(key < currNode->key)
            {
                //if there are still nodes to the left, continue going left in the tree
                if(currNode->left != nullptr)
                    currNode = currNode->left;
                //if there are no more nodes to the left, add new node to the tree
                else
                {
                    currNode->left = new Node(key);
                    currNode->left->right = nullptr;
                    currNode->left->left = nullptr;
                    currNode->left->values.push_back(value);
                    return;
                }
            }
            //if inserted key should go to the right of current node
            else if(key > currNode->key)
            {
                //if there are still nodes to the right, continue going right in the tree
                if(currNode->right != nullptr)
                    currNode = currNode->right;
                //if there are no more nodes to the right, add new node to the tree
                else
                {
                    currNode->right = new Node(key);
                    currNode->right->left = nullptr;
                    currNode->right->right = nullptr;
                    currNode->right->values.push_back(value);
                    return;
                }
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        Node* currNode = m_head;
        
        //continue going left or right in the tree until key is found
        while(currNode != nullptr)
        {
            if(key == currNode->key)
                return Iterator(currNode);
            else if(key < currNode->key)
                currNode = currNode->left;
            else
                currNode = currNode->right;
        }
        
        //if key is not found in the tree
        return Iterator();
    }
};

#endif // TREEMULTIMAP_INCLUDED
