#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <config_parser.hpp>
#include <simple_data_generator.hpp>

using namespace std;

void usage(const char *cmd)
{
    cerr << "Usage: " << cmd << " config_file" << endl;
}

void gen_data(SimpleDataGenerator& g, size_t count, const string& file,
              double xmin, double xmax)
{
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<> dist(xmin, xmax);
    ofstream out(file);
    double x, y;

    for(size_t i = 0; i < count; ++i) {
        x = dist(gen);
        y = g(x);
        out << x << ' ' << y << endl;
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2) {
        usage(argv[0]);
        exit(1);
    }


    double slope, intercept, stddev, xmin, xmax;
    bool slope_avail = false, intercept_avail = false, stddev_avail = false;
    bool xmin_avail = false, xmax_avail = false;
    size_t train_count = 0, validate_count = 0;
    string train_file, validate_file;
    ConfigParser parser(argv[1]);
    string key, value;

    while(parser.next_config(key, value)) {
        cerr << key << ' ' << value << endl;
        if(key == "slope") {
            slope = stod(value);
            slope_avail = true;
        } else if(key == "intercept") {
            intercept = stod(value);
            intercept_avail = true;
        } else if(key == "stddev") {
            stddev = stod(value);
            stddev_avail = true;
        } else if(key == "xmin") {
            xmin = stod(value);
            xmin_avail = true;
        } else if(key == "xmax") {
            xmax = stod(value);
            xmax_avail = true;
        } else if(key == "train_count") {
            int s = stoi(value);
            if(s > 0) train_count = static_cast<size_t>(s);
        } else if(key == "validate_count") {
            int s = stoi(value);
            if(s > 0) validate_count = static_cast<size_t>(s);
        } else if(key == "train_file") {
            train_file = value;
        } else if(key == "validate_file") {
            validate_file = value;
        } else {
            cerr << "Unknown key: " << int(key[0]) << endl;
            exit(1);
        }
    }

    if(!slope_avail || !intercept_avail || !stddev_avail || !xmin_avail ||
       !xmax_avail || train_count == 0 || validate_count == 0 ||
       train_file.length() == 0 || validate_file.length() == 0) {

        cerr << "Parameter missing or invalid!" << endl;
        exit(1);
    }

    cout << "Generating linear data:\ntrain_count=" << train_count
         << " trail_file=" << train_file << "\nvalidate_count="
         << validate_count << " validate_file=" << validate_file << endl;

    auto *g = SimpleDataGenerator::linear_generator(slope, intercept, stddev);
    gen_data(*g, train_count, train_file, xmin, xmax);
    gen_data(*g, validate_count, validate_file, xmin, xmax);
}
