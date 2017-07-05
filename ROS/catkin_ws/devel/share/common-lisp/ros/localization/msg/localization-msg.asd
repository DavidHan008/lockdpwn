
(cl:in-package :asdf)

(defsystem "localization-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "LocalizationData" :depends-on ("_package_LocalizationData"))
    (:file "_package_LocalizationData" :depends-on ("_package"))
    (:file "GpsReceiverData" :depends-on ("_package_GpsReceiverData"))
    (:file "_package_GpsReceiverData" :depends-on ("_package"))
    (:file "CarCanData" :depends-on ("_package_CarCanData"))
    (:file "_package_CarCanData" :depends-on ("_package"))
  ))