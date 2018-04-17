#ifndef Filter_h
#define Filter_h

class Filter {
	
private:

  static const int numReadings = 15;
  float readings[numReadings];      // the readings from the analog input
  int readIndex = 0;              // the index of the current reading
  float total = 0;                  // the running total
  float average = 0;                // the average

  /*
  float Q = 0.000001;
	float R = 0.0001;
	float P = 1, X = 0, K;
  */
	
	void measurementUpdate();
  void measurementUpdate(float value);

public:
  
  Filter();
  float setFilteredDistance(float value);
	float getFilteredDistance();
	float updateFilteredDistance(float value);
	
};

#endif

