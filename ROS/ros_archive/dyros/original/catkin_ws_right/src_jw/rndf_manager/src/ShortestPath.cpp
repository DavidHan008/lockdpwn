#include "../inc/ShortestPath.h"
#include <string>     // std::string, std::to_string
#include <sstream>
#include <boost/format.hpp>
#include <map>


CShortestPath::CShortestPath(struct RNDF *pRNDF, struct MDF* pMDF)
    :m_pRNDF(pRNDF), m_pMDF(pMDF)
{
    m_TargetCheckPointIndex = 0;

    array_type::extent_gen extents;
    vertex_array.resize(extents[MAXSEG][MAXLANE][MAXWAYPT]);


    array_waypoint::extent_gen extents_waypoint;
    vertex_array_waypoint.resize(extents_waypoint[MAXSEG][MAXLANE][MAXWAYPT]);

}


CShortestPath::~CShortestPath()
{
}

bool CShortestPath::GetIndexPosition(id* pId, float& lat, float& lon)
{
    if( vertex_array_waypoint[pId->x][pId->y][pId->z] != NULL )
    {
        lat = vertex_array_waypoint[pId->x][pId->y][pId->z]->latitude;
        lon = vertex_array_waypoint[pId->x][pId->y][pId->z]->longitude;
        return true;
    }
    else
    {
        return false;
    }
}

bool CShortestPath::ValidVertexId(id* pId)
{
	if( vertex_array_waypoint[pId->x][pId->y][pId->z] != NULL )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CShortestPath::ValidCheckPointId(int index, id* pId)
{
    for(int i=0; i<m_pRNDF->number_of_segments; i++)
    {
        for( int j=0; j<m_pRNDF->segments_list[i]->number_of_lanes; j++)
        {
            for( int k=0; k<m_pRNDF->segments_list[i]->lanes_list[j]->number_of_checkpoints; k++)
            {
                if( m_pRNDF->segments_list[i]->lanes_list[j]->checkpoints_list[k]->checkpoint_id == index )
                {
                    pId->x = m_pRNDF->segments_list[i]->lanes_list[j]->checkpoints_list[k]->waypoint_id->x;
                    pId->y = m_pRNDF->segments_list[i]->lanes_list[j]->checkpoints_list[k]->waypoint_id->y;
                    pId->z = m_pRNDF->segments_list[i]->lanes_list[j]->checkpoints_list[k]->waypoint_id->z;
                    //std::cout<< pId->x << "." << pId->y <<"." << pId->z <<std::endl;
                    return true;
                }
            }
        }
    }
    //////////////////////////////////
    // ZONE TARGET
    for( int j=0; j<m_pRNDF->number_of_zones; j++)
    {
        for( int k=0; k<m_pRNDF->zones_list[j]->number_of_parking_spots; k++)
        {
            if( m_pRNDF->zones_list[j]->parking_spots_list[k]->check_waypoint->checkpoint_id == index )
            {
               pId->x = m_pRNDF->zones_list[j]->parking_spots_list[k]->check_waypoint->waypoint_id->x;
               pId->y = m_pRNDF->zones_list[j]->parking_spots_list[k]->check_waypoint->waypoint_id->y;
               pId->z = m_pRNDF->zones_list[j]->parking_spots_list[k]->check_waypoint->waypoint_id->z;
               return true;
            }
        }
    }
    return false;
}
void CShortestPath::SetTargetCheckIndex(int index)
{
    m_TargetCheckPointIndex=index;
}
void CShortestPath::GetPathCurrentPosToCheckPoint2(id* startId, id* targetId)
{
    // Property Map 가져오기

    boost::property_map< Graph, boost::edge_weight_t >::type		mapEdgeWeight			= boost::get( boost::edge_weight, m_Graph );
    boost::property_map< Graph, boost::vertex_index_t >::type		mapVertexIndex			= boost::get( boost::vertex_index, m_Graph );
    boost::property_map< Graph, boost::vertex_distance_t >::type	mapVertexDistance		= boost::get( boost::vertex_distance, m_Graph );
    boost::property_map< Graph, boost::vertex_predecessor_t >::type	mapVertexPredecessor	= boost::get( boost::vertex_predecessor, m_Graph );


    std::vector< VertexDescriptor > vecResolvePath;

    const VertexDescriptor vStartVertex =vertex_array[startId->x][startId->y][startId->z];

    boost::dijkstra_shortest_paths(

                m_Graph,

                vStartVertex,

                boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

                );
    const VertexDescriptor vEndVertex = vertex_array[targetId->x][targetId->y][targetId->z];
    ResolvePath(vStartVertex, vEndVertex,vecResolvePath);


}
//void CShortestPath::GetPathCurrentPosToCheckPoint2(id* startId, id* targetId)
//{
//    // Property Map 가져오기

//    boost::property_map< Graph, boost::edge_weight_t >::type		mapEdgeWeight			= boost::get( boost::edge_weight, m_Graph );
//    boost::property_map< Graph, boost::vertex_index_t >::type		mapVertexIndex			= boost::get( boost::vertex_index, m_Graph );
//    boost::property_map< Graph, boost::vertex_distance_t >::type	mapVertexDistance		= boost::get( boost::vertex_distance, m_Graph );
//    boost::property_map< Graph, boost::vertex_predecessor_t >::type	mapVertexPredecessor	= boost::get( boost::vertex_predecessor, m_Graph );

//    int nType = 0; // 0: NULL, 1: LANE CHECKPOINT, 2: SPOT CHECKPOINT
//    int nStartType = 1; // 1: LANE CHECKPOINT, 2: SPOT CHECKPOINT
//    //////////////////////////////////////////////////////////////////////////////////////////////////
//    // Find Current Checkpoint Type and Id
//    //( if Type is 2(spot checkpoint) then path will be generated to zone entry point --> local path will generate path between entry and spot)
//    /////////////////////////////////
//    // LANE TARGET
//    for(int i=0; i<m_pRNDF->number_of_segments; i++)
//    {
//        for( int j=0; j<m_pRNDF->segments_list[i]->number_of_lanes; j++)
//        {
//            for( int k=0; k<m_pRNDF->segments_list[i]->lanes_list[j]->number_of_waypoints; k++)
//            {
//                if( m_pRNDF->segments_list[i]->lanes_list[j]->waypoints_list[k]->waypoint_id->x == targetId->x &&
//                    m_pRNDF->segments_list[i]->lanes_list[j]->waypoints_list[k]->waypoint_id->y == targetId->y &&
//                    m_pRNDF->segments_list[i]->lanes_list[j]->waypoints_list[k]->waypoint_id->z == targetId->z )
//                {
//                    nType = 1;
//                }
//            }
//        }
//    }
//    //////////////////////////////////
//    // ZONE TARGET
//    for( int j=0; j<m_pRNDF->number_of_zones; j++)
//    {
//        if( m_pRNDF->zones_list[j]->zone_id == startId->x)
//        {
//            nStartType = 2;
//        }

//        if( m_pRNDF->zones_list[j]->zone_id == targetId->x )
//        {
//            nType = 2;
//        }
//    }
//    ///////////////////////////////////
//    std::vector< VertexDescriptor > vecResolvePath;

//    if( startId->x != -1 && startId->y != -1 && startId->z != -1 )
//    {
//        if( nType == 1) // LANE CHECKPT
//        {
//            if( nStartType == 2 )
//            {
//               // std::cout<<" s3 "<<std::endl;
//                std::map<int,int>::iterator finder = zoneExitIndexMap.find(startId->x);
//                if(finder != zoneExitIndexMap.end())
//                {
//                    const VertexDescriptor vStartVertex =vertex_array[startId->x][0][(*finder).second];

//                    boost::dijkstra_shortest_paths(

//                                m_Graph,

//                                vStartVertex,

//                                boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

//                                );
//                    const VertexDescriptor vEndVertex = vertex_array[targetId->x][targetId->y][targetId->z];
//                    ResolvePath(vStartVertex, vEndVertex,vecResolvePath);
//                }
//                else
//                {
//                    std::cout << "no zone exit id"<< std::endl;
//                }
//            }
//            else
//            {
//               const VertexDescriptor vStartVertex = vertex_array[startId->x][startId->y][startId->z];

//                boost::dijkstra_shortest_paths(

//                            m_Graph,

//                            vStartVertex,

//                            boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

//                            );
//                const VertexDescriptor vEndVertex = vertex_array[targetId->x][targetId->y][targetId->z];


//                ResolvePath(vStartVertex, vEndVertex,vecResolvePath);

//            }
//        }
//        else if( nType == 2 ) // SPOT CHECKPT
//        {
//            std::map<int,int>::iterator finder = zoneEntryIndexMap.find(targetId->x);
//            if(finder != zoneEntryIndexMap.end())
//            {
//                const VertexDescriptor vStartVertex = vertex_array[startId->x][startId->y][startId->z];

//                boost::dijkstra_shortest_paths(

//                            m_Graph,

//                            vStartVertex,

//                            boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

//                            );
//                const VertexDescriptor vEndVertex =vertex_array[targetId->x][0][(*finder).second];
//                ResolvePath(vStartVertex, vEndVertex,vecResolvePath);
//            }
//            else
//            {
//                std::cout << "no zone entry id"<< std::endl;
//            }
//        }
//    }

//}

void CShortestPath::GetPathCurrentPosToCheckPoint(id* startId)
{
    // Property Map 가져오기

    boost::property_map< Graph, boost::edge_weight_t >::type		mapEdgeWeight			= boost::get( boost::edge_weight, m_Graph );
    boost::property_map< Graph, boost::vertex_index_t >::type		mapVertexIndex			= boost::get( boost::vertex_index, m_Graph );
    boost::property_map< Graph, boost::vertex_distance_t >::type	mapVertexDistance		= boost::get( boost::vertex_distance, m_Graph );
    boost::property_map< Graph, boost::vertex_predecessor_t >::type	mapVertexPredecessor	= boost::get( boost::vertex_predecessor, m_Graph );


    int t = m_TargetCheckPointIndex;

    int checkPointId = m_pMDF->checkpoints_list[t];
    int nType = 0; // 0: NULL, 1: LANE CHECKPOINT, 2: SPOT CHECKPOINT
    int nStartType = 1; // 1: LANE CHECKPOINT, 2: SPOT CHECKPOINT
    id* targetId = NULL;

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Find Current Checkpoint Type and Id
    //( if Type is 2(spot checkpoint) then path will be generated to zone entry point --> local path will generate path between entry and spot)
    /////////////////////////////////
    // LANE TARGET
    for(int i=0; i<m_pRNDF->number_of_segments; i++)
    {
        for( int j=0; j<m_pRNDF->segments_list[i]->number_of_lanes; j++)
        {
            for( int k=0; k<m_pRNDF->segments_list[i]->lanes_list[j]->number_of_checkpoints; k++)
            {
                if( m_pRNDF->segments_list[i]->lanes_list[j]->checkpoints_list[k]->checkpoint_id == checkPointId )
                {
                    nType = 1;
                    targetId = m_pRNDF->segments_list[i]->lanes_list[j]->checkpoints_list[k]->waypoint_id;
                }
            }
        }
    }
    //////////////////////////////////
    // ZONE TARGET
    for( int j=0; j<m_pRNDF->number_of_zones; j++)
    {
        if( m_pRNDF->zones_list[j]->zone_id == startId->x)
        {
            nStartType = 2;
        }
        for( int k=0; k<m_pRNDF->zones_list[j]->number_of_parking_spots; k++)
        {
            if( m_pRNDF->zones_list[j]->parking_spots_list[k]->check_waypoint->checkpoint_id == checkPointId )
            {
                nType = 2;
                targetId = m_pRNDF->zones_list[j]->parking_spots_list[k]->check_waypoint->waypoint_id;
            }
        }
    }
    ///////////////////////////////////
    std::vector< VertexDescriptor > vecResolvePath;


    if( startId->x != -1 && startId->y != -1 && startId->z != -1 )
    {
        if( nType == 1) // LANE CHECKPT
        {
            if( nStartType == 2 )
            {
                std::map<int,int>::iterator finder = zoneExitIndexMap.find(startId->x);
                if(finder != zoneExitIndexMap.end())
                {
                    const VertexDescriptor vStartVertex =vertex_array[startId->x][0][(*finder).second];

                    boost::dijkstra_shortest_paths(

                                m_Graph,

                                vStartVertex,

                                boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

                                );
                    const VertexDescriptor vEndVertex = vertex_array[targetId->x][targetId->y][targetId->z];
                    ResolvePath(vStartVertex, vEndVertex,vecResolvePath);
                }
                else
                {
                    std::cout << "no zone exit id"<< std::endl;
                }
            }
            else
            {

                const VertexDescriptor vStartVertex = vertex_array[startId->x][startId->y][startId->z];

                boost::dijkstra_shortest_paths(

                            m_Graph,

                            vStartVertex,

                            boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

                            );
                const VertexDescriptor vEndVertex = vertex_array[targetId->x][targetId->y][targetId->z];


                ResolvePath(vStartVertex, vEndVertex,vecResolvePath);

            }
        }
        else if( nType == 2 ) // SPOT CHECKPT
        {
            std::map<int,int>::iterator finder = zoneEntryIndexMap.find(targetId->x);
            if(finder != zoneEntryIndexMap.end())
            {
                const VertexDescriptor vStartVertex = vertex_array[startId->x][startId->y][startId->z];

                boost::dijkstra_shortest_paths(

                            m_Graph,

                            vStartVertex,

                            boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

                            );
                const VertexDescriptor vEndVertex =vertex_array[targetId->x][0][(*finder).second];
                ResolvePath(vStartVertex, vEndVertex,vecResolvePath);
            }
            else
            {
                std::cout << "no zone entry id"<< std::endl;
            }
        }
    }

}

void CShortestPath::BuildGraph()
{
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Read All Waypoint Info and Convert to Vertex Info
    for(int i=0; i<m_pRNDF->number_of_segments; i++)
    {
        for( int j=0; j<m_pRNDF->segments_list[i]->number_of_lanes; j++)
        {
            for( int k=0; k<m_pRNDF->segments_list[i]->lanes_list[j]->number_of_waypoints; k++)
            {
                id* pId = m_pRNDF->segments_list[i]->lanes_list[j]->waypoints_list[k]->waypoint_id;
                boost::format fmt = boost::format("%d.%d.%d") % pId->x % pId->y % pId->z;
                std::string str = fmt.str();
                int x = pId->x;
                int y = pId->y;
                int z = pId->z;
std::cout << pId->x <<"."<< pId->y <<"."<<  pId->z <<" dist: "<<std::endl;
		std::cout <<x<<" "<<y<<" "<<z<<"|"<<str<<std::endl;
                vertex_array[x][y][z] = boost::add_vertex( str, m_Graph );
		printf("111\n");
                vertex_array_waypoint[x][y][z] = m_pRNDF->segments_list[i]->lanes_list[j]->waypoints_list[k];
		printf("222\n");
                if( k > 0 ) // edge generation between lane waypoint z-1 and z
                {
		printf("333\n");
                    const EdgeDescriptor edgeDes = boost::add_edge( vertex_array[x][y][z-1], vertex_array[x][y][z], m_Graph ).first;
		printf("444\n");
                    float _lat = vertex_array_waypoint[x][y][z-1]->latitude;
                    float _lon = vertex_array_waypoint[x][y][z-1]->longitude;

                    float lat = vertex_array_waypoint[x][y][z]->latitude;
                    float lon = vertex_array_waypoint[x][y][z]->longitude;
                    float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

                    std::cout << pId->x <<"."<< pId->y <<"."<<  pId->z <<" dist: "<<dist<<std::endl;
                    boost::put( boost::edge_weight, m_Graph, edgeDes, dist );
                }

            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Convert Zone periment to Node ( if a periment point is not a exit or a entry point then node will not be used )
    // and Convert Parking Spot to Node
    for(int i=0; i<m_pRNDF->number_of_zones; i++)
    {
        for( int j=0; j<m_pRNDF->zones_list[i]->zone_perimeter->number_of_perimeterpoints; j++)
        {
            id* pId = m_pRNDF->zones_list[i]->zone_perimeter->perimeterpoints_list[j]->perimeterpoint_id;
            boost::format fmt = boost::format("%d.%d.%d") % pId->x % pId->y % pId->z;
            std::string str = fmt.str();
            int x = pId->x;
            int y = pId->y;
            int z = pId->z;

            vertex_array[x][y][z] = boost::add_vertex( str, m_Graph );
            vertex_array_waypoint[x][y][z] = (waypoint*)m_pRNDF->zones_list[i]->zone_perimeter->perimeterpoints_list[j];
        }

        for( int j=0; j<m_pRNDF->zones_list[i]->number_of_parking_spots; j++)
        {
            id* pId = m_pRNDF->zones_list[i]->parking_spots_list[j]->waypoint1->waypoint_id;
            boost::format fmt = boost::format("%d.%d.%d") % pId->x % pId->y % pId->z;
            std::string str = fmt.str();
            int x = pId->x;
            int y = pId->y;
            int z = pId->z;

            vertex_array[x][y][z] = boost::add_vertex( str, m_Graph );
            vertex_array_waypoint[x][y][z] = (waypoint*)m_pRNDF->zones_list[i]->parking_spots_list[j]->waypoint1;

            pId = m_pRNDF->zones_list[i]->parking_spots_list[j]->waypoint2->waypoint_id;
            fmt = boost::format("%d.%d.%d") % pId->x % pId->y % pId->z;
            str = fmt.str();
            x = pId->x;
            y = pId->y;
            z = pId->z;

            vertex_array[x][y][z] = boost::add_vertex( str, m_Graph );
            vertex_array_waypoint[x][y][z] = (waypoint*)m_pRNDF->zones_list[i]->parking_spots_list[j]->waypoint2;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Read All Lane Entry Info and Convert to Edge Info. ( if id->y is zero then id means a zone entry )
    for(int i=0; i<m_pRNDF->number_of_segments; i++)
    {
        for( int j=0; j<m_pRNDF->segments_list[i]->number_of_lanes; j++)
        {
            for( int k=0; k<m_pRNDF->segments_list[i]->lanes_list[j]->number_of_exits; k++)
            {
                id * pEntry_id= m_pRNDF->segments_list[i]->lanes_list[j]->exits_list[k]->entry_point_id;
                id * pExit_id= m_pRNDF->segments_list[i]->lanes_list[j]->exits_list[k]->exit_waypoint_id;

               // std::cout << "Edge :"<<pEntry_id->x <<"."<< pEntry_id->y <<"."<< pEntry_id->z<<" "
               //           <<pExit_id->x <<"."<< pExit_id->y <<"."<< pExit_id->z <<std::endl;

                float _lat = vertex_array_waypoint[pExit_id->x][pExit_id->y][pExit_id->z]->latitude;
                float _lon = vertex_array_waypoint[pExit_id->x][pExit_id->y][pExit_id->z]->longitude;

                float lat = vertex_array_waypoint[pEntry_id->x][pEntry_id->y][pEntry_id->z]->latitude;
                float lon = vertex_array_waypoint[pEntry_id->x][pEntry_id->y][pEntry_id->z]->longitude;


                float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

                //std::cout << "Edge :"<<pEntry_id->x <<"."<< pEntry_id->y <<"."<< pEntry_id->z<<" "
                //<<pExit_id->x <<"."<< pExit_id->y <<"."<< pExit_id->z <<" dist: "<< dist<<std::endl;

                const EdgeDescriptor edgeDes = boost::add_edge(
                            vertex_array[pExit_id->x][pExit_id->y][pExit_id->z],
                        vertex_array[pEntry_id->x][pEntry_id->y][pEntry_id->z],
                        m_Graph ).first;

                boost::put( boost::edge_weight, m_Graph, edgeDes, dist );

                ///////////////////////////////////////////
                // Zone Entry Index Mapping
                if( pEntry_id->y == 0 )
                {
                 //   std::cout << "zone entry id mapping" << pEntry_id->x << pEntry_id->z << std::endl;
                    zoneEntryIndexMap.insert(ZonePair(pEntry_id->x, pEntry_id->z));
                }

            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Generate Zone entry/exit edge
    for(int i=0; i<m_pRNDF->number_of_zones; i++)
    {
        for( int j=0; j<m_pRNDF->zones_list[i]->zone_perimeter->number_of_exits; j++)
        {
            id * pEntry_id= m_pRNDF->zones_list[i]->zone_perimeter->exits_list[j]->entry_point_id;
            id * pExit_id= m_pRNDF->zones_list[i]->zone_perimeter->exits_list[j]->exit_waypoint_id;

            float _lat = vertex_array_waypoint[pExit_id->x][pExit_id->y][pExit_id->z]->latitude;
            float _lon = vertex_array_waypoint[pExit_id->x][pExit_id->y][pExit_id->z]->longitude;

            float lat = vertex_array_waypoint[pEntry_id->x][pEntry_id->y][pEntry_id->z]->latitude;
            float lon = vertex_array_waypoint[pEntry_id->x][pEntry_id->y][pEntry_id->z]->longitude;


            float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

            const EdgeDescriptor edgeDes = boost::add_edge(
                        vertex_array[pExit_id->x][pExit_id->y][pExit_id->z],
                    vertex_array[pEntry_id->x][pEntry_id->y][pEntry_id->z],
                    m_Graph ).first;

            boost::put( boost::edge_weight, m_Graph, edgeDes, dist );

            ///////////////////////////////////////////
            // Zone Exit Index Mapping
            if( pExit_id->y == 0 )
            {
                zoneExitIndexMap.insert(ZonePair(pExit_id->x, pExit_id->z));
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Generation of inner zone edge ( assumption: zone has just only one entry and one exit point )
    std::map< int, int >::iterator Iter_Pos;
    for( Iter_Pos = zoneEntryIndexMap.begin(); Iter_Pos != zoneEntryIndexMap.end(); ++Iter_Pos)
    {
        //std::cout << "zone edge"<< (*Iter_Pos).first <<std::endl;
        std::map<int,int>::iterator finder = zoneExitIndexMap.find((*Iter_Pos).first);
        if(finder != zoneExitIndexMap.end())
        {
           // std::cout << (*Iter_Pos).first << " "<<(*Iter_Pos).second <<" "<< (*finder).second <<" "<< (*finder).first << std::endl;
            float _lat = vertex_array_waypoint[(*Iter_Pos).first][0][(*Iter_Pos).second]->latitude;
            float _lon = vertex_array_waypoint[(*Iter_Pos).first][0][(*Iter_Pos).second]->longitude;

            float lat = vertex_array_waypoint[(*finder).first][0][(*finder).second]->latitude;
            float lon = vertex_array_waypoint[(*finder).first][0][(*finder).second]->longitude;


            float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

            const EdgeDescriptor edgeDes = boost::add_edge(
                        vertex_array[(*Iter_Pos).first][0][(*Iter_Pos).second],
                    vertex_array[(*finder).first][0][(*finder).second],
                    m_Graph ).first;

            boost::put( boost::edge_weight, m_Graph, edgeDes, dist );

        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Generate Parking Spot Edge (waypoint1 & waypoint2)
    // & zone entry - waypoint1
    // & zone exit - waypoint2
    for(int i=0; i<m_pRNDF->number_of_zones; i++)
    {
        for( int j=0; j<m_pRNDF->zones_list[i]->number_of_parking_spots; j++)
        {
            id * pWaypointId1= m_pRNDF->zones_list[i]->parking_spots_list[j]->waypoint1->waypoint_id;
            id * pWaypointId2= m_pRNDF->zones_list[i]->parking_spots_list[j]->waypoint2->waypoint_id;

            float _lat = vertex_array_waypoint[pWaypointId1->x][pWaypointId1->y][pWaypointId1->z]->latitude;
            float _lon = vertex_array_waypoint[pWaypointId1->x][pWaypointId1->y][pWaypointId1->z]->longitude;

            float lat = vertex_array_waypoint[pWaypointId2->x][pWaypointId2->y][pWaypointId2->z]->latitude;
            float lon = vertex_array_waypoint[pWaypointId2->x][pWaypointId2->y][pWaypointId2->z]->longitude;


            float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

            const EdgeDescriptor edgeDes = boost::add_edge(
                    vertex_array[pWaypointId1->x][pWaypointId1->y][pWaypointId1->z],
                    vertex_array[pWaypointId2->x][pWaypointId2->y][pWaypointId2->z],
                    m_Graph ).first;

            boost::put( boost::edge_weight, m_Graph, edgeDes, dist );

            std::map<int,int>::iterator finder = zoneExitIndexMap.find(pWaypointId2->x);
            if(finder != zoneExitIndexMap.end())
            {
                float _lat = vertex_array_waypoint[pWaypointId2->x][pWaypointId2->y][pWaypointId2->z]->latitude;
                float _lon = vertex_array_waypoint[pWaypointId2->x][pWaypointId2->y][pWaypointId2->z]->longitude;

                float lat = vertex_array_waypoint[(*finder).first][0][(*finder).second]->latitude;
                float lon = vertex_array_waypoint[(*finder).first][0][(*finder).second]->longitude;


                float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

                const EdgeDescriptor edgeDes = boost::add_edge(
                            vertex_array[pWaypointId2->x][pWaypointId2->y][pWaypointId2->z],
                        vertex_array[(*finder).first][0][(*finder).second],
                        m_Graph ).first;

                boost::put( boost::edge_weight, m_Graph, edgeDes, dist );
            }

            finder = zoneEntryIndexMap.find(pWaypointId1->x);
            if(finder != zoneEntryIndexMap.end())
            {
                 float _lat = vertex_array_waypoint[(*finder).first][0][(*finder).second]->latitude;
                 float _lon = vertex_array_waypoint[(*finder).first][0][(*finder).second]->longitude;

                 float lat = vertex_array_waypoint[pWaypointId1->x][pWaypointId1->y][pWaypointId1->z]->latitude;
                 float lon = vertex_array_waypoint[pWaypointId1->x][pWaypointId1->y][pWaypointId1->z]->longitude;

                 float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

                 const EdgeDescriptor edgeDes = boost::add_edge(
                             vertex_array[(*finder).first][0][(*finder).second],
                         vertex_array[pWaypointId1->x][pWaypointId1->y][pWaypointId1->z],
                         m_Graph ).first;

                 boost::put( boost::edge_weight, m_Graph, edgeDes, dist );
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    WriteGraphviz();
    std::cout << "Graph Generated !!"<<std::endl;

    //id startId;
    //startId.x = 1;
    //startId.y = 2;
    //startId.z = 4;
    //GetPathCurrentPosToCheckPoint(&startId);
}

std::size_t CShortestPath::ResolvePath( const VertexDescriptor& vStart, const VertexDescriptor& vEnd, std::vector< VertexDescriptor >& vecResolvePath)
{
    std::cout << "ResolvePath : ";
    m_vResolvedPath.clear();
    for( VertexDescriptor v_it = vEnd; v_it != vStart; v_it = boost::get( boost::vertex_predecessor, m_Graph, v_it ) )
    {
        vecResolvePath.push_back( v_it );
    }
    vecResolvePath.push_back( vStart );
    std::size_t sizeDistance = 0;
    for( std::vector< VertexDescriptor >::const_reverse_iterator it = vecResolvePath.rbegin();
         it != vecResolvePath.rend();
         ++it )
    {
        std::string strVertexName( boost::get( boost::vertex_name, m_Graph, (*it) ) );
        std::cout << strVertexName.c_str() << " ";
        sizeDistance += boost::get( boost::vertex_distance, m_Graph, (*it) );

        std::vector<int> vect;
        std::stringstream ss(strVertexName);
        int i;
        while (ss >> i)
        {
            vect.push_back(i);
            if (ss.peek() == '.')
                ss.ignore();
        }

        //std::cout <<vertex_array_waypoint[vect[0]][vect[1]][vect[2]]->latitude<<","<<
        //         vertex_array_waypoint[vect[0]][vect[1]][vect[2]]->longitude<<std::endl;

        m_vResolvedPath.push_back(
                    Vector2d(
                        vertex_array_waypoint[vect[0]][vect[1]][vect[2]]->latitude,
                        vertex_array_waypoint[vect[0]][vect[1]][vect[2]]->longitude));
    }

    std::cout << std::endl;
    return sizeDistance;
}

void CShortestPath::ResolvePath( const VertexDescriptor& vStart, const VertexDescriptor& vEnd )
{
    std::cout << "ResolvePath : ";
    std::vector< VertexDescriptor > vecResolvePath;

    for( VertexDescriptor v_it = vEnd; v_it != vStart; v_it = boost::get( boost::vertex_predecessor, m_Graph, v_it ) )
    {
        vecResolvePath.push_back( v_it );
    }
    vecResolvePath.push_back( vStart );

    for( std::vector< VertexDescriptor >::const_reverse_iterator it = vecResolvePath.rbegin();
         it != vecResolvePath.rend();
         ++it )
    {
        std::string strVertexName( boost::get( boost::vertex_name, m_Graph, (*it) ) );
        std::cout << strVertexName.c_str() << " ";
    }

    std::cout << std::endl;
}

void CShortestPath::PrintShortestPath( const VertexDescriptor& vStartVertex )
{
    Graph::vertex_iterator v_it, v_it_end;
    for( boost::tie( v_it, v_it_end ) = boost::vertices( m_Graph ); v_it != v_it_end; ++v_it )
    {
        std::string strStartVertexName( boost::get( boost::vertex_name, m_Graph, vStartVertex ) );
        std::string strEndVertexName( boost::get( boost::vertex_name, m_Graph, (*v_it) ) );

        std::size_t sizeDistance = boost::get( boost::vertex_distance, m_Graph, (*v_it) );

        if( sizeDistance < 1000 )
        {
            std::cout << "Distance( Start : " << strStartVertexName.c_str() << " End : " << strEndVertexName.c_str() << " ) = " << sizeDistance << std::endl;

            ResolvePath( vStartVertex, (*v_it) );
        }
    }
}

void CShortestPath::PrintShortestPath_( const VertexDescriptor& vStartVertex, const VertexDescriptor& vEndVertex )
{
    ResolvePath( vStartVertex, vEndVertex );
}


void CShortestPath::WriteGraphviz()
{
    std::ofstream ofstream( "Graphviz.dot", std::ios::out | std::ios::trunc );
    if( !ofstream )
    {
        std::cout << "Could not open file." << std::endl;
        assert( 0 );
        return;
    }

    boost::write_graphviz( ofstream, m_Graph, vertexWriter( m_Graph ), edgeWriter( m_Graph ), graphWriter() );

    ofstream.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GetAllMissionPath
void CShortestPath::GetAllMissionPath()
{
    typedef boost::multi_array<VertexDescriptor, 3> array_type;
    array_type::extent_gen extents;
    array_type vertex_array(extents[MAXSEG][MAXLANE][MAXWAYPT]);

    typedef boost::multi_array<waypoint*, 3> array_waypoint;

    array_waypoint::extent_gen extents_waypoint;
    array_waypoint vertex_array_waypoint(extents_waypoint[MAXSEG][MAXLANE][MAXWAYPT]);

    typedef std::map<int, int> ZoneMap;
    typedef std::pair<int, int> ZonePair;
    ZoneMap zoneEntryIndexMap;
    ZoneMap zoneExitIndexMap;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Read All Waypoint Info and Convert to Vertex Info
    for(int i=0; i<m_pRNDF->number_of_segments; i++)
    {
        for( int j=0; j<m_pRNDF->segments_list[i]->number_of_lanes; j++)
        {
            for( int k=0; k<m_pRNDF->segments_list[i]->lanes_list[j]->number_of_waypoints; k++)
            {
                id* pId = m_pRNDF->segments_list[i]->lanes_list[j]->waypoints_list[k]->waypoint_id;
                boost::format fmt = boost::format("%d.%d.%d") % pId->x % pId->y % pId->z;
                std::string str = fmt.str();
                int x = pId->x;
                int y = pId->y;
                int z = pId->z;

                vertex_array[x][y][z] = boost::add_vertex( str, m_Graph );
                vertex_array_waypoint[x][y][z] = m_pRNDF->segments_list[i]->lanes_list[j]->waypoints_list[k];
                if( k > 0 ) // edge generation between lane waypoint z-1 and z
                {
                    const EdgeDescriptor edgeDes = boost::add_edge( vertex_array[x][y][z-1], vertex_array[x][y][z], m_Graph ).first;

                    float _lat = vertex_array_waypoint[x][y][z-1]->latitude;
                    float _lon = vertex_array_waypoint[x][y][z-1]->longitude;

                    float lat = vertex_array_waypoint[x][y][z]->latitude;
                    float lon = vertex_array_waypoint[x][y][z]->longitude;
                    float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

                    //std::cout << pId->x <<"."<< pId->y <<"."<<  pId->z <<"dist: "<<dist<<std::endl;
                    boost::put( boost::edge_weight, m_Graph, edgeDes, dist );
                }

            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Convert Zone periment to Node ( if a periment point is not a exit or a entry point then node will not be used )
    for(int i=0; i<m_pRNDF->number_of_zones; i++)
    {
        for( int j=0; j<m_pRNDF->zones_list[i]->zone_perimeter->number_of_perimeterpoints; j++)
        {
            id* pId = m_pRNDF->zones_list[i]->zone_perimeter->perimeterpoints_list[j]->perimeterpoint_id;
            boost::format fmt = boost::format("%d.%d.%d") % pId->x % pId->y % pId->z;
            std::string str = fmt.str();
            int x = pId->x;
            int y = pId->y;
            int z = pId->z;

            vertex_array[x][y][z] = boost::add_vertex( str, m_Graph );
            vertex_array_waypoint[x][y][z] = (waypoint*)m_pRNDF->zones_list[i]->zone_perimeter->perimeterpoints_list[j];
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Read All Lane Entry Info and Convert to Edge Info. ( if id->y is zero then id means a zone entry )
    for(int i=0; i<m_pRNDF->number_of_segments; i++)
    {
        for( int j=0; j<m_pRNDF->segments_list[i]->number_of_lanes; j++)
        {
            for( int k=0; k<m_pRNDF->segments_list[i]->lanes_list[j]->number_of_exits; k++)
            {
                id * pEntry_id= m_pRNDF->segments_list[i]->lanes_list[j]->exits_list[k]->entry_point_id;
                id * pExit_id= m_pRNDF->segments_list[i]->lanes_list[j]->exits_list[k]->exit_waypoint_id;

                std::cout << "Edge :"<<pEntry_id->x <<"."<< pEntry_id->y <<"."<< pEntry_id->z<<" "
                <<pExit_id->x <<"."<< pExit_id->y <<"."<< pExit_id->z <<std::endl;

                float _lat = vertex_array_waypoint[pExit_id->x][pExit_id->y][pExit_id->z]->latitude;
                float _lon = vertex_array_waypoint[pExit_id->x][pExit_id->y][pExit_id->z]->longitude;

                float lat = vertex_array_waypoint[pEntry_id->x][pEntry_id->y][pEntry_id->z]->latitude;
                float lon = vertex_array_waypoint[pEntry_id->x][pEntry_id->y][pEntry_id->z]->longitude;


                float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

                //std::cout << "Edge :"<<pEntry_id->x <<"."<< pEntry_id->y <<"."<< pEntry_id->z<<" "
                //<<pExit_id->x <<"."<< pExit_id->y <<"."<< pExit_id->z <<" dist: "<< dist<<std::endl;

                const EdgeDescriptor edgeDes = boost::add_edge(
                            vertex_array[pExit_id->x][pExit_id->y][pExit_id->z],
                            vertex_array[pEntry_id->x][pEntry_id->y][pEntry_id->z],
                        m_Graph ).first;

                boost::put( boost::edge_weight, m_Graph, edgeDes, dist );

                ///////////////////////////////////////////
                // Zone Entry Index Mapping
                if( pEntry_id->y == 0 )
                {
                    std::cout << "zone entry id mapping" << pEntry_id->x << pEntry_id->z << std::endl;
                    zoneEntryIndexMap.insert(ZonePair(pEntry_id->x, pEntry_id->z));
                }

            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Generate Zone entry/exit edge
    for(int i=0; i<m_pRNDF->number_of_zones; i++)
    {
        for( int j=0; j<m_pRNDF->zones_list[i]->zone_perimeter->number_of_exits; j++)
        {
            id * pEntry_id= m_pRNDF->zones_list[i]->zone_perimeter->exits_list[j]->entry_point_id;
            id * pExit_id= m_pRNDF->zones_list[i]->zone_perimeter->exits_list[j]->exit_waypoint_id;

            float _lat = vertex_array_waypoint[pExit_id->x][pExit_id->y][pExit_id->z]->latitude;
            float _lon = vertex_array_waypoint[pExit_id->x][pExit_id->y][pExit_id->z]->longitude;

            float lat = vertex_array_waypoint[pEntry_id->x][pEntry_id->y][pEntry_id->z]->latitude;
            float lon = vertex_array_waypoint[pEntry_id->x][pEntry_id->y][pEntry_id->z]->longitude;


            float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

            const EdgeDescriptor edgeDes = boost::add_edge(
                        vertex_array[pExit_id->x][pExit_id->y][pExit_id->z],
                        vertex_array[pEntry_id->x][pEntry_id->y][pEntry_id->z],
                    m_Graph ).first;

            boost::put( boost::edge_weight, m_Graph, edgeDes, dist );

            ///////////////////////////////////////////
            // Zone Exit Index Mapping
            if( pExit_id->y == 0 )
            {
                zoneExitIndexMap.insert(ZonePair(pExit_id->x, pExit_id->z));
            }
        }
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Generation of inner zone edge ( assumption: zone has just only one entry and one exit point )
    std::map< int, int >::iterator Iter_Pos;
    for( Iter_Pos = zoneEntryIndexMap.begin(); Iter_Pos != zoneEntryIndexMap.end(); ++Iter_Pos)
    {
        std::cout << "zone edge"<< (*Iter_Pos).first <<std::endl;
        std::map<int,int>::iterator finder = zoneExitIndexMap.find((*Iter_Pos).first);
        if(finder != zoneExitIndexMap.end())
        {
            std::cout << (*Iter_Pos).first << " "<<(*Iter_Pos).second <<" "<< (*finder).second <<" "<< (*finder).first << std::endl;
            float _lat = vertex_array_waypoint[(*Iter_Pos).first][0][(*Iter_Pos).second]->latitude;
            float _lon = vertex_array_waypoint[(*Iter_Pos).first][0][(*Iter_Pos).second]->longitude;

            float lat = vertex_array_waypoint[(*finder).first][0][(*finder).second]->latitude;
            float lon = vertex_array_waypoint[(*finder).first][0][(*finder).second]->longitude;


            float dist = sqrt((_lat-lat)*(_lat-lat)+(_lon-lon)*(_lon-lon))*10000.0;

            const EdgeDescriptor edgeDes = boost::add_edge(
                        vertex_array[(*Iter_Pos).first][0][(*Iter_Pos).second],
                        vertex_array[(*finder).first][0][(*finder).second],
                    m_Graph ).first;

            boost::put( boost::edge_weight, m_Graph, edgeDes, dist );

        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    WriteGraphviz();
    // Property Map 가져오기

    boost::property_map< Graph, boost::edge_weight_t >::type		mapEdgeWeight			= boost::get( boost::edge_weight, m_Graph );
    boost::property_map< Graph, boost::vertex_index_t >::type		mapVertexIndex			= boost::get( boost::vertex_index, m_Graph );
    boost::property_map< Graph, boost::vertex_distance_t >::type	mapVertexDistance		= boost::get( boost::vertex_distance, m_Graph );
    boost::property_map< Graph, boost::vertex_predecessor_t >::type	mapVertexPredecessor	= boost::get( boost::vertex_predecessor, m_Graph );

    id* preTargetId = NULL;
    int preType=0;

    for( int t=0; t<m_pMDF->number_of_checkpoints; t++)
    {

        int checkPointId = m_pMDF->checkpoints_list[t];
        int nType = 0; // 0: NULL, 1: LANE CHECKPOINT, 2: SPOT CHECKPOINT
        id* targetId = NULL;

        std::cout << "############################   " << checkPointId << std::endl;

        ///////////////////////////////////////////////////////////////////////
        // LANE TARGET
        for(int i=0; i<m_pRNDF->number_of_segments; i++)
        {
            for( int j=0; j<m_pRNDF->segments_list[i]->number_of_lanes; j++)
            {
                for( int k=0; k<m_pRNDF->segments_list[i]->lanes_list[j]->number_of_checkpoints; k++)
                {
                    if( m_pRNDF->segments_list[i]->lanes_list[j]->checkpoints_list[k]->checkpoint_id == checkPointId )
                    {
                        nType = 1;
                        targetId = m_pRNDF->segments_list[i]->lanes_list[j]->checkpoints_list[k]->waypoint_id;
                    }
                }
            }
        }
        ///////////////////////////////////////////////////////////////////////
        // ZONE TARGET
        for( int j=0; j<m_pRNDF->number_of_zones; j++)
        {
            for( int k=0; k<m_pRNDF->zones_list[j]->number_of_parking_spots; k++)
            {
                if( m_pRNDF->zones_list[j]->parking_spots_list[k]->check_waypoint->checkpoint_id == checkPointId )
                {
                    nType = 2;
                    targetId = m_pRNDF->zones_list[j]->parking_spots_list[k]->check_waypoint->waypoint_id;
                }
            }
        }
        ///////////////////////////////////////////////////////////////////////

        std::cout << "######  " << nType << "," << targetId <<std::endl;

        if( t == 0)
        {
            const VertexDescriptor vStartVertex = vertex_array[targetId->x][targetId->y][targetId->z];

            boost::dijkstra_shortest_paths(

                        m_Graph,

                        vStartVertex,

                        boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

                        );
        }
        else
        {
            std::cout << "[" << preTargetId->x<<"," << preTargetId->y<<","<< preTargetId->z<< "," << preType <<"]"
                      << "--> [" << targetId->x << ","<< targetId->y << ","<< targetId->z << "," << nType <<"]" << std::endl;
            std::vector< VertexDescriptor > vecResolvePath;

            if( nType == 1) // LANE CHECKPT
            {
                if( preType == 2 )
                {
                    std::map<int,int>::iterator finder = zoneExitIndexMap.find(preTargetId->x);
                    if(finder != zoneExitIndexMap.end())
                    {
                        const VertexDescriptor vStartVertex =vertex_array[preTargetId->x][0][(*finder).second];

                        boost::dijkstra_shortest_paths(

                                    m_Graph,

                                    vStartVertex,

                                    boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

                                    );
                         const VertexDescriptor vEndVertex = vertex_array[targetId->x][targetId->y][targetId->z];
                        ResolvePath(vStartVertex, vEndVertex,vecResolvePath);
                    }
                    else
                    {
                        std::cout << "no zone exit id"<< std::endl;
                    }
                }
                else
                {
                    const VertexDescriptor vStartVertex = vertex_array[preTargetId->x][preTargetId->y][preTargetId->z];
                    boost::dijkstra_shortest_paths(

                                m_Graph,

                                vStartVertex,

                                boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

                                );
                    const VertexDescriptor vEndVertex = vertex_array[targetId->x][targetId->y][targetId->z];

                    std::cout << "***[" << preTargetId->x<<"," << preTargetId->y<<","<< preTargetId->z<< "," << preType <<"]"
                              << "--> [" << targetId->x << ","<< targetId->y << ","<< targetId->z << "," << nType <<"]" << std::endl;

                    ResolvePath(vStartVertex, vEndVertex,vecResolvePath);

                }
            }
            else if( nType == 2 ) // SPOT CHECKPT
            {
                const VertexDescriptor vStartVertex = vertex_array[preTargetId->x][preTargetId->y][preTargetId->z];
                boost::dijkstra_shortest_paths(

                            m_Graph,

                            vStartVertex,

                            boost::weight_map( mapEdgeWeight ).vertex_index_map( mapVertexIndex ).distance_map( mapVertexDistance ).predecessor_map( mapVertexPredecessor )

                            );
                std::map<int,int>::iterator finder = zoneEntryIndexMap.find(targetId->x);
                if(finder != zoneEntryIndexMap.end())
                {
                    const VertexDescriptor vEndVertex =vertex_array[targetId->x][0][(*finder).second];
                    ResolvePath(vStartVertex, vEndVertex,vecResolvePath);
                }
                else
                {
                    std::cout << "no zone entry id"<< std::endl;
                }
            }
        }
        preTargetId = targetId;
        preType = nType;
    }

    //WriteGraphviz();

    //////////////////////////////////////////////////////////////////////////

    std::cout<<"end of print path"<<std::endl;



}
