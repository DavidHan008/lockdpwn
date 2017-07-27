; Auto-generated. Do not edit!


(cl:in-package motion_planner-srv)


;//! \htmlinclude srvParkingCmd-request.msg.html

(cl:defclass <srvParkingCmd-request> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (theta
    :reader theta
    :initarg :theta
    :type cl:float
    :initform 0.0)
   (mode
    :reader mode
    :initarg :mode
    :type cl:integer
    :initform 0))
)

(cl:defclass srvParkingCmd-request (<srvParkingCmd-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <srvParkingCmd-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'srvParkingCmd-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name motion_planner-srv:<srvParkingCmd-request> is deprecated: use motion_planner-srv:srvParkingCmd-request instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <srvParkingCmd-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motion_planner-srv:x-val is deprecated.  Use motion_planner-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <srvParkingCmd-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motion_planner-srv:y-val is deprecated.  Use motion_planner-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'theta-val :lambda-list '(m))
(cl:defmethod theta-val ((m <srvParkingCmd-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motion_planner-srv:theta-val is deprecated.  Use motion_planner-srv:theta instead.")
  (theta m))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <srvParkingCmd-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motion_planner-srv:mode-val is deprecated.  Use motion_planner-srv:mode instead.")
  (mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <srvParkingCmd-request>) ostream)
  "Serializes a message object of type '<srvParkingCmd-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'theta))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <srvParkingCmd-request>) istream)
  "Deserializes a message object of type '<srvParkingCmd-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'theta) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mode) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<srvParkingCmd-request>)))
  "Returns string type for a service object of type '<srvParkingCmd-request>"
  "motion_planner/srvParkingCmdRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvParkingCmd-request)))
  "Returns string type for a service object of type 'srvParkingCmd-request"
  "motion_planner/srvParkingCmdRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<srvParkingCmd-request>)))
  "Returns md5sum for a message object of type '<srvParkingCmd-request>"
  "6f559bfa1f52d42afbe43f629231fbe9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'srvParkingCmd-request)))
  "Returns md5sum for a message object of type 'srvParkingCmd-request"
  "6f559bfa1f52d42afbe43f629231fbe9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<srvParkingCmd-request>)))
  "Returns full string definition for message of type '<srvParkingCmd-request>"
  (cl:format cl:nil "float64 x~%float64 y~%float64 theta~%int64 mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'srvParkingCmd-request)))
  "Returns full string definition for message of type 'srvParkingCmd-request"
  (cl:format cl:nil "float64 x~%float64 y~%float64 theta~%int64 mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <srvParkingCmd-request>))
  (cl:+ 0
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <srvParkingCmd-request>))
  "Converts a ROS message object to a list"
  (cl:list 'srvParkingCmd-request
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':theta (theta msg))
    (cl:cons ':mode (mode msg))
))
;//! \htmlinclude srvParkingCmd-response.msg.html

(cl:defclass <srvParkingCmd-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:integer
    :initform 0))
)

(cl:defclass srvParkingCmd-response (<srvParkingCmd-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <srvParkingCmd-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'srvParkingCmd-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name motion_planner-srv:<srvParkingCmd-response> is deprecated: use motion_planner-srv:srvParkingCmd-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <srvParkingCmd-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motion_planner-srv:result-val is deprecated.  Use motion_planner-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <srvParkingCmd-response>) ostream)
  "Serializes a message object of type '<srvParkingCmd-response>"
  (cl:let* ((signed (cl:slot-value msg 'result)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <srvParkingCmd-response>) istream)
  "Deserializes a message object of type '<srvParkingCmd-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'result) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<srvParkingCmd-response>)))
  "Returns string type for a service object of type '<srvParkingCmd-response>"
  "motion_planner/srvParkingCmdResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvParkingCmd-response)))
  "Returns string type for a service object of type 'srvParkingCmd-response"
  "motion_planner/srvParkingCmdResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<srvParkingCmd-response>)))
  "Returns md5sum for a message object of type '<srvParkingCmd-response>"
  "6f559bfa1f52d42afbe43f629231fbe9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'srvParkingCmd-response)))
  "Returns md5sum for a message object of type 'srvParkingCmd-response"
  "6f559bfa1f52d42afbe43f629231fbe9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<srvParkingCmd-response>)))
  "Returns full string definition for message of type '<srvParkingCmd-response>"
  (cl:format cl:nil "int64 result~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'srvParkingCmd-response)))
  "Returns full string definition for message of type 'srvParkingCmd-response"
  (cl:format cl:nil "int64 result~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <srvParkingCmd-response>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <srvParkingCmd-response>))
  "Converts a ROS message object to a list"
  (cl:list 'srvParkingCmd-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'srvParkingCmd)))
  'srvParkingCmd-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'srvParkingCmd)))
  'srvParkingCmd-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvParkingCmd)))
  "Returns string type for a service object of type '<srvParkingCmd>"
  "motion_planner/srvParkingCmd")