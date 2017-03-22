/*
	*Team ID: eYRC-BV#1651
	*Author List: Aayush, Pradyumna, Pranjal, Shashwat
	*filename: dStarRequirement.c
	*Theme: Bothoven
	*Functions: BFS(int), heuristic(int), fCostCalc(int, int), 
				extractMin(int[], int[],int), reverse(int*, int),
				pathFind(int*, int, int*)
	*Global Variable: externals: map, map_link, map_angle
*/

#ifndef __BFS_PATH_FIND__
#define __BFS_PATH_FIND__
#include <iostream>
#include "master_visited.h"
#include "DynamicQueue.h"
#include <stdlib.h>
#include <math.h>

//const int size = 49;
// #define INF 600000

#include "adjacency.h"
using namespace std;
/*
	*Function name: reverse (int *, int)
	*Input: Array to be reversed and the size of the array
	*Output: Reversed array (due to the use of pointer)
	*Logic: Maintains a pointer at both ends of the array and while the left
			index is strictly less than the right one, it swaps those. It then
			increases the left pointer while decreasing the right one.
	*Example Call: reverse (arr, size);
*/
void reverse (signed int *Rev, signed int path_Size) {
	signed int j = path_Size-1, i = 0, temp;
	while(i < j) {
		temp = Rev[i];
		Rev[i] = Rev[j];
		Rev[j] = temp;
		i++;
		j--;
	}
	int k = 1;
	int l = 1;
	for (i = 0; i < path_Size-1; i++){
		if (l == 17){
			l = 1;
			k = 2;
		}
		l += 2;
	}
}
int* move (int path[], int count) {
	int *res = new int[3];
	res[0] = res[1] = res[2] = 0;
	//for (int i = 0; i < count; i++)
	//	cout << path[i] << "\t";
	//cout << endl << "Angle: ";
	//signed int *angle = (signed int*) malloc(count*sizeof(int));
	//for (int j = 0, i = 1; i < count-1; i++, j++) {
	//	//This could be buggy
	//	angle[j] = map_angle[path[i]][path[i+1]] - 
	//				map_angle[path[i-1]][path[i]];
	//	cout << angle[j] << "\t";
	//}
	//angle[count-1] = -1;
	cout << path[0] << "\t";
	for (int i = 0; i < count-1; i++) {
		if ((path[i] == 32 && path[i+1] == 48) || (path[i] == 48 && 
			path[i+1] == 32) || (path[i] == 24 && path[i+1] == 1) ||
			(path[i] == 1 && path[i+1] == 24) || (path[i] == 35 && 
			path[i+1] == 36) || (path[i] == 36 && path[i+1] == 35) || 
			(path[i] == 11 && path[i+1] == 12) || (path[i] == 12 && 
			path[i+1] == 11)) {
				cout << "Obstacle between " << path[i] << " and " << path[i+1];
				res[0] = 1;
				res[1] = path[i];
				res[2] = path[i+1];
				return res;
			}
			cout << path [i+1] << "\t";
	}
	return res;
}
/*
	*Funtion Name: Move (int[], int)
	*Input: An array that contains the path to be followed and
			the number of nodes in that path
	*Output: 3 integers where the first one tells if there was an obstacle
			In case an obstacle is encountered:
				2nd tells the node left
				3rd tells the node it was supposed to go to.
	*Logic: Converts nodes to an array of angle and calls the run function
			Returns the result by changing index to actual nodes
	*Example Call: int *res = Move (path, pathSize);
*//*
signed int* Move (signed int path[], signed int pathSize) {
	signed int *angle = (signed int*) malloc((pathSize - 1)*sizeof(signed int)); // addded the prefix so pathSize needs to be -= 1
	for (signed int j = 0, i = 1; i < pathSize-1; i++, j++) {
		//This could be buggy
		signed int initial_angle, final_angle;
		for (signed int index = 0; index < 5; ++index) {
			if (map[path[i]][index] == path[i+1]) {
				final_angle = map_angle[path[i]][index];
				break;
			}
		}
		for (signed int index = 0; index < 5; ++index) {
			if (map[path[i-1]][index] == path[i]) {
				initial_angle = map_angle[path[i-1]][index];
				break;
			}
		}
		angle[j] = final_angle - initial_angle;
	}
	angle[pathSize-2] = -1;
	signed int *res = mapRun (angle, pathSize);
	if (res[0] != 0) {
		//Assuming that mapRun returns the index of the nodes in res[1] and res[2]	
		// I think count+1 will be the index
		res[1] = path[res[1] + 1];
		res[2] = path[res[2] + 1];
	}
	free(angle);
	return res;
}*/


/*
	*Function name: pathFind (int*, int, int*)
	*Input: An array that stores the parent of each node as returned by dStar,
			The destination we need to reach and a pointer which will be
			updated to store the number of nodes required to reach the
			destination
	*Output: An array starting from the source at zeroth index and contains
			the path all the way to the destination.
	*Logic: Traces back tha parent from the destination until it reaches the
			the source (where the index of the parent is -1.) In the process,
			it also keeps updating the number of nodes in the path from source
			to the destination.	
	*Example Call: int *path = pathFind (parent, destination, &pathSize);
*/
signed int* pathFind (signed int *parent, signed int destination, signed int *pathSize) {
	signed int *path = (signed int*) malloc (size*sizeof(signed int));
	*pathSize = 1;			//There is at least one element (destination)
	signed int i = destination, j = 1;
	path[0] = destination;
	//Creates a path 
	while (parent[i] != -1) {
		(*pathSize)++;
		path[j++] = parent[i];
		i = parent[i];
	}
	path[j] = -1;
	
	//Corrects the order of the path
	reverse (path, *pathSize);
	/*for (int i = 0; i < *pathSize; i++)
		cout << path[i] << "\t";
	cout << endl;
	*/
	return path;
}

/*
	*Function name: BFS (int)
	*Input: Source of the search tree
	*Output: An array with cost of traversing all nodes from the source
	*Logic: This is a simple implementation of standard Breadth First Search
			It puts the source to a queue. Then as long as the queue is not
			empty, it dequeues the first element, enqueues all the neighbours
			which were not already explored and updates the cost.
	*Example Call: int *cost = BFS(source);
*/
signed int* BFS (signed int source, signed int destination, signed int *pSize, int callUnsuccessful) {
	struct Queue *Q = NewQueue();	//Initializing the queue required to 
									//maintain nodes to be visited
	signed int *bfs, current = source, *parent;
	parent = (signed int *) calloc (size,sizeof(signed int));
	bfs = (signed int *) calloc (size,sizeof (signed int));
	// signed int visited[size];				//Maintains if the node is visited
	signed int *visited = (signed int *) calloc (size,sizeof(signed int));
	for (signed int i = 1; i < size; i++) {
		bfs[i] = 0;
		parent[i] = -1;
		visited[i] = 0;
	}
	if (!callUnsuccessful)
		markVisited(visited);
	bfs[current] = 1;
	visited[current] = 1;
	parent[source] = -1;
	EnQueue (Q, current);
	signed int flag = 1;	
	while (!IsEmpty (Q) && flag == 1) {
		//Accessing the first node in the queue and marking it's neighbours to
		//be searched 
		current = DeQueue (Q);
		for (signed int i = 0, j = map[current][0]; map[current][i] != -1; ++i, j = map[current][i]) {
			// I think i should be replaced by j in the following lines
			if (visited[j] == 0) {
				//Adding weight to bfs if the node is connected
				bfs[j] = 1 + bfs[current];
				//In that case, neighbours of this node needs to be scanned
				//too
				parent[j] = current;			
				EnQueue (Q, j);
				visited [j] = 1;				
				if (j == destination) {			
					flag = 0;	//Found a path to destination
					break;
				}
			}
		}
	}
	free (bfs);
	EmptyQueue(Q);
	if (parent[destination] == -1){
		signed int *path = (signed int*) malloc (sizeof(signed int));
		path[0] = -2;
		return path;
	}
	signed int *path = pathFind(parent, destination, pSize);
	free(parent);
	free(visited);
	return path; 
}

signed int* BFSPathFind (signed int source, signed int destination, signed int prefix, int callUnsuccessful = 1) {		//prefix will be the additional node which has to be added
	signed int *ret = (signed int *) malloc (2*sizeof(signed int));						//in front of the path to calculate correct angles
	while (1) {
		signed int pSize;	
		signed int *path = BFS (source, destination, &pSize, callUnsuccessful);
		//In case no path is possible, return 1 for failure and the node the bot is standing on.	
		if (path[0] == -2){
			ret[0] = source;			// If failed it will return current node at 0th index
			ret[1] = prefix;			// and previous node at 1st index
			free(path);
			break;
		}
		pSize++;										//adding prefix into the path
		for (signed int i = pSize-1; i >= 0; --i) {
			path[i+1] = path[i];
		}

		path[0] = prefix;
		
		signed int *res = move (path, pSize);
		// free (pSize);		//We need pSize and path when res[0] == 0
		// free (path);			//So copying this statement to if-else condition seperately
		//If movement is successful, the function will return 0, and the destination
		//node that the bot has reached.
		if (res[0] == 0) {
			ret[0] = 0;
			// ret[1] = destination;
			ret[1] = path[(pSize)-2];		//We need a last node robot reached before reaching destination
			free (res);
			// free (pSize);
			free (path);
			break;
		} else { //Otherwise try to run it again.
			for (signed int i = 0, cur = res[1]; map[cur][i+1] != -1; i++){
				if (map[cur][i] == path[res[2]]) {
					while (map[cur][i] != -1) {
						map[cur][i] = map[cur][i+1];
						map_angle[cur][i] = map_angle[cur][i+1];		//Along with map we need to change the angles
						++i;
					}
					break;
				}
			}
			for (signed int i = 0, cur = res[2]; map[cur][i+1] != -1; i++){
				if (map[cur][i] == path[res[1]]) {
					while (map[cur][i] != -1) {
						map[cur][i] = map[cur][i+1];
						map_angle[cur][i] = map_angle[cur][i+1];		//Along with map we need to change the angles
						++i;
					}
					break; 
				}
			}
		}
		source = path[res[1]];
		prefix = path[res[2]];
		// free (pSize);
		free (path);
		free (res);
		free (ret);
	}
	return ret;
}

#endif		//__BFS_PATH_FIND__
