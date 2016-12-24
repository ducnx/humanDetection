#ifndef _MC_CONFIG
#define _MC_CONFIG 1

#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>

#include "Detector.h"
#include "DefaultDetector.h"
#include "TestDetector.h"

#include "Tracker.h"
#include "DefaultTracker.h"

using namespace std;

struct Config {
	static const string VIDEO;
	static const string WIDTH;
	static const string HEIGHT;
	static const string DETECTOR;
	static const string TRACKER;
	static const string STEP;
		
	map<string, string> config;
	int width = 640;
	int height = 480;
	int step = 10;
	string video = "0";	
	string detector = "DEFAULT_DETECTOR";
	string tracker = "DEFAULT_TRACKER";
	
	bool checkConfig(string key){
		return config.find(key) != config.end();
	}
	
		
	Config(string name = "config.txt") {
		ifstream fi(name);
		string line;
		while (getline(fi, line)){
			stringstream ss(line);
			string key, value;
			getline(ss, key, '=');
			getline(ss, value);
			config[key] = value;
		}
		
		if (checkConfig(VIDEO))
			video = config[VIDEO];
		
		if (checkConfig(WIDTH))
			width = atoi(config[WIDTH].c_str());
		
		if (checkConfig(HEIGHT))
			height = atoi(config[HEIGHT].c_str());
		
		if (checkConfig(DETECTOR))
			detector = config[DETECTOR];
		
		if (checkConfig(TRACKER))
			tracker = config[TRACKER];
		
		if (checkConfig(STEP))
			step = atoi(config[STEP].c_str());
		
		
		//cout << video << " " << width << " " << height << endl;
	}
	
	int getWidth(){
		return width;		
	}
	
	int getHeight(){
		return height;		
	}
	
	int getStep(){
		return step;
	}
	
	string getVideo(){
		return video;
	}
	
	Detector* getDetector(){
		if (detector == "DEFAULT_DETECTOR")
			return new DefaultDetector;
		
		if (detector == "TEST_DETECTOR")
			return new TestDetector;
		
		return new DefaultDetector;
	}
	
	Tracker* getTracker(){
		if (tracker == "DEFAULT_TRACKER")
			return new DefaultTracker;
			
		return new DefaultTracker;
	}
	
};

const string Config::VIDEO = "VIDEO";
const string Config::WIDTH = "WIDTH";
const string Config::HEIGHT = "HEIGHT";
const string Config::DETECTOR = "DETECTOR";
const string Config::TRACKER = "TRACKER";
const string Config::STEP = "STEP";

#endif