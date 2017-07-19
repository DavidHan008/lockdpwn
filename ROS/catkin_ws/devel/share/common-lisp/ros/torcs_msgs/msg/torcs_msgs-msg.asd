
(cl:in-package :asdf)

(defsystem "torcs_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "TORCSCtrl" :depends-on ("_package_TORCSCtrl"))
    (:file "_package_TORCSCtrl" :depends-on ("_package"))
    (:file "TORCSSensors" :depends-on ("_package_TORCSSensors"))
    (:file "_package_TORCSSensors" :depends-on ("_package"))
  ))