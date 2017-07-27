#pragma once
#include <vector>
#include <algorithm>

#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/multi_array.hpp>
#include "./RNDF_LIB/rndf_mdf_reader.h"
#include <Eigen/Core>

#define MAXSEG 50
#define MAXLANE 8
#define MAXWAYPT 300

using namespace Eigen;

namespace
{	
typedef int		Weight;

typedef boost::adjacency_list <
boost::vecS,
boost::vecS,
boost::bidirectionalS,
boost::property< boost::vertex_name_t, std::string,						// Vertex Property 설정
boost::property< boost::vertex_index_t, size_t,
boost::property< boost::vertex_distance_t, size_t,
boost::property< boost::vertex_predecessor_t, size_t
> > > >,
boost::property< boost::edge_name_t, std::string,						// Edge Property 설정
boost::property< boost::edge_weight_t, Weight > >
>	Graph;

typedef boost::graph_traits< Graph >::vertex_descriptor		VertexDescriptor;
typedef boost::graph_traits< Graph >::edge_descriptor		EdgeDescriptor;

typedef boost::multi_array<VertexDescriptor, 3> array_type;
typedef boost::multi_array<waypoint*, 3> array_waypoint;
typedef std::map<int, int> ZoneMap;
typedef std::pair<int, int> ZonePair;


// vertex & Edge Writer
struct vertexWriter
{
    vertexWriter( const Graph& graph )
        : _Graph( graph ) {};

    template <typename Vertex>
    void operator()(std::ostream& outStream, Vertex v)
    {
        std::string vertexName( boost::get( boost::vertex_name, _Graph, v ) );
        outStream << "[label=\"" << vertexName.c_str() << "\"]";
    };

private:
    const Graph& _Graph;
};

struct edgeWriter
{
    edgeWriter( const Graph& graph )
        : _Graph( graph ) {};

    template <typename Edge>
    void operator()(std::ostream& outStream, Edge e)
    {
        std::string edgeName( boost::get( boost::edge_name, _Graph, e ) );
        Weight EdgeWeight = boost::get( boost::edge_weight, _Graph, e );
        outStream << "[label=\"" << edgeName.c_str() << " weight = " << EdgeWeight << "\"]";
    }

private:
    const Graph& _Graph;
};

struct graphWriter
{
    void operator()(std::ostream& outStream) const
    {
        outStream << "graph [bgcolor=white]" << std::endl;
        outStream << "node [shape=record color=blue]" << std::endl;
        // just an example, showing that local options override global
        outStream << "edge [color=red]" << std::endl;
        outStream << "rankdir=LR" << std::endl;
    }
};

struct vertexInfo
{
    int segmentIndex;
    int laneIndex;
    int waypointIndex;
};
};

class CShortestPath
{
public:
    CShortestPath(struct RNDF *pRNDF, struct MDF* pMDF);
    ~CShortestPath();

public:
    void BuildGraph();
    void ResolvePath( const VertexDescriptor& vStart, const VertexDescriptor& vEnd );
    std::size_t ResolvePath( const VertexDescriptor& vStart, const VertexDescriptor& vEnd, std::vector< VertexDescriptor >& vecResolvePath);

    bool GetIndexPosition(id* pId, float& lat, float& lon);
    void PrintShortestPath( const VertexDescriptor& vStartVertex );
    void PrintShortestPath_( const VertexDescriptor& vStartVertex, const VertexDescriptor& vEndVertex );
    void WriteGraphviz();
    void GetPathCurrentPosToCheckPoint(id* startId);
    void GetPathCurrentPosToCheckPoint2(id* startId, id* targetId);
    bool ValidVertexId(id* pId);
    bool ValidCheckPointId(int index, id* pId);
    void GetAllMissionPath(); // it will be deprecated !!
    void SetTargetCheckIndex(int index);
    std::vector<Vector2d> GetResolvedPath(){ return m_vResolvedPath; }
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
        Graph m_Graph;
    struct RNDF *m_pRNDF;
    struct MDF *m_pMDF;
    int m_TargetCheckPointIndex;

    std::vector<Vector2d> m_vResolvedPath;
    array_type vertex_array;
    array_waypoint vertex_array_waypoint;

    ZoneMap zoneEntryIndexMap;
    ZoneMap zoneExitIndexMap;
};

