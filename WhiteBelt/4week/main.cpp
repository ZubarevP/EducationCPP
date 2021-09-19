#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

struct Image {
  double quality;
  double freshness;
  double rating;
};

struct Params {
  double a;
  double b;
  double c;
};

class FunctionPart {
public:
		FunctionPart (char new_operation, double new_value) {
			operation = new_operation;
			value = new_value;
		}
		double Apply (double source_value) const {
			if (operation == '+') {
				return source_value + value;
			}
			else {
				return source_value - value;
			}
		}
		void Invert () {
			if (operation == '+') {
				operation = '-';
			}
			else {
				operation = '+';
			}
		}

private:
char operation;
double value;
};

class Function {
public:
	void AddPart (char operation, double value) {
		parts.push_back({operation, value});
	}
	double Apply (double value) const {
for (const FunctionPart& part : parts) {
	value = part.Apply(value);
}
return  value;
	}
	void Invert () {
		for (FunctionPart& part : parts) {
			part.Invert();
		}
		reverse(begin(parts), end(parts));
	}
private:
	vector<FunctionPart> parts;
};



Function MakeWeightFunction(const Params& params,
                            const Image& image) {
  Function function;
  function.AddPart('-', image.freshness * params.a + params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
  Function function = MakeWeightFunction(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
  Function function = MakeWeightFunction(params, image);
  function.Invert();
  return function.Apply(weight);
}

int main() {
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  cout << ComputeImageWeight(params, image) << endl;
  cout << ComputeQualityByWeight(params, image, 46) << endl;
  return 0;
}



Compile error:
       b"/tmp/submission0f8rdnwt/invertible_function.cpp:25:8: fatal error: redefinition of 'Image'\n"
		"struct Image {\n"
		"       ^\n"
		"/tmp/submission0f8rdnwt/invertible_function.cpp:7:8: note: previous definition is here\n"
		"struct Image {\n"
		"       ^\n"
		"1 error generated.\n"
