; Auto-generated. Do not edit!


(cl:in-package model_predictive_navigation-msg)


;//! \htmlinclude EgoGoal.msg.html

(cl:defclass <EgoGoal> (roslisp-msg-protocol:ros-message)
  ((r
    :reader r
    :initarg :r
    :type cl:float
    :initform 0.0)
   (theta
    :reader theta
    :initarg :theta
    :type cl:float
    :initform 0.0)
   (delta
    :reader delta
    :initarg :delta
    :type cl:float
    :initform 0.0)
   (vMax
    :reader vMax
    :initarg :vMax
    :type cl:float
    :initform 0.0)
   (k1
    :reader k1
    :initarg :k1
    :type cl:float
    :initform 0.0)
   (k2
    :reader k2
    :initarg :k2
    :type cl:float
    :initform 0.0))
)

(cl:defclass EgoGoal (<EgoGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <EgoGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'EgoGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name model_predictive_navigation-msg:<EgoGoal> is deprecated: use model_predictive_navigation-msg:EgoGoal instead.")))

(cl:ensure-generic-function 'r-val :lambda-list '(m))
(cl:defmethod r-val ((m <EgoGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader model_predictive_navigation-msg:r-val is deprecated.  Use model_predictive_navigation-msg:r instead.")
  (r m))

(cl:ensure-generic-function 'theta-val :lambda-list '(m))
(cl:defmethod theta-val ((m <EgoGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader model_predictive_navigation-msg:theta-val is deprecated.  Use model_predictive_navigation-msg:theta instead.")
  (theta m))

(cl:ensure-generic-function 'delta-val :lambda-list '(m))
(cl:defmethod delta-val ((m <EgoGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader model_predictive_navigation-msg:delta-val is deprecated.  Use model_predictive_navigation-msg:delta instead.")
  (delta m))

(cl:ensure-generic-function 'vMax-val :lambda-list '(m))
(cl:defmethod vMax-val ((m <EgoGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader model_predictive_navigation-msg:vMax-val is deprecated.  Use model_predictive_navigation-msg:vMax instead.")
  (vMax m))

(cl:ensure-generic-function 'k1-val :lambda-list '(m))
(cl:defmethod k1-val ((m <EgoGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader model_predictive_navigation-msg:k1-val is deprecated.  Use model_predictive_navigation-msg:k1 instead.")
  (k1 m))

(cl:ensure-generic-function 'k2-val :lambda-list '(m))
(cl:defmethod k2-val ((m <EgoGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader model_predictive_navigation-msg:k2-val is deprecated.  Use model_predictive_navigation-msg:k2 instead.")
  (k2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <EgoGoal>) ostream)
  "Serializes a message object of type '<EgoGoal>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'r))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'theta))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'delta))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vMax))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'k1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'k2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <EgoGoal>) istream)
  "Deserializes a message object of type '<EgoGoal>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'r) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'theta) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'delta) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vMax) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'k1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'k2) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<EgoGoal>)))
  "Returns string type for a message object of type '<EgoGoal>"
  "model_predictive_navigation/EgoGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'EgoGoal)))
  "Returns string type for a message object of type 'EgoGoal"
  "model_predictive_navigation/EgoGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<EgoGoal>)))
  "Returns md5sum for a message object of type '<EgoGoal>"
  "a8793baddedab0f35d8e3e4d6b9fdc7b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'EgoGoal)))
  "Returns md5sum for a message object of type 'EgoGoal"
  "a8793baddedab0f35d8e3e4d6b9fdc7b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<EgoGoal>)))
  "Returns full string definition for message of type '<EgoGoal>"
  (cl:format cl:nil "float32 r~%float32 theta~%float32 delta~%float32 vMax~%float32 k1~%float32 k2~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'EgoGoal)))
  "Returns full string definition for message of type 'EgoGoal"
  (cl:format cl:nil "float32 r~%float32 theta~%float32 delta~%float32 vMax~%float32 k1~%float32 k2~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <EgoGoal>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <EgoGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'EgoGoal
    (cl:cons ':r (r msg))
    (cl:cons ':theta (theta msg))
    (cl:cons ':delta (delta msg))
    (cl:cons ':vMax (vMax msg))
    (cl:cons ':k1 (k1 msg))
    (cl:cons ':k2 (k2 msg))
))
