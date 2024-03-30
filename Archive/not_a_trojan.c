#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "user32.lib")
#endif

#ifdef __linux__
#include <gtk/gtk.h>
#endif

static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void trojan() {
    CURL *curl;
    FILE *fp;
    CURLcode res;

    const char *img_url = "https://www.team17.com/wp-content/uploads/2020/08/W-BANNER1-2048x608.jpg";

    curl = curl_easy_init();
    if (curl) {
        fp = fopen("worms.png", "wb");
        if (fp) {
            curl_easy_setopt(curl, CURLOPT_URL, img_url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            fclose(fp);
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            } else {
#ifdef _WIN32
                ShellExecuteA(NULL, "open", "worms.png", NULL, NULL, SW_SHOWNORMAL);
#elif __linux__
                // GtkWidget *window, *image;
                // GError *error = NULL;
                // gtk_init(NULL, NULL);

                // window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                // gtk_window_set_title(GTK_WINDOW(window), "Worms");
                // gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
                // g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

                // image = gtk_image_new_from_file("worms.png");
                // gtk_container_add(GTK_CONTAINER(window), image);
                // gtk_widget_show_all(window);

                // gtk_main();
                system("wslview worms.png");
#else
                printf("Unsupported platform. Unable to display the image.\n");
#endif
            }
        } else {
            fprintf(stderr, "Failed to create file\n");
        }
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "curl_easy_init() failed\n");
    }
}

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    trojan();
    curl_global_cleanup();
    return 0;
}