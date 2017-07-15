;; Auto-generated. Do not edit!


(when (boundp 'torcs_msgs::TORCSSensors)
  (if (not (find-package "TORCS_MSGS"))
    (make-package "TORCS_MSGS"))
  (shadow 'TORCSSensors (find-package "TORCS_MSGS")))
(unless (find-package "TORCS_MSGS::TORCSSENSORS")
  (make-package "TORCS_MSGS::TORCSSENSORS"))

(in-package "ROS")
;;//! \htmlinclude TORCSSensors.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass torcs_msgs::TORCSSensors
  :super ros::object
  :slots (_header _angle _currentLapTime _damage _distFromStart _distRaced _fuel _gear _lastLapTime _racePos _rpm _trackPos _wheelSpinVel _z ))

(defmethod torcs_msgs::TORCSSensors
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:angle __angle) 0.0)
    ((:currentLapTime __currentLapTime) 0.0)
    ((:damage __damage) 0.0)
    ((:distFromStart __distFromStart) 0.0)
    ((:distRaced __distRaced) 0.0)
    ((:fuel __fuel) 0.0)
    ((:gear __gear) 0)
    ((:lastLapTime __lastLapTime) 0.0)
    ((:racePos __racePos) 0)
    ((:rpm __rpm) 0.0)
    ((:trackPos __trackPos) 0.0)
    ((:wheelSpinVel __wheelSpinVel) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:z __z) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _angle (float __angle))
   (setq _currentLapTime (float __currentLapTime))
   (setq _damage (float __damage))
   (setq _distFromStart (float __distFromStart))
   (setq _distRaced (float __distRaced))
   (setq _fuel (float __fuel))
   (setq _gear (round __gear))
   (setq _lastLapTime (float __lastLapTime))
   (setq _racePos (round __racePos))
   (setq _rpm (float __rpm))
   (setq _trackPos (float __trackPos))
   (setq _wheelSpinVel __wheelSpinVel)
   (setq _z (float __z))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:currentLapTime
   (&optional __currentLapTime)
   (if __currentLapTime (setq _currentLapTime __currentLapTime)) _currentLapTime)
  (:damage
   (&optional __damage)
   (if __damage (setq _damage __damage)) _damage)
  (:distFromStart
   (&optional __distFromStart)
   (if __distFromStart (setq _distFromStart __distFromStart)) _distFromStart)
  (:distRaced
   (&optional __distRaced)
   (if __distRaced (setq _distRaced __distRaced)) _distRaced)
  (:fuel
   (&optional __fuel)
   (if __fuel (setq _fuel __fuel)) _fuel)
  (:gear
   (&optional __gear)
   (if __gear (setq _gear __gear)) _gear)
  (:lastLapTime
   (&optional __lastLapTime)
   (if __lastLapTime (setq _lastLapTime __lastLapTime)) _lastLapTime)
  (:racePos
   (&optional __racePos)
   (if __racePos (setq _racePos __racePos)) _racePos)
  (:rpm
   (&optional __rpm)
   (if __rpm (setq _rpm __rpm)) _rpm)
  (:trackPos
   (&optional __trackPos)
   (if __trackPos (setq _trackPos __trackPos)) _trackPos)
  (:wheelSpinVel
   (&optional __wheelSpinVel)
   (if __wheelSpinVel (setq _wheelSpinVel __wheelSpinVel)) _wheelSpinVel)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _angle
    8
    ;; float64 _currentLapTime
    8
    ;; float64 _damage
    8
    ;; float64 _distFromStart
    8
    ;; float64 _distRaced
    8
    ;; float64 _fuel
    8
    ;; uint8 _gear
    1
    ;; float64 _lastLapTime
    8
    ;; uint8 _racePos
    1
    ;; float64 _rpm
    8
    ;; float64 _trackPos
    8
    ;; float64[] _wheelSpinVel
    (* 8    (length _wheelSpinVel)) 4
    ;; float64 _z
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _angle
       (sys::poke _angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _currentLapTime
       (sys::poke _currentLapTime (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _damage
       (sys::poke _damage (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _distFromStart
       (sys::poke _distFromStart (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _distRaced
       (sys::poke _distRaced (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fuel
       (sys::poke _fuel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint8 _gear
       (write-byte _gear s)
     ;; float64 _lastLapTime
       (sys::poke _lastLapTime (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint8 _racePos
       (write-byte _racePos s)
     ;; float64 _rpm
       (sys::poke _rpm (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _trackPos
       (sys::poke _trackPos (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64[] _wheelSpinVel
     (write-long (length _wheelSpinVel) s)
     (dotimes (i (length _wheelSpinVel))
       (sys::poke (elt _wheelSpinVel i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _angle
     (setq _angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _currentLapTime
     (setq _currentLapTime (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _damage
     (setq _damage (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _distFromStart
     (setq _distFromStart (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _distRaced
     (setq _distRaced (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fuel
     (setq _fuel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint8 _gear
     (setq _gear (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float64 _lastLapTime
     (setq _lastLapTime (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint8 _racePos
     (setq _racePos (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float64 _rpm
     (setq _rpm (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _trackPos
     (setq _trackPos (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64[] _wheelSpinVel
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _wheelSpinVel (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _wheelSpinVel i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get torcs_msgs::TORCSSensors :md5sum-) "a1fc40496a3236414af873ea65b87df2")
(setf (get torcs_msgs::TORCSSensors :datatype-) "torcs_msgs/TORCSSensors")
(setf (get torcs_msgs::TORCSSensors :definition-)
      "std_msgs/Header header
# Angle between the car direction and the direction of the track axis [-PI,PI] in rad
float64 angle
# Time elapsed during current lap in seconds
float64 currentLapTime
# Current damage of the car (the higher is the value the higher is the damage)
float64 damage
# Distance of the car from the start line along the track line
float64 distFromStart
# Distance covered by the car from the beginning of the race
float64 distRaced
# Current fuel level
float64 fuel
# Current gear: -1 is reverse, 0 is neutral and the gear from 1 to 6
uint8 gear
# Time to complete the last lap
float64 lastLapTime
# Position in the race with respect to other cars
uint8 racePos
# Number of rotation per minute of the car engine
float64 rpm
# Distance between the car and the track axis. The value is
# normalized w.r.t to the track width: it is 0 when car is on
# the axis, -1 when the car is on the right edge of the track
# and +1 when it is on the left edge of the car. Values greater
# than 1 or smaller than -1 mean that the car is outside of
# the track.
float64 trackPos
# Vector of 4 sensors representing the rotation speed of
# wheels in radians
float64[] wheelSpinVel
# Distance of the car mass center from the surface of the track
# along the Z axis in meters
float64 z

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



(provide :torcs_msgs/TORCSSensors "a1fc40496a3236414af873ea65b87df2")


