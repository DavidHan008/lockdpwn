
(cl:in-package :asdf)

(defsystem "rndf_manager-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "srvHeightMap" :depends-on ("_package_srvHeightMap"))
    (:file "_package_srvHeightMap" :depends-on ("_package"))
  ))