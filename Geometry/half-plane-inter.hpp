#pragma once 

#include "./geometry-template.hpp"
#include "./line.hpp"

vector<Line> half_plane_inter(vector<Line> &L){
    sort(L.begin(), L.end()); 
    deque<Line> q;
    vector<Line> res;
    for (int i = 0; i < L.size(); ++i){
        if (i && same_dir(L[i], L[i - 1])) continue;
        while (q.size() > 1 && (!check_pos(q[q.size() - 2], q[q.size() - 1], L[i]))) q.pop_back();
        while (q.size() > 1 && (!check_pos(q[1], q[0], L[i]))) q.pop_front();
        q.push_back(L[i]);
    }
    while (q.size() > 2 && (!check_pos(q[q.size() - 2], q[q.size() - 1], q[0]))) q.pop_back();
    while (q.size() > 2 && (!check_pos(q[1], q[0], q[q.size() - 1]))) q.pop_front();
    for (int i = 0; i < q.size(); ++i) res.push_back(q[i]);
    return res;
}