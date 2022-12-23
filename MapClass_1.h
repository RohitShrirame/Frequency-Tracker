
#include<string>
using namespace std;
template<typename V>
class MapNode{
    public:
        string key;
        V value;
        MapNode<V> *next;
        MapNode(string key,V value)
        {
            this->key=key;
            this->value=value;
            next=NULL;
        }
        ~MapNode()
        {
            delete next;
        }
};
template<typename V>
class myMap{
    private:
        MapNode<V>** buckets;
        int Count;
        int numBuckets;
    public:
        myMap()
        {
            Count=0;
            numBuckets=5;
            buckets=new MapNode<V>*[numBuckets];
            for(int i=0;i<numBuckets;i++)
            {
                buckets[i]=NULL;
            } 
        }
        ~myMap(){
            for(int i=0; i<numBuckets; i++){
                delete buckets[i];
            }
            delete []buckets;
        } 
    private:
        int getBucketIndex(string key)
        {
            int hashCode=0;
            int currentCoeff=1; // Acts as prime multiple as P^0 = 1
            for(int i=key.length()-1;i>=0;i--)
            {
                hashCode=hashCode+key[i]*currentCoeff;
                // to make sure it does not go out of range
                hashCode=hashCode%numBuckets;
                currentCoeff*=31;
                currentCoeff=currentCoeff%numBuckets;
            }
            return hashCode%numBuckets;
        }
    public:
    void rehash()
    {
        MapNode<V>**temp=buckets;
        buckets=new MapNode<V>* [2*numBuckets];
        //new bucket array has garbage value
        //set it to null
            for(int i=0;i<2*numBuckets;i++)
            {
                buckets[i]=NULL;
            }
        int oldBucketscount = numBuckets;
        numBuckets*=2;
        Count=0;
            for(int i=0;i<oldBucketscount;i++)
            {
                MapNode<V>*head=temp[i];
                while(head!=NULL)
                {
                    insert(head->key,head->value);
                    head=head->next;
                }
            }
        for(int i=0;i<numBuckets/2;i++){
            delete temp[i];
        }
        delete [] temp;
        temp=NULL;
    }

    double getLoadFactor(){
        return (1.0*Count)/numBuckets;
    }

    void insert(string key,V value)
    {
        int bucketIndex=getBucketIndex(key);
        // we need an external head to traverse 
        //bcoz we do not want to move bucket array head
        MapNode<V>*head=buckets[bucketIndex];

        // check if it is already present 
        //if present update value
        while(head!=NULL)
        {
            ///during this traversal if you happen to find the key
            if(head->key==key)
            {
                head->value=value;
                return;
            }
            head=head->next;
        }
        
        head=buckets[bucketIndex];
        MapNode<V>*node=new MapNode<V>(key,value);
        node->next=head;
        buckets[bucketIndex]=node;
        Count++;
        ///check if load factor > 0.7
        if(Count/(numBuckets*1.0)>0.7)
        {
            rehash();
        }
        return;
    }
        /*returns number of nodes inserted*/
    V getSize(){
        return Count;
    }

    V getValue(string key)
    {
        int bucketIndex=getBucketIndex(key);
        MapNode<V>*head=buckets[bucketIndex];
        while(head!=NULL)
        {
            ///during this traversal if you happen to find the key
            if(head->key==key)
            {
                return head->value;
            }

            head=head->next;
        }

        return 0;
        //thats why square brackets return 0 if key not present
    }
        
    V remove(string key)
    {
        int bucketIndex=getBucketIndex( key);
        MapNode<V>*head=buckets[bucketIndex];
        MapNode<V>*prev=NULL;
        while(head!=NULL)
        {
            ///during this traversal if you happen to find the key
            if(head->key==key)
            {
                if(prev==NULL)
                {
                    buckets[bucketIndex]=head->next;
                }
                else
                {
                    prev->next=head->next;
                }
                //store value to be returned
                V value=head->value;
                head->next=NULL;
                delete head;
                Count--;
                return value;

            }
            
            prev=head;
            head=head->next;
        }

         return 0; 
    }

    bool Search(string key)
    {
        int bucketIndex=getBucketIndex(key);

        MapNode<V>* head=buckets[bucketIndex];
        while(head!=NULL)
        {
            if(head->key==key)
            {
                return true;
            }
            head=head->next;
        }
        return false;
    }
};
