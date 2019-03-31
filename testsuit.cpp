#define FACTORY_TEST 1
#define BOOT_TEST 2
#define CYCLE_TEST 3
#define ONCE_TEST 4
#define MONOBITFREQUENCYTEST  					0
#define FREQUENCYTESTWITHINABLOCK				1
#define POKERTEST 								2
#define SERIALTEST 								3
#define RUNSTEST								4
#define RUNSDISTRIBUTIONTEST					5
#define TESTFORTHELONGESTRUNOFONESINABOLOCK		6
#define BINARYDERIVATIVETEST					7
#define AUTOCORRELATIONTEST						8
#define BINARYMATRIXRANKTEST					9
#define CUMULATIVETEST							10	
#define APPROXIMATEENTROPYTEST					11
#define LINEARCOMPLEXITYTEST					12
#define MAURERSUNIVERSALTEST					13
#define DISCRETEFOURIERTRANSFORMTEST			14
#define TIME_TEST_START() gettimeofday(&start, NULL);
#define TIME_TEST_TICK(x) do {gettimeofday(&end, NULL);int  timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;time_array[x] = time_array[x] + timeuse;TIME_TEST_START();}while(0);
namespace testSuit{
    vector<test::TestMethod*> tests;

    void initDefaultTests(int test_flag){
        for (test::TestMethod* t:tests) delete t; tests.clear();
		if( (test_flag ==  FACTORY_TEST) || (test_flag == BOOT_TEST) || (test_flag == CYCLE_TEST)){
			tests.push_back(new test::MonobitFrequencyTest());		
			tests.push_back(new test::FrequencyTestWithinABlock(100));
			tests.push_back(new test::PokerTest(4));
			tests.push_back(new test::PokerTest(8));
			tests.push_back(new test::SerialTest(2));
			tests.push_back(new test::SerialTest2(2));
			tests.push_back(new test::SerialTest(5));
			tests.push_back(new test::SerialTest2(5));
			tests.push_back(new test::RunsTest());
			tests.push_back(new test::RunsDistributionTest());			
			tests.push_back(new test::TestForTheLongestRunOfOnesInABolock(10000));
			tests.push_back(new test::BinaryDerivativeTest(3));
			tests.push_back(new test::BinaryDerivativeTest(7));
			tests.push_back(new test::AutocorrelationTest(1));
			tests.push_back(new test::AutocorrelationTest(2));
			tests.push_back(new test::AutocorrelationTest(8));
			tests.push_back(new test::AutocorrelationTest(16));
			tests.push_back(new test::BinaryMatrixRankTest(32, 32));
			tests.push_back(new test::CumulativeTest());
			tests.push_back(new test::ApproximateEntropyTest(2));
			tests.push_back(new test::ApproximateEntropyTest(3));
		if( (test_flag ==  FACTORY_TEST) || (test_flag == BOOT_TEST)){
			tests.push_back(new test::LinearComplexityTest(500));
			tests.push_back(new test::MaurersUniversalTest(7, 1280));
			tests.push_back(new test::DiscreteFourierTransformTest());
			}
		}		
		else if( (test_flag ==  ONCE_TEST)){
			tests.push_back(new test::PokerTest(4));
			tests.push_back(new test::PokerTest(8));
		}
    }

    void runTest(vector<bool>& bits, map<string, double> &name_score_map){
    	struct timeval start, end;
		TIME_TEST_START();
        for (test::TestMethod* t:tests){
            t->run(bits);
			TIME_TEST_TICK(t->id);
        }
#if 0
        cout<<endl;
        cout<<"           T E S T   R E S U L T       "<<endl;
        cout<<setiosflags(ios::left);
        cout<<setw(50)<<"Name";
        cout<<setw(10)<<" P-value";
        cout<<resetiosflags(ios::left)<<endl;
        cout<<"-----------------------------------------------------------------"<<endl;
		#endif
        for (test::TestMethod* t:tests){
			#if 0
           	cout<<setiosflags(ios::left);
            cout<<setw(50)<<t->testName();
            cout<<resetiosflags(ios::left);
            cout<<setiosflags(ios::right);
            cout<<setw(8)<<setprecision(4)<<t->P*100<<"%";
            cout<<setw(3)<<(t->result()?'P':'F')<<endl;
            cout<<resetiosflags(ios::right);
			#endif
			if(t->testName() == "Monobit frequency test" && t->P>=0.01){
				name_score_map["MonobitFrequencyTest"] += 1;
			}
			if(t->testName() == "Frequency test within a block" && t->P>=0.01){
				name_score_map["FrequencyTestWithinABlock"] += 1;
			}
			if(t->testName() == "Poker test" && t->P>=0.01){
				name_score_map["PokerTest"] += (float)0.5;
			}
			if(t->testName() == "Serial test (1)" && t->P>=0.01){
				name_score_map["SerialTest"] += (float)0.25;
			}
			if(t->testName() == "Serial test (2)" && t->P>=0.01){
				name_score_map["SerialTest"] += (float)0.25;
			}
			if(t->testName() == "Runs test" && t->P>=0.01){
				name_score_map["RunsTest"] += 1;
			}
			if(t->testName() == "Runs distribution test" && t->P>=0.01){
				name_score_map["RunsDistributionTest"] += 1;
			}
			if(t->testName() == "Test for the longest run of ones in a block" && t->P>=0.01){
				name_score_map["TestForTheLongestRunOfOnesInABolock"] += 1;
			}
			if(t->testName() == "Binary derivative test" && t->P>=0.01){
				name_score_map["BinaryDerivativeTest"] += (float)0.5;
			}
			if(t->testName() == "Autocorrelation test" && t->P>=0.01){
				name_score_map["AutocorrelationTest"] += (float)0.25;
			}
			if(t->testName() == "Binary matrix rank test" && t->P>=0.01){
				name_score_map["BinaryMatrixRankTest"] += 1;
			}
			if(t->testName() == "Cumulative test" && t->P>=0.01){
				name_score_map["CumulativeTest"] += 1;
			}
			if(t->testName() == "Approximate entropy test" && t->P>=0.01){
				name_score_map["ApproximateEntropyTest"] += (float)0.5;
			}
			if(t->testName() == "Linear complexity test" && t->P>=0.01){
				name_score_map["LinearComplexityTest"] += 1;
			}
			if(t->testName() == "Maurer's universal test" && t->P>=0.01){
				name_score_map["MaurersUniversalTest"] += 1;
			}
			if(t->testName() == "Discrete Fourier Transform test" && t->P>=0.01){
					name_score_map["DiscreteFourierTransformTest"] += 1;
				}
        }
    }
}
