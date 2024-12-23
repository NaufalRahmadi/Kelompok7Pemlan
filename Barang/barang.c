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
