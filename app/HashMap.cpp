#include "HashMap.hpp"

namespace {
    unsigned int ELFHash(const std::string &key){
	    unsigned int hash = 0;
	    unsigned int x = 0;
	    unsigned int i = 0;
	    unsigned int len = key.length();
	    for( i = 0; i < len ; i++)
	    {
		    hash = (hash << 4) + key[i];
		    if((x = hash & 0xF0000000) != 0)
		    {
			    hash ^= (x >> 24);
		    }
		    hash &= ~x;
	    }
	    return hash;
    }
}

HashMap::HashMap(){
    
    sizeNode = 0;
    bucketNum = INITIAL_BUCKET_COUNT;
    
    hashFunction = ELFHash;
    
    buckets = new Node*[bucketNum];
    setBucketList(buckets, bucketNum);
}

HashMap::HashMap(HashFunction hashFunction){
    
    sizeNode = 0;
    bucketNum = INITIAL_BUCKET_COUNT;
    
    this->hashFunction = hashFunction;
    
    buckets = new Node*[bucketNum];
    setBucketList(buckets, bucketNum);
}

HashMap::HashMap(const HashMap &hm){
    
    hashFunction = hm.hashFunction;
    bucketNum = hm.bucketNum;
    sizeNode = hm.sizeNode;

    buckets = new Node* [hm.bucketNum];
    setBucketList(buckets, bucketNum);

    for (int i = 0; i < hm.bucketNum; ++i){
        Node* bucketPtr = hm.buckets[i];
        
        if (bucketPtr != nullptr){
            buckets[i] = new Node;
            Node* tempPtr = buckets[i];

            while(bucketPtr != nullptr){
                tempPtr->key = bucketPtr->key;
                tempPtr->value = bucketPtr->value;

                if (bucketPtr->next == nullptr){
                    tempPtr->next = nullptr;
                } 
                
                else if (bucketPtr->next != nullptr){
                    tempPtr->next = new Node;
                    tempPtr = tempPtr->next;
                }
                bucketPtr = bucketPtr->next;
            }
        }
    }
}

HashMap::~HashMap(){
    
    for (int i = 0; i < bucketNum; ++i){
        deleteNode(buckets[i]);
    }
    delete[] buckets;

}

HashMap& HashMap::operator=(const HashMap& hm){

    if (this != &hm){

        this->~HashMap();

        buckets = new Node*[hm.bucketNum];
        setBucketList(buckets, hm.bucketNum);

        for (int i = 0; i < hm.bucketNum; ++i){
            Node* bucketPtr = hm.buckets[i];
        
            if (bucketPtr != nullptr){
                buckets[i] = new Node;
                Node* tempPtr = buckets[i];

                while(bucketPtr != nullptr){
                    tempPtr->key = bucketPtr->key;
                    tempPtr->value = bucketPtr->value;

                    if (bucketPtr->next == nullptr){
                        tempPtr->next = nullptr;
                    } 
                
                    else if (bucketPtr->next != nullptr){
                        tempPtr->next = new Node;
                        tempPtr = tempPtr->next;
                    }
                    bucketPtr = bucketPtr->next;
                }
            }
        }
    }
    return *this;
}

void HashMap::add(const std::string& key, const std::string& value){

    if (!contains(key)){
        unsigned int index = hashing(key);

        Node* node = new Node;
        node->key = key;
        node->value = value;
        node->next = buckets[index];
    
        buckets[index] = node;

        sizeNode++;

        if (loadFactor() > 0.8)
            reHashing();
    }
}

bool HashMap::remove(const std::string& key){

    if (contains(key)){
        unsigned int index = hashing(key);

        Node* temp = buckets[index];
        Node* prev = temp;

        if (buckets[index]->key == key){
            temp = buckets[index]->next;
            delete buckets[index];
            buckets[index] = temp;
        }
        else {
            temp = buckets[index];

            while(temp->key != key && temp != nullptr){
                prev = temp;
                temp = temp->next;
            }

            prev->next = temp->next;
            delete temp;
        }
        sizeNode--;
        return true;
    }
    else 
        return false;
}

bool HashMap::contains(const std::string &key) const{
    
    bool found = false;
    unsigned int index = hashing(key);
    HashMap::Node *node = buckets[index];

    while (node!= nullptr){
        if (node->key == key){
            found = true;
            break;
        }
        else {
            node = node->next;
        }
    }
    return found;
}

std::string HashMap::value(const std::string &key) const{

    std::string nodeValue = "";
    unsigned int index = HashMap::hashing(key);
    Node* node = buckets[index];

    while (node != nullptr){
        if(node->key == key){
            nodeValue = node->value;
            break;
        }
        else {
            node = node->next;
        }
    }
    return nodeValue;
}

unsigned int HashMap::maxBucketSize() const{

    unsigned int max = getBucketNodes(0);
    unsigned int current;
   
    for(int i = 0; i < bucketNum; ++i){
        current = getBucketNodes(i);

        if (current > max)
            max = current;
    }
    return max;
}

unsigned int HashMap::size() const{
    return sizeNode;
}

unsigned int HashMap::bucketCount() const{
    return bucketNum;
}

double HashMap::loadFactor() const{
    double loadfactor;
    loadfactor = ((double) size())/bucketCount();
    return loadfactor;
}

void HashMap::clear(){

    for (unsigned int i = 0; i < bucketNum; ++i){
        Node* temp = buckets[i];
        while(temp != nullptr){
            buckets[i] = buckets[i]->next;
            delete temp;
            temp = buckets[i];
        }
        buckets[i] = nullptr;
    }
    sizeNode = 0;
}

//================ Added Functions =====================

void HashMap::setBucketList(Node** &bucketList, unsigned int sz){
    
    for(int i = 0; i < sz; ++i){
        bucketList[i] = nullptr;
    }
}

unsigned int HashMap::getBucketNodes(unsigned int index) const{

    unsigned int length = 0;
    HashMap::Node* node = buckets[index];

    while(node != nullptr){
        length++;
        node = node->next;
    }
    return length;
}

unsigned int HashMap::hashing(const std::string &key) const{
    
    unsigned int hashKey = hashFunction(key);
    unsigned int bucketIndex = hashKey % bucketNum;
    return bucketIndex;
}

void HashMap::reHashing(){

	int oldBucketCount = bucketNum;
    bucketNum = oldBucketCount * 2 + 1;
    Node** newbuckets = new Node* [bucketNum]();

    for (unsigned int i = 0; i < oldBucketCount; ++i)
    {
        Node* entry = buckets[i];
        while (entry != nullptr)
        {
            Node* temp= entry;
            entry = entry->next;

            Node*& bucket =newbuckets[hashing(temp->key)];
            temp->next = bucket;
            bucket = temp;
        }
    }
    delete[] buckets;
    buckets = newbuckets;
}

void HashMap::deleteNode(Node* node){
    
    if (node == nullptr)
        return;

    Node* temp = node;

    while(temp != nullptr){
        node = node->next;
        delete temp;
        temp = node;
    }
}
