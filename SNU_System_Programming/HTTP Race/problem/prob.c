#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <stdarg.h>
#include <ctype.h>
#include <malloc.h>

#define BUFFER_SIZE 1024
#define ADMIN_PASSWORD_LENGTH 16
#define MAX_PARAMS 2

#define HANDLE_FAIL -1
#define HANDLE_OK 0

volatile int is_admin = 0;
uint64_t response_size = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // mutex for global `response_size`
char admin_password[ADMIN_PASSWORD_LENGTH + 1];
typedef struct {
    char *rawRequest;     // input
    char *responseBuffer; // output
} httpIO;

// Random password generator
void generateRandomPassword(char *password, size_t length) {
    const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        dprintf(2, "Error opening /dev/urandom\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < length; i++) {
        unsigned char randomChar;
        read(fd, &randomChar, 1);
        password[i] = characters[randomChar % (sizeof(characters) - 1)];
    }
    password[length] = '\0';
    close(fd);
}

// Parse HTTP Header
void parseHeaders(const char *request, char **bodyContent, char headers[][2][256], int *header_count) {
    const char *line = request;
    while (*line != '\0') {
        const char *colon = strstr(line, ": ");
        if (colon) {
            size_t key_len = colon - line;
            assert(key_len < 256 && "Header key too long");

            size_t value_len = strcspn(colon + 2, "\r\n");
            assert(value_len < 256 && "Header key too long");

            strncpy(headers[*header_count][0], line, key_len);
            headers[*header_count][0][key_len] = '\0';

            strncpy(headers[*header_count][1], colon + 2, value_len);
            headers[*header_count][1][value_len] = '\0';

            (*header_count)++;
            line = strstr(line, "\n") + 1;
        } else {
            break;
        }
    }

    // Extract body content
    char *bodyPtr = strstr(line, "\r\n\r\n");
    *bodyContent = bodyPtr ? 
                    bodyPtr + 4 : // Skip \r\n\r\n
                    NULL;         // No body
}

// Acquire lock and update response_size
void lockedUpdateResponseSize(uint64_t size) {
    pthread_mutex_lock(&mutex);
    response_size = size;
    printf("\n\n[*] Updated response size: %lu\n", response_size);
    pthread_mutex_unlock(&mutex);
}

void handleSecretPage(char *responseBuffer) {
    const char *response_header = "HTTP/1.1 200 OK\r\n"
                                  "Content-Type: text/html\r\n"
                                  "Connection: close\r\n\r\n";

    char response_body[BUFFER_SIZE] = "<html><body><h1>Secret Page</h1><p>The contents of the flag.txt are: </p><pre>";

    // Open the flag.txt file
    FILE *flagFile = fopen("flag.txt", "r");
    if (!flagFile) {
        printf("Please contact the admin.\n");
        exit(1);
    }

    // Read the file content
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), flagFile)) {
        strncat(response_body, buffer, BUFFER_SIZE - strlen(response_body) - 1);
    }
    fclose(flagFile);

    strncat(response_body, "</pre></body></html>", BUFFER_SIZE - strlen(response_body) - 1);

    snprintf(responseBuffer, BUFFER_SIZE * 2, "%s%s", response_header, response_body);
}

void handleAccessDenied(char *responseBuffer) {
    memset(responseBuffer, 0, malloc_usable_size(responseBuffer));
    const char *response = "HTTP/1.1 403 Forbidden\r\n"
                           "Content-Type: text/html\r\n"
                           "Connection: close\r\n\r\n"
                           "<html><body><h1>Access Denied</h1></body></html>";
    strcpy(responseBuffer, response);
}

// Generate HTTP response
void generateResponse(const char *method, const char *path, const char *body, char *responseBuffer) {
    sprintf(responseBuffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Connection: close\n\n"
            "<html><body>"
            "<!DOCTYPE html><html><head><title>Simple HTTP Server</title></head>\n"
            "<body><h1>Welcome to the Simple HTTP Server!</h1>\n"
            "<p>This is a basic response from the server.</p>\n"
            "<p>Method: %s</p>"
            "<p>Path: %s</p>"
            "<p>Body: %s</p>"
            "</body></html>",
            method, path, body);
}

int handleGetRequest(const char *path, char *responseBuffer) {
    if (strcmp(path, "/secret") == 0) {
        handleSecretPage(responseBuffer);
        if (!is_admin) {
            printf("[*] Access Denied\n");
            return HANDLE_FAIL;
        }
    } else {
        generateResponse("GET", path, "", responseBuffer);
    }

    return HANDLE_OK;
}

// Function to parse form data (at most 2 parameters)
// e.g. data = "username=admin&password=123456" 
//      params[0][0] = "username", params[0][1] = "admin", params[1][0] = "password", params[1][1] = "123456"
int parseFormData(const char *data, char *params[][2]) {
    int param_count = 0;
    const char *pair = data;
    const char *next_pair;

    char *key_value = calloc(strlen(data) + 1, 1);
    while (pair != NULL && param_count < MAX_PARAMS) {
        next_pair = strchr(pair, '&');

        if (next_pair != NULL) {
            size_t pair_length = next_pair - pair;
            strncpy(key_value, pair, pair_length);
            key_value[pair_length] = '\0';
        } else {
            strcpy(key_value, pair);
        }

        char *equals_pos = strchr(key_value, '=');
        if (equals_pos != NULL) {
            *equals_pos = '\0';
            strcpy(params[param_count][0], key_value);
            strcpy(params[param_count][1], equals_pos + 1);
            printf(" [PARAM] %s: %s\n", params[param_count][0], params[param_count][1]);
            param_count++;
        }

        if (next_pair != NULL) {
            pair = next_pair + 1;
        } else {
            pair = NULL;
        }
    }
    free(key_value);
    return param_count;
}

int handlePostRequest(const char *path, const char *body, char *responseBuffer) {
    char *params[MAX_PARAMS][2];
    for (int i = 0; i < MAX_PARAMS; i++) {
        params[i][0] = calloc(strlen(body) + 1, 1);
        params[i][1] = calloc(strlen(body) + 1, 1);
    }
    int param_count = parseFormData(body, params); // body can be null
    if (strcmp(path, "/login") == 0) {
        for (int i = 0; i < param_count; i++) {
            if (strcmp(params[i][0], "username") == 0 && strcmp(params[i][1], "admin") == 0) {
                for (int j = 0; j < param_count; j++) {
                    if (strcmp(params[j][0], "password") == 0 
                    && memcmp(params[j][1], admin_password, ADMIN_PASSWORD_LENGTH) == 0) {
                        // Login successful
                        is_admin = 1;
                    }
                }
            }
        }

        if (is_admin) {
            strcpy(responseBuffer,
                   "HTTP/1.1 200 OK\n"
                   "Content-Type: text/html\n"
                   "Connection: close\n\n"
                   "<html><body><h1>Login Successful</h1></body></html>");
        } else {
            strcpy(responseBuffer,
                   "HTTP/1.1 401 Unauthorized\n"
                   "Content-Type: text/html\n"
                   "Connection: close\n\n"
                   "<html><body><h1>Login Failed</h1></body></html>");
        }
    } else {
        generateResponse("POST", path, body, responseBuffer);
    }
    for (int i = 0; i < MAX_PARAMS; i++) {
        free(params[i][0]);
        free(params[i][1]);
    }
    return HANDLE_OK;
}

int handleHttpRequest(const char *request, char *responseBuffer) {
    char method[16], path[4096], version[16], *bodyContent;
    char headers[16][2][256];
    int header_count = 0, ret = HANDLE_OK;

    sscanf(request, "%15s %4095s %15s", method, path, version);

    parseHeaders(request, &bodyContent, headers, &header_count);
    printf("[%s] Body: %.10s ... (omitted)\n", method, (bodyContent ? bodyContent : "(empty)"));

    if (strcmp(method, "GET") == 0) {
        ret = handleGetRequest(path, responseBuffer);
    } else if (strcmp(method, "POST") == 0) {
        ret = handlePostRequest(path, bodyContent, responseBuffer);
    } else {
        // Unsupported method
        strcpy(responseBuffer,
               "<!DOCTYPE html><html><head><title>405 Method Not Allowed</title></head>"
               "<body><h1>405 Method Not Allowed</h1>"
               "<p>The request method is not supported by the server.</p>"
               "</body></html>");
    }

    lockedUpdateResponseSize(strlen(responseBuffer));

    // Partially dump valid `GET` response 
    if (ret != HANDLE_FAIL && strcmp(method, "GET") == 0) {
        char * ptr= responseBuffer;
        ptr = strstr(responseBuffer, "<p>Method");
        for (int i = 0; i < strlen(ptr) / 10; i++) {
            write(STDOUT_FILENO, ptr + i - 0, 1);
        }
    }
    return ret;
}

// Per-request handler on a separate thread
void *clientHandler(void *arg) {
    httpIO *io = (httpIO *)arg;
    char *rawRequest = io->rawRequest;
    char *responseBuffer = io->responseBuffer;

    printf("[*] Begin request handler\n");
    int res = handleHttpRequest(rawRequest, responseBuffer);
    if (res == HANDLE_FAIL) {
        printf("[*] Detect strange packet. Please wait...\n");
        sleep(3);
        goto cleanup;
    }
    else {
        printf("[+] Successfully handled request\n");
    }

    // Write the response to stdout (holding the lock)
    pthread_mutex_lock(&mutex);
    puts("\n=== Here is the response ===");
    write(STDOUT_FILENO, responseBuffer, response_size);
    puts("\n============================");
    pthread_mutex_unlock(&mutex);

cleanup:
    printf("[*] End request handler\n");
    free(rawRequest);
    free(responseBuffer);
    free(io);
    return NULL;
}

// Main loop
void startProcessing() {
    uint64_t packetLength;
    ssize_t bytesRead;

    while (1) {
        printf("[*] Waiting for the next packet...\n");
        bytesRead = read(STDIN_FILENO, &packetLength, sizeof(packetLength));
        if (bytesRead < sizeof(packetLength)) {
            dprintf(2, "Failed to read packet length\n");
            return;
        }
        
        printf("[*] Packet length: %lu\n", packetLength);
        char *rawRequest = calloc(packetLength + 1, 1);
        if (!rawRequest) {
            dprintf(2, "Failed to allocate memory for request\n");
            return;
        }

        ssize_t totalBytesRead = 0;
        
        while (totalBytesRead < packetLength) {
            bytesRead = read(0, &rawRequest[totalBytesRead], packetLength - totalBytesRead);
            if (bytesRead <= 0) {
                dprintf(2, "Failed to read the complete packet\n");
                return;
            }
            totalBytesRead += bytesRead;
        }

        rawRequest[packetLength] = '\0'; // null-terminate the string
        httpIO *arg = calloc(sizeof(httpIO), 1);
        arg->rawRequest = rawRequest;
        char *responseBuffer = calloc(packetLength + 0x300, 1);
        if (!responseBuffer) {
            dprintf(2, "Failed to allocate memory for response\n");
            return;
        }
        arg->responseBuffer = responseBuffer;

        pthread_t thread;
        int ret = pthread_create(&thread, NULL, clientHandler, arg);
        if (ret != 0) {
            dprintf(2, "Failed to create thread\n");
            free(arg->rawRequest);
            free(arg->responseBuffer);
            free(arg);
        }
        pthread_detach(thread);
    }
}

int main() {
    generateRandomPassword(admin_password, ADMIN_PASSWORD_LENGTH);
    startProcessing();
    return 0;
}
