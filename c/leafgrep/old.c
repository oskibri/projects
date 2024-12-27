#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <libgen.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAX_SITES 4096
#define MAX_THREADS 10
#define NUM_THREADS 4096
#define MAX_LINE_LEN 1024

sem_t sem;

typedef struct {
	int tid;
	char *path;
} thread_site;


bool search_in_file(const char *file_path, const char *pattern) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("fopen");
        return false;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern) != NULL) {
            fclose(file);
            return true;  // Pattern found
        }
    }

    fclose(file);
    return false;  // Pattern not found
}

bool dont_want_dir(const char *filename) {
	char *strarr[] = {".", "..", "backup", "phpmyadmin", "defaultsite", "lost+found"};
	for (int i = 0; i < sizeof(strarr) / sizeof(char*); i++) {
		if (strcmp(filename, strarr[i]) == 0) return true;
	}
	return false;
}

void remove_extra_trailslash(char **path) {
	char *tmp = *path;
	while (tmp[strlen(tmp)-1] == '/') {
		tmp[strlen(tmp)-1] = '\0';
	}
	strcat(tmp, "/");
}


void traverse(char *path, int depth, char **sites, int *count) {
	DIR *dir = opendir(path);
	if (dir == NULL) {
		perror("opendir");
		exit(1);
	}

	if (depth == 2) {
		return;
	}

	depth++;

	remove_extra_trailslash(&path);

	struct dirent *file;
	while ((file = readdir(dir)) != NULL) {
		char filename[PATH_MAX];
		strncpy(filename, file->d_name, PATH_MAX);

		if (dont_want_dir(filename) || file->d_type != DT_DIR) 
			continue;

		char tmp[PATH_MAX] = {0};
		strncpy(tmp, path, PATH_MAX);
		strncat(tmp, filename, PATH_MAX);
		strncpy(filename, tmp, PATH_MAX);
		
		char respath[PATH_MAX];
		if (realpath(filename, respath) == NULL) {
			perror("realpath");
			continue;
		};

		if (depth == 2) {
			sites[*count] = malloc(strlen(respath) * sizeof(char*));
			strcpy(sites[*count], respath);
			// printf("%d\n", *count);
			*count = *count + 1;
			// printf("(%d):\t%s\t%s\n", file->d_type, respath, basename(respath));
		} else {
			traverse(respath, depth, sites, count);
		}
	}
	closedir(dir);
}

void cleanup(char **sites) {
	for (int i = 0; i < sizeof(*sites); i++) {
		free(sites[i]);
	}
}

char* get_time() {
	time_t epoch;
	time(&epoch);
	char *buf = malloc(sizeof(char*));

	struct tm *lt = localtime(&epoch);
	strftime(buf, 20, "%F %T", lt);
	return buf;
}


void* rungrep(void *arg) {
	thread_site *args = (thread_site*)arg;

	// printf("Running tid: %d\tPath: %s\n", args->tid, args->path);
	char *grep = malloc(1024);
	sprintf(grep, "grep -lioEr --include \*.php 'Leaf PHP Mailer' %s 1>/dev/null", args->path);

	if (system(grep) == 0) {
		char *time = get_time();
		printf("[%s] TID:%04d PATH:%s Leaf PHP Mailer found!\n", time, args->tid, args->path);
		free(time);
	}

	free(grep);
	sem_post(&sem);

	// printf("Finished grep for tid: %d\tPath: %s\n", args->tid, args->path);
	return NULL;
}



int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <path>\n", argv[0]);
		return EXIT_FAILURE;
	}

	pthread_t threads[NUM_THREADS];
	thread_site ts[NUM_THREADS];
	int res;

	int count = 0;
	char *sites[MAX_SITES];
	traverse(argv[1], 0, sites, &count);

	sem_init(&sem, 0, MAX_THREADS);

	for (int i = 0; sites[i] != NULL; i++) {
		sem_wait(&sem);

		ts[i].tid = i;
		ts[i].path = sites[i];

		if (pthread_create(&threads[i], NULL, rungrep, &ts[i]) != 0) {;
			fprintf(stderr, "error creating thread %d", i);
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; sites[i] != NULL; i++) {
		pthread_join(threads[i], NULL);
	}

	cleanup(sites);
	sem_destroy(&sem);
	return EXIT_SUCCESS;
}
