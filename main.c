#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_TRANSACTION 50
#define MAX_NAME 20

// Struct transaksi
typedef struct {
    char name[MAX_NAME + 1];
    int nominal;
    char type;
} transaction;

// Prototype
void mainMenu();
void addTransaction();
void getBalance();
void getReport();

// Variabel global
transaction transactions[MAX_TRANSACTION];
int length = 0;

// Fungsi Main
int main()
{
    mainMenu();

    return 0;
}

// Fungsi pemilihan layanan
void mainMenu() {
    int choice;
    char isAccessing;

    do {
        // Menampilkan menu layanan
        puts("===== Aplikasi Manajemen Keuangan =====");
        puts("1. Buat catatan baru");
        puts("2. Hitung saldo");
        puts("3. Laporan keuangan");

        // Input layanan yang dipilih
        do {
            printf("\nPilih layanan: ");
            scanf("%d", &choice);
            fflush(stdin);
            puts("");
        } while(choice < 1 || choice > 3);

        // Menjalankan fungsi sesuai yang dipilih
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

        // Input apakah mau melakukan transaksi lain
        // Jika iya, kembali ke awal fungsi mainMenu()
        do {
            printf("\nIngin melakukan transaksi lain (Y/T)? ");
            isAccessing = getchar();
            fflush(stdin);
            puts("");
        } while(isAccessing != 'Y' && isAccessing != 'y' && isAccessing != 'T' && isAccessing != 't');
    } while (isAccessing == 'Y' || isAccessing == 'y');

    puts("===== Selesai =====");
}

// Fungsi tambah catatan transaksi
void addTransaction() {
    int nameLength;

    puts("===== Tambah Catatan Baru =====");

    // Input nama transaksi
    printf("Nama transaksi\t: ");
    fgets(transactions[length].name, MAX_NAME, stdin);
    fflush(stdin);

    nameLength = strlen(transactions[length].name);
    if(transactions[length].name[nameLength - 1] == '\n')
        transactions[length].name[nameLength - 1] = 0;

    // Input nominal transaksi
    printf("Nominal\t\t: Rp ");
    scanf("%d, ", &transactions[length].nominal);
    fflush(stdin);

    // Input tipe transaksi, pemasukan/pengeluaran
    do {
        printf("Tipe (+ / -)\t: ");
        transactions[length].type = getchar();
        fflush(stdin);
    } while (transactions[length].type != '+' && transactions[length].type != '-');

    length++;

    printf("\nTransaksi sukses ditambahkan!\n");
}

// Fungsi hitung saldo
void getBalance() {
    int i, balance = 0;

    puts("===== Hitung Saldo =====");

    // Menjumlahkan semua nominal dari array transactions
    for (i = 0; i < length; i++) {
        if (transactions[i].type == '+') {
            balance += transactions[i].nominal;
        } else {
            balance -= transactions[i].nominal;
        }
    }

    printf("Jumlah saldo\t: %cRp %d\n", balance < 0 ? '-' : 0, abs(balance));
}

// Fungsi laporan keuangan
void getReport() {
    int i, balance = 0, income = 0, outcome = 0;

    printf("===== Laporan Keuangan =====\n\n");
    puts("---------------------------------------------------------");
    puts("| Nama Transaksi\t | Tipe\t\t | Nominal\t|");
    puts("---------------------------------------------------------");

    if (length == 0) {
        puts("|                  Belum ada transaksi                  |");
    } else {
        for (i = 0; i < length; i++) {
            // Print tabel transaksi
            printf("| %s\t\t | %s\t | %cRp %7d \t|\n", transactions[i].name, transactions[i].type == '+' ? "Pemasukan" : "Pengeluaran", transactions[i].type, transactions[i].nominal);

            if (transactions[i].type == '+') {
                // Menjumlahkan total saldo dan total pemasukan
                balance += transactions[i].nominal;
                income += transactions[i].nominal;
            } else {
                // Menjumlahkan total saldo dan total pengeluaran
                balance -= transactions[i].nominal;
                outcome += transactions[i].nominal;
            }
        }
    }

    puts("---------------------------------------------------------");

    // Print total pemasukan, pengeluaran, dan saldo
    printf("\nTotal pemasukan\t\t: +Rp %7d\n", income);
    printf("Total pengeluaran\t: -Rp %7d\n", outcome);
    printf("Jumlah saldo\t\t:  Rp %7d\n", balance);
}
