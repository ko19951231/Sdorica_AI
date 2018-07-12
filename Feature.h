#ifndef FEATURE_H
#define FEATURE_H
#include<cstdio>
#include<cstdlib>
#include<string>
#include<iostream>
#include "simple_state.h"

class Feature {
public:
	Feature(){
		//Consist of 4 features: 3 players' state, enemy state
		length = 25;
		weight = new float[(1 << 25)];
		for(int i = 0 ; i < (1 << 25) ; i++){
			weight[i] = 0;
		}
	}
	virtual ~Feature() { delete[] weight; }
	float& operator[] (size_t i) { return weight[i];}
	float operator[] (size_t i) const { return weight[i];}
	size_t size() const { return (1 << length);}

public:

	/**
	 * estimate the value of a given board
	 */
	float estimate(const simple_state& s);
	/**
	 * update the value of a given board, and return its updated value
	 */
	float update(const simple_state& s, float u);

    /**
	 * get the name of this feature
	 */
	virtual std::string name() const {
		return "Sdorica Feature";
	}

	friend std::ostream& operator <<(std::ostream& out, const Feature& w) {
		std::string name = w.name();
		int len = name.length();
		out.write(reinterpret_cast<char*>(&len), sizeof(int));
		out.write(name.c_str(), len);
		float* weight = w.weight;
		size_t size = w.size();
		out.write(reinterpret_cast<char*>(&size), sizeof(size_t));
		out.write(reinterpret_cast<char*>(weight), sizeof(float) * size);
		return out;
	}

	friend std::istream& operator >>(std::istream& in, Feature& w) {
		std::string name;
		int len = 0;
		in.read(reinterpret_cast<char*>(&len), sizeof(int));
		name.resize(len);
		in.read(&name[0], len);
		if (name != w.name()) {
			std::cerr << "unexpected feature: " << name << " (" << w.name() << " is expected)" << std::endl;
			std::exit(1);
		}
		float* weight = w.weight;
		size_t size;
		in.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		if (size != w.size()) {
			std::cerr << "unexpected feature size " << size << "for " << w.name();
			std::cerr << " (" << w.size() << " is expected)" << std::endl;
			std::exit(1);
		}
		in.read(reinterpret_cast<char*>(weight), sizeof(float) * size);
		if (!in) {
			std::cerr << "unexpected end of binary" << std::endl;
			std::exit(1);
		}
		return in;
	}

    /**
	 * dump the detail of weight table of a given board
	 */
	void dump(const simple_state& s, std::ostream& out = std::cout) {
		//out << "Sdorica Feature Estimate = " << estimate(s) << std::endl;
	}

	float* alloc(size_t num) {
		size_t total = 0;
		size_t limit = (1 << 30); // 1G memory
		try {
			total += 1 << num;
			if (total > limit) throw std::bad_alloc();
			return new float[(1 << num)]();
		} catch (std::bad_alloc&) {
			std::cerr << "memory limit exceeded" << std::endl;
			std::exit(-1);
		}
		return NULL;
	}
private:
	float* weight;
	size_t length;
};

#endif