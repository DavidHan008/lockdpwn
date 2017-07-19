;; Auto-generated. Do not edit!


(when (boundp 'motion_planner::srvHeightMap)
  (if (not (find-package "MOTION_PLANNER"))
    (make-package "MOTION_PLANNER"))
  (shadow 'srvHeightMap (find-package "MOTION_PLANNER")))
(unless (find-package "MOTION_PLANNER::SRVHEIGHTMAP")
  (make-package "MOTION_PLANNER::SRVHEIGHTMAP"))
(unless (find-package "MOTION_PLANNER::SRVHEIGHTMAPREQUEST")
  (make-package "MOTION_PLANNER::SRVHEIGHTMAPREQUEST"))
(unless (find-package "MOTION_PLANNER::SRVHEIGHTMAPRESPONSE")
  (make-package "MOTION_PLANNER::SRVHEIGHTMAPRESPONSE"))

(in-package "ROS")





(defclass motion_planner::srvHeightMapRequest
  :super ros::object
  :slots (_x _y _theta _mode ))

(defmethod motion_planner::srvHeightMapRequest
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

(defclass motion_planner::srvHeightMapResponse
  :super ros::object
  :slots (_result ))

(defmethod motion_planner::srvHeightMapResponse
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

(defclass motion_planner::srvHeightMap
  :super ros::object
  :slots ())

(setf (get motion_planner::srvHeightMap :md5sum-) "6f559bfa1f52d42afbe43f629231fbe9")
(setf (get motion_planner::srvHeightMap :datatype-) "motion_planner/srvHeightMap")
(setf (get motion_planner::srvHeightMap :request) motion_planner::srvHeightMapRequest)
(setf (get motion_planner::srvHeightMap :response) motion_planner::srvHeightMapResponse)

(defmethod motion_planner::srvHeightMapRequest
  (:response () (instance motion_planner::srvHeightMapResponse :init)))

(setf (get motion_planner::srvHeightMapRequest :md5sum-) "6f559bfa1f52d42afbe43f629231fbe9")
(setf (get motion_planner::srvHeightMapRequest :datatype-) "motion_planner/srvHeightMapRequest")
(setf (get motion_planner::srvHeightMapRequest :definition-)
      "float64 x
float64 y
float64 theta
int64 mode
---
int64 result


")

(setf (get motion_planner::srvHeightMapResponse :md5sum-) "6f559bfa1f52d42afbe43f629231fbe9")
(setf (get motion_planner::srvHeightMapResponse :datatype-) "motion_planner/srvHeightMapResponse")
(setf (get motion_planner::srvHeightMapResponse :definition-)
      "float64 x
float64 y
float64 theta
int64 mode
---
int64 result


")



(provide :motion_planner/srvHeightMap "6f559bfa1f52d42afbe43f629231fbe9")


