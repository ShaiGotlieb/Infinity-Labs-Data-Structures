#include "uid.h"

const task_uid_t BAD_UID = {0,0,0};

task_uid_t UIDCreate()
{
	task_uid_t uid;
	static size_t counter = 1;

	counter++;
	uid.counter = counter;
	uid.time_stamp = time(0);
	uid.pid = getpid();

	return (uid);
}

int UIDIsSame(const task_uid_t uid1, const task_uid_t uid2)
{
	if (uid1.counter == uid2.counter && 
		uid1.time_stamp == uid2.time_stamp &&
		 uid1.pid == uid2.pid)
	{
		return (1);
	}

	return (0);
}