#ifndef FEATURE_H
#define FEATURE_H
#include<cstdio>
#include<cstdlib>
#include<string>
#include<iostream>
#include "simple_state.h"

class Feature {
public:
	Feature(size_t len) : length(len), weight(alloc(len)) {}
	Feature(Feature& f) : length(f.length), weight(f.weight) { f.weight = NULL; }
	Feature(const Feature& f) = delete;
	Feature& operator =(const Feature& f) = delete;
	virtual ~Feature() { delete[] weight; }

	float& operator[] (size_t i) { return weight[i];}
	float operator[] (size_t i) const { return weight[i];}
	size_t size() const { return length;}

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

	/**
	 * dump the detail of weight table of a given board
	 */
	void dump(const simple_state& s, std::ostream& out = std::cout) const {
		out << s << "estimate = " << estimate(s) << std::endl;
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

	static float* alloc(size_t num) {
		static size_t total = 0;
		static size_t limit = (1 << 30) / sizeof(float); // 1G memory
		try {
			total += num;
			if (total > limit) throw std::bad_alloc();
			return new float[num]();
		} catch (std::bad_alloc&) {
			std::cerr << "memory limit exceeded" << std::endl;
			std::exit(-1);
		}
		return nullptr;
	}
private:
    int generateIndex(const simple_state &s);
    int getDiamondIndex(int **diamond);
	size_t length;
	float* weight;
};

#endif