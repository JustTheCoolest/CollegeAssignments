// Tasks: Thread, semaphore
void round_robin(int n, int processes[][4]){
	sort_by_entry_time(n, processes);
	int flag;
	int current_time = 0;
	do{
		flag = true;
		for(int i=0; i<n; ++i){
			if(processes[i][0] > current_time){
				break;
			}
			if(processes[i][1]==0){
				continue;
			}
			flag = false;
			int exec_time = min(next_entry, current_time + round_time);
			processes[i][1] -= exec_time;
			current_time += exec_time;
			processes[i][3] = 1;
	} while(!flag);
}


int main(){
	// {entry time, burst time, remaining time, priority, chanced}
	int processes[][] = {{}};
	int n = 0;
	round_robin(n, processes);
}
