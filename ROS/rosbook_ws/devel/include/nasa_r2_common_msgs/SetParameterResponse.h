// Generated by gencpp from file nasa_r2_common_msgs/SetParameterResponse.msg
// DO NOT EDIT!


#ifndef NASA_R2_COMMON_MSGS_MESSAGE_SETPARAMETERRESPONSE_H
#define NASA_R2_COMMON_MSGS_MESSAGE_SETPARAMETERRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <nasa_r2_common_msgs/CommandStatus.h>

namespace nasa_r2_common_msgs
{
template <class ContainerAllocator>
struct SetParameterResponse_
{
  typedef SetParameterResponse_<ContainerAllocator> Type;

  SetParameterResponse_()
    : header()
    , name()
    , command()  {
    }
  SetParameterResponse_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , name(_alloc)
    , command(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _name_type;
  _name_type name;

   typedef  ::nasa_r2_common_msgs::CommandStatus_<ContainerAllocator>  _command_type;
  _command_type command;




  typedef boost::shared_ptr< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SetParameterResponse_

typedef ::nasa_r2_common_msgs::SetParameterResponse_<std::allocator<void> > SetParameterResponse;

typedef boost::shared_ptr< ::nasa_r2_common_msgs::SetParameterResponse > SetParameterResponsePtr;
typedef boost::shared_ptr< ::nasa_r2_common_msgs::SetParameterResponse const> SetParameterResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "71d8d3ef535abb6951a4e8228fc751e1";
  }

  static const char* value(const ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x71d8d3ef535abb69ULL;
  static const uint64_t static_value2 = 0x51a4e8228fc751e1ULL;
};

template<class ContainerAllocator>
struct DataType< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nasa_r2_common_msgs/SetParameterResponse";
  }

  static const char* value(const ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
string name\n\
CommandStatus command\n\
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
MSG: nasa_r2_common_msgs/CommandStatus\n\
bool success\n\
string status\n\
";
  }

  static const char* value(const ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.name);
      stream.next(m.command);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetParameterResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nasa_r2_common_msgs::SetParameterResponse_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.name);
    s << indent << "command: ";
    s << std::endl;
    Printer< ::nasa_r2_common_msgs::CommandStatus_<ContainerAllocator> >::stream(s, indent + "  ", v.command);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NASA_R2_COMMON_MSGS_MESSAGE_SETPARAMETERRESPONSE_H
