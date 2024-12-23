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
