// Generated by gencpp from file nasa_r2_common_msgs/PriorityArray.msg
// DO NOT EDIT!


#ifndef NASA_R2_COMMON_MSGS_MESSAGE_PRIORITYARRAY_H
#define NASA_R2_COMMON_MSGS_MESSAGE_PRIORITYARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace nasa_r2_common_msgs
{
template <class ContainerAllocator>
struct PriorityArray_
{
  typedef PriorityArray_<ContainerAllocator> Type;

  PriorityArray_()
    : axis_priorities()  {
    }
  PriorityArray_(const ContainerAllocator& _alloc)
    : axis_priorities(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<uint8_t, typename ContainerAllocator::template rebind<uint8_t>::other >  _axis_priorities_type;
  _axis_priorities_type axis_priorities;


    enum { IGNORE = 0u };
     enum { CRITICAL = 1u };
     enum { HIGH = 2u };
     enum { MEDIUM = 3u };
     enum { LOW = 4u };
     enum { OPT = 5u };
 

  typedef boost::shared_ptr< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> const> ConstPtr;

}; // struct PriorityArray_

typedef ::nasa_r2_common_msgs::PriorityArray_<std::allocator<void> > PriorityArray;

typedef boost::shared_ptr< ::nasa_r2_common_msgs::PriorityArray > PriorityArrayPtr;
typedef boost::shared_ptr< ::nasa_r2_common_msgs::PriorityArray const> PriorityArrayConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace nasa_r2_common_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'trajectory_msgs': ['/opt/ros/indigo/share/trajectory_msgs/cmake/../msg'], 'nasa_r2_common_msgs': ['/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/src/deprecated_nasa_r2_common/nasa_r2_common_msgs/msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'visualization_msgs': ['/opt/ros/indigo/share/visualization_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b680195622dc1787258149093c8d5b54";
  }

  static const char* value(const ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb680195622dc1787ULL;
  static const uint64_t static_value2 = 0x258149093c8d5b54ULL;
};

template<class ContainerAllocator>
struct DataType< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nasa_r2_common_msgs/PriorityArray";
  }

  static const char* value(const ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# axis_priorities must be 0, 1, or 6 elements\n\
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
";
  }

  static const char* value(const ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.axis_priorities);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PriorityArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nasa_r2_common_msgs::PriorityArray_<ContainerAllocator>& v)
  {
    s << indent << "axis_priorities[]" << std::endl;
    for (size_t i = 0; i < v.axis_priorities.size(); ++i)
    {
      s << indent << "  axis_priorities[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.axis_priorities[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // NASA_R2_COMMON_MSGS_MESSAGE_PRIORITYARRAY_H
