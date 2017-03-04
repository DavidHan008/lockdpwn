#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==>
'''
import tensorflow as tf

hello = tf.constant('hello tf')

a = tf.constant(10)
b = tf.constant(32)
c = a + b

X = tf.placeholder("float", [None,3])

W = tf.Variable(tf.random_normal([3,2]), name='Weights')
b = tf.Variable(tf.random_normal([2,1]), name='Bias')

xdata = [[1,2,3,] , [4,5,6]]

expr = tf.matmul(X,W) + b

sess = tf.Session()
sess.run(tf.global_variables_initializer())

print sess.run(hello)
print "a + b = c = ", sess.run(c)
print xdata
print sess.run(W)
print sess.run(b)
print sess.run(expr, feed_dict={X: xdata})

sess.close()
