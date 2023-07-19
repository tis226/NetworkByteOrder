    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <netinet/in.h>

    typedef struct {
        const char *filename;
        FILE *file;
        uint32_t value;
    } FileData;

    FileData* open_file(const char *filename) {
        FileData *data = malloc(sizeof(FileData));
        if (data == NULL) {
            fprintf(stderr, "Error allocating memory.\n");
            exit(EXIT_FAILURE);
        }
        data->filename = filename;
        data->file = fopen(filename, "rb");
        if (data->file == NULL) {
            fprintf(stderr, "Error opening a file: %s\n", filename);
            free(data);
            exit(EXIT_FAILURE);
        }
        return data;
    }

    uint32_t read_int32(FileData *data) {
        fread(&(data->value), sizeof(uint32_t), 1, data->file);
        fclose(data->file);
        free(data);
        return ntohl(data->value);
    }

    int main(int argc, char *argv[]) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
            return EXIT_FAILURE;
        }

        FileData *file1 = open_file(argv[1]);
        uint32_t num1 = read_int32(file1);

        FileData *file2 = open_file(argv[2]);
        uint32_t num2 = read_int32(file2);

        uint32_t sum = num1 + num2;
        printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", num1, num1, num2, num2, sum, sum);

        return EXIT_SUCCESS;
    }

