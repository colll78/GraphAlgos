#pragma once
#include <array>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "PriorityQueue.h"

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2> &p) const {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);

		// Mainly for demonstration purposes, i.e. works but is overly simple
		// In the real world, use sth. like boost.hash_combine
		return h1 ^ h2;
	}
};

class WeightedGrid {
	static std::array<std::pair<int,int>, 4> DIRS;
	int width;
	int height;
	std::unordered_set<std::pair<int, int>, pair_hash> walls;
	std::unordered_set<std::pair<int, int>, pair_hash> forests;
	std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> came_from;
	std::unordered_map<std::pair<int, int>, double, pair_hash> cost_so_far;
public:
	WeightedGrid(int width, int height, bool autogen = false);
	bool in_bounds(std::pair<int,int> id) const;
	bool passable(std::pair<int,int> id) const;
	std::vector<std::pair<int, int>> reconstruct_path(std::pair<int, int> start, std::pair<int, int> goal);
	double cost(std::pair<int, int> from_node, std::pair<int, int> to_node) const;
	std::vector<std::pair<int, int>> neighbors(std::pair<int, int> id) const;
	void dijkstras_search(std::pair<int, int> start, std::pair<int, int> goal);
	std::unordered_map<std::pair<int,int>, std::pair<int, int>, pair_hash> breadth_first_search(std::pair<int,int> start);
	std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> breadth_first_search(std::pair<int, int> start, std::pair<int, int> goal);
	void print(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::pair<int,int>> *path = nullptr);
private:
	void add_rect(int x_1, int y_1, int x_2, int y_2);
};