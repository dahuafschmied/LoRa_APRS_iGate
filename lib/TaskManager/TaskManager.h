#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include <list>
#include <memory>
#include <Arduino.h>
#include <configuration.h>
#include <BoardFinder.h>

#include "TaskQueue.h"

class Task
{
public:
	Task(String & name, int taskId) : _name(name), _taskId(taskId) {}
	Task(const char * name, int taskId) : _name(name), _taskId(taskId) {}
	virtual ~Task() {}

	String getName() const { return _name; }
	int getTaskId() const { return _taskId; }

	virtual bool setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) = 0;
	virtual bool loop(std::shared_ptr<Configuration> config) = 0;

private:
	String _name;
	int _taskId;
};

class TaskManager
{
public:
	static TaskManager & instance()
	{
		static TaskManager _instance;
		return _instance;
	}

	~TaskManager() {}

	void addTask(std::shared_ptr<Task> task);
	std::shared_ptr<Task> getTask(const char * name);

	bool setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig);
	bool loop(std::shared_ptr<Configuration> config);

private:
	std::list<std::shared_ptr<Task>> _tasks;

	TaskManager();
	TaskManager(const TaskManager &);
	TaskManager & operator = (const TaskManager &);
};

#endif
