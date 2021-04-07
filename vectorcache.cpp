#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

struct Datas{
	int n;
	double fn;
};

typedef struct Datas calculatedValues;

class BaseFunctionCalculator{

public:
	virtual ~BaseFunctionCalculator(){}
	virtual void setCacheSize(int) = 0;
	virtual double calculate(int) = 0;
	virtual int getCacheElement(int) = 0;

};

class MyFunctionCalculator : public BaseFunctionCalculator{

	int capacity;
	int size;
	int lastSearched;


	int swap(vector<Datas>& vec, unsigned int swapIndex, int n){

		if(vec[swapIndex].n == n && vec[swapIndex].n != vec[0].n){
			calculatedValues temp = vec[swapIndex-1];
			vec[swapIndex-1] = vec[swapIndex];
			vec[swapIndex] = temp;
			return vec[swapIndex-1].n;
		}
		return vec[swapIndex].n;
	}

	int search(int n){

		for(unsigned int index = 0 ; index < vectorArray.size(); index++){

			if(vectorArray[index].n == n){

				if(lastSearched == n){
					lastSearched = swap(vectorArray,index,n);
					return 1;
				}
				lastSearched = vectorArray[index].n;
				return 1;
			}
		}
		return 0;

	}

	void add(int n,double result){

		if(size != capacity ){
			vectorArray.insert(vectorArray.begin(), calculatedValues{n,result});
			size++;
		}
		else{
			vectorArray.pop_back();
			vectorArray.insert(vectorArray.begin(), calculatedValues{n,result});
		}

	}


public:


	vector<calculatedValues> vectorArray;
	MyFunctionCalculator(){

		lastSearched = 0;
		capacity = 0;
		size = 0;

	}

	~MyFunctionCalculator() override{}


	void setCacheSize(int size) override{

		capacity = size;

	}

	double calculate(int n) override{

		int found = search(n);

		if(found != 0)
			return n;

		double result = 0;

		for(int i = 0; i <= n; ++i){
			result += (sin(i)*i);
		}
		add(n,result);

		return result;

	}

	int getCacheElement(int index) override{

		int vecIndex = 0;

		if(index > (capacity-1))
			return -1;


		while(index > 0){
			vecIndex++;
			index--;
		}

		return vectorArray.at(vecIndex).n;

	}

	friend std::ostream& operator<<(std::ostream& out, MyFunctionCalculator& obj){

		std::string delimeter = "";
		for(unsigned int i = 0; i < obj.vectorArray.size(); i++){
			std::cout << delimeter << obj.vectorArray[i].n << " ";
			std::cout << "f(" << obj.vectorArray[i].fn << ")";
			delimeter = ", ";
		}
		return out;

	}

};


int main(){

	MyFunctionCalculator myCalculator;

	myCalculator.setCacheSize(221);
	for(int i = 0 ; i < 221; i ++){
		myCalculator.calculate(i);
		myCalculator.calculate(i*221);
	}
	//myCalculator.calculate(3);
	//myCalculator.calculate(2);
	std::cout << myCalculator << std::endl;
	/*myCalculator.calculate(5);
	myCalculator.calculate(20);
	myCalculator.calculate(10);
	myCalculator.calculate(5);
	myCalculator.calculate(5);
	myCalculator.calculate(5);
	myCalculator.calculate(2);
	myCalculator.calculate(3);
	std::cout << myCalculator << std::endl;
	std::cout << std::endl;
	std::cout << myCalculator.getCacheElement(0) << std::endl;
	std::cout << myCalculator.getCacheElement(1) << std::endl;
	std::cout << myCalculator.getCacheElement(2) << std::endl;
	std::cout << myCalculator.getCacheElement(3) << std::endl;*/


}
