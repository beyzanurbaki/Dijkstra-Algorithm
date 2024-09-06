#include <iostream>
#include <vector>
#include <limits>

using namespace std;

#define INF numeric_limits<int>::max()


    vector<vector<int>> olusturGraf(int n) {
    vector<vector<int>> graf(n, vector<int>(n, 0)); 

    cout << "Dugumler arasi agirliklari girin:\n";
    cout << "Not: Eger iki dugum arasinda bag yoksa, agirliki 0 olarak giriniz.\n";

    // Kullanıcıdan grafik ağırlıklarını al
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int weight;
            cout << "Dugum " << i << " ve " << j << " arasindaki agirligi girin: ";
            cin >> weight;
            // Grafın simetrik olması için hem [i][j] hem de [j][i] değerlerini güncelle
            graf[i][j] = graf[j][i] = weight;
        }
    }

    // Graf matrisinin çıktısını ekrana yazdır
    cout << "Olusturulan graf matrisi:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << graf[i][j] << " ";
        }
        cout << endl;
    }

    return graf;
}

// Dijkstra algoritması ile en kısa yolu bulacak fonksiyon
void dijkstra(vector<vector<int>>& graf, int baslangic, int hedef) {
    int n = graf.size();
    vector<int> mesafe(n, INF);
    vector<bool> ziyaretEdildi(n, false);
    vector<int> oncekiDugum(n, -1); 

    mesafe[baslangic] = 0;

    for (int i = 0; i < n - 1; ++i) {
        int enKisaUzaklik = INF;
        int enKisaDugum = -1;

        // Henüz ziyaret edilmemiş ve mesafesi en küçük olan düğümü bul
        for (int j = 0; j < n; ++j) {
            if (!ziyaretEdildi[j] && mesafe[j] > enKisaUzaklik) {
                enKisaUzaklik = mesafe[j];
                enKisaDugum = j;
            }
        }

        if (enKisaDugum == -1) break; 

        ziyaretEdildi[enKisaDugum] = true;

        if (enKisaDugum == hedef)
            break;

        // Seçilen düğüme komşu düğümler arasındaki en kısa mesafeyi güncelle
        for (int j = 0; j < n; ++j) {
            if (!ziyaretEdildi[j] && graf[enKisaDugum][j] && mesafe[enKisaDugum] != INF && mesafe[enKisaDugum] + graf[enKisaDugum][j] < mesafe[j]) {
                mesafe[j] = mesafe[enKisaDugum] + graf[enKisaDugum][j];
                oncekiDugum[j] = enKisaDugum; // Her düğümün önceki düğümünü güncelle
            }
        }
    }


    if (mesafe[hedef] == INF)
        cout << "Hedef dugume ulasilamadi!\n";
    else {
        cout << "En kisa mesafe hedef dugume: " << mesafe[hedef] << endl;

        // Hedef düğüme giden yolu gösterir
        vector<int> yol;
        for (int i = hedef; i != -1; i = oncekiDugum[i]) {
            yol.push_back(i);
        }

        cout << "Yol: ";
        for (int i = yol.size() - 1; i >= 0; --i) {
            cout << yol[i];
            if (i != 0)
                cout << " -> ";
        }
        cout << endl;

        cout << "En kisa yol: " << mesafe[hedef] << endl;
    }
}

int main() {
    int n;
    cout << "Dugum sayisini girin: ";
    cin >> n;

    // Graf matrisini oluşturur
    vector<vector<int>> grafMatrisi = olusturGraf(n);

    int baslangic, hedef;
    // Başlangıç ve hedef düğümleri kullanıcıdan alır
    do {
        cout << "Baslangic dugumunu girin: ";
        cin >> baslangic;
        if (baslangic < 0 || baslangic >= n) {
            cout << "Gecersiz baslangic dugumu! Tekrar deneyin.\n";
        }
    } while (baslangic < 0 || baslangic >= n);

    do {
        cout << "Hedef dugumunu girin: ";
        cin >> hedef;
        if (hedef < 0 || hedef >= n) {
            cout << "Gecersiz hedef dugumu! Tekrar deneyin.\n";
        }
    } while (hedef < 0 || hedef >= n);

    // Dijkstra algoritmasını çağırır
    dijkstra(grafMatrisi, baslangic, hedef);

    return 0;
}
