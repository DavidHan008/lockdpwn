// Generated by gencpp from file basics/WordCountRequest.msg
// DO NOT EDIT!


#ifndef BASICS_MESSAGE_WORDCOUNTREQUEST_H
#define BASICS_MESSAGE_WORDCOUNTREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace basics
{
template <class ContainerAllocator>
struct WordCountRequest_
{
  typedef WordCountRequest_<ContainerAllocator> Type;

  WordCountRequest_()
    : words()  {
    }
  WordCountRequest_(const ContainerAllocator& _alloc)
    : words(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _words_type;
  _words_type words;




  typedef boost::shared_ptr< ::basics::WordCountRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::basics::WordCountRequest_<ContainerAllocator> const> ConstPtr;

}; // struct WordCountRequest_

typedef ::basics::WordCountRequest_<std::allocator<void> > WordCountRequest;

typedef boost::shared_ptr< ::basics::WordCountRequest > WordCountRequestPtr;
typedef boost::shared_ptr< ::basics::WordCountRequest const> WordCountRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::basics::WordCountRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::basics::WordCountRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace basics

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'basics': ['/home/edward/gitrepo/lockdpwn/ROS/catkin_ws/src/basics/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::basics::WordCountRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::basics::WordCountRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::basics::WordCountRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::basics::WordCountRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::basics::WordCountRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::basics::WordCountRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::basics::WordCountRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6f897d3845272d18053a750c1cfb862a";
  }

  static const char* value(const ::basics::WordCountRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6f897d3845272d18ULL;
  static const uint64_t static_value2 = 0x053a750c1cfb862aULL;
};

template<class ContainerAllocator>
struct DataType< ::basics::WordCountRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "basics/WordCountRequest";
  }

  static const char* value(const ::basics::WordCountRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::basics::WordCountRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string words\n\
";
  }

  static const char* value(const ::basics::WordCountRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::basics::WordCountRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.words);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct WordCountRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::basics::WordCountRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::basics::WordCountRequest_<ContainerAllocator>& v)
  {
    s << indent << "words: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.words);
  }
};

} // namespace message_operations
} // namespace ros

#endif // BASICS_MESSAGE_WORDCOUNTREQUEST_H
