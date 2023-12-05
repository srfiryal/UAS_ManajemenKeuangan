#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_TRANSACTION 50
#define MAX_NAME 20

typedef struct {
    int nominal;
    char name[MAX_NAME + 1];
    char type;
} transaction;

transaction transactions[MAX_TRANSACTION];
int length = 0;

int main()
{
    int choice;
    char isAccessing;

    puts("===== Aplikasi Manajemen Keuangan =====");
    puts("1. Buat catatan baru");
    puts("2. Hitung saldo");
    puts("3. Laporan keuangan");

    do {
        printf("\nPilih layanan: ");
        scanf("%d", &choice);
        fflush(stdin);
        puts("");
    } while(choice < 1 || choice > 3);

    switch(choice) {
        case 1:
            addTransaction();
            break;
        case 2:
            getBalance();
            break;
        case 3:
            getReport();
            break;
    }

    do {
        printf("\nIngin menggunakan transaksi lain (Y/T)? ");
        isAccessing = getchar();
        fflush(stdin);
        puts("");
    } while(isAccessing != 'Y' && isAccessing != 'y' && isAccessing != 'T' && isAccessing != 't');

    if (isAccessing == 'Y' || isAccessing == 'y')
        main();
    else {
        puts("===== Selesai =====");
    }

    return 0;
}

void addTransaction() {
    int nameLength;

    puts("===== Tambah Catatan Baru =====");

    printf("Nama transaksi\t: ");
    fgets(transactions[length].name, MAX_NAME, stdin);
    fflush(stdin);

    nameLength = strlen(transactions[length].name);
    if(transactions[length].name[nameLength - 1] == '\n')
        transactions[length].name[nameLength - 1] = 0;

    printf("Nominal\t\t: Rp ");
    scanf("%d, ", &transactions[length].nominal);
    fflush(stdin);

    printf("Tipe (+ / -)\t: ");
    transactions[length].type = getchar();
    fflush(stdin);

    length++;

    printf("\nTransaksi sukses ditambahkan!\n");
}

void getBalance() {
    int i, balance = 0;

    puts("===== Hitung Saldo =====");

    for (i = 0; i < length; i++) {
        if (transactions[i].type == '+') {
            balance += transactions[i].nominal;
        } else {
            balance -= transactions[i].nominal;
        }
    }

    printf("Jumlah saldo\t: %cRp %d\n", balance < 0 ? '-' : 0, abs(balance));
}

void getReport() {
    int i, balance = 0, income = 0, outcome = 0;

    printf("===== Laporan Keuangan =====\n\n");
    puts("---------------------------------------------------------");
    puts("| Nama Transaksi\t | Kategori\t | Nominal\t|");
    puts("---------------------------------------------------------");

    if (length == 0) {
        puts("|                  Belum ada transaksi                  |");
    } else {
        for (i = 0; i < length; i++) {
            printf("| %s\t\t | %s\t | %cRp %7d \t|\n", transactions[i].name, transactions[i].type == '+' ? "Pemasukan" : "Pengeluaran", transactions[i].type, transactions[i].nominal);

            if (transactions[i].type == '+') {
                balance += transactions[i].nominal;
                income += transactions[i].nominal;
            } else {
                balance -= transactions[i].nominal;
                outcome += transactions[i].nominal;
            }
        }
    }

    puts("---------------------------------------------------------");

    printf("\nTotal pemasukan\t\t: +Rp %7d\n", income);
    printf("Total pengeluaran\t: -Rp %7d\n", outcome);
    printf("Jumlah saldo\t\t:  Rp %7d\n", balance);
}
