#pragma once
#include <unordered_map>
#include <string>
using namespace std;

template <typename DataType>
class LRUCache
{
public:
    LRUCache(int capacity);
    std::pair<DataType, bool> Get(std::string key);
    void Put(std::string key, DataType value);

private:
    struct Node
    {
        Node* prev_ = nullptr;
        Node* next_ = nullptr;
        std::string val;
        Node(std::string val_) : val(val_) {}
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
    Node* head_;
    Node* tail_;
    const int size_;
};

// The templated class members have to be implemented in the .h file itself
// This is because compiler needs to see the code in order to instantiate templates.
template <typename T>
LRUCache<T>::LRUCache(int capacity) : size_(capacity) {}

template <typename T>
void LRUCache<T>::PutNodeAtHead(Node* curr_node)
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

template <typename T>
void LRUCache<T>::EvictTail()
{
    if (tail_ == nullptr) throw "Error!";
    Node* retVal = tail_;
    tail_ = tail_->prev_;
    tail_->next_ = nullptr;
    hash_map_.erase(retVal->val);
    delete retVal;
}

template <typename T>
pair<T, bool> LRUCache<T>::Get(string key)
{
    // Get the value from the hash_map
    auto it = hash_map_.find(key);
    if (it == hash_map_.end())
    {
        // Not found
        T invalid;
        return { invalid, false };
    }

    PutNodeAtHead(it->second.loc_);
    return{ it->second.data_, true };
}

template<typename T>
inline void LRUCache<T>::Put(std::string key, T value)
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
        if (static_cast<int>(hash_map_.size()) > size_) EvictTail();
    }
}