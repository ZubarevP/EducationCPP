#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <vector>

using namespace std;


// enum class TaskStatus {
//   NEW,          // новая
//   IN_PROGRESS,  // в разработке
//   TESTING,      // на тестировании
//   DONE          // завершена
// };

// using TasksInfo = map<TaskStatus, int>;

TaskStatus Next(TaskStatus task_status) {
  return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

void WithoutZero (map<TaskStatus, int>& Zero) {
	vector<TaskStatus> for_delete;
	for (const auto& LL : Zero ) {
		if (LL.second == 0) {
			for_delete.push_back(LL.first);
		}
	}
	for (const auto& LL : for_delete) {
		Zero.erase(LL);
	}
} 

class TeamTasks {
public:
  void AddNewTask(const string& person) {
	  ++Company[person][TaskStatus::NEW];
  }
  const TasksInfo& GetPersonTasksInfo(const string& person) const {
	  return Company.at(person);
  }
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {

  TasksInfo updated_tasks, untouched_tasks;
  TasksInfo& tasks = Company[person];
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    updated_tasks[Next(status)] = min(task_count, tasks[status]);
    task_count -= updated_tasks[Next(status)];
  }
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
    tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
  }
  tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];


	//   map<TaskStatus, int> New;
	//    if (Company.count(person) == 0) {
	// 	  return {New, New};
	//   } else {
	//   map<TaskStatus, int> Old = Company[person];
	//   for (int i = 0; i < task_count; i++) {
	// 	  if(Company[person][TaskStatus::NEW]) {
	// 		  --Company[person][TaskStatus::NEW];
	// 		  --Old[TaskStatus::NEW];
	// 		  ++Company[person][TaskStatus::IN_PROGRESS];
	// 		  ++New[TaskStatus::IN_PROGRESS];
	// 	  } else if (Company[person][TaskStatus::IN_PROGRESS]) {
	// 		  --Company[person][TaskStatus::IN_PROGRESS];
	// 		  --Old[TaskStatus::IN_PROGRESS];
	// 		  ++Company[person][TaskStatus::TESTING];
	// 		  ++New[TaskStatus::TESTING];
	// 	  } else if (Company[person][TaskStatus::TESTING]) {
	// 		  --Company[person][TaskStatus::TESTING];
	// 		  --Old[TaskStatus::TESTING];
	// 		  ++Company[person][TaskStatus::DONE];
	// 		  ++New[TaskStatus::DONE];
	// 	  }
	//   }
	//   Old.erase(TaskStatus::DONE);
	  WithoutZero(updated_tasks);
	  WithoutZero(untouched_tasks);
	  WithoutZero(Company.at(person));
	  return {updated_tasks, untouched_tasks};
	   }

private: 
map<string, TasksInfo> Company;
};

void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
  TasksInfo updated_tasks, untouched_tasks;
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}