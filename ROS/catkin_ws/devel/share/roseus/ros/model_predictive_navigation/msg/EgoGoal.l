;; Auto-generated. Do not edit!


(when (boundp 'model_predictive_navigation::EgoGoal)
  (if (not (find-package "MODEL_PREDICTIVE_NAVIGATION"))
    (make-package "MODEL_PREDICTIVE_NAVIGATION"))
  (shadow 'EgoGoal (find-package "MODEL_PREDICTIVE_NAVIGATION")))
(unless (find-package "MODEL_PREDICTIVE_NAVIGATION::EGOGOAL")
  (make-package "MODEL_PREDICTIVE_NAVIGATION::EGOGOAL"))

(in-package "ROS")
;;//! \htmlinclude EgoGoal.msg.html


(defclass model_predictive_navigation::EgoGoal
  :super ros::object
  :slots (_r _theta _delta _vMax _k1 _k2 ))

(defmethod model_predictive_navigation::EgoGoal
  (:init
   (&key
    ((:r __r) 0.0)
    ((:theta __theta) 0.0)
    ((:delta __delta) 0.0)
    ((:vMax __vMax) 0.0)
    ((:k1 __k1) 0.0)
    ((:k2 __k2) 0.0)
    )
   (send-super :init)
   (setq _r (float __r))
   (setq _theta (float __theta))
   (setq _delta (float __delta))
   (setq _vMax (float __vMax))
   (setq _k1 (float __k1))
   (setq _k2 (float __k2))
   self)
  (:r
   (&optional __r)
   (if __r (setq _r __r)) _r)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:delta
   (&optional __delta)
   (if __delta (setq _delta __delta)) _delta)
  (:vMax
   (&optional __vMax)
   (if __vMax (setq _vMax __vMax)) _vMax)
  (:k1
   (&optional __k1)
   (if __k1 (setq _k1 __k1)) _k1)
  (:k2
   (&optional __k2)
   (if __k2 (setq _k2 __k2)) _k2)
  (:serialization-length
   ()
   (+
    ;; float32 _r
    4
    ;; float32 _theta
    4
    ;; float32 _delta
    4
    ;; float32 _vMax
    4
    ;; float32 _k1
    4
    ;; float32 _k2
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _r
       (sys::poke _r (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _delta
       (sys::poke _delta (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vMax
       (sys::poke _vMax (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _k1
       (sys::poke _k1 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _k2
       (sys::poke _k2 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _r
     (setq _r (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _theta
     (setq _theta (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _delta
     (setq _delta (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vMax
     (setq _vMax (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _k1
     (setq _k1 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _k2
     (setq _k2 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get model_predictive_navigation::EgoGoal :md5sum-) "a8793baddedab0f35d8e3e4d6b9fdc7b")
(setf (get model_predictive_navigation::EgoGoal :datatype-) "model_predictive_navigation/EgoGoal")
(setf (get model_predictive_navigation::EgoGoal :definition-)
      "float32 r
float32 theta
float32 delta
float32 vMax
float32 k1
float32 k2
")



(provide :model_predictive_navigation/EgoGoal "a8793baddedab0f35d8e3e4d6b9fdc7b")


