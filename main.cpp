#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <map>
#include <time.h>
#include <sys/time.h>


using namespace std;

#include "util.cpp"

#include "algo/rank.cpp"
#include "algo/berlekamp_massey.cpp"
#include "algo/dfft.cpp"

#include "test/test.cpp"
#include "test/monobit_frequency_test.cpp"
#include "test/frequency_test_within_a_block.cpp"
#include "test/poker_test.cpp"
#include "test/serial_test.cpp"
#include "test/runs_test.cpp"
#include "test/runs_distribution_test.cpp"
#include "test/test_for_the_longest_run_of_ones_in_a_block.cpp"
#include "test/binary_derivative_test.cpp"
#include "test/autocorrelation_test.cpp"
#include "test/binary_matrix_rank_test.cpp"
#include "test/cumulative_test.cpp"
#include "test/approximate_entropy_test.cpp"
#include "test/linear_complexity_test.cpp"
#include "test/Maurers_universal_test.cpp"
#include "test/Discrete_Fourier_Transform_test.cpp"
int  time_array[15] = {0};

#include "testsuit.cpp"


default_random_engine generator(time(NULL));
uniform_int_distribution<int> distribution(0, 1);


int main(int argc, char* argv[]){
	/*argv[1]=filepath 
	  argv[2]=group_count 
	  argv[3] = group_size 
	  argv[4]=test_flag
    */
    
	unsigned char bit;
	unsigned char buffer[4]; 
	
	if(argc != 5){
		printf("Parameter number error!\n");
		exit(-1);
	}
	int test_flag = 0;
	if(strncmp(argv[4], "factory", 7) == 0){
		test_flag = 1;
	}
	if(strncmp(argv[4], "boot", 4) == 0){
		test_flag = 2;
	}
	if(strncmp(argv[4], "cycle", 5) == 0){
		test_flag = 3;
	}
	if(strncmp(argv[4], "once", 4) == 0){
		test_flag = 4;
	}	
	int group_cnt = atoi(argv[2]);
	int group_size = atoi(argv[3]);
	int	input_size = group_cnt;
    FILE* fp;
	if ((fp = fopen(argv[1], "rb")) == NULL ){
		printf("Input file error\n");
		exit(-1);
	}
	map<string, double> name_score_map;
	#if 0
	name_score_map["MonobitFrequencyTest"] = 0;
	name_score_map["FrequencyTestWithinABlock"] = 0;
	name_score_map["PokerTest"] = 0;
	name_score_map["SerialTest"] = 0;
	name_score_map["RunsTest"] = 0;
	name_score_map["RunsDistributionTest"] = 0;
	name_score_map["TestForTheLongestRunOfOnesInABolock"] = 0;
	name_score_map["BinaryDerivativeTest"] = 0;
	name_score_map["AutocorrelationTest"] = 0;
	name_score_map["BinaryMatrixRankTest"] = 0;
	name_score_map["CumulativeTest"] = 0;
	name_score_map["ApproximateEntropyTest"] = 0;
	name_score_map["LinearComplexityTest"] = 0;
	name_score_map["MaurersUniversalTest"] = 0;
	name_score_map["DiscreteFourierTransformTest"] = 0;
	#endif
	for(int l = 0; l < group_cnt; l++){
	vector<bool> v;
	if (argc == 5){
		int k = 0;			
        for (int i = 0; i < group_size/8; i++){
			if ( fread(&bit, sizeof(char), 1, fp) == EOF ) {
				printf("ERROR:Insufficient data in file\n");
				fclose(fp);
				return -1;
			}
			else {			
				v.push_back((bit>>7)&0x1);
				v.push_back((bit>>6)&0x1);
				v.push_back((bit>>5)&0x1);
				v.push_back((bit>>4)&0x1);
				v.push_back((bit>>3)&0x1);
				v.push_back((bit>>2)&0x1);
				v.push_back((bit>>1)&0x1);
				v.push_back((bit)&0x1);
			}
        }
    } else {
        fstream f(argv[1]);
        char c;
        while (f>>c){
            if (c=='0') v.push_back(false);
            else if(c=='1') v.push_back(true);
            else {
                cout<< "Invalid character!"<<endl;
                return 0;
            }
        }
    }	
    testSuit::initDefaultTests(test_flag);
    testSuit::runTest(v, name_score_map);
	}

	map<string,double>::iterator it;
	// 通过检测样本的最少值
	int benchMark = 0;
	benchMark = group_cnt*(1-0.01-3*sqrt(0.01*(1-0.01)/group_cnt));
	#if 1
	for(it = name_score_map.begin(); it != name_score_map.end(); ++it){
		if(it->second < benchMark){
			printf("it->second=%d\n", it->second);
			cout<<it->first <<" Fail!"<<endl;
			return -1;
		}		
	}
	#endif
	/*获取测试时间*/
	printf("get time\n");
	for(int m = 0; m <= 11; m++){
		printf("%f\n", (float)time_array[m]/1000);
	}
    return 0;
}

