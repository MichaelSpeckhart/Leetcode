#include "../graph.hpp"

#include <iostream>
#include <queue>

/// @brief course schedule leetcode problem: https://leetcode.com/problems/course-schedule-ii/description/?envType=problem-list-v2&envId=graph
/// Medium Difficulty
class course_schedule {

    public:

    bool find_order(int num_courses, vector<vector<int>>& prerequisites) {
        // check that prerequisites is not empty
        if (prerequisites.size() == 0) return false;

        // Because we only get the edges as input (i.e. [1,0], [1, 2], ... ) we need to create
        // a mapping of nodes to their neighbors (i.e. [0] -> <1, 2, 3, ..., n> )
        vector<vector<int>> adjList(num_courses);

        // Also need to keep track of in degrees of each node
        // meaning how many nodes connect to that node
        vector<int> in_degrees(num_courses);

        // Now we need to add the edges to the adjacency list 
        // and count the in degrees

        // Simply, each entry in prerequisite represents [course, dependency] meaning we need
        // to take dependency before we take course
        // In a graph representation, this would mean dependency -> course
        // so course has at least one in degree
        for (const auto& prereq : prerequisites) {
            int course = prereq[0];
            int dependency = prereq[1];
            adjList[dependency].push_back(course);
            in_degrees[course]++;
        }

        // Create a queue for BFS search (could also use dfs but bfs works better here and is more intuitive :) )
        queue<int> q;

        // Iterate through the in degrees and add those in degrees that are zero
        // nodes with in degree zero are courses that have no prerequisites
        // which make great starting points
        for (int i = 0; i < in_degrees.size(); ++i) {
            if (in_degrees[i] == 0) {
                q.push(i);
            }
        }

        // Keep tracker of how many courses were able to process
        // if at the end the number of courses we processed does not equal the totla number of courses
        // we know we have a cycle :)
        int num_processed = 0;

        while (q.empty() != true) {
            int curr_course = q.front();
            q.pop();

            num_processed += 1;

            for (const auto& neighbor : adjList[curr_course]) {
                // For each neighbor, decrement the in degree from the prereq
                in_degrees[neighbor] -= 1;
                // If the neighbor now has an in degree of zero, push into queue due
                // to previous reason
                if (in_degrees[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // This return value will check if we processed all the courses
        return num_courses == num_processed;
    }

};

int main(void) {

    vector<vector<int>> edges = {
        {1,0},
        {2,0},
        {3,1},
        {3,2}
    };

    int courses = 4;

    course_schedule solution;

    bool isTop = solution.find_order(courses, edges);

    std::cout << boolalpha;
    std::cout << "No Cycle Detected: " << isTop << "\n";

    edges.clear();
    edges = {
        {1, 0},
        {0, 1}
    };

    courses = 2;

    isTop = solution.find_order(courses, edges);

    
    std::cout << "No Cycle Detected: " << isTop << "\n";

    return 0;


}