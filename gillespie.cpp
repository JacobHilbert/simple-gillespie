#include <iostream> // print things, cout
#include <fstream> // save to files, ofstream
#include <array>
#include <random>
#include <string> // unused for now, stoi
#include <cmath> // log
#include <algorithm> // accumulate, fill

#include "setup.cpp"

int main(){
	const int time_size = (int)(tmax/dt)+1;
	std::array<double,time_size> t_means,arn_means,pr_means;
	arn_means[0] = 0.0;
	pr_means[0] = 0.0;

	std::iota(t_means.begin(),t_means.end(),0.0);
	std::transform(t_means.begin(),t_means.end(),t_means.begin(),[=](double d){return d*dt;});

	// each of this array will contain the result of an individual cells
	std::array<int,n_cells> arn_local,pr_local;
	// initialized in zeros...
	std::fill(arn_local.begin(),arn_local.end(),0);
	std::fill(pr_local.begin(),pr_local.end(),0);
	int r,p;


	for(int i=1; i<time_size; i++){
		for(int j=0; j<n_cells; j++){
			gillespie::delta(&arn_local[j],&pr_local[j],dt);
		}
		pr_means[i] = mean(pr_local.begin(),pr_local.end(),time_size);
		arn_means[i] = mean(arn_local.begin(),arn_local.end(),time_size);
		std::cout << "\r" << (int)t_means[i] << "/" << (int)tmax << std::flush;
	}

	std::ofstream output_arn("arn.dat");
	for(int i=0; i<time_size; i++){
		output_arn << t_means[i] << "\t" << arn_means[i] << "\n";
	}

	std::ofstream output_pr("pr.dat");
	for(int i=0; i<time_size; i++){
		output_pr << t_means[i] << "\t" << pr_means[i] << "\n";
	}
	std::cout << "\nFnished" << std::endl;
	return 0;
}
