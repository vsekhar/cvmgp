#!/usr/bin/python3

import pickle

import vmgp

if __name__ == '__main__':
	pop = vmgp.make_population(1000, 10, 100)
	for b in pop['']:
		assert b == pickle.loads(pickle.dumps(b))
	
