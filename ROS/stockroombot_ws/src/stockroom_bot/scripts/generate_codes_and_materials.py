#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> ROS programming, ALVAR 표지태그의 영상과 재료 스크립트 파일을 생성하는 코드
'''
import os

for i in xrange(0, 12):
	# 해당패키지에서 createMarker 프로그램을 실행해서 지정된 숫자를 부호화한 PNG 영상파일을 생성한다
	os.system("rosrun ar_track_alvar createMarker {0}".format(i))
	fn = "MarkerData_{0}.png".format(i)

	# ImageMagick 유틸리티로 인식을 개선시키기 위해 하얀 테두리를 추가한다
	os.system("convert {0} -bordercolor white -border 100x100 {0}".format(fn))

	# ALVAR 텍스처영상에 참조를 포함하는 재료스크립트를 생성한다
	with open("product_{0}.material".format(i), 'w') as f:
		f.write("""
material product_%d {
receive_shadows on
technique {
	pass {
		ambient 1.0 1.0 1.0 1.0
		diffuse 1.0 1.0 1.0 1.0
		specular 0.5 0.5 0.5 1.0
		lighting on
		shading gouraud
		texture_unit { texture MarkerData_%d.png }
		}
	}
}
""" % (i, i))
