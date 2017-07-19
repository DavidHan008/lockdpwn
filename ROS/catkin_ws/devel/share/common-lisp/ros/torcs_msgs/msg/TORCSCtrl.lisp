; Auto-generated. Do not edit!


(cl:in-package torcs_msgs-msg)


;//! \htmlinclude TORCSCtrl.msg.html

(cl:defclass <TORCSCtrl> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (accel
    :reader accel
    :initarg :accel
    :type cl:float
    :initform 0.0)
   (brake
    :reader brake
    :initarg :brake
    :type cl:float
    :initform 0.0)
   (clutch
    :reader clutch
    :initarg :clutch
    :type cl:float
    :initform 0.0)
   (gear
    :reader gear
    :initarg :gear
    :type cl:fixnum
    :initform 0)
   (steering
    :reader steering
    :initarg :steering
    :type cl:float
    :initform 0.0)
   (focus
    :reader focus
    :initarg :focus
    :type cl:float
    :initform 0.0)
   (meta
    :reader meta
    :initarg :meta
    :type cl:fixnum
    :initform 0))
)

(cl:defclass TORCSCtrl (<TORCSCtrl>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TORCSCtrl>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TORCSCtrl)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name torcs_msgs-msg:<TORCSCtrl> is deprecated: use torcs_msgs-msg:TORCSCtrl instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <TORCSCtrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader torcs_msgs-msg:header-val is deprecated.  Use torcs_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'accel-val :lambda-list '(m))
(cl:defmethod accel-val ((m <TORCSCtrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader torcs_msgs-msg:accel-val is deprecated.  Use torcs_msgs-msg:accel instead.")
  (accel m))

(cl:ensure-generic-function 'brake-val :lambda-list '(m))
(cl:defmethod brake-val ((m <TORCSCtrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader torcs_msgs-msg:brake-val is deprecated.  Use torcs_msgs-msg:brake instead.")
  (brake m))

(cl:ensure-generic-function 'clutch-val :lambda-list '(m))
(cl:defmethod clutch-val ((m <TORCSCtrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader torcs_msgs-msg:clutch-val is deprecated.  Use torcs_msgs-msg:clutch instead.")
  (clutch m))

(cl:ensure-generic-function 'gear-val :lambda-list '(m))
(cl:defmethod gear-val ((m <TORCSCtrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader torcs_msgs-msg:gear-val is deprecated.  Use torcs_msgs-msg:gear instead.")
  (gear m))

(cl:ensure-generic-function 'steering-val :lambda-list '(m))
(cl:defmethod steering-val ((m <TORCSCtrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader torcs_msgs-msg:steering-val is deprecated.  Use torcs_msgs-msg:steering instead.")
  (steering m))

(cl:ensure-generic-function 'focus-val :lambda-list '(m))
(cl:defmethod focus-val ((m <TORCSCtrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader torcs_msgs-msg:focus-val is deprecated.  Use torcs_msgs-msg:focus instead.")
  (focus m))

(cl:ensure-generic-function 'meta-val :lambda-list '(m))
(cl:defmethod meta-val ((m <TORCSCtrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader torcs_msgs-msg:meta-val is deprecated.  Use torcs_msgs-msg:meta instead.")
  (meta m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TORCSCtrl>) ostream)
  "Serializes a message object of type '<TORCSCtrl>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'accel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'brake))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'clutch))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'steering))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'focus))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'meta)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TORCSCtrl>) istream)
  "Deserializes a message object of type '<TORCSCtrl>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'accel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'brake) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'clutch) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steering) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'focus) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'meta)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TORCSCtrl>)))
  "Returns string type for a message object of type '<TORCSCtrl>"
  "torcs_msgs/TORCSCtrl")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TORCSCtrl)))
  "Returns string type for a message object of type 'TORCSCtrl"
  "torcs_msgs/TORCSCtrl")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TORCSCtrl>)))
  "Returns md5sum for a message object of type '<TORCSCtrl>"
  "4848a66993e5bb22e0199af44ab1d070")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TORCSCtrl)))
  "Returns md5sum for a message object of type 'TORCSCtrl"
  "4848a66993e5bb22e0199af44ab1d070")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TORCSCtrl>)))
  "Returns full string definition for message of type '<TORCSCtrl>"
  (cl:format cl:nil "Header header~%# Virtual gas pedal (0 means no gas, 1 full gas)~%float64 accel~%# Virtual brake pedal (0 means no brake, 1 full brake)~%float64 brake~%# Virtual clutch pedal (0 means no clutch, 1 full clutch)~%float64 clutch~%# Gear value: -1,0,1,...,6 where -1 means backwards driving and 0 means idle~%uint8 gear~%# Steering value: -1 and +1 means respectively full right and~%# left, that corresponds to an angle of 0.366519 rad~%float64 steering~%# Focus direction for the focus sensors in degrees. Currently unused~%float64 focus~%# This is meta-control command: 0 do nothing, 1 ask compe-~%# tition server to restart the race. Currently unused~%uint8 meta~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TORCSCtrl)))
  "Returns full string definition for message of type 'TORCSCtrl"
  (cl:format cl:nil "Header header~%# Virtual gas pedal (0 means no gas, 1 full gas)~%float64 accel~%# Virtual brake pedal (0 means no brake, 1 full brake)~%float64 brake~%# Virtual clutch pedal (0 means no clutch, 1 full clutch)~%float64 clutch~%# Gear value: -1,0,1,...,6 where -1 means backwards driving and 0 means idle~%uint8 gear~%# Steering value: -1 and +1 means respectively full right and~%# left, that corresponds to an angle of 0.366519 rad~%float64 steering~%# Focus direction for the focus sensors in degrees. Currently unused~%float64 focus~%# This is meta-control command: 0 do nothing, 1 ask compe-~%# tition server to restart the race. Currently unused~%uint8 meta~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TORCSCtrl>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     8
     8
     8
     1
     8
     8
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TORCSCtrl>))
  "Converts a ROS message object to a list"
  (cl:list 'TORCSCtrl
    (cl:cons ':header (header msg))
    (cl:cons ':accel (accel msg))
    (cl:cons ':brake (brake msg))
    (cl:cons ':clutch (clutch msg))
    (cl:cons ':gear (gear msg))
    (cl:cons ':steering (steering msg))
    (cl:cons ':focus (focus msg))
    (cl:cons ':meta (meta msg))
))
