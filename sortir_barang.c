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
