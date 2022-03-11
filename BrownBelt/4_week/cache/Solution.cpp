#include "Common.h"
#include <string>
#include <unordered_map>
#include <mutex>
#include <list>

using namespace std;

class LruCache : public ICache {
public:
    LruCache(
        shared_ptr<IBooksUnpacker> books_unpacker,
        const Settings& settings
        )
        : books_unpacker_(move(books_unpacker))
        , settings_(settings)
    {
        // реализуйте метод
    }

    struct Cont {
        BookPtr book;
        list<string>::const_iterator it;
    };

    virtual BookPtr GetBook(const string& book_name) override {
        lock_guard<mutex> guard(m);

        if(auto result = storage.find(book_name); result != storage.end()) 
        {
            rating.splice(rating.end(), rating, result->second.it);
            return result->second.book;
        }
        

        auto book = books_unpacker_->UnpackBook(book_name);
        auto content_size = book->GetContent().size();

        if(clean_up_cache(content_size))
        {
            current_size += content_size;
            storage[book_name] = {
                move(book),
                rating.insert(rating.end(), book_name)    
            };
            return storage[book_name].book;
        }

        return book;
    }
private:
    bool clean_up_cache (size_t content_size) 
    {
        while (current_size + content_size > settings_.max_memory &&  
              current_size != 0) 
        {   
            current_size -=  storage[rating.front()].book->GetContent().size();
            storage.erase(rating.front());
            rating.pop_front();
        }
        return current_size + content_size <= settings_.max_memory;
    }

    mutex m;

    unordered_map<string, Cont> storage;
    list<string> rating;

    const Settings& settings_;
    size_t current_size = 0;
    
    shared_ptr<IBooksUnpacker> books_unpacker_;
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
    ) 
{
    return make_unique<LruCache>(move(books_unpacker), settings);
}
