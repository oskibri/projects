#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <libgen.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <ctype.h>

#define MAX_SITES 4096
#define MAX_THREADS 2
#define NUM_THREADS 4096
#define MAX_LINE_LEN 1024

sem_t sem;

typedef struct {
	int tid;
	char *path;
} thread_site;

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
			*count = *count + 1;
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

bool contains_keywords(const char *line) {
    char lower_line[MAX_LINE_LEN];
    for (size_t i = 0; i < strlen(line) && i < MAX_LINE_LEN - 1; i++) {
        lower_line[i] = tolower(line[i]);
    }
    lower_line[strlen(line)] = '\0';

    const char *keywords[] = {"leaf", "php", "mailer"};
    int keywords_found = 0;

    for (int i = 0; i < 3; i++) {
        if (strstr(lower_line, keywords[i]) != NULL) {
            keywords_found++;
        }
    }

    return (keywords_found == 3);
}

bool search_in_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("fopen");
        return false;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        if (contains_keywords(line)) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

void grep(const char *dir_path, int tid) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            grep(full_path, tid);
        } else if (entry->d_type == DT_REG && strstr(entry->d_name, ".php") != NULL) {
            if (search_in_file(full_path)) {
                char *time_str = get_time();
				printf("[%s] TID:%04d PATH:%s Leaf PHP Mailer found!\n", time_str, tid, full_path);
                // printf("\x1B[1;31m[%s] Found in: %s\n\x1B[0m", time_str, full_path);
                free(time_str);
            }
        }
    }

    closedir(dir);
}


void* rungrep(void *arg) {
    thread_site *args = (thread_site*)arg;
    sem_wait(&sem);

    grep(args->path, args->tid);

    sem_post(&sem);
    return NULL;
}



int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <path>\n", argv[0]);
		return EXIT_FAILURE;
	}

	pthread_t threads[NUM_THREADS];
	thread_site ts[NUM_THREADS];
	int count = 0;

	char *sites[MAX_SITES];
	traverse(argv[1], 0, sites, &count);

	sem_init(&sem, 0, MAX_THREADS);

	for (int i = 0; sites[i] != NULL; i++) {
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
