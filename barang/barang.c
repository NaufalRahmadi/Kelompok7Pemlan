#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define FILENAME "barang.txt"
#define LOGFILE "riwayat.txt"

typedef struct {
    int  id;
    char nama[50];
    char kategori[50]; // Menambahkan kategori barang
    int  jumlah;
    char lokasi[50];
    char tanggal[20]; // Untuk menyimpan tanggal penambahan
} Barang;

Barang barang[MAX];
int jumlahBarang = 0;

void writeLog(const char *aksi, Barang b) {
    FILE *logFile = fopen(LOGFILE, "a");
    if (!logFile) {
        printf("Gagal membuka file log!\n");
        return;
    }
    time_t now = time(NULL);
    fprintf(logFile, "%s: %s | ID: %d, Nama: %s, Stok: %d, Lokasi Penyimpanan: %s\n",
            aksi, ctime(&now), b.id, b.nama, b.jumlah, b.lokasi);
    fclose(logFile);
}

void saveFile() {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("Gagal membuka file data!\n");
        return;
    }
    
    int i;
    for (i = 0; i < jumlahBarang; i++) {
        fprintf(file, "%d %s %s %d %s %s\n", barang[i].id, barang[i].nama, barang[i].kategori,
                barang[i].jumlah, barang[i].lokasi, barang[i].tanggal);
    }
    fclose(file);
}

void readFile() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) return;

    jumlahBarang = 0;
    while (fscanf(file, "%d %49s %49s %d %49s %19s",
                  &barang[jumlahBarang].id, barang[jumlahBarang].nama, barang[jumlahBarang].kategori,
                  &barang[jumlahBarang].jumlah, barang[jumlahBarang].lokasi,
                  barang[jumlahBarang].tanggal) == 6) {
        jumlahBarang++;
    }
    fclose(file);
}

void insertBarang() {
    Barang barang1;
    printf("Masukkan ID Barang: ");
    scanf("%d", &barang1.id);
    printf("Masukkan Nama Barang: ");
    scanf("%s", barang1.nama);
    printf("Masukkan Kategori Barang: ");
    scanf("%s", barang1.kategori);
    printf("Masukkan Stok Barang: ");
    scanf("%d", &barang1.jumlah);
    printf("Masukkan Kode Lokasi Penyimpanan Barang: ");
    scanf("%s", barang1.lokasi);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(barang1.tanggal, sizeof(barang1.tanggal), "%Y-%m-%d", t);

    barang[jumlahBarang++] = barang1;
    saveFile();
    writeLog("Insert", barang1);
    printf("Barang berhasil ditambahkan pada %s!\n", barang1.tanggal);
}

void deleteBarang() {
    if (jumlahBarang == 0) {
        printf("Inventaris kosong.\n");
        return;
    }

    int id;
    printf("Masukkan ID Barang yang akan dihapus: ");
    scanf("%d", &id);

    int found = 0;
    int i, j;
    for (i = 0; i < jumlahBarang; i++) {
        if (barang[i].id == id) {
            writeLog("Delete", barang[i]);
            for (j = i; j < jumlahBarang - 1; j++) {
                barang[j] = barang[j + 1];
            }
            jumlahBarang--;
            found = 1;
            break;
        }
    }

    if (found) {
        saveFile();
        printf("Barang berhasil dihapus.\n");
    } else {
        printf("Barang dengan ID tersebut tidak ditemukan.\n");
    }
}

void searchBarang() {
    int id, i;
    printf("Masukkan ID Barang yang ingin dicari: ");
    scanf("%d", &id);

    for (i = 0; i < jumlahBarang; i++) {
        if (barang[i].id == id) {
            printf("Barang dengan ID %d ditemukan\n", id);
            printf("%-10s %-20s %-20s %-10s %-20s\n", "ID", "Nama", "Kategori", "Stok", "Lokasi");
            printf("===============================================================\n");
            printf("%-10d %-20s %-20s %-10d %-20s\n", barang[i].id, barang[i].nama, barang[i].kategori,
                   barang[i].jumlah, barang[i].lokasi);
            return;
        }
    }
    printf("Barang dengan ID tersebut tidak ditemukan.\n");
}

void viewBarang() {
    printf("Data barang:\n");
    printf("%-10s %-20s %-20s %-10s %-20s\n", "ID", "Nama", "Kategori", "Stok", "Lokasi");
    printf("===============================================================\n");
    
    int i;
    for (i = 0; i < jumlahBarang; i++) {
        printf("%-10d %-20s %-20s %-10d %-20s\n", barang[i].id, barang[i].nama, barang[i].kategori,
               barang[i].jumlah, barang[i].lokasi);
    }
}

void viewLaporan() {
    FILE *logFile = fopen(LOGFILE, "r");
    if (!logFile) {
        printf("Tidak ada laporan.\n");
        return;
    }
    char ch;
    while ((ch = fgetc(logFile)) != EOF) {
        putchar(ch);
    }
    fclose(logFile);
}

void sortirBarang() {
    if (jumlahBarang == 0) {
        printf("Inventaris kosong.\n");
        return;
    }

    int pilihan;
    printf("\nPilih kriteria sortir:\n");
    printf("1. Berdasarkan ID\n");
    printf("2. Berdasarkan Nama\n");
    printf("3. Berdasarkan Waktu (Tanggal barang ditambahkan)\n");
    printf("Pilih opsi: ");
    scanf("%d", &pilihan);

    int i, j;
    for (i = 0; i < jumlahBarang - 1; i++) {
        for (j = i + 1; j < jumlahBarang; j++) {
            int swap = 0;
            if (pilihan == 1 && barang[i].id > barang[j].id) {
                swap = 1;
            } else if (pilihan == 2 && strcmp(barang[i].nama, barang[j].nama) > 0) {
                swap = 1;
            } else if (pilihan == 3 && strcmp(barang[i].tanggal, barang[j].tanggal) > 0) {
                swap = 1;
            }
            if (swap) {
                Barang temp = barang[i];
                barang[i] = barang[j];
                barang[j] = temp;
            }
        }
    }

    printf("Barang berhasil diurutkan.\n");
}

void menuBarang() {
    int pilihan;
    do {
        printf("\nMenu Barang:\n");
        printf("1. Tambah Barang\n");
        printf("2. Hapus Barang\n");
        printf("3. Cari Barang\n");
        printf("4. Lihat Barang\n");
        printf("5. Kembali ke Menu Utama\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
        case 1:
            insertBarang();
            break;
        case 2:
            deleteBarang();
            break;
        case 3:
            searchBarang();
            break;
        case 4:
            viewBarang();
            break;
        case 5:
            printf("Kembali ke Menu Utama.\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 5);
}

int main() {
    int pilihan;
    readFile();

    do {
        printf("\nMenu Utama:\n");
        printf("1. Menu Barang\n");
        printf("2. Sorting Barang\n");
        printf("3. Lihat Laporan\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
        case 1:
            menuBarang();
            break;
        case 2:
            sortirBarang();
            break;
        case 3:
            viewLaporan();
            break;
        case 4:
            printf("Keluar dari program.\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 4);

    return 0;
}

