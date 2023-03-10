#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            currIndex = 0;
        }
        
        Iterator(KeyType& key)
        {
            this->key = key;
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
            if(is_valid())
                return values[index];
        }

        bool is_valid() const
        {
            return values.size() > 0 && (currIndex >= 0 && currIndex < values.size());
        }

        void advance()
        {
            currIndex++;
        }

      private:
        KeyType key;
        std::vector<ValueType*> values;
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
            Node* n = p->m_next;
            delete p;
            p = n;
        }
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        Iterator existingKey = find(key);
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
        }
        
        Node* currNode = m_head;
        for(;;)
        {
            if(key == currNode->m_value.key)
                return;
            if(key < currNode->m_value.key)
            {
                if(currNode->m_prev != nullptr)
                    currNode = currNode->m_prev;
                else
                {
                    currNode->m_prev = new Node(Iterator(key));
                    return;
                }
            }
            else if(key > currNode->m_value.key)
            {
                if(currNode->m_next != nullptr)
                    currNode = currNode->m_next;
                else
                {
                    currNode->m_next = new Node(Iterator(key));
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
            if(key == currNode->m_value.key)
                return currNode->m_value;
            else if(key < currNode->m_value.key)
                currNode = currNode->m_prev;
            else
                currNode = currNode->m_next;
        }
        return Iterator();
    }

  private:
    //std::vector<Iterator> keys;
    struct Node
    {
        Node(Iterator value) {m_value = value;}
        Iterator m_value;
        Node*    m_next;
        Node*    m_prev;
    };
    Node* m_head;
    int size;
};

#endif // TREEMULTIMAP_INCLUDED
