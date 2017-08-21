;; Auto-generated. Do not edit!


(when (boundp 'localization::CarCanData)
  (if (not (find-package "LOCALIZATION"))
    (make-package "LOCALIZATION"))
  (shadow 'CarCanData (find-package "LOCALIZATION")))
(unless (find-package "LOCALIZATION::CARCANDATA")
  (make-package "LOCALIZATION::CARCANDATA"))

(in-package "ROS")
;;//! \htmlinclude CarCanData.msg.html


(defclass localization::CarCanData
  :super ros::object
  :slots (_t _gyro _accl _magnet _sas _obdVel1 _obdVel2 ))

(defmethod localization::CarCanData
  (:init
   (&key
    ((:t __t) 0.0)
    ((:gyro __gyro) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:accl __accl) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:magnet __magnet) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:sas __sas) 0.0)
    ((:obdVel1 __obdVel1) 0.0)
    ((:obdVel2 __obdVel2) 0.0)
    )
   (send-super :init)
   (setq _t (float __t))
   (setq _gyro __gyro)
   (setq _accl __accl)
   (setq _magnet __magnet)
   (setq _sas (float __sas))
   (setq _obdVel1 (float __obdVel1))
   (setq _obdVel2 (float __obdVel2))
   self)
  (:t
   (&optional __t)
   (if __t (setq _t __t)) _t)
  (:gyro
   (&optional __gyro)
   (if __gyro (setq _gyro __gyro)) _gyro)
  (:accl
   (&optional __accl)
   (if __accl (setq _accl __accl)) _accl)
  (:magnet
   (&optional __magnet)
   (if __magnet (setq _magnet __magnet)) _magnet)
  (:sas
   (&optional __sas)
   (if __sas (setq _sas __sas)) _sas)
  (:obdVel1
   (&optional __obdVel1)
   (if __obdVel1 (setq _obdVel1 __obdVel1)) _obdVel1)
  (:obdVel2
   (&optional __obdVel2)
   (if __obdVel2 (setq _obdVel2 __obdVel2)) _obdVel2)
  (:serialization-length
   ()
   (+
    ;; float64 _t
    8
    ;; float64[3] _gyro
    (* 8    3)
    ;; float64[3] _accl
    (* 8    3)
    ;; float64[3] _magnet
    (* 8    3)
    ;; float64 _sas
    8
    ;; float64 _obdVel1
    8
    ;; float64 _obdVel2
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _t
       (sys::poke _t (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64[3] _gyro
     (dotimes (i 3)
       (sys::poke (elt _gyro i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _accl
     (dotimes (i 3)
       (sys::poke (elt _accl i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _magnet
     (dotimes (i 3)
       (sys::poke (elt _magnet i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64 _sas
       (sys::poke _sas (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _obdVel1
       (sys::poke _obdVel1 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _obdVel2
       (sys::poke _obdVel2 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _t
     (setq _t (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64[3] _gyro
   (dotimes (i (length _gyro))
     (setf (elt _gyro i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _accl
   (dotimes (i (length _accl))
     (setf (elt _accl i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _magnet
   (dotimes (i (length _magnet))
     (setf (elt _magnet i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64 _sas
     (setq _sas (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _obdVel1
     (setq _obdVel1 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _obdVel2
     (setq _obdVel2 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get localization::CarCanData :md5sum-) "aad0b4ce5de8f6b9c2d6a08270853f6e")
(setf (get localization::CarCanData :datatype-) "localization/CarCanData")
(setf (get localization::CarCanData :definition-)
      "float64 t
float64[3] gyro
float64[3] accl
float64[3] magnet
float64 sas
float64 obdVel1
float64 obdVel2

")



(provide :localization/CarCanData "aad0b4ce5de8f6b9c2d6a08270853f6e")


