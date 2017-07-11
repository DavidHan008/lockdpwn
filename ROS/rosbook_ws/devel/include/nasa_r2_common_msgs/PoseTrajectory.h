// Generated by gencpp from file nasa_r2_common_msgs/PoseTrajectory.msg
// DO NOT EDIT!


#ifndef NASA_R2_COMMON_MSGS_MESSAGE_POSETRAJECTORY_H
#define NASA_R2_COMMON_MSGS_MESSAGE_POSETRAJECTORY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <nasa_r2_common_msgs/PriorityArray.h>
#include <nasa_r2_common_msgs/PoseTrajectoryPoint.h>

namespace nasa_r2_common_msgs
{
template <class ContainerAllocator>
struct PoseTrajectory_
{
  typedef PoseTrajectory_<ContainerAllocator> Type;

  PoseTrajectory_()
    : header()
    , nodes()
    , node_priorities()
    , refFrames()
    , points()  {
    }
  PoseTrajectory_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , nodes(_alloc)
    , node_priorities(_alloc)
    , refFrames(_alloc)
    , points(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _nodes_type;
  _nodes_type nodes;

   typedef std::vector< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >::other >  _node_priorities_type;
  _node_priorities_type node_priorities;

   typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _refFrames_type;
  _refFrames_type refFrames;

   typedef std::vector< ::nasa_r2_common_msgs::PoseTrajectoryPoint_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::nasa_r2_common_msgs::PoseTrajectoryPoint_<ContainerAllocator> >::other >  _points_type;
  _points_type points;




  typedef boost::shared_ptr< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> const> ConstPtr;

}; // struct PoseTrajectory_

typedef ::nasa_r2_common_msgs::PoseTrajectory_<std::allocator<void> > PoseTrajectory;

typedef boost::shared_ptr< ::nasa_r2_common_msgs::PoseTrajectory > PoseTrajectoryPtr;
typedef boost::shared_ptr< ::nasa_r2_common_msgs::PoseTrajectory const> PoseTrajectoryConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace nasa_r2_common_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'trajectory_msgs': ['/opt/ros/indigo/share/trajectory_msgs/cmake/../msg'], 'nasa_r2_common_msgs': ['/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/src/deprecated_nasa_r2_common/nasa_r2_common_msgs/msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'visualization_msgs': ['/opt/ros/indigo/share/visualization_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> >
{
  static const char* value()
  {
    return "635ae07b754d8dde1d1ec77316124e02";
  }

  static const char* value(const ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x635ae07b754d8ddeULL;
  static const uint64_t static_value2 = 0x1d1ec77316124e02ULL;
};

template<class ContainerAllocator>
struct DataType< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nasa_r2_common_msgs/PoseTrajectory";
  }

  static const char* value(const ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
# length of nodes must match length of poses in each point\n\
string[] nodes\n\
# priorities must have nodes length or be omitted which defaults all to HIGH\n\
PriorityArray[]  node_priorities\n\
# refFrames must either have one item or be nodes length\n\
string[] refFrames\n\
PoseTrajectoryPoint[] points\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: nasa_r2_common_msgs/PriorityArray\n\
# axis_priorities must be 0, 1, or 6 elements\n\
# empty defaults to high, 1 sets all axes equal priority, 6 sets each axis (x, y, z, r, p, y)\n\
uint8[]  axis_priorities\n\
\n\
uint8 IGNORE          = 0   # Exclude from trajectory\n\
uint8 CRITICAL        = 1   # Most important priority in trajectory\n\
uint8 HIGH            = 2   # Second most important priority in trajectory\n\
uint8 MEDIUM          = 3   # Medium prioirty in trajectory\n\
uint8 LOW             = 4   # Low priority in trajectory\n\
uint8 OPT             = 5   # Optimize trajectory (solve for, but do not iterate to achieve)\n\
\n\
#uint8 IGNORE = 0\n\
#uint8 LOW = 1\n\
#uint8 MEDIUM = 128\n\
#uint8 HIGH = 254\n\
#uint8 CRITICAL = 255\n\
\n\
================================================================================\n\
MSG: nasa_r2_common_msgs/PoseTrajectoryPoint\n\
# currently, position only but could add velocity and acceleration later\n\
geometry_msgs/Pose[] positions\n\
geometry_msgs/Twist[] velocities\n\
geometry_msgs/Twist[] accelerations\n\
duration time_from_start\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of postion and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Twist\n\
# This expresses velocity in free space broken into its linear and angular parts.\n\
Vector3  linear\n\
Vector3  angular\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
# It is only meant to represent a direction. Therefore, it does not\n\
# make sense to apply a translation to it (e.g., when applying a \n\
# generic rigid transformation to a Vector3, tf2 will only apply the\n\
# rotation). If you want your data to be translatable too, use the\n\
# geometry_msgs/Point message instead.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.nodes);
      stream.next(m.node_priorities);
      stream.next(m.refFrames);
      stream.next(m.points);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PoseTrajectory_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nasa_r2_common_msgs::PoseTrajectory_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "nodes[]" << std::endl;
    for (size_t i = 0; i < v.nodes.size(); ++i)
    {
      s << indent << "  nodes[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.nodes[i]);
    }
    s << indent << "node_priorities[]" << std::endl;
    for (size_t i = 0; i < v.node_priorities.size(); ++i)
    {
      s << indent << "  node_priorities[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >::stream(s, indent + "    ", v.node_priorities[i]);
    }
    s << indent << "refFrames[]" << std::endl;
    for (size_t i = 0; i < v.refFrames.size(); ++i)
    {
      s << indent << "  refFrames[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.refFrames[i]);
    }
    s << indent << "points[]" << std::endl;
    for (size_t i = 0; i < v.points.size(); ++i)
    {
      s << indent << "  points[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::nasa_r2_common_msgs::PoseTrajectoryPoint_<ContainerAllocator> >::stream(s, indent + "    ", v.points[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // NASA_R2_COMMON_MSGS_MESSAGE_POSETRAJECTORY_H
