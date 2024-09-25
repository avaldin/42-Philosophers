typedef struct {
	pthread_mutex_t mutex;
	bool taken;
} t_fork;

void fork_init(t_fork* self) {
	pthread_mutex_init(&self->mutex, NULL);
	self->taken = false;
}

bool fork_try_take(t_fork* self) {
	bool could_take_fork;

	could_take_fork = false;
	pthread_mutex_lock(&self->mutex);
	if (!self->taken) {
		could_take_fork = true;
		self->taken = true;
	}
	pthread_mutex_unlock(&self->mutex);
	return could_take_fork;
}

void fork_give_back(t_fork* self) {
	pthread_mutex_lock(&self->mutex);
	if (!self->taken) {
		printf("Fork has been duplicated");
		exit(-1);
	}
	self->taken = false;
	pthread_mutex_unlock(&self->mutex);
	return could_take_fork;
}