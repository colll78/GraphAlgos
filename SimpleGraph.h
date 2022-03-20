#pragma once
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>

class SimpleGraph {
	std::unordered_map<char, std::vector<char>> edges;
public:
	SimpleGraph(std::unordered_map<char, std::vector<char>> edges);
	std::vector<char> neighbors(char id);
	void breadth_first_search(char start);
	void breadth_first_search(char start, char goal);
};