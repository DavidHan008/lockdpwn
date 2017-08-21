// Generated by gencpp from file dbw_mkz_msgs/Gear.msg
// DO NOT EDIT!


#ifndef DBW_MKZ_MSGS_MESSAGE_GEAR_H
#define DBW_MKZ_MSGS_MESSAGE_GEAR_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace dbw_mkz_msgs
{
template <class ContainerAllocator>
struct Gear_
{
  typedef Gear_<ContainerAllocator> Type;

  Gear_()
    : gear(0)  {
    }
  Gear_(const ContainerAllocator& _alloc)
    : gear(0)  {
  (void)_alloc;
    }



   typedef uint8_t _gear_type;
  _gear_type gear;


    enum { NONE = 0u };
     enum { PARK = 1u };
     enum { REVERSE = 2u };
     enum { NEUTRAL = 3u };
     enum { DRIVE = 4u };
     enum { LOW = 5u };
 

  typedef boost::shared_ptr< ::dbw_mkz_msgs::Gear_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::dbw_mkz_msgs::Gear_<ContainerAllocator> const> ConstPtr;

}; // struct Gear_

typedef ::dbw_mkz_msgs::Gear_<std::allocator<void> > Gear;

typedef boost::shared_ptr< ::dbw_mkz_msgs::Gear > GearPtr;
typedef boost::shared_ptr< ::dbw_mkz_msgs::Gear const> GearConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::dbw_mkz_msgs::Gear_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::dbw_mkz_msgs::Gear_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace dbw_mkz_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'dbw_mkz_msgs': ['/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros_simulator/dbw_mkz_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::dbw_mkz_msgs::Gear_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::dbw_mkz_msgs::Gear_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dbw_mkz_msgs::Gear_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dbw_mkz_msgs::Gear_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dbw_mkz_msgs::Gear_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dbw_mkz_msgs::Gear_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::dbw_mkz_msgs::Gear_<ContainerAllocator> >
{
  static const char* value()
  {
    return "79b3cd667a7556f4bc4a66af7d189c96";
  }

  static const char* value(const ::dbw_mkz_msgs::Gear_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x79b3cd667a7556f4ULL;
  static const uint64_t static_value2 = 0xbc4a66af7d189c96ULL;
};

template<class ContainerAllocator>
struct DataType< ::dbw_mkz_msgs::Gear_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dbw_mkz_msgs/Gear";
  }

  static const char* value(const ::dbw_mkz_msgs::Gear_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::dbw_mkz_msgs::Gear_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint8 gear\n\
\n\
uint8 NONE=0\n\
uint8 PARK=1\n\
uint8 REVERSE=2\n\
uint8 NEUTRAL=3\n\
uint8 DRIVE=4\n\
uint8 LOW=5\n\
";
  }

  static const char* value(const ::dbw_mkz_msgs::Gear_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::dbw_mkz_msgs::Gear_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.gear);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Gear_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::dbw_mkz_msgs::Gear_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::dbw_mkz_msgs::Gear_<ContainerAllocator>& v)
  {
    s << indent << "gear: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.gear);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DBW_MKZ_MSGS_MESSAGE_GEAR_H
