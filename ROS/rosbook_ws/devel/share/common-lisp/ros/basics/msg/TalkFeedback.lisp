; Auto-generated. Do not edit!


(cl:in-package basics-msg)


;//! \htmlinclude TalkFeedback.msg.html

(cl:defclass <TalkFeedback> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass TalkFeedback (<TalkFeedback>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TalkFeedback>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TalkFeedback)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name basics-msg:<TalkFeedback> is deprecated: use basics-msg:TalkFeedback instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TalkFeedback>) ostream)
  "Serializes a message object of type '<TalkFeedback>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TalkFeedback>) istream)
  "Deserializes a message object of type '<TalkFeedback>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TalkFeedback>)))
  "Returns string type for a message object of type '<TalkFeedback>"
  "basics/TalkFeedback")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TalkFeedback)))
  "Returns string type for a message object of type 'TalkFeedback"
  "basics/TalkFeedback")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TalkFeedback>)))
  "Returns md5sum for a message object of type '<TalkFeedback>"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TalkFeedback)))
  "Returns md5sum for a message object of type 'TalkFeedback"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TalkFeedback>)))
  "Returns full string definition for message of type '<TalkFeedback>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# No feedback content needed~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TalkFeedback)))
  "Returns full string definition for message of type 'TalkFeedback"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# No feedback content needed~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TalkFeedback>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TalkFeedback>))
  "Converts a ROS message object to a list"
  (cl:list 'TalkFeedback
))
