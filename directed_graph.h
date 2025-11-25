#ifndef OOP_DERECTED_GRAPH
#define OOP_DERECTED_GRAPH
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
namespace oop
{
    class DirectedGraph
    {
    private:
        std::map<int, std::vector<int>> adjList;

    public:
        // เพิ่ม vertex
        void addVertex(int v)
        {
            if (adjList.find(v) == adjList.end())
            {
                adjList[v] = std::vector<int>();
            }
        }

        // เพิ่ม edge
        void addEdge(int from, int to)
        {
            addVertex(from);
            addVertex(to);
            adjList[from].push_back(to);
        }

        // ลบ edge
        void removeEdge(int from, int to)
        {
            if (adjList.find(from) != adjList.end())
            {
                auto &neighbors = adjList[from];
                neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), to), neighbors.end());
            }
        }

        // ลบ vertex
        void removeVertex(int v)
        {
            adjList.erase(v);
            for (auto &[key, neighbors] : adjList)
            {
                neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), v), neighbors.end());
            }
        }

        // ตรวจสอบว่ามี edge ไหม
        bool hasEdge(int from, int to)
        {
            if (adjList.find(from) != adjList.end())
            {
                auto &neighbors = adjList[from];
                return std::find(neighbors.begin(), neighbors.end(), to) != neighbors.end();
            }
            return false;
        }

        // คืน neighbors ของ vertex
        std::vector<int> getNeighbors(int v)
        {
            if (adjList.find(v) != adjList.end())
            {
                return adjList[v];
            }
            return std::vector<int>();
        }

        // BFS
        void BFS(int start)
        {
            if (adjList.find(start) == adjList.end())
                return;

            std::set<int> visited;
            std::queue<int> q;
            visited.insert(start);
            q.push(start);

            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                std::cout << v << " ";

                for (int neighbor : adjList[v])
                {
                    if (visited.find(neighbor) == visited.end())
                    {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
            std::cout << "\n";
        }

        // DFS
        void DFS(int start)
        {
            if (adjList.find(start) == adjList.end())
                return;

            std::set<int> visited;
            std::stack<int> s;
            s.push(start);

            while (!s.empty())
            {
                int v = s.top();
                s.pop();

                if (visited.find(v) == visited.end())
                {
                    std::cout << v << " ";
                    visited.insert(v);
                }

                for (auto it = adjList[v].rbegin(); it != adjList[v].rend(); ++it)
                {
                    if (visited.find(*it) == visited.end())
                    {
                        s.push(*it);
                    }
                }
            }
            std::cout << "\n";
        }

        // พิมพ์กราฟ
        void printGraph()
        {
            for (auto &[v, neighbors] : adjList)
            {
                std::cout << v << " -> ";
                for (int n : neighbors)
                {
                    std::cout << n << " ";
                }
                std::cout << "\n";
            }
        }
    };
}

#endif