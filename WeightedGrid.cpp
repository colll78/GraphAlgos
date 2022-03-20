#include "WeightedGrid.h"

WeightedGrid::WeightedGrid(int width, int height, bool autogen) : width(width), height(height) {
	if (autogen) {
		add_rect(1, 7, 4, 9);
		typedef std::pair<int, int> pii;
		forests = std::unordered_set<std::pair<int, int>, pair_hash>{
				pii{3, 4}, pii{3, 5}, pii{4, 1}, pii{4, 2},
				pii{4, 3}, pii{4, 4}, pii{4, 5}, pii{4, 6},
				pii{4, 7}, pii{4, 8}, pii{5, 1}, pii{5, 2},
				pii{5, 3}, pii{5, 4}, pii{5, 5}, pii{5, 6},
				pii{5, 7}, pii{5, 8}, pii{6, 2}, pii{6, 3},
				pii{6, 4}, pii{6, 5}, pii{6, 6}, pii{6, 7},
				pii{7, 3}, pii{7, 4}, pii{7, 5}
		};
	}
}

bool WeightedGrid::in_bounds(std::pair<int, int> id) const {
	return 0 < id.first && id.first < width && 0 <= id.second && id.second < height;
}

bool WeightedGrid::passable(std::pair<int,int> id) const{
	return walls.count(id) <= 0;
}

std::vector<std::pair<int, int>> WeightedGrid::reconstruct_path(std::pair<int, int> start, std::pair<int, int> goal){
	std::vector<std::pair<int, int>> path;
	std::pair<int, int> curr = goal;
	while (curr != start) {
		path.push_back(curr);
		curr = came_from[curr];
	}
	path.push_back(start);
	std::reverse(path.begin(), path.end());
	return path;
}

double WeightedGrid::cost(std::pair<int, int> from_node, std::pair<int, int> to_node) const{
	return forests.count(from_node) > 0 ? 5 : 1;
}

std::vector<std::pair<int, int>> WeightedGrid::neighbors(std::pair<int, int> id) const {
	std::vector<std::pair<int, int>> results;

	for (std::pair<int,int> dir : DIRS) {
		std::pair<int, int> next = { id.first + dir.first, id.second + dir.second };
		if (passable(next) && in_bounds(next)) {
			results.push_back(next);
		}
	}

	if ((id.first + id.second) % 2 == 0) {
		std::reverse(results.begin(), results.end());
	}
	return results;
}

void WeightedGrid::dijkstras_search(std::pair<int, int> start, std::pair<int, int> goal){
	PriorityQueue<std::pair<int, int>, double> frontier;
	frontier.put(start, 0);
	came_from.clear();
	cost_so_far.clear();
	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		std::pair<int, int> current = frontier.get();
		if (current == goal) {
			break;
		}
		for (std::pair<int, int> next : neighbors(current)) {
			double new_cost = cost_so_far[current] + cost(current, next);
			if (cost_so_far.count(next) <= 0 || new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				frontier.put(next, new_cost);
			}
		}
	}
}


std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> WeightedGrid::breadth_first_search(std::pair<int, int> start){
	std::queue<std::pair<int, int>> frontier;
	frontier.push(start);
	std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> came_from;
	came_from[start] = start;

	while (!frontier.empty()) {
		std::pair<int, int> current = frontier.front();
		frontier.pop();

		for (std::pair<int, int> next : neighbors(current)) {
			if (came_from.count(current) <= 0) {
				frontier.push(next);
				came_from[next] = current;
			}
		}
	}
	return came_from;
}

std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> WeightedGrid::breadth_first_search(std::pair<int, int> start, std::pair<int, int> goal){
	std::queue<std::pair<int, int>> frontier;
	frontier.push(start);
	came_from[start] = start;

	while (!frontier.empty()) {
		std::pair<int, int> current = frontier.front();
		frontier.pop();

		if (current == goal) {
			break;
		}

		for (std::pair<int, int> next : neighbors(current)) {
			if (came_from.count(current) <= 0) {
				frontier.push(next);
				came_from[next] = current;
			}
		}
	}
	return came_from;
}

void WeightedGrid::print(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::pair<int,int>> *path){
	std::string result; 
	for (int y = 0; y != height; ++y) {
		for (int x = 0; x != width; ++x) {
			std::pair<int, int> id{ x,y };
			//std::cout << id.first << " " << id.second << '\n';
			if (walls.count(id) > 0) {
				std::cout << "###";
			}
			else if (start == id) {
				std::cout << " A ";
			}
			else if (goal == id) {
				std::cout << " Z ";
			}
			else if (path && find(path->begin(), path->end(), id) != path->end()) {
				std::cout << " @ ";
			}
			else {
				std::cout << " . ";
			}
		}
		std::cout << "\n";
	}
}

void WeightedGrid::add_rect(int x_1, int y_1, int x_2, int y_2){
	for (int x = x_1; x < x_2; x++) {
		for (int y = y_1; y < y_2; y++) {
			walls.insert(std::make_pair(x, y));
			//std::cout << x << " " << y << "\n";
		}
	}
}

std::array<std::pair<int,int>, 4> WeightedGrid::DIRS = {
	/* East, West, North, South */
	std::pair<int,int>{1, 0}, std::pair<int,int>{-1, 0},
	std::pair<int,int>{0, -1}, std::pair<int,int>{0, 1}
};