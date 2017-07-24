;; Auto-generated. Do not edit!


(when (boundp 'localization_gazebo::GpsReceiverData)
  (if (not (find-package "LOCALIZATION_GAZEBO"))
    (make-package "LOCALIZATION_GAZEBO"))
  (shadow 'GpsReceiverData (find-package "LOCALIZATION_GAZEBO")))
(unless (find-package "LOCALIZATION_GAZEBO::GPSRECEIVERDATA")
  (make-package "LOCALIZATION_GAZEBO::GPSRECEIVERDATA"))

(in-package "ROS")
;;//! \htmlinclude GpsReceiverData.msg.html


(defclass localization_gazebo::GpsReceiverData
  :super ros::object
  :slots (_t _utc _gps_quality _no_sats _hdop _latitude _longitude _altitude _heading _velocity _tm_x _tm_y ))

(defmethod localization_gazebo::GpsReceiverData
  (:init
   (&key
    ((:t __t) 0.0)
    ((:utc __utc) 0.0)
    ((:gps_quality __gps_quality) 0)
    ((:no_sats __no_sats) 0)
    ((:hdop __hdop) 0.0)
    ((:latitude __latitude) 0.0)
    ((:longitude __longitude) 0.0)
    ((:altitude __altitude) 0.0)
    ((:heading __heading) 0.0)
    ((:velocity __velocity) 0.0)
    ((:tm_x __tm_x) 0.0)
    ((:tm_y __tm_y) 0.0)
    )
   (send-super :init)
   (setq _t (float __t))
   (setq _utc (float __utc))
   (setq _gps_quality (round __gps_quality))
   (setq _no_sats (round __no_sats))
   (setq _hdop (float __hdop))
   (setq _latitude (float __latitude))
   (setq _longitude (float __longitude))
   (setq _altitude (float __altitude))
   (setq _heading (float __heading))
   (setq _velocity (float __velocity))
   (setq _tm_x (float __tm_x))
   (setq _tm_y (float __tm_y))
   self)
  (:t
   (&optional __t)
   (if __t (setq _t __t)) _t)
  (:utc
   (&optional __utc)
   (if __utc (setq _utc __utc)) _utc)
  (:gps_quality
   (&optional __gps_quality)
   (if __gps_quality (setq _gps_quality __gps_quality)) _gps_quality)
  (:no_sats
   (&optional __no_sats)
   (if __no_sats (setq _no_sats __no_sats)) _no_sats)
  (:hdop
   (&optional __hdop)
   (if __hdop (setq _hdop __hdop)) _hdop)
  (:latitude
   (&optional __latitude)
   (if __latitude (setq _latitude __latitude)) _latitude)
  (:longitude
   (&optional __longitude)
   (if __longitude (setq _longitude __longitude)) _longitude)
  (:altitude
   (&optional __altitude)
   (if __altitude (setq _altitude __altitude)) _altitude)
  (:heading
   (&optional __heading)
   (if __heading (setq _heading __heading)) _heading)
  (:velocity
   (&optional __velocity)
   (if __velocity (setq _velocity __velocity)) _velocity)
  (:tm_x
   (&optional __tm_x)
   (if __tm_x (setq _tm_x __tm_x)) _tm_x)
  (:tm_y
   (&optional __tm_y)
   (if __tm_y (setq _tm_y __tm_y)) _tm_y)
  (:serialization-length
   ()
   (+
    ;; float64 _t
    8
    ;; float64 _utc
    8
    ;; int32 _gps_quality
    4
    ;; int32 _no_sats
    4
    ;; float64 _hdop
    8
    ;; float64 _latitude
    8
    ;; float64 _longitude
    8
    ;; float64 _altitude
    8
    ;; float64 _heading
    8
    ;; float64 _velocity
    8
    ;; float64 _tm_x
    8
    ;; float64 _tm_y
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _t
       (sys::poke _t (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _utc
       (sys::poke _utc (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _gps_quality
       (write-long _gps_quality s)
     ;; int32 _no_sats
       (write-long _no_sats s)
     ;; float64 _hdop
       (sys::poke _hdop (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _latitude
       (sys::poke _latitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _longitude
       (sys::poke _longitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _altitude
       (sys::poke _altitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _heading
       (sys::poke _heading (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velocity
       (sys::poke _velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _tm_x
       (sys::poke _tm_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _tm_y
       (sys::poke _tm_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _t
     (setq _t (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _utc
     (setq _utc (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _gps_quality
     (setq _gps_quality (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _no_sats
     (setq _no_sats (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _hdop
     (setq _hdop (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _latitude
     (setq _latitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _longitude
     (setq _longitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _altitude
     (setq _altitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _heading
     (setq _heading (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velocity
     (setq _velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _tm_x
     (setq _tm_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _tm_y
     (setq _tm_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get localization_gazebo::GpsReceiverData :md5sum-) "6fcd8b41f0982f00b09b9c6b9702d7ca")
(setf (get localization_gazebo::GpsReceiverData :datatype-) "localization_gazebo/GpsReceiverData")
(setf (get localization_gazebo::GpsReceiverData :definition-)
      "float64 t
float64 utc
int32 gps_quality
int32 no_sats
float64 hdop
float64 latitude
float64 longitude
float64 altitude
float64 heading
float64 velocity
float64 tm_x
float64 tm_y

")



(provide :localization_gazebo/GpsReceiverData "6fcd8b41f0982f00b09b9c6b9702d7ca")


