
(cl:in-package :asdf)

(defsystem "car_can-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "CarCanData" :depends-on ("_package_CarCanData"))
    (:file "_package_CarCanData" :depends-on ("_package"))
  ))