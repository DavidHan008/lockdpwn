import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
import scipy.misc
import scipy.io
import random

#-------------------------------------------------------------------------------
# train
train_images = []
tlabels = []

for num in range(1,701):
    train_images.append(scipy.misc.imread('train_image/train_'+ str(num)+'.bmp'))


with open("train_label.txt") as f:
    line = [line.rstrip() for line in f]
    tlabels.append(line)

train_images = np.array(train_images)
train_images = train_images.reshape(700, 2200, )

tlabels = np.array(tlabels)     # tlabels = (1,700)
tlabels = tlabels.reshape(700,1)

train_labels  = np.array(np.zeros(70000).reshape(700,100))
for num in range(0,700):
    train_labels[num][int(tlabels[num][0]) - 1] = 1

#-------------------------------------------------------------------------------
# test
test_images = []
testlabels = []

for num in range(1,701):
    test_images.append(scipy.misc.imread('test_image/test_'+ str(num)+'.bmp'))


with open("test_label.txt") as f:
    line = [line.rstrip() for line in f]
    testlabels.append(line)


test_images = np.array(test_images)
test_images = test_images.reshape(700, 2200, )

testlabels = np.array(testlabels)     # tlabels = (1,700)
testlabels = testlabels.reshape(700,1)

test_labels  = np.array(np.zeros(70000).reshape(700,100))
for num in range(0,700):
    test_labels[num][int(testlabels[num][0]) - 1] = 1


#-------------------------------------------------------------------------------
# train_image 배열 데이터를 0 ~ 1 사이로 정규화시키는 함수
def normalize(v):
    norm=np.linalg.norm(v)
    if norm==0: 
       return v
    return v/norm


train_images = normalize(train_images)
test_images = normalize(test_images)

_num_examples = 700
_index_in_epoch = 0
_images = train_images
_labels = train_labels
_epochs_completed = 0

def next_batch(batch_size):
    """Return the next `batch_size` examples from this data set."""
    global _index_in_epoch
    global _images
    global _labels
    global _epochs_completed

    start = _index_in_epoch
    _index_in_epoch += batch_size

    if _index_in_epoch > _num_examples:
      # Finished epoch
      _epochs_completed += 1

      # Shuffle the data
      perm = np.arange(_num_examples)
      np.random.shuffle(perm)
      _images = _images[perm]
      _labels = _labels[perm]

      # Start next epoch
      start = 0
      _index_in_epoch = batch_size
      assert batch_size <= _num_examples

    end = _index_in_epoch
    return _images[start:end], _labels[start:end]



# 가중치를 초기화하는 함수 (정규분포 stddev=0.1로 초기화한다)
def weight_variable(shape):
	initial = tf.truncated_normal(shape, stddev=0.1)
	return tf.Variable(initial)


# 바이어스를 초기화하는 함수 (0.1로 초기화한다)
def bias_variable(shape):
	initial = tf.constant(0.1, shape=shape)
	return tf.Variable(initial)


# 컨벌루션을 실행하는 함수
# padding = 'same' 입력과 출력의 이미지 크기가 같도록 해준다
def conv2d(x, W):
	return tf.nn.conv2d(x, W, strides=[1,1,1,1], padding='SAME')


# max pooling을 실행하는 함수
def max_pool_2x2(x):
	return tf.nn.max_pool(x, ksize=[1,2,2,1], strides=[1,2,2,1], padding='SAME')



#-------------------------------------------------------------------------------
# Tensorflow 코드
#-------------------------------------------------------------------------------

x = tf.placeholder("float32", [None, 2200]) # mnist data image of shape 55 x 40 = 2200
y = tf.placeholder("float32", [None, 100]) 

W = tf.Variable(tf.zeros([2200,100]))
b = tf.Variable(tf.zeros([100]))
yy = tf.nn.softmax(tf.matmul(x, W) + b)



# 1st conv layer ----------------------
W_conv1 = weight_variable([5,5,1,32])
b_conv1 = bias_variable([32])

# -1 : 아직 디멘젼이 결정되지 않았다
# x은 2200x1인데 55x40x1로 행렬을 다시 만들어준다
x_image = tf.reshape(x, [-1,55,40,1])

# y = x*w + b에 ReLU를 적용한다
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1)




# 2nd conv layer -----------------------
W_conv2 = weight_variable([5,5,32,64])
b_conv2 = bias_variable([64])

h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2)




# 1st fully connected layer -----------------------
W_fc1 = weight_variable([14*10*64, 2200])
b_fc1 = bias_variable([2200])

h_pool2_flat = tf.reshape(h_pool2, [-1, 14*10*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)
# 위 연산으로 1024x1의 벡터가 생성된다



# Dropout ------------------------
keep_prob = tf.placeholder(tf.float32)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)



# 2nd fully connected layer --------------
W_fc2 = weight_variable([2200, 100])
b_fc2 = bias_variable([100])
y_conv = tf.matmul(h_fc1_drop, W_fc2) + b_fc2



#cost = tf.reduce_mean(-tf.reduce_sum(y * tf.log(cost), reduction_indices = 1))
cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y, logits=y_conv))

learning_rate = 0.1
optimizer = tf.train.AdamOptimizer(learning_rate).minimize(cost)

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)


# 정답률을 계산한다  y_conv  vs  y
correct_prediction = tf.equal(tf.argmax(y_conv, 1), tf.argmax(y, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

#----------------------------------------------

for i in range(2000):
	batch = next_batch(50)
	# 100번 돌릴 때마다 결과를 확인한다
	if i % 100 == 0:
		train_accuracy = sess.run(accuracy,feed_dict={x:batch[0], y:batch[1], keep_prob:1.0})

		print('step', i , 'training_accuracy', train_accuracy)
	sess.run(optimizer,feed_dict={x:batch[0],y:batch[1], keep_prob:0.5})



# 전부 학습이 끝나면 테스트 데이터를 넣는다
test_accuracy = sess.run(accuracy,feed_dict={x: test_images, y: test_labels, keep_prob: 1.0})
print('test accuracy', test_accuracy)


#----------------------------------------------
# 임의의 얼굴 하나를 출력한 다음 맞혀보는 코드 
r = random.randint(0, _num_examples -1)
print ("Label: ", sess.run(tf.argmax(test_labels[r:r+1], 1)))
print ("Prediction: ", sess.run(tf.argmax(cost, 1), {x:test_images[r:r+1]}))

plt.imshow(test_images[r:r+1].reshape(55, 40), cmap='gray', interpolation='nearest')
plt.show()


