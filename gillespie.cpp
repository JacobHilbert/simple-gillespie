#include <iostream> // print things, cout
#include <fstream> // save to files, ofstream
#include <vector>
#include <array>
#include <random>
#include <string> // unused for now, stoi
#include <cmath> // log
#include <algorithm> // accumulate, fill

#include "setup.cpp"

int main(){

	std::vector<double> arn_means,pr_means;
	std::vector<double> t_means;
	arn_means.push_back(0);
	pr_means.push_back(0);
	t_means.push_back(0.0);

	// each of this arrays will contain the result of an individual cell
	std::array<int,n_cells> arn_local,pr_local;
	// initialized in ceros...
	std::fill(arn_local.begin(),arn_local.end(),0);
	std::fill(pr_local.begin(),pr_local.end(),0);
	int r,p;


	while(t_means.back()<tmax){


		for(int i=0; i<n_cells; i++){
			gillespie::delta(&arn_local[i],&pr_local[i],dt);
		}
		pr_means.push_back(mean(pr_local.begin(),pr_local.end(),pr_local.size()) );
		arn_means.push_back(mean(arn_local.begin(),arn_local.end(),arn_local.size()) );
		t_means.push_back(t_means.back()+dt);
		std::cout << "\r" << (int)t_means.back() << "/" << (int)tmax << std::flush;
	}

	std::ofstream output_arn("arn.dat");
	for(int i=0; i<arn_means.size(); i++){
		output_arn << t_means[i] << "\t" << arn_means[i] << "\n";
	}

	std::ofstream output_pr("pr.dat");
	for(int i=0; i<arn_means.size(); i++){
		output_pr << t_means[i] << "\t" << pr_means[i] << "\n";
	}
	std::cout << "Fnished" << std::endl;
	return 0;
}
