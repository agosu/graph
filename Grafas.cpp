#include <cstdlib>
#include <iostream>
#include <climits>

using namespace std;

bool is_unvisited(int j, int unvisited[], int number_of_cities){
	bool unvisit = false;
	for(int i = 0; i < number_of_cities && unvisit == false; i++){
		if(unvisited[i] == j){
			unvisit = true;
		}
	}
	return unvisit;
}

void add_to_visited(int current_city, int unvisited[], int visited[], int number_of_cities){
	int i = 0;
	while(visited[i] != -1){
		i++;
	}
	visited[i] = current_city;
	i = 0;
	while(unvisited[i] != current_city){
		i++;
	}
	for(; i < number_of_cities - 1 && unvisited[i] != -1; i++){
		unvisited[i] = unvisited[i + 1];
	}
	unvisited[i] = -1;
}

int main() {
	int number_of_cities = 7;
	int adjacency_matrix[number_of_cities][number_of_cities] =
		{
			{-1, 5, -1, 4, -1, -1, -1},
			{5, -1, 3, -1, -1, -1, -1},
			{-1, 3, -1, 4, -1, -1, 2},
			{4, -1, 4, -1, 3, 1, -1},
			{-1, -1, -1, 3, -1, -1, -1},
			{-1, -1, -1, 1, -1, -1, 1},
			{-1, -1, 2, -1, -1, 1, -1}
		};
    /*int adjacency_matrix[number_of_cities][number_of_cities] =
		{
			{-1, 5, -1, 4, -1, -1, -1},
			{5, -1, 3, -1, -1, -1, -1},
			{-1, 3, -1, 4, -1, -1, 2},
			{4, -1, 4, -1, -1, 1, -1},
			{-1, -1, -1, -1, -1, -1, -1},
			{-1, -1, -1, 1, -1, -1, 1},
			{-1, -1, 2, -1, -1, 1, -1}
		};*/
	int visited[number_of_cities];
	int unvisited[number_of_cities];
	for(int i = 0; i < number_of_cities; i++){
		visited[i] = -1;
		unvisited[i] = i;
	}
	// atstumas iki pradinio miesto, previous city
	// kur pirmas 0, nuo to miesto ieškom
	int rezults_table[number_of_cities][2] =
		{
			{0, -1},
			{INT_MAX-1, -1},
			{INT_MAX-1, -1},
			{INT_MAX-1, -1},
			{INT_MAX-1, -1},
			{INT_MAX-1, -1},
			{INT_MAX-1, -1}
		};
	int current_city = 0;
	int start_city = 0;
	int end_city = 4;
	int min_neighbour_cost;
	int min_neighbour;
	int min_cost_among_unvisited;
	int min_among_unvisited;
	while(unvisited[0] != -1 && current_city != -1){
		min_neighbour_cost = INT_MAX;
		min_neighbour = -1;
		for(int j = 0; j < number_of_cities; j++){
			if(is_unvisited(j, unvisited, number_of_cities) && adjacency_matrix[current_city][j] != -1){
				rezults_table[j][0] = rezults_table[current_city][0] + adjacency_matrix[current_city][j];
				rezults_table[j][1] = current_city;
				if(rezults_table[j][0] < min_neighbour_cost){
					min_neighbour_cost = rezults_table[j][0];
					min_neighbour = j;
				}
			}
		}
		add_to_visited(current_city, unvisited, visited, number_of_cities);
		if(min_neighbour != -1){
			current_city = min_neighbour;
		} else{
			min_cost_among_unvisited = INT_MAX;
			min_among_unvisited = -1;
			for(int i = 0; i < number_of_cities && unvisited[i] != -1; i++){
				if(rezults_table[unvisited[i]][0] < min_cost_among_unvisited){
					min_cost_among_unvisited = rezults_table[unvisited[i]][0];
					min_among_unvisited = unvisited[i];
				}
			}
			current_city = min_among_unvisited; //jei pabaiga, tai bus -1
		}
	}
	int min_cost = rezults_table[end_city][0];
	if(min_cost == INT_MAX-1){
        cout << "No path" << endl;
	}else{
        int path[number_of_cities];
        for(int i = 0; i < number_of_cities; i++){
            path[i] = -1;
        }
        bool finished = false;
        int i = 0;
        int reverse_end_city_helper = end_city;
        path[i] = end_city;
        i++;
        int kiek_path_elementu = 1;
        while(!finished){
            kiek_path_elementu++;
            path[i] = rezults_table[reverse_end_city_helper][1];
            if(path[i] == start_city){
                finished = true;
            }
            reverse_end_city_helper = path[i];
            i++;
        }
        cout << "Min_cost: " << min_cost << endl;
        cout << "Path: ";
        for(int i = kiek_path_elementu - 1; i >= 0; i--){
            cout << path[i] << " ";
        }
	}
}
