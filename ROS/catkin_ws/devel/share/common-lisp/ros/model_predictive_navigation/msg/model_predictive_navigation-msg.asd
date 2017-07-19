
(cl:in-package :asdf)

(defsystem "model_predictive_navigation-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "EgoGoal" :depends-on ("_package_EgoGoal"))
    (:file "_package_EgoGoal" :depends-on ("_package"))
  ))