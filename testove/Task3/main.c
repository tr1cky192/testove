#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEYS 200
#define MAX_CHESTS 200
#define IMPOSSIBLE -1

typedef struct {
    int required_key;  // ключ, необхідний для відкриття скрині
    int num_keys_inside;  // кількість ключів у скрині
    int keys_inside[MAX_KEYS];  // типи ключів у скрині
} Chest;

Chest chests[MAX_CHESTS];
bool opened[MAX_CHESTS]; // для відстеження відкритих скринь
bool have_key[MAX_KEYS]; // для відстеження наявних ключів
int order[MAX_CHESTS]; // для відстеження порядку відкритих скринь

// Функція для порівняння
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b); // Просто порівняння цілих чисел
}

int canOpenAllChests(int N) {
    int openedCount = 0;

    while (openedCount < N) {
        bool found = false;

        // Зберігання індексів скринь, які можна відкрити
        int possibleChests[MAX_CHESTS];
        int possibleCount = 0;

        // Знайти всі скрині, які можна відкрити
        for (int i = 0; i < N; i++) {
            if (!opened[i] && have_key[chests[i].required_key - 1]) {
                possibleChests[possibleCount++] = i; // Зберегти індекс
            }
        }

        // Якщо ми знайшли можливі скрині, відкриваємо лексикографічно найменшу
        if (possibleCount > 0) {
            // Сортуємо можливі скрині
            qsort(possibleChests, possibleCount, sizeof(int), compare);

            // Відкриваємо першу (найменший індекс)
            int chestToOpen = possibleChests[0];
            opened[chestToOpen] = true; // Позначаємо скриню як відкриту
            order[openedCount++] = chestToOpen + 1; // Зберігаємо результат (1-індекс)

            // Додаємо ключі, що знаходяться в скрині
            for (int j = 0; j < chests[chestToOpen].num_keys_inside; j++) {
                have_key[chests[chestToOpen].keys_inside[j] - 1] = true;
            }
            found = true; // Ми знайшли хоча б одну скриню для відкриття
        }

        if (!found) {
            return IMPOSSIBLE; // якщо не можна відкрити жодну скриню
        }
    }
    return 0; // всі скрині можна відкрити
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Використання: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Відкриваємо вхідний файл для читання
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Не вдалося відкрити файл: %s\n", argv[1]);
        return 1;
    }

    int T; // кількість тестових випадків
    fscanf(file, "%d", &T); // Читаємо кількість тестових випадків
    for (int caseNumber = 1; caseNumber <= T; caseNumber++) {
        int K, N; // Кількість ключів і кількість скринь
        fscanf(file, "%d %d", &K, &N);

        // Ініціалізуємо масиви
        memset(opened, false, sizeof(opened));
        memset(have_key, false, sizeof(have_key));

        // Зчитуємо початкові ключі
        for (int i = 0; i < K; i++) {
            int key;
            fscanf(file, "%d", &key);
            have_key[key - 1] = true; // Зберігаємо ключ (з поправкою на 0-індексацію)
        }

        // Зчитуємо інформацію про скрині
        for (int i = 0; i < N; i++) {
            fscanf(file, "%d %d", &chests[i].required_key, &chests[i].num_keys_inside);
            for (int j = 0; j < chests[i].num_keys_inside; j++) {
                fscanf(file, "%d", &chests[i].keys_inside[j]);
            }
        }

        // Перевіряємо, чи можна відкрити всі скрині
        if (canOpenAllChests(N) == IMPOSSIBLE) {
            printf("Case #%d: IMPOSSIBLE\n", caseNumber);
        } else {
            printf("Case #%d: ", caseNumber);
            for (int i = 0; i < N; i++) {
                printf("%d ", order[i]); // Виводимо індекс відкритих скринь (1-індекс)
            }
            printf("\n");
        }
    }

    fclose(file); // Закриваємо файл
    return 0;
}
