#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>
#include <string>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    private:
      //std::vector<Iterator> keys;
      struct Node
      {
          Node(KeyType keyValue) {key = keyValue;}
          vector<ValueType> values;
          KeyType key;
          Node*    right;
          Node*    left;
      };
      Node* m_head;
      int size;
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
        
        ~Iterator()
        {
            /*delete key;
            
            vector<ValueType*>::iterator it = v.begin();
            while(it != v.end())
            {
                delete *it;
                it = v.erase(it);
            }*/
        }

        ValueType& get_value() const
        {
            //if(is_valid())
                return node->values[currIndex];
            
        }

        bool is_valid() const
        {
            return node != nullptr && (currIndex >= 0 && currIndex < node->values.size());
        }

        void advance()
        {
            currIndex++;
        }

      private:
        Node* node;
        //std::vector<ValueType*> values;
        int currIndex;
    
    };

    TreeMultimap()
    {
        m_head = nullptr;
        // Replace this line with correct code.
    }

    ~TreeMultimap()
    {
        Node* p = m_head;
        //create a new Node that stores the next node, delete the current node, and set current node to the next node
        while(p != nullptr)
        {
            Node* n = p->right;
            delete p;
            p = n;
        }
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        /*Iterator existingKey = find(key);
        //if key exists already
        if(existingKey.is_valid())
        {
            existingKey.values.push_back(new ValueType(value));
        }
        else
        {
            if(m_head == nullptr)
            {
                m_head = new Node(key);
                return;
            }
        }*/
        
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
            if(key == currNode->key)
            {
                //std::cerr << key << std::endl;
                currNode->values.push_back(value);
                return;
            }
            if(key < currNode->key)
            {
                if(currNode->left != nullptr)
                    currNode = currNode->left;
                else
                {
                    currNode->left = new Node(key);
                    currNode->left->right = nullptr;
                    currNode->left->left = nullptr;
                    currNode->left->values.push_back(value);
                    return;
                }
            }
            else if(key > currNode->key)
            {
                if(currNode->right != nullptr)
                    currNode = currNode->right;
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
        while(currNode != nullptr)
        {
            if(key == currNode->key)
                return Iterator(currNode);
            else if(key < currNode->key)
                currNode = currNode->left;
            else
                currNode = currNode->right;
        }
        std::cerr << "item not found" << std::endl;
        return Iterator();
    }
};

#endif // TREEMULTIMAP_INCLUDED
