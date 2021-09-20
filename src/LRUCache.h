#pragma once
#include <unordered_map>
#include <string>

template <typename DataType>
class LRUCache
{
public:
    LRUCache(int capacity);
    ~LRUCache();
    std::pair<DataType, bool> Get(std::string key);
    void Put(std::string key, DataType value);
    int Capacity() const { return capacity_; }
    int Size() const { return static_cast<int>(hash_map_.size()); }

private:
    struct Node
    {
        Node* prev_ = nullptr;
        Node* next_ = nullptr;
        std::string val_;
        Node(std::string val_) : val_(val_) {}
    };
    struct Data
    {
        DataType data_;
        Node* loc_ = nullptr;
    };

    void PutNodeAtHead(Node* curr_node);
    void PutNewNodeAtHead(Node* new_node);
    void EvictTail();
private:
    std::unordered_map<std::string, Data> hash_map_;
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    const int capacity_ = -1;
};

// The templated class members have to be implemented in the .h file itself
// This is because compiler needs to see the code in order to instantiate templates.
template <typename DataType>
LRUCache<DataType>::LRUCache(int capacity) : capacity_(capacity) {
    if (Capacity() < 3) throw "Error: Can't initialize with capacity less than 3";
}

template<typename DataType>
inline LRUCache<DataType>::~LRUCache()
{
    for (Node* curr = head_; curr != nullptr; )
    {
        Node* tmp = curr;
        curr = curr->next_;

        hash_map_.erase(tmp->val_);
        delete tmp; 
        tmp = nullptr;
    }
}

template <typename DataType>
void LRUCache<DataType>::PutNodeAtHead(Node* curr_node)
{
    if (curr_node == head_) return;

    curr_node->prev_->next_ = curr_node->next_;
    
    if (curr_node == tail_) tail_ = curr_node->prev_;
    else curr_node->next_->prev_ = curr_node->prev_;

    PutNewNodeAtHead(curr_node);
}

template<typename DataType>
inline void LRUCache<DataType>::PutNewNodeAtHead(Node* new_node)
{
    if (head_ == nullptr && tail_ == nullptr)
    {
        head_ = new_node;
        tail_ = new_node;
        return;
    }
    new_node->prev_ = nullptr;
    new_node->next_ = head_;
    head_->prev_ = new_node;
    head_ = new_node;
}

template <typename DataType>
void LRUCache<DataType>::EvictTail()
{
    if (tail_ == nullptr) throw "Error!";
    Node* retVal = tail_;
    tail_ = tail_->prev_;
    tail_->next_ = nullptr;
    hash_map_.erase(retVal->val_);
    delete retVal;
}

template <typename DataType>
std::pair<DataType, bool> LRUCache<DataType>::Get(std::string key)
{
    // Get the value from the hash_map
    auto it = hash_map_.find(key);
    if (it == hash_map_.end())
    {
        // Not found
        DataType invalid;
        return { invalid, false };
    }

    PutNodeAtHead(it->second.loc_);
    return{ it->second.data_, true };
}

template<typename DataType>
inline void LRUCache<DataType>::Put(std::string key, DataType value)
{
    // Check if the key is already at the hash-map
    auto it = hash_map_.find(key);
    if (it != hash_map_.end())
    {
        // Found!
        it->second.data_ = value;
        PutNodeAtHead(it->second.loc_);
    }
    else
    {
        Node* location = new Node(key);
        hash_map_.insert({ key, {value, location} });
        PutNewNodeAtHead(location);
        if (Size() > Capacity()) EvictTail();
    }
}