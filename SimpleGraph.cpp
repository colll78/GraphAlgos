#include "SimpleGraph.h"

SimpleGraph::SimpleGraph(std::unordered_map<char, std::vector<char>> edges) : edges(edges) {}

std::vector<char> SimpleGraph::neighbors(char id){ return edges[id]; }

void SimpleGraph::breadth_first_search(char start){
	std::queue<char> frontier;
	frontier.push(start);

	std::unordered_set<char> reached;
	reached.insert(start);

	while (!frontier.empty()) {
		char current = frontier.front();
		frontier.pop();

		std::cout << " Visiting " << current << '\n';
		for (char next : neighbors(current)) {
			if (reached.count(next) <= 0) {
				frontier.push(next);
				reached.insert(next);
			}
		}
		
	}
}

void SimpleGraph::breadth_first_search(char start, char goal){
	std::queue<char> frontier;
	frontier.push(start);

	std::unordered_set<char> reached;
	reached.insert(start);
	
	while (!frontier.empty()) {
		char current = frontier.front();
		frontier.pop();

		std::cout << " Visiting " << current << "\n";

		if (current == goal) {
			std::cout << " Reached Goal!\n";
			break;
		}

		for (char next : neighbors(current)) {
			if (reached.count(next) <= 0) {
				frontier.push(next);
				reached.insert(next);
			}
		}
	}
}
