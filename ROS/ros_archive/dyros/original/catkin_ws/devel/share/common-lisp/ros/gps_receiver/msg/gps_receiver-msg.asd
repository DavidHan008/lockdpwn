
(cl:in-package :asdf)

(defsystem "gps_receiver-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "GpsReceiverData" :depends-on ("_package_GpsReceiverData"))
    (:file "_package_GpsReceiverData" :depends-on ("_package"))
  ))