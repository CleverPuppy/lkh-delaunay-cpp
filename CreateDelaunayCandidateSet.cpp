#include "ctsp.h"
#include "Delaunay.h"
#include <cstdio>

/*
 * The CreateDelaunayCandidateSet function determines for each node its set 
 * of incident candidate edges. The edges are found by Delaunay triangulation. 
 *
 * The function is called from CreateCandidateSet.
 */

void CreateDelaunayCandidateSet(CTSP& ctsp)
{
    Node *From, *To;
    point *u, *v;
    edge *e_start, *e;
    int d, i, Count;
    int TraceLevel = 3;
    
    /* 分不同的颜色 */
    for(int color = 1; color <= ctsp.salesman_num; ++color)
    {
        std::vector<Node*> allNodesCanVisitCurColor;
        for(int nodeid = 1; nodeid < ctsp.vNode.size(); ++nodeid)
        {
            if(ctsp.vNode[nodeid].visibility[color])
            {
                allNodesCanVisitCurColor.emplace_back(&ctsp.vNode[nodeid]);
            }
        }
        /* Find the Delaunay edges */
        delaunay(allNodesCanVisitCurColor);
        /* Add the Delaunay edges to the candidate set */
        for(int i = 0; i < allNodesCanVisitCurColor.size(); ++i)
        {
            u = &p_array[i];
            From = &ctsp.vNode[u->id];
            e_start = e = u->entry_pt;
            Count = 0;
            do {
                v = Other_point(e, u);
                if (u < v) {
                    To = &ctsp.vNode[v->id];
                    // d = From->vWeight[To->id];
                    // AddCandidate(From, To, d, 1);
                    // AddCandidate(To, From, d, 1);
                    From->candidates.emplace_back(To);
                    To->candidates.emplace_back(From);
                }
            } while ((e = Next(e, u)) != e_start && ++Count < allNodesCanVisitCurColor.size());
        }
        free_memory();
    }
}