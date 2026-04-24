#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_LINE 256
#define MAX_EMPLOYEES 1000

typedef struct {
    char name[MAX_NAME];
    int id;
    char level[20];
} Employee;

void save_to_binary(Employee* employees, int count, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) { perror("Ошибка записи"); return; }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(employees, sizeof(Employee), count, file);
    fclose(file);
}

int load_and_search(const char* filename, int search_id) {
    FILE* file = fopen(filename, "rb");
    if (!file) { perror("Ошибка поиска"); return -1; }
    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) { fclose(file); return -1; }
    Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(Employee), 1, file) == 1) {
        if (emp.id == search_id) {
            printf("Найден: %s (ID: %d, %s)\n", emp.name, emp.id, emp.level);
            found = 1; break;
        }
    }
    fclose(file);
    if (!found) printf("ID %d не найден\n", search_id);
    return found;
}

long get_file_size(const char* filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return (size + 1023) / 1024;
}

void compress(const char* input, const char* output) {
    FILE *in = fopen(input, "rb"), *out = fopen(output, "wb");
    if (!in || !out) { perror("Ошибка сжатия"); return; }
    
    unsigned char byte, prev_byte;
    int run = 1;
    
    if (fread(&prev_byte, 1, 1, in) != 1) { fclose(in); fclose(out); return; }
    
    while (fread(&byte, 1, 1, in) == 1) {
        if (byte == prev_byte && run < 255) run++;
        else {
            fputc(run, out); fputc(prev_byte, out);
            prev_byte = byte; run = 1;
        }
    }
    fputc(run, out); fputc(prev_byte, out);
    fclose(in); fclose(out);
}

void decompress(const char* input, const char* output) {
    FILE *in = fopen(input, "rb"), *out = fopen(output, "wb");
    if (!in || !out) { perror("Ошибка"); return; }
    unsigned char run, byte;
    while (fread(&run, 1, 1, in) == 1 && fread(&byte, 1, 1, in) == 1) {
        for (int i = 0; i < run; i++) fputc(byte, out);
    }
    fclose(in); fclose(out);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s staff.csv\n", argv[0]);
        return 1;
    }

    FILE *csv = fopen(argv[1], "r");
    if (!csv) { perror("CSV"); return 1; }

    Employee employees[MAX_EMPLOYEES];
    int count = 0;
    
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), csv) && count < MAX_EMPLOYEES) {
        line[strcspn(line, "\n")] = 0;
        char *name = strtok(line, ";");
        char *id_str = strtok(NULL, ";");
        char *level = strtok(NULL, ";");
        if (name && id_str && level) {
            strncpy(employees[count].name, name, MAX_NAME-1);
            employees[count].name[MAX_NAME-1] = '\0';
            employees[count].id = atoi(id_str);
            strncpy(employees[count].level, level, 19);
            employees[count].level[19] = '\0';
            printf("%-20s %-6d %-10s\n", employees[count].name, 
                   employees[count].id, employees[count].level);
            count++;
        }
    }
    fclose(csv);

    save_to_binary(employees, count, "database.dat");
    
    compress("database.dat", "database.rle");
    decompress("database.rle", "database_restored.dat");

    long orig = get_file_size("database.dat");
    long comp = get_file_size("database.rle");
    printf("\nСжатие:\nРазмер до:     %ld Кб\nРазмер после:  %ld Кб\n", orig, comp);
    if (orig > 0) printf("Сжатие:        %.1f%%\n", (1.0 - (double)comp/orig)*100);

    int search_id;
    printf("\nID для поиска: ");
    fflush(stdout);
    if (scanf("%d", &search_id) == 1) {
        load_and_search("database.dat", search_id);
    }
    return 0;
}