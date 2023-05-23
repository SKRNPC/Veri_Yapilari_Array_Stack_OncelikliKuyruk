#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

// Kişi veri yapısı
struct Kisi {
    int numara;
    int islemSuresi;
    bool operator<(const Kisi& other) const {
        if (islemSuresi == other.islemSuresi) {
            return numara > other.numara;
        }
        else {
            return islemSuresi > other.islemSuresi;
        }
    }
};

int main() {
    // Random sayı üretimi için srand fonksiyonu kullanılıyor
    srand(time(0));

    int N;
    cout << "Kac kisi icin kuyruk olusturulsun? ";
    cin >> N;

    // Yığın oluşturma işlemi
    Kisi* yigin = new Kisi[N];
    for (int i = 0; i < N; i++) {
        yigin[i].numara = i + 1;
        yigin[i].islemSuresi = rand() % 271 + 30; // Random işlem süresi belirleme
    }

    // Yığın sıralama işlemi
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (yigin[i].islemSuresi < yigin[j].islemSuresi) {
                Kisi temp = yigin[i];
                yigin[i] = yigin[j];
                yigin[j] = temp;
            }
        }
    }

    // Öncelikli kuyruk yapısı için priority_queue kullanımı
    priority_queue<Kisi> kuyruk;
    for (int i = 0; i < N; i++) {
        kuyruk.push(yigin[i]);
    }

    // Öncelikli kuyruk yapısı ile kuyruk işlemleri
    cout << "Oncelikli kuyruk yapisi ile kuyruk islemleri:" << endl;

    int toplamSure = 0; // Toplam işlem süresi
    while (!kuyruk.empty()) {
        Kisi kisi = kuyruk.top();
        kuyruk.pop();
        toplamSure += kisi.islemSuresi; // Toplam işlem süresine ekleme
        cout << "Kisi numarasi: " << kisi.numara << ", islem suresi: " << kisi.islemSuresi;
        cout << ", kuyrukta kalma suresi: " << toplamSure << endl;
    }

    // Ortalama işlem süresi
    float ortalamaSure = (float)toplamSure / N;
    cout << "Ortalama islem suresi: " << ortalamaSure << endl;

    // Bellekten yığın alanının temizlenmesi
    delete[] yigin;

    return 0;
}
