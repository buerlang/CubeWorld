#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

class TimeManager
{
private:
	double mark = 0;
	static TimeManager* instance;
	TimeManager();
	

public:
	double delta = 0;

	~TimeManager();
	static TimeManager* getInstance();
	void beginDelta();
	void endDelta();
};

#endif // !TIME_MANAGER_H
