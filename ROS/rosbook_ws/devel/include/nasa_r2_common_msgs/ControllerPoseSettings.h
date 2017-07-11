// Generated by gencpp from file nasa_r2_common_msgs/ControllerPoseSettings.msg
// DO NOT EDIT!


#ifndef NASA_R2_COMMON_MSGS_MESSAGE_CONTROLLERPOSESETTINGS_H
#define NASA_R2_COMMON_MSGS_MESSAGE_CONTROLLERPOSESETTINGS_H


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
struct ControllerPoseSettings_
{
  typedef ControllerPoseSettings_<ContainerAllocator> Type;

  ControllerPoseSettings_()
    : maxLinearVelocity(0.0)
    , maxRotationalVelocity(0.0)
    , maxLinearAcceleration(0.0)
    , maxRotationalAcceleration(0.0)  {
    }
  ControllerPoseSettings_(const ContainerAllocator& _alloc)
    : maxLinearVelocity(0.0)
    , maxRotationalVelocity(0.0)
    , maxLinearAcceleration(0.0)
    , maxRotationalAcceleration(0.0)  {
  (void)_alloc;
    }



   typedef double _maxLinearVelocity_type;
  _maxLinearVelocity_type maxLinearVelocity;

   typedef double _maxRotationalVelocity_type;
  _maxRotationalVelocity_type maxRotationalVelocity;

   typedef double _maxLinearAcceleration_type;
  _maxLinearAcceleration_type maxLinearAcceleration;

   typedef double _maxRotationalAcceleration_type;
  _maxRotationalAcceleration_type maxRotationalAcceleration;




  typedef boost::shared_ptr< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> const> ConstPtr;

}; // struct ControllerPoseSettings_

typedef ::nasa_r2_common_msgs::ControllerPoseSettings_<std::allocator<void> > ControllerPoseSettings;

typedef boost::shared_ptr< ::nasa_r2_common_msgs::ControllerPoseSettings > ControllerPoseSettingsPtr;
typedef boost::shared_ptr< ::nasa_r2_common_msgs::ControllerPoseSettings const> ControllerPoseSettingsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace nasa_r2_common_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'trajectory_msgs': ['/opt/ros/indigo/share/trajectory_msgs/cmake/../msg'], 'nasa_r2_common_msgs': ['/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/src/deprecated_nasa_r2_common/nasa_r2_common_msgs/msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'visualization_msgs': ['/opt/ros/indigo/share/visualization_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f62b594a8f4b5a5afec86445f0b7a4f2";
  }

  static const char* value(const ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf62b594a8f4b5a5aULL;
  static const uint64_t static_value2 = 0xfec86445f0b7a4f2ULL;
};

template<class ContainerAllocator>
struct DataType< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nasa_r2_common_msgs/ControllerPoseSettings";
  }

  static const char* value(const ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 maxLinearVelocity\n\
float64 maxRotationalVelocity\n\
float64 maxLinearAcceleration\n\
float64 maxRotationalAcceleration\n\
";
  }

  static const char* value(const ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.maxLinearVelocity);
      stream.next(m.maxRotationalVelocity);
      stream.next(m.maxLinearAcceleration);
      stream.next(m.maxRotationalAcceleration);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ControllerPoseSettings_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nasa_r2_common_msgs::ControllerPoseSettings_<ContainerAllocator>& v)
  {
    s << indent << "maxLinearVelocity: ";
    Printer<double>::stream(s, indent + "  ", v.maxLinearVelocity);
    s << indent << "maxRotationalVelocity: ";
    Printer<double>::stream(s, indent + "  ", v.maxRotationalVelocity);
    s << indent << "maxLinearAcceleration: ";
    Printer<double>::stream(s, indent + "  ", v.maxLinearAcceleration);
    s << indent << "maxRotationalAcceleration: ";
    Printer<double>::stream(s, indent + "  ", v.maxRotationalAcceleration);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NASA_R2_COMMON_MSGS_MESSAGE_CONTROLLERPOSESETTINGS_H
