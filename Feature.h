#ifndef FEATURE_H
#define FEATURE_H
#include<cstdio>
#include<cstdlib>
#include<string>

class Feature {
public:
	Feature(size_t len) : length(len), weight(alloc(len)) {}
	Feature(Feature&& f) : length(f.length), weight(f.weight) { f.weight = nullptr; }
	Feature(const Feature& f) = delete;
	Feature& operator =(const Feature& f) = delete;
	virtual ~Feature() { delete[] weight; }

	float& operator[] (size_t i) { return weight[i]; }
	float operator[] (size_t i) const { return weight[i]; }
	size_t size() const { return length; }

public: // should be implemented

	/**
	 * estimate the value of a given board
	 */
	//virtual float estimate(const board& b) const = 0;
	/**
	 * update the value of a given board, and return its updated value
	 */
	//virtual float update(const board& b, float u) = 0;
	/**
	 * get the name of this feature
	 */
	virtual std::string name() const = 0;

public:

	/**
	 * dump the detail of weight table of a given board
	 */
	//virtual void dump(const board& b, std::ostream& out = info) const;

	friend std::ostream& operator <<(std::ostream& out, const feature& w);

	friend std::istream& operator >>(std::istream& in, feature& w);

protected:
	static float* alloc(size_t num);
	size_t length;
	float* weight;
};

#endif