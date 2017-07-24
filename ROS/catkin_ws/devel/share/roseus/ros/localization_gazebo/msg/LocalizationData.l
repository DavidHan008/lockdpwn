;; Auto-generated. Do not edit!


(when (boundp 'localization_gazebo::LocalizationData)
  (if (not (find-package "LOCALIZATION_GAZEBO"))
    (make-package "LOCALIZATION_GAZEBO"))
  (shadow 'LocalizationData (find-package "LOCALIZATION_GAZEBO")))
(unless (find-package "LOCALIZATION_GAZEBO::LOCALIZATIONDATA")
  (make-package "LOCALIZATION_GAZEBO::LOCALIZATIONDATA"))

(in-package "ROS")
;;//! \htmlinclude LocalizationData.msg.html


(defclass localization_gazebo::LocalizationData
  :super ros::object
  :slots (_heading _x _y _v ))

(defmethod localization_gazebo::LocalizationData
  (:init
   (&key
    ((:heading __heading) 0.0)
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:v __v) 0.0)
    )
   (send-super :init)
   (setq _heading (float __heading))
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _v (float __v))
   self)
  (:heading
   (&optional __heading)
   (if __heading (setq _heading __heading)) _heading)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:v
   (&optional __v)
   (if __v (setq _v __v)) _v)
  (:serialization-length
   ()
   (+
    ;; float64 _heading
    8
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _v
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _heading
       (sys::poke _heading (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _v
       (sys::poke _v (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _heading
     (setq _heading (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _v
     (setq _v (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get localization_gazebo::LocalizationData :md5sum-) "81dcd86073f3af8543535f8323fd4adc")
(setf (get localization_gazebo::LocalizationData :datatype-) "localization_gazebo/LocalizationData")
(setf (get localization_gazebo::LocalizationData :definition-)
      "float64 heading
float64 x
float64 y
float64 v

")



(provide :localization_gazebo/LocalizationData "81dcd86073f3af8543535f8323fd4adc")


