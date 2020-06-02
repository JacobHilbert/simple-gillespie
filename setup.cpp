// constants. c stands for creation, d for destruction, r for arn, p for protein
const double
	tmax = 200.0,
	dt = 2.0, // time step on the averages
	cr = 1.0,
	dr = 0.2,
	cp = 50,
	dp = 0.03333333;
const int n_cells = 2000;

std::random_device random_device; // collects a seed from a random device
std::mt19937 mersenne_engine {random_device()}; // Mersenne Twister
std::uniform_real_distribution<double> distribution (0.0,1.0);

namespace gillespie {

	double step(int* arn, int* pr){
		double s1,s2,s3,s4,st,x,tau;
		s1 = cr;
		s2 = dr*(*arn);
		s3 = cp*(*arn);
		s4 = dp*(*pr);
		st = s1+s2+s3+s4;

		x = distribution(mersenne_engine);
		tau = -std::log(distribution(mersenne_engine))/st;

		if(x < (s1)/st){
			++(*arn);
		} else if(x < (s1+s2)/st){
			--(*arn);
		} else if(x < (s1+s2+s3)/st){
			++(*pr);
		} else {
			--(*pr);
		}
		return tau;
	}

	void delta(int* arn, int* pr, double time_delta){
		double time = 0.0;
		while(time < time_delta){
			time += step(arn,pr);
		}
	}

}

template <typename T, typename Iterator>
double mean(Iterator begin, Iterator end, T coll_size){
	return (double)(std::accumulate(begin,end,0.0))/coll_size;
}
