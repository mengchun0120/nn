#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <act_func.hpp>
#include <output_model.hpp>
#include <neural_net.hpp>
#include <learn.hpp>

using namespace std;

void usage(const char *cmd)
{
    cerr << "Usage: " << cmd << " -h hidden_nodes -t test_data_file -l learn_rate"
         << " -e num_epochs -m init_min -M init_max -s stop_thresh -o output_file -f func" << endl;
}

void construct_nn(NeuralNet *net, size_t hidden_nodes, ActFunc *act_func)
{

}

int main(int argc, char *argv[])
{
    size_t hidden_nodes = 0, num_epochs = 0, stop_thresh = 0;
    const char *test_data_file = nullptr, *output_file = nullptr;
    double learn_rate;
    bool learn_avail = false;
    int opt;

    while((opt = getopt(argc, argv, "h:t:l:e:s:o:")) != -1) {
        switch(opt) {
        case 'h':
            hidden_nodes = atoi(optarg);
            break;
        case 't':
            test_data_file = optarg;
            break;
        case 'l':
            learn_rate = atof(optarg);
            break;
        case 'e':
            num_epochs = atoi(optarg);
            break;
        case 's':
            stop_thresh = atoi(optarg);
            break;
        case 'o':
            output_file = optarg;
            break;
        default:
            usage(argv[0]);
            exit(1);
        }
    }

    if(!hidden_nodes || !num_epochs || !stop_thresh || !test_data_file || !output_file || !learn_avail) {
        usage(argv[0]);
        exit(1);
    }

    OutputModel out_model = OutputModel::square_loss_regression_model();
    NeuralNet net(&out_model);
}
