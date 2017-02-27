#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> machine learning 관련된 K-Mean을 구하는 코드 
                아직 이해 못함
'''
from __future__ import division
from linear_algebra import squared_distance, vector_mean
import random

class KMeans:
	def __init__(self,k):
		self.k = k
		self.means = None

	def classify(self,input):
		return min(range(self,k)), 
				key = lambda i: squared_distance(input, self.means[i]))


	def train(self, inputs):
		self.means = random.sample(inputs, self.k)
		assignments = None

		while True:
			new_assignments = map(self.classify, inputs)
			if assignments == new_assignments:
				return

		assignments = new_assignments
		for i in range(self.k):
			i_points = [p for p, a in zip(inputs, assignments) if a == i]

			if i_points:
				self.means[i] = vector_mean(i_points)


if __name__ == "__main__":
	inputs = [[-14,-5],[13,13],[20,23],[-19,-11],[-9,-16],[21,27],[-49,15],
                [26,13],[-46,5],[-34,-1],[11,15],[-49,0],[-22,-16],[19,28],[-12,-8],
                [-13,-19],[-41,8],[-11,-6],[-25,-9],[-18,-3]]

    random.seed(0) # so you get the same results as me
    clusterer = KMeans(3)
    clusterer.train(inputs)
    print "3-means:"
    print clusterer.means
    print















