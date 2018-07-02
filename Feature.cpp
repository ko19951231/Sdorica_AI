#include "Feature.h"

/*virtual void Feature::dump(const board& b, std::ostream& out = info) const {
	out << b << "estimate = " << estimate(b) << std::endl;
}*/

friend std::ostream& Feature::operator <<(std::ostream& out, const feature& w) {
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

friend std::istream& Feature::operator >>(std::istream& in, feature& w) {
	std::string name;
	int len = 0;
	in.read(reinterpret_cast<char*>(&len), sizeof(int));
	name.resize(len);
	in.read(&name[0], len);
	if (name != w.name()) {
		error << "unexpected feature: " << name << " (" << w.name() << " is expected)" << std::endl;
		std::exit(1);
	}
	float* weight = w.weight;
	size_t size;
	in.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	if (size != w.size()) {
		error << "unexpected feature size " << size << "for " << w.name();
		error << " (" << w.size() << " is expected)" << std::endl;
		std::exit(1);
	}
	in.read(reinterpret_cast<char*>(weight), sizeof(float) * size);
	if (!in) {
		error << "unexpected end of binary" << std::endl;
		std::exit(1);
	}
	return in;
}

static float* Feature::alloc(size_t num) {
	static size_t total = 0;
	static size_t limit = (1 << 30) / sizeof(float); // 1G memory
	try {
		total += num;
		if (total > limit) throw std::bad_alloc();
		return new float[num]();
	} catch (std::bad_alloc&) {
		error << "memory limit exceeded" << std::endl;
		std::exit(-1);
	}
	return nullptr;
}