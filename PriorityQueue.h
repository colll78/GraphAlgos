#pragma once
#include <utility>

template<typename T, typename priority_t> 
class PriorityQueue {
	typedef std::pair<priority_t, T> pq_ele;
	std::priority_queue<pq_ele, std::vector<pq_ele>, std::greater<pq_ele>> elements;
public:
	inline bool empty() const {
		return elements.empty();
	}

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
	
};