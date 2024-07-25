#include <iostream>
#include <list>
#include <unordered_map>

template<typename Key, typename Value>
class LRUCache {
public:
	LRUCache(int capacity) : capacity(capacity) {
		std::cout << "init LURCache with " << this->capacity << " items" << std::endl;
	}
	~LRUCache() {
		std::cout << "release LURCache" << std::endl;
	}

	Value get(Key key) {
		auto it = cache.find(key);
		if (it != cache.end()) {
			items.splice(items.begin(), items, it->second);
			return it->second->second;
		} else {
			throw std::runtime_error("Key not found");
		}
	}

	void put(Key key, Value value) {
		auto it = cache.find(key);
		if (it != cache.end()) {
			it->second->second = value;
			items.splice(items.begin(), items, it->second);
		} else {
			if (items.size() == capacity) {
				auto del = items.back();
				cache.erase(del.first);
				items.pop_back();
			}
			items.emplace_front(key, value);
			cache[key] = items.begin();
		}
	}
private:
	int capacity;
	std::list<std::pair<Key, Value>> items;
	std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cache;
};

int main() {
	LRUCache<int, std::string> lru(3);

	lru.put(1, "one");
	lru.put(2, "two");
	lru.put(3, "three");
	std::cout << "Get key 1 : " << lru.get(1) << std::endl;

	lru.put(4, "four");
	try {
		std::cout << "Get Key 2 (should not exist) : " << lru.get(2) << std::endl;
	} catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}

	lru.put(5, "five");
	std::cout << "Get key 1 : " << lru.get(1) << std::endl;
	std::cout << "Get key 4 : " << lru.get(4) << std::endl;
	std::cout << "Get key 5 : " << lru.get(5) << std::endl;
}
