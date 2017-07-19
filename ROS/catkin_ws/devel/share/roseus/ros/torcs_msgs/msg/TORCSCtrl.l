;; Auto-generated. Do not edit!


(when (boundp 'torcs_msgs::TORCSCtrl)
  (if (not (find-package "TORCS_MSGS"))
    (make-package "TORCS_MSGS"))
  (shadow 'TORCSCtrl (find-package "TORCS_MSGS")))
(unless (find-package "TORCS_MSGS::TORCSCTRL")
  (make-package "TORCS_MSGS::TORCSCTRL"))

(in-package "ROS")
;;//! \htmlinclude TORCSCtrl.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass torcs_msgs::TORCSCtrl
  :super ros::object
  :slots (_header _accel _brake _clutch _gear _steering _focus _meta ))

(defmethod torcs_msgs::TORCSCtrl
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:accel __accel) 0.0)
    ((:brake __brake) 0.0)
    ((:clutch __clutch) 0.0)
    ((:gear __gear) 0)
    ((:steering __steering) 0.0)
    ((:focus __focus) 0.0)
    ((:meta __meta) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _accel (float __accel))
   (setq _brake (float __brake))
   (setq _clutch (float __clutch))
   (setq _gear (round __gear))
   (setq _steering (float __steering))
   (setq _focus (float __focus))
   (setq _meta (round __meta))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:accel
   (&optional __accel)
   (if __accel (setq _accel __accel)) _accel)
  (:brake
   (&optional __brake)
   (if __brake (setq _brake __brake)) _brake)
  (:clutch
   (&optional __clutch)
   (if __clutch (setq _clutch __clutch)) _clutch)
  (:gear
   (&optional __gear)
   (if __gear (setq _gear __gear)) _gear)
  (:steering
   (&optional __steering)
   (if __steering (setq _steering __steering)) _steering)
  (:focus
   (&optional __focus)
   (if __focus (setq _focus __focus)) _focus)
  (:meta
   (&optional __meta)
   (if __meta (setq _meta __meta)) _meta)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _accel
    8
    ;; float64 _brake
    8
    ;; float64 _clutch
    8
    ;; uint8 _gear
    1
    ;; float64 _steering
    8
    ;; float64 _focus
    8
    ;; uint8 _meta
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _accel
       (sys::poke _accel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _brake
       (sys::poke _brake (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _clutch
       (sys::poke _clutch (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint8 _gear
       (write-byte _gear s)
     ;; float64 _steering
       (sys::poke _steering (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _focus
       (sys::poke _focus (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint8 _meta
       (write-byte _meta s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _accel
     (setq _accel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _brake
     (setq _brake (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _clutch
     (setq _clutch (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint8 _gear
     (setq _gear (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float64 _steering
     (setq _steering (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _focus
     (setq _focus (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint8 _meta
     (setq _meta (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get torcs_msgs::TORCSCtrl :md5sum-) "4848a66993e5bb22e0199af44ab1d070")
(setf (get torcs_msgs::TORCSCtrl :datatype-) "torcs_msgs/TORCSCtrl")
(setf (get torcs_msgs::TORCSCtrl :definition-)
      "Header header
# Virtual gas pedal (0 means no gas, 1 full gas)
float64 accel
# Virtual brake pedal (0 means no brake, 1 full brake)
float64 brake
# Virtual clutch pedal (0 means no clutch, 1 full clutch)
float64 clutch
# Gear value: -1,0,1,...,6 where -1 means backwards driving and 0 means idle
uint8 gear
# Steering value: -1 and +1 means respectively full right and
# left, that corresponds to an angle of 0.366519 rad
float64 steering
# Focus direction for the focus sensors in degrees. Currently unused
float64 focus
# This is meta-control command: 0 do nothing, 1 ask compe-
# tition server to restart the race. Currently unused
uint8 meta

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

")



(provide :torcs_msgs/TORCSCtrl "4848a66993e5bb22e0199af44ab1d070")


