# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from dbw_mkz_msgs/GearCmd.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import dbw_mkz_msgs.msg

class GearCmd(genpy.Message):
  _md5sum = "14694bb9a291d2a80b8033843d95776e"
  _type = "dbw_mkz_msgs/GearCmd"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# Gear command enumeration
Gear cmd

# Clear driver overrides
bool clear

================================================================================
MSG: dbw_mkz_msgs/Gear
uint8 gear

uint8 NONE=0
uint8 PARK=1
uint8 REVERSE=2
uint8 NEUTRAL=3
uint8 DRIVE=4
uint8 LOW=5
"""
  __slots__ = ['cmd','clear']
  _slot_types = ['dbw_mkz_msgs/Gear','bool']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       cmd,clear

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(GearCmd, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.cmd is None:
        self.cmd = dbw_mkz_msgs.msg.Gear()
      if self.clear is None:
        self.clear = False
    else:
      self.cmd = dbw_mkz_msgs.msg.Gear()
      self.clear = False

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_2B.pack(_x.cmd.gear, _x.clear))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.cmd is None:
        self.cmd = dbw_mkz_msgs.msg.Gear()
      end = 0
      _x = self
      start = end
      end += 2
      (_x.cmd.gear, _x.clear,) = _struct_2B.unpack(str[start:end])
      self.clear = bool(self.clear)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_2B.pack(_x.cmd.gear, _x.clear))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.cmd is None:
        self.cmd = dbw_mkz_msgs.msg.Gear()
      end = 0
      _x = self
      start = end
      end += 2
      (_x.cmd.gear, _x.clear,) = _struct_2B.unpack(str[start:end])
      self.clear = bool(self.clear)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_2B = struct.Struct("<2B")
