
# tf.placeholder   : 실제 입력에 사용되는 데이터들을 받을 변수를 설정한다
	tf.placeholder(tf.float32, [None, 10])
	keep_prob = tf.placeholder(tf.float32)



# tf.Variable   : 신경망에서 가중치와 바이어스 등을 선언할 때 사용한다
	tf.Variable(initial)



# tf.constant
	tf.constant(0.1, shape=shape)



# tf.nn

	# tf.nn.conv2d
		tf.nn.conv2d(x, W, strides=[1,1,1,1], padding='SAME')



	# tf.nn.relu
		tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)




	# tf.nn.max_pool
		tf.nn.max_pool(x, ksize=[1,2,2,1], strides=[1,2,2,1], padding='SAME')




	# tf.nn.dropout
		h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)



	# tf.nn.softmax_cross_entropy_with_logits
		cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y_input, logits=y_conv))





# tf.reshape   : 특정행렬을 axbxc 행렬로 바꾼다
	tf.reshape(x_input, [-1,28,28,1])



# tf.matmul  : 두 개의 행렬을 곱한다
	y_conv = tf.matmul(h_fc1_drop, W_fc2) + b_fc2
	tf.matmul(h_pool2_flat, W_fc1)




# tf.reduce_mean
	accuracy = tf.reduce_mean(tf.cast(corerct_predition, tf.float32))




# tf.train.AdamOptimizer
	train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)




# tf.equal
	corerct_predition = tf.equal(tf.argmax(y_conv, 1) , tf.argmax(y_input, 1))




# tf.InteractiveSession
	sess = tf.InteractiveSession()
	sess.run(tf.global_variables_initializer())




# tf.argmax
 



