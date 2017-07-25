;; Auto-generated. Do not edit!


(when (boundp 'motion_planner_gazebo::srvParkingCmd)
  (if (not (find-package "MOTION_PLANNER_GAZEBO"))
    (make-package "MOTION_PLANNER_GAZEBO"))
  (shadow 'srvParkingCmd (find-package "MOTION_PLANNER_GAZEBO")))
(unless (find-package "MOTION_PLANNER_GAZEBO::SRVPARKINGCMD")
  (make-package "MOTION_PLANNER_GAZEBO::SRVPARKINGCMD"))
(unless (find-package "MOTION_PLANNER_GAZEBO::SRVPARKINGCMDREQUEST")
  (make-package "MOTION_PLANNER_GAZEBO::SRVPARKINGCMDREQUEST"))
(unless (find-package "MOTION_PLANNER_GAZEBO::SRVPARKINGCMDRESPONSE")
  (make-package "MOTION_PLANNER_GAZEBO::SRVPARKINGCMDRESPONSE"))

(in-package "ROS")





(defclass motion_planner_gazebo::srvParkingCmdRequest
  :super ros::object
  :slots (_x _y _theta _mode ))

(defmethod motion_planner_gazebo::srvParkingCmdRequest
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:theta __theta) 0.0)
    ((:mode __mode) 0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _theta (float __theta))
   (setq _mode (round __mode))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _theta
    8
    ;; int64 _mode
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int64 _mode
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _mode (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _mode) (= (length (_mode . bv)) 2)) ;; bignum
              (write-long (ash (elt (_mode . bv) 0) 0) s)
              (write-long (ash (elt (_mode . bv) 1) -1) s))
             ((and (class _mode) (= (length (_mode . bv)) 1)) ;; big1
              (write-long (elt (_mode . bv) 0) s)
              (write-long (if (>= _mode 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _mode s)(write-long (if (>= _mode 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _theta
     (setq _theta (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int64 _mode
#+(or :alpha :irix6 :x86_64)
      (setf _mode (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _mode (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(defclass motion_planner_gazebo::srvParkingCmdResponse
  :super ros::object
  :slots (_result ))

(defmethod motion_planner_gazebo::srvParkingCmdResponse
  (:init
   (&key
    ((:result __result) 0)
    )
   (send-super :init)
   (setq _result (round __result))
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; int64 _result
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _result
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _result (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _result) (= (length (_result . bv)) 2)) ;; bignum
              (write-long (ash (elt (_result . bv) 0) 0) s)
              (write-long (ash (elt (_result . bv) 1) -1) s))
             ((and (class _result) (= (length (_result . bv)) 1)) ;; big1
              (write-long (elt (_result . bv) 0) s)
              (write-long (if (>= _result 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _result s)(write-long (if (>= _result 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _result
#+(or :alpha :irix6 :x86_64)
      (setf _result (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _result (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(defclass motion_planner_gazebo::srvParkingCmd
  :super ros::object
  :slots ())

(setf (get motion_planner_gazebo::srvParkingCmd :md5sum-) "6f559bfa1f52d42afbe43f629231fbe9")
(setf (get motion_planner_gazebo::srvParkingCmd :datatype-) "motion_planner_gazebo/srvParkingCmd")
(setf (get motion_planner_gazebo::srvParkingCmd :request) motion_planner_gazebo::srvParkingCmdRequest)
(setf (get motion_planner_gazebo::srvParkingCmd :response) motion_planner_gazebo::srvParkingCmdResponse)

(defmethod motion_planner_gazebo::srvParkingCmdRequest
  (:response () (instance motion_planner_gazebo::srvParkingCmdResponse :init)))

(setf (get motion_planner_gazebo::srvParkingCmdRequest :md5sum-) "6f559bfa1f52d42afbe43f629231fbe9")
(setf (get motion_planner_gazebo::srvParkingCmdRequest :datatype-) "motion_planner_gazebo/srvParkingCmdRequest")
(setf (get motion_planner_gazebo::srvParkingCmdRequest :definition-)
      "float64 x
float64 y
float64 theta
int64 mode
---
int64 result


")

(setf (get motion_planner_gazebo::srvParkingCmdResponse :md5sum-) "6f559bfa1f52d42afbe43f629231fbe9")
(setf (get motion_planner_gazebo::srvParkingCmdResponse :datatype-) "motion_planner_gazebo/srvParkingCmdResponse")
(setf (get motion_planner_gazebo::srvParkingCmdResponse :definition-)
      "float64 x
float64 y
float64 theta
int64 mode
---
int64 result


")



(provide :motion_planner_gazebo/srvParkingCmd "6f559bfa1f52d42afbe43f629231fbe9")


