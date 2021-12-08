#include <iostream>
#include "operations.hpp"
#include <boost/random.hpp>

int main() {
	std::cout<<"Hello CMake!"<<std::endl;
        math::operations op;
        int sum = op.sum(3, 4);
	std::cout<<"Sum of 3 + 4 :"<<sum<<std::endl;

    //Add Boost support
    boost::mt19937 rng;
    double mean = 2.3;
    double std = 0.34;
    auto normal_dist = boost::random::normal_distribution<double>(mean, std);
    boost::variate_generator<boost::mt19937&,
            boost::normal_distribution<> > random_generator(rng, normal_dist);
    
    for(int i = 0; i < 2; i++){
        auto rand_val = random_generator();
        std::cout<<"Random Val "<<i+1<<" :"<<rand_val<<std::endl;
    }

	return 0;
}