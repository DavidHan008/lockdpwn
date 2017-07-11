// Generated by gencpp from file nasa_r2_common_msgs/WrenchMonitorLimit.msg
// DO NOT EDIT!


#ifndef NASA_R2_COMMON_MSGS_MESSAGE_WRENCHMONITORLIMIT_H
#define NASA_R2_COMMON_MSGS_MESSAGE_WRENCHMONITORLIMIT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace nasa_r2_common_msgs
{
template <class ContainerAllocator>
struct WrenchMonitorLimit_
{
  typedef WrenchMonitorLimit_<ContainerAllocator> Type;

  WrenchMonitorLimit_()
    : header()
    , name()
    , force()
    , torque()
    , isFraction()  {
    }
  WrenchMonitorLimit_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , name(_alloc)
    , force(_alloc)
    , torque(_alloc)
    , isFraction(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _name_type;
  _name_type name;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _force_type;
  _force_type force;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _torque_type;
  _torque_type torque;

   typedef std::vector<uint8_t, typename ContainerAllocator::template rebind<uint8_t>::other >  _isFraction_type;
  _isFraction_type isFraction;




  typedef boost::shared_ptr< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> const> ConstPtr;

}; // struct WrenchMonitorLimit_

typedef ::nasa_r2_common_msgs::WrenchMonitorLimit_<std::allocator<void> > WrenchMonitorLimit;

typedef boost::shared_ptr< ::nasa_r2_common_msgs::WrenchMonitorLimit > WrenchMonitorLimitPtr;
typedef boost::shared_ptr< ::nasa_r2_common_msgs::WrenchMonitorLimit const> WrenchMonitorLimitConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4535825230d82d19f739062cbc5d17ed";
  }

  static const char* value(const ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4535825230d82d19ULL;
  static const uint64_t static_value2 = 0xf739062cbc5d17edULL;
};

template<class ContainerAllocator>
struct DataType< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nasa_r2_common_msgs/WrenchMonitorLimit";
  }

  static const char* value(const ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
string[] name\n\
float64[] force\n\
float64[] torque\n\
bool[] isFraction\n\
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
";
  }

  static const char* value(const ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.name);
      stream.next(m.force);
      stream.next(m.torque);
      stream.next(m.isFraction);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct WrenchMonitorLimit_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nasa_r2_common_msgs::WrenchMonitorLimit_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "name[]" << std::endl;
    for (size_t i = 0; i < v.name.size(); ++i)
    {
      s << indent << "  name[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.name[i]);
    }
    s << indent << "force[]" << std::endl;
    for (size_t i = 0; i < v.force.size(); ++i)
    {
      s << indent << "  force[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.force[i]);
    }
    s << indent << "torque[]" << std::endl;
    for (size_t i = 0; i < v.torque.size(); ++i)
    {
      s << indent << "  torque[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.torque[i]);
    }
    s << indent << "isFraction[]" << std::endl;
    for (size_t i = 0; i < v.isFraction.size(); ++i)
    {
      s << indent << "  isFraction[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.isFraction[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // NASA_R2_COMMON_MSGS_MESSAGE_WRENCHMONITORLIMIT_H
