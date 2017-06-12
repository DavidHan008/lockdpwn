#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 비주얼컴퓨팅, 최종 프로젝트 
'''
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import tensorflow as tf
import scipy.misc
import scipy.io
import random
import cv2
from PIL import Image, ImageDraw
import math
import os

orig_img = cv2.imread('./FudanPed00005.png', 0)
cols, rows = orig_img.shape

dic = {}  # 딕서녀리 생성
num_images = 0 # 전체 trim 된 이미지의 갯수

# 이미지 사이즈를 70x134로 리사이징하는 함수
def im_resize_to_orig(img):
    thumbnail = cv2.resize(img, (70, 134))
    return thumbnail


# 이미지를 자르는 함수
def im_trim(img, w, h, prefix, trim_prop):
    global num_images, dic
    iy, ix = img.shape
    xcnt = 0
    ycnt = 0

    # 이미지를 w x h 만큼 잘라서 하나하나씩 저장한다
    for y in range(0, iy, int(h*trim_prop)):
        ycnt += 1
        xcnt = 0
        for x in range(0, ix, int(w*trim_prop)):
            img_trim = img[y:y+h, x:x+w]
            
            # 이미지 크기가 70 x 134 보다 작으면 강제로 70x134로 리사이징 후 저장한다
            cols, rows = img_trim.shape
            if(cols < 134 or rows < 70):
                img_trim = im_resize_to_orig(img_trim)

            dic[num_images] = [prefix, xcnt, ycnt]  # 이미지 이름과 정보를 저장한다. keypoint!

            cv2.imwrite('./cropped_image_forVC/'+ str(num_images) + '.jpg', img_trim)
            xcnt += 1
            num_images += 1

    print("[*] Trim Done!")



# 이미지 크기를 줄이는 함수
def im_resize(img, prop):
    iy, ix = img.shape
    thumbnail = cv2.resize(img, (int(ix/prop), int(iy/prop)))
    newiy, newix = thumbnail.shape

    # 리사이징한 이미지 rows가 70보다 작으면 trim을 할 수 없으므로 skip한다
    if(newix < 70):
        return False

    print("orig : (", iy, ",", ix, ") ==> (", newiy, ",", newix ,")")

    cv2.imwrite('./resize_image_forVC/' + '_' + str(prop) +'.jpg', thumbnail)

    print("[*] Resize Done!")
    return True


# 이미저 전체 크기가 70x134보다 작으면 리사이징할 필요가 없으므로 아래 변수를 사용해 실제 리사이징된 이미지를 카운트한다
num_resize_img = 0

# 이미지를 리사이징한다. 두번째파라미터는 1/n
for i in range(2, 11):
    isOK = im_resize(orig_img, i)
    if isOK == True:
        num_resize_img += 1


img_1 = orig_img

# img_1, img_2 같은 변수를 loop 안에서 다루기 위해 namespace 변수를 추가한다
namespace = globals()
for i in range(2, num_resize_img+2):
    namespace['img_%d' % i] = cv2.imread('./resize_image_forVC/_'+str(i) +'.jpg',0)

# 이미지를 잘라서 저장한다
for i in range(1, num_resize_img+2):
    im_trim(namespace['img_%d' %i] , 70, 134, i, 0.25)









#-------------------------------------------------------------
# 결과적으로 trim된 이미지들을 불러온다
test_images = []

for num in range(0, num_images):
    test_images.append(scipy.misc.imread('./cropped_image_forVC/'+ str(num)+'.jpg', flatten=True))


# Image 데이터를 numpy 데이터로 수정한다
test_images = np.array(test_images)
test_images = test_images.reshape(num_images, 9380) # (70,134) ==> (9380,1)
test_images = test_images / 255.   # 데이터 정규화  0~1




#-----------------------------------------------------------------
# Tensorflow 코드
#-----------------------------------------------------------------
x = tf.placeholder("float32", [None, 9380]) # mnist data image of shape 134 x 70
y = tf.placeholder("float32", [None, 2]) 

W = tf.Variable(tf.zeros([9380,2]))
b = tf.Variable(tf.zeros([2]))


# 1st conv layer ----------------------
W_conv1 = weight_variable([8,8,1,32])
b_conv1 = bias_variable([32])

# -1 : 아직 디멘젼이 결정되지 않았다
# 1 : 흑백이므로 1을 삽입한다. 칼라이면 3을 삽입한다
# x은 9380x1인데 134x70x1로 행렬을 다시 만들어준다
x_image = tf.reshape(x, [-1, 134, 70, 1])

# y = x*w + b에 ReLU를 적용한다
# (134, 70) ==> (134, 70)
h_conv1 = tf.nn.relu(conv2d_same(x_image, W_conv1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1)
# (134, 70) ==> (67, 35)



# 2nd conv layer -----------------------
W_conv2 = weight_variable([4,4,32,64])
b_conv2 = bias_variable([64])

# (67, 35) ==> (64, 32)
h_conv2 = tf.nn.relu(conv2d_valid(h_pool1, W_conv2) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2)
# (64, 32) ==> (32, 16)



# 1st fully connected layer -----------------------
W_fc1 = weight_variable([32*16*64, 5000])
b_fc1 = bias_variable([5000])

h_pool2_flat = tf.reshape(h_pool2, [-1, 32*16*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)
# 위 연산으로 1000x1의 벡터가 생성된다



# Dropout ------------------------
keep_prob = tf.placeholder(tf.float32)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)



# 2nd fully connected layer --------------
W_fc2 = weight_variable([5000, 2])
b_fc2 = bias_variable([2])
y_conv = tf.matmul(h_fc1_drop, W_fc2) + b_fc2


# learning_rate 잘 설정하는게 중요하다.. 0.1로 하니 전혀 변화가 없었다
learning_rate = 1e-3


cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y, logits=y_conv))
optimizer = tf.train.AdamOptimizer(learning_rate).minimize(cost)


init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)


# 정답률을 계산한다  y_conv  vs  y
correct_prediction = tf.equal(tf.argmax(y_conv, 1), tf.argmax(y, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))




#----------------------------------------------
saver = tf.train.Saver()
sess = tf.Session()
saver.restore(sess, 'd:/edward/hangeul3')


# 테스트 데이터를 넣어 정확도를 계산한다
test_accuracy = sess.run(accuracy,feed_dict={x: test_images, y: test_labels, keep_prob: 1.0})
print('test accuracy', test_accuracy)





#----------------------------------------------
# 임의의 얼굴 하나를 출력한 다음 맞혀보는 코드 
r = random.randint(0, _num_examples -1)
print ("Label: ", sess.run(tf.argmax(test_labels[r:r+1], 1)))
print ("Prediction: ", sess.run(tf.argmax(y_conv, 1), {x:test_images[r:r+1], keep_prob:1.0}))

plt.imshow(test_images[r:r+1].reshape(134, 70), cmap='gray', interpolation='nearest')
plt.show()


#----------------------------------------------
orig_img = cv2.imread('./FudanPed00005.png', 0)
skip_count = 0

for i in range(0, num_images):
    flag = sess.run(tf.argmax(y_conv, 1), {x:test_images[i:i+1], keep_prob:1.0})

    if flag[0] ==0:
        skip_count += 1

        prop, xcnt, ycnt = dic[i]
    
        point_box = (int(prop*70*xcnt*0.25), int(prop*(ycnt-1)*134*0.25))
        
        end_x = point_box[0] + prop*70 
        end_y = point_box[1] +  prop*134

        if end_x > rows:
            end_x = rows
        if end_y > cols:
            end_y = cols

        end_box = (int(end_x), int(end_y))
        if skip_count == 3:
            skip_count = 0
            cv2.rectangle(orig_img, point_box , end_box ,(0,255,0),3)
