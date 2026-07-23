/**
 * Program Kalkulasi Resep Minuman
 * ================================
 * Program ini menghitung bahan-bahan yang dibutuhkan
 * berdasarkan jumlah resep yang diinginkan.
 *
 * Daftar Resep:
 * 1. Base Teh          : bubuk teh naga 2 pack, bubuk teh gopek 1 pack, air 3000ml
 * 2. Biang Orange      : powder orange 1pack(560gr), air panas 1000ml, air suhu ruang 4000ml
 * 3. Biang Lemon Tea   : powder lemon tea 1pack(560gr), air panas 1000ml, simple sirup 375ml, air suhu ruang 2625ml
 * 4. Base Thai Tea     : bubuk thai tea 150gr, air panas 2000ml, creamer bubuk 80gr
 * 5. Biang Milo        : powder milo 1 pack(960gr), air panas 500ml, simple sirup 160ml, air suhu ruang 1580ml
 * 6. Biang Green Tea   : bubuk green tea 150gr, air panas 2000ml, creamer bubuk 248gr, susu evaporasi 630ml, skm 630gr, basic syrup 630gr
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

struct Bahan {
    string nama;
    double jumlah;
    string satuan;
    double konversi_pack_ke_gram; // 0 jika tidak relevan
};

struct Resep {
    string nama;
    vector<Bahan> bahan_list;
    double total_volume_ml;
};

vector<Resep> initResep() {
    vector<Resep> daftar_resep;

    // 1. Base Teh
    Resep r1;
    r1.nama = "Base Teh";
    r1.bahan_list = {
        {"Bubuk Teh Naga", 2, "pack", 250},
        {"Bubuk Teh Gopek", 1, "pack", 250},
        {"Air", 3000, "ml", 0}
    };
    r1.total_volume_ml = 3000;
    daftar_resep.push_back(r1);

    // 2. Biang Orange
    Resep r2;
    r2.nama = "Biang Orange";
    r2.bahan_list = {
        {"Powder Orange", 1, "pack", 560},
        {"Air Panas", 1000, "ml", 0},
        {"Air Suhu Ruang", 4000, "ml", 0}
    };
    r2.total_volume_ml = 5000;
    daftar_resep.push_back(r2);

    // 3. Biang Lemon Tea
    Resep r3;
    r3.nama = "Biang Lemon Tea";
    r3.bahan_list = {
        {"Powder Lemon Tea", 1, "pack", 560},
        {"Air Panas", 1000, "ml", 0},
        {"Simple Sirup", 375, "ml", 0},
        {"Air Suhu Ruang", 2625, "ml", 0}
    };
    r3.total_volume_ml = 4000;
    daftar_resep.push_back(r3);

    // 4. Base Thai Tea
    Resep r4;
    r4.nama = "Base Thai Tea";
    r4.bahan_list = {
        {"Bubuk Thai Tea", 150, "gr", 0},
        {"Air Panas", 2000, "ml", 0},
        {"Creamer Bubuk", 80, "gr", 0}
    };
    r4.total_volume_ml = 2000;
    daftar_resep.push_back(r4);

    // 5. Biang Milo
    Resep r5;
    r5.nama = "Biang Milo";
    r5.bahan_list = {
        {"Powder Milo", 1, "pack", 960},
        {"Air Panas", 500, "ml", 0},
        {"Simple Sirup", 160, "ml", 0},
        {"Air Suhu Ruang", 1580, "ml", 0}
    };
    r5.total_volume_ml = 2240;
    daftar_resep.push_back(r5);

    // 6. Biang Green Tea
    Resep r6;
    r6.nama = "Biang Green Tea";
    r6.bahan_list = {
        {"Bubuk Green Tea", 150, "gr", 0},
        {"Air Panas", 2000, "ml", 0},
        {"Creamer Bubuk", 248, "gr", 0},
        {"Susu Evaporasi", 630, "ml", 0},
        {"SKM", 630, "gr", 0},
        {"Basic Syrup", 630, "ml", 0}
    };
    r6.total_volume_ml = 3260;
    daftar_resep.push_back(r6);

    return daftar_resep;
}

void tampilkanResep(const Resep& r, double jumlah_resep = 1.0) {
    cout << "\n";
    cout << "========================================\n";
    cout << "  " << r.nama << "\n";
    cout << "  " << jumlah_resep << "x resep\n";
    cout << "========================================\n";

    cout << left << setw(28) << "Nama Bahan"
         << right << setw(14) << "Jumlah"
         << "  Satuan\n";
    cout << string(58, '-') << "\n";

    for (const auto& b : r.bahan_list) {
        double jumlah = b.jumlah * jumlah_resep;

        if (b.satuan == "pack" && b.konversi_pack_ke_gram > 0) {
            double pack_bulat;
            double sisa_pack = modf(jumlah, &pack_bulat);

            if (sisa_pack > 0.001) {
                // Ada pecahan pack
                double gram = jumlah * b.konversi_pack_ke_gram;
                cout << left << setw(28) << b.nama
                     << right << setw(10) << fixed << setprecision(3) << jumlah
                     << "  pack";
                cout << "  (" << fixed << setprecision(1) << gram << " gr)";
            } else {
                double gram = jumlah * b.konversi_pack_ke_gram;
                cout << left << setw(28) << b.nama
                     << right << setw(10) << fixed << setprecision(0) << jumlah
                     << "  pack";
                cout << "  (" << fixed << setprecision(1) << gram << " gr)";
            }
        } else {
            cout << left << setw(28) << b.nama
                 << right << setw(10) << fixed << setprecision(1) << jumlah
                 << "  " << b.satuan;
        }
        cout << "\n";
    }

    cout << string(58, '-') << "\n";
    cout << "Total Volume: " << fixed << setprecision(1)
         << r.total_volume_ml * jumlah_resep << " ml\n";
    cout << "Estimasi Gelas (@250ml): "
         << fixed << setprecision(1)
         << (r.total_volume_ml * jumlah_resep) / 250.0 << " gelas\n";
    cout << "\n";
}

int main() {
    vector<Resep> daftar_resep = initResep();
    int pilihan;

    do {
        cout << "\n\n";
        cout << "========================================\n";
        cout << "     KALKULATOR RESEP MINUMAN\n";
        cout << "========================================\n";
        cout << "\n";
        cout << "Pilih resep:\n";
        cout << "----------------------------------------\n";

        for (size_t i = 0; i < daftar_resep.size(); i++) {
            cout << "  " << (i + 1) << ". " << daftar_resep[i].nama << "\n";
        }

        cout << "----------------------------------------\n";
        cout << "  0. Keluar\n";
        cout << "========================================\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan >= 1 && pilihan <= (int)daftar_resep.size()) {
            int idx = pilihan - 1;

            cout << "\n--- " << daftar_resep[idx].nama << " ---\n";
            cout << "Masukkan jumlah resep yang diinginkan: ";
            double jumlah_resep;
            cin >> jumlah_resep;

            if (jumlah_resep > 0) {
                tampilkanResep(daftar_resep[idx], jumlah_resep);

                // Opsi setelah hitung
                int opsi;
                do {
                    cout << "----------------------------------------\n";
                    cout << "  1. Hitung resep lainnya\n";
                    cout << "  2. Keluar\n";
                    cout << "----------------------------------------\n";
                    cout << "Pilihan: ";
                    cin >> opsi;

                    if (opsi == 1) {
                        break; // kembali ke menu utama (loop luar)
                    } else if (opsi == 2) {
                        pilihan = 0; // set pilihan jadi 0 agar loop luar berhenti
                        break;
                    } else {
                        cout << "\n[!] Pilihan tidak valid!\n";
                    }
                } while (true);

            } else {
                cout << "\n[!] Jumlah resep harus lebih dari 0!\n";
            }
        }
        else if (pilihan != 0) {
            cout << "\n[!] Pilihan tidak valid! Silakan coba lagi.\n";
        }

    } while (pilihan != 0);

    cout << "\nTerima kasih! Program selesai.\n\n";

    return 0;
}

